/*
 * ============================================================================
 *  sintatico.y - Analisador SINTÁTICO da linguagem Aurora (Bison)
 * ============================================================================
 *
 *  Este arquivo contém a GRAMÁTICA da linguagem. O Bison transforma essas
 *  regras em um analisador LALR(1) (arquivo sintatico.tab.c) que recebe os
 *  tokens do analisador léxico e verifica se eles formam um programa válido.
 *
 *  Cada regra tem uma AÇÃO em C (entre chaves) que é executada quando a
 *  regra é reconhecida. As ações chamam o módulo semântico (semantico.c),
 *  que confere os tipos e monta a árvore sintática do programa.
 *
 *  Notação usada nas ações:
 *    $$       -> valor produzido pela regra (o nó da árvore)
 *    $1, $2.. -> valores dos símbolos à direita da regra, na ordem
 *    @1       -> localização (linha) do primeiro símbolo da regra
 *
 *  Estrutura de um arquivo Bison:
 *      declarações (tokens, tipos, precedência)
 *      %%
 *      regras da gramática
 *      %%
 *      funções auxiliares em C
 */

/* ---------------------------------------------------------------------------
 *  Código copiado para sintatico.tab.h (precisa estar no cabeçalho porque a
 *  %union abaixo usa os tipos No e Tipo, e o léxico inclui esse cabeçalho)
 * ------------------------------------------------------------------------- */
%code requires {
    #include "aurora.h"
}

/* ---------------------------------------------------------------------------
 *  Código copiado apenas para sintatico.tab.c
 * ------------------------------------------------------------------------- */
%code {
    #include <stdio.h>
    #include <stdlib.h>

    int  yylex(void);
    void yyerror(const char *mensagem);

    /* Nome do programa, informado em "programa <Nome> { ... }" */
    char *nome_programa = NULL;
}

/* ---------------------------------------------------------------------------
 *  Configurações do Bison
 *    locations          -> cada símbolo carrega a sua linha (usada em @1)
 *    parse.error custom -> nós mesmos escrevemos a mensagem de erro sintático
 *                          (em português), na função yyreport_syntax_error
 * ------------------------------------------------------------------------- */
%locations
%define parse.error custom

/* ---------------------------------------------------------------------------
 *  Valores semânticos: cada token/não terminal pode carregar um valor.
 *  A %union lista os tipos possíveis desses valores.
 * ------------------------------------------------------------------------- */
%union {
    long     inteiro;   /* valor de um literal inteiro              */
    double   real;      /* valor de um literal real                 */
    char    *texto;     /* nome de identificador ou literal texto   */
    No      *no;        /* nó (ou lista de nós) da árvore sintática */
    Tipo     tipo;      /* tipo de dado (inteiro, real, ...)        */
}

/* ===========================================================================
 *  SÍMBOLOS TERMINAIS (tokens), produzidos pelo analisador léxico.
 *  O texto entre aspas é o nome usado nas mensagens de erro.
 * ========================================================================= */

/* estrutura do programa */
%token PROGRAMA     "programa"
%token INICIO       "inicio"
%token FUNCAO       "funcao"
%token RETORNE      "retorne"

/* declaração e tipos */
%token SEJA         "seja"
%token TIPO_INTEIRO "inteiro"
%token TIPO_REAL    "real"
%token TIPO_LOGICO  "logico"
%token TIPO_TEXTO   "texto"

/* entrada e saída */
%token ESCREVA      "escreva"
%token LEIA         "leia"

/* decisão e repetição */
%token SE           "se"
%token SENAO        "senao"
%token ENQUANTO     "enquanto"
%token PARA         "para"
%token DE           "de"
%token ATE          "ate"
%token PASSO        "passo"

/* operadores e constantes lógicas */
%token E            "e"
%token OU           "ou"
%token NAO          "nao"
%token VERDADEIRO   "verdadeiro"
%token FALSO        "falso"
%token IGUAL        "=="
%token DIFERENTE    "!="
%token MENOR_IGUAL  "<="
%token MAIOR_IGUAL  ">="

/* tokens que carregam valor */
%token <inteiro> LIT_INTEIRO "numero inteiro"
%token <real>    LIT_REAL    "numero real"
%token <texto>   LIT_TEXTO   "texto entre aspas"
%token <texto>   ID          "identificador"

/* Os símbolos de um caractere (+ - * / % ^ < > = ( ) { } , ; :) não
 * precisam ser declarados: são usados diretamente como 'x' nas regras. */

/* ===========================================================================
 *  SÍMBOLOS NÃO TERMINAIS e o tipo do valor que cada um produz
 * ========================================================================= */
%type <no>   bloco lista_comandos comando
%type <no>   declaracao atribuicao escrita leitura chamada_comando retorno
%type <no>   condicional senao_opcional repeticao_enquanto repeticao_para passo_opcional
%type <no>   expressao chamada_expressao argumentos_opcionais lista_argumentos
%type <tipo> tipo

/* ===========================================================================
 *  PRECEDÊNCIA E ASSOCIATIVIDADE (da MENOR para a MAIOR precedência)
 *
 *  Resolve a ambiguidade das expressões. Ex.: 2 + 3 * 4 é 2 + (3 * 4)
 *  porque '*' aparece numa linha mais abaixo (precedência maior).
 *    %left     -> associa à esquerda:  a - b - c  = (a - b) - c
 *    %right    -> associa à direita:   a ^ b ^ c  = a ^ (b ^ c)
 *    %nonassoc -> não pode encadear:   a < b < c  é erro
 *    %precedence -> só define a precedência (operadores unários)
 * ========================================================================= */
%left     OU
%left     E
%precedence NAO
%nonassoc IGUAL DIFERENTE '<' '>' MENOR_IGUAL MAIOR_IGUAL
%left     '+' '-'
%left     '*' '/' '%'
%precedence MENOS_UNARIO
%right    '^'

/* Símbolo inicial da gramática */
%start programa

%%

/* ===========================================================================
 *  REGRAS DA GRAMÁTICA
 * ========================================================================= */

/* ---------------------------------------------------------------------------
 *  Estrutura geral (INÍCIO e FIM do programa):
 *
 *      programa Nome {
 *          funcao ...      (zero ou mais funções)
 *          inicio { ... }  (bloco principal, obrigatório)
 *      }
 * ------------------------------------------------------------------------- */
programa
    : PROGRAMA ID '{' lista_funcoes bloco_principal '}'
        { nome_programa = $2; }
    ;

lista_funcoes
    : %empty
    | lista_funcoes funcao
    ;

/* "inicio" cria o escopo do programa principal antes de analisar o bloco */
bloco_principal
    : INICIO
        { funcao_principal_criar(@1.first_line); }
      bloco
        { sem_finalizar_funcao($3); }
    ;

/* ---------------------------------------------------------------------------
 *  Funções:
 *
 *      funcao nome(param1: tipo, param2: tipo): tipo_retorno { ... }
 *
 *  O tipo de retorno é opcional (sem ele, a função não devolve valor).
 *  A ação no meio da regra registra a função ANTES de ler parâmetros e
 *  corpo, o que permite que a função chame a si mesma (recursão).
 * ------------------------------------------------------------------------- */
funcao
    : FUNCAO ID
        { funcao_criar($2, @2.first_line); }
      '(' parametros_opcionais ')' retorno_opcional bloco
        { sem_finalizar_funcao($8); }
    ;

parametros_opcionais
    : %empty
    | lista_parametros
    ;

lista_parametros
    : parametro
    | lista_parametros ',' parametro
    ;

parametro
    : ID ':' tipo
        { funcao_adicionar_parametro($1, $3, @1.first_line); }
    ;

retorno_opcional
    : %empty        { funcao_atual->retorno = T_VAZIO; }
    | ':' tipo      { funcao_atual->retorno = $2; }
    ;

tipo
    : TIPO_INTEIRO  { $$ = T_INTEIRO; }
    | TIPO_REAL     { $$ = T_REAL; }
    | TIPO_LOGICO   { $$ = T_LOGICO; }
    | TIPO_TEXTO    { $$ = T_TEXTO; }
    ;

/* ---------------------------------------------------------------------------
 *  Bloco: { comandos }
 *  Abrir/fechar chaves abre/fecha um escopo de variáveis.
 * ------------------------------------------------------------------------- */
bloco
    : '{'
        { escopo_abrir(); }
      lista_comandos '}'
        { escopo_fechar(); $$ = $3; }
    ;

lista_comandos
    : %empty                    { $$ = NULL; }
    | lista_comandos comando    { $$ = lista_anexar($1, $2); }
    ;

/* Comandos simples terminam com ';'. Estruturas com bloco não precisam. */
comando
    : declaracao ';'            { $$ = $1; }
    | atribuicao ';'            { $$ = $1; }
    | escrita ';'               { $$ = $1; }
    | leitura ';'               { $$ = $1; }
    | chamada_comando ';'       { $$ = $1; }
    | retorno ';'               { $$ = $1; }
    | condicional               { $$ = $1; }
    | repeticao_enquanto        { $$ = $1; }
    | repeticao_para            { $$ = $1; }
    ;

/* ---------------------------------------------------------------------------
 *  Criação de variáveis:    seja nome: tipo;
 *                           seja nome: tipo = expressao;
 * ------------------------------------------------------------------------- */
declaracao
    : SEJA ID ':' tipo
        { $$ = sem_declaracao($2, $4, NULL, @1.first_line); }
    | SEJA ID ':' tipo '=' expressao
        { $$ = sem_declaracao($2, $4, $6, @1.first_line); }
    ;

/* Atribuição:  nome = expressao; */
atribuicao
    : ID '=' expressao
        { $$ = sem_atribuicao($1, $3, @1.first_line); }
    ;

/* Saída:  escreva(valor1, valor2, ...); */
escrita
    : ESCREVA '(' lista_argumentos ')'
        { $$ = sem_escreva($3, @1.first_line); }
    ;

/* Entrada:  leia(variavel); */
leitura
    : LEIA '(' ID ')'
        { $$ = sem_leia($3, @1.first_line); }
    ;

/* Chamada de função usada como comando:  mostrar_menu(); */
chamada_comando
    : ID '(' argumentos_opcionais ')'
        { $$ = sem_chamada($1, $3, 1, @1.first_line); }
    ;

/* Retorno de função:  retorne expressao;   ou   retorne; */
retorno
    : RETORNE expressao     { $$ = sem_retorne($2, @1.first_line); }
    | RETORNE               { $$ = sem_retorne(NULL, @1.first_line); }
    ;

/* ---------------------------------------------------------------------------
 *  Decisão:
 *      se (condicao) { ... }
 *      se (condicao) { ... } senao { ... }
 *      se (condicao) { ... } senao se (condicao) { ... } senao { ... }
 *
 *  Como os blocos são obrigatórios (sempre com chaves), não existe o
 *  problema do "senao pendurado" (dangling else).
 * ------------------------------------------------------------------------- */
condicional
    : SE '(' expressao ')' bloco senao_opcional
        { $$ = sem_se($3, $5, $6, @1.first_line); }
    ;

senao_opcional
    : %empty                { $$ = NULL; }
    | SENAO bloco           { $$ = $2; }
    | SENAO condicional     { $$ = $2; }
    ;

/* ---------------------------------------------------------------------------
 *  Repetição:
 *      enquanto (condicao) { ... }
 *      para i de 1 ate 10 { ... }
 *      para i de 10 ate 0 passo -2 { ... }
 * ------------------------------------------------------------------------- */
repeticao_enquanto
    : ENQUANTO '(' expressao ')' bloco
        { $$ = sem_enquanto($3, $5, @1.first_line); }
    ;

repeticao_para
    : PARA ID DE expressao ATE expressao passo_opcional bloco
        { $$ = sem_para($2, $4, $6, $7, $8, @1.first_line); }
    ;

passo_opcional
    : %empty                { $$ = NULL; }
    | PASSO expressao       { $$ = $2; }
    ;

/* ---------------------------------------------------------------------------
 *  Expressões (operações matemáticas, comparações e lógicas)
 *  A precedência declarada lá em cima decide a ordem das operações.
 * ------------------------------------------------------------------------- */
expressao
    /* valores básicos */
    : LIT_INTEIRO           { $$ = no_literal_inteiro($1, @1.first_line); }
    | LIT_REAL              { $$ = no_literal_real($1, @1.first_line); }
    | LIT_TEXTO             { $$ = no_literal_texto($1, @1.first_line); }
    | VERDADEIRO            { $$ = no_literal_logico(1, @1.first_line); }
    | FALSO                 { $$ = no_literal_logico(0, @1.first_line); }
    | ID                    { $$ = sem_variavel($1, @1.first_line); }
    | chamada_expressao     { $$ = $1; }
    | '(' expressao ')'     { $$ = $2; }

    /* aritméticas */
    | expressao '+' expressao   { $$ = sem_binario(OP_SOMA,          $1, $3, @2.first_line); }
    | expressao '-' expressao   { $$ = sem_binario(OP_SUBTRACAO,     $1, $3, @2.first_line); }
    | expressao '*' expressao   { $$ = sem_binario(OP_MULTIPLICACAO, $1, $3, @2.first_line); }
    | expressao '/' expressao   { $$ = sem_binario(OP_DIVISAO,       $1, $3, @2.first_line); }
    | expressao '%' expressao   { $$ = sem_binario(OP_RESTO,         $1, $3, @2.first_line); }
    | expressao '^' expressao   { $$ = sem_binario(OP_POTENCIA,      $1, $3, @2.first_line); }
    | '-' expressao %prec MENOS_UNARIO
                                { $$ = sem_unario(OP_NEGATIVO, $2, @1.first_line); }

    /* relacionais */
    | expressao IGUAL expressao       { $$ = sem_binario(OP_IGUAL,       $1, $3, @2.first_line); }
    | expressao DIFERENTE expressao   { $$ = sem_binario(OP_DIFERENTE,   $1, $3, @2.first_line); }
    | expressao '<' expressao         { $$ = sem_binario(OP_MENOR,       $1, $3, @2.first_line); }
    | expressao MENOR_IGUAL expressao { $$ = sem_binario(OP_MENOR_IGUAL, $1, $3, @2.first_line); }
    | expressao '>' expressao         { $$ = sem_binario(OP_MAIOR,       $1, $3, @2.first_line); }
    | expressao MAIOR_IGUAL expressao { $$ = sem_binario(OP_MAIOR_IGUAL, $1, $3, @2.first_line); }

    /* lógicas */
    | expressao E expressao     { $$ = sem_binario(OP_E,  $1, $3, @2.first_line); }
    | expressao OU expressao    { $$ = sem_binario(OP_OU, $1, $3, @2.first_line); }
    | NAO expressao             { $$ = sem_unario(OP_NAO, $2, @1.first_line); }
    ;

/* Chamada de função dentro de expressão:  x = dobro(3) + 1; */
chamada_expressao
    : ID '(' argumentos_opcionais ')'
        { $$ = sem_chamada($1, $3, 0, @1.first_line); }
    ;

argumentos_opcionais
    : %empty                { $$ = NULL; }
    | lista_argumentos      { $$ = $1; }
    ;

lista_argumentos
    : expressao                         { $$ = $1; }
    | lista_argumentos ',' expressao    { $$ = lista_anexar($1, $3); }
    ;

%%

/* ===========================================================================
 *  Relato de erros sintáticos
 * ========================================================================= */

/*
 * Escreve o nome de um símbolo nas mensagens de erro. Palavras reservadas
 * e operadores aparecem entre aspas simples ('se', ';'); tokens que
 * representam uma categoria aparecem por extenso (identificador, ...).
 */
static void escrever_simbolo(yysymbol_kind_t simbolo)
{
    const char *nome = yysymbol_name(simbolo);
    int categoria = simbolo == YYSYMBOL_ID || simbolo == YYSYMBOL_LIT_INTEIRO
                 || simbolo == YYSYMBOL_LIT_REAL || simbolo == YYSYMBOL_LIT_TEXTO;

    if (categoria || nome[0] == '\'')
        fputs(nome, stderr);                 /* já vem como 'x' ou é categoria */
    else
        fprintf(stderr, "'%s'", nome);       /* palavra reservada: 'escreva'   */
}

/*
 * Chamada pelo Bison quando os tokens não se encaixam em nenhuma regra.
 * Monta uma mensagem em português com o token encontrado e os esperados:
 *
 *   Erro sintatico na linha 7: encontrado ';', mas era esperado ')' ou '+'
 */
static int yyreport_syntax_error(const yypcontext_t *contexto)
{
    enum { MAX_ESPERADOS = 6 };
    yysymbol_kind_t esperados[MAX_ESPERADOS];
    yysymbol_kind_t encontrado = yypcontext_token(contexto);
    int quantidade = yypcontext_expected_tokens(contexto, esperados, MAX_ESPERADOS);

    fprintf(stderr, "Erro sintatico na linha %d: ", yypcontext_location(contexto)->first_line);

    if (encontrado == YYSYMBOL_YYEOF) {
        fprintf(stderr, "o arquivo terminou antes do esperado");
    } else {
        fprintf(stderr, "encontrado ");
        escrever_simbolo(encontrado);
    }

    /* quantidade == 0 significa que há esperados demais para listar */
    if (quantidade > 0) {
        fprintf(stderr, ", mas era esperado ");
        for (int i = 0; i < quantidade; i++) {
            if (i > 0) fprintf(stderr, " ou ");
            escrever_simbolo(esperados[i]);
        }
    }
    fprintf(stderr, "\n");
    return 0;
}

/* Usada pelo Bison apenas para erros internos (ex.: falta de memória) */
void yyerror(const char *mensagem)
{
    fprintf(stderr, "Erro na linha %d: %s\n", yylloc.first_line, mensagem);
}
