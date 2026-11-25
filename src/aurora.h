/*
 * ============================================================================
 *  aurora.h - Declarações compartilhadas por todo o compilador Aurora
 * ============================================================================
 *
 *  Um único cabeçalho com todas as estruturas e funções públicas, dividido
 *  em seções na mesma ordem em que o programa é processado:
 *
 *    1. Tipos da linguagem
 *    2. Erros e memória ................ implementados em main.c
 *    3. Árvore sintática (AST) ......... ast.c
 *    4. Tabela de símbolos ............. tabela.c
 *    5. Análise semântica .............. semantico.c
 *    6. Interpretador .................. interpretador.c
 *
 *  O analisador léxico (lexico.l) e o sintático (sintatico.y) também
 *  incluem este arquivo.
 */

#ifndef AURORA_H
#define AURORA_H

#include <stdio.h>
#include <stddef.h>

/* ============================================================================
 *  1. TIPOS DA LINGUAGEM
 * ========================================================================== */

/*
 *   T_INTEIRO -> números inteiros            (ex.: 10, -3)
 *   T_REAL    -> números com casas decimais  (ex.: 2.5)
 *   T_LOGICO  -> verdadeiro ou falso
 *   T_TEXTO   -> sequência de caracteres     (ex.: "ola")
 *   T_VAZIO   -> "tipo de retorno" de funções que não devolvem valor
 */
typedef enum {
    T_INTEIRO,
    T_REAL,
    T_LOGICO,
    T_TEXTO,
    T_VAZIO
} Tipo;

typedef struct No     No;       /* nó da árvore sintática (seção 3)   */
typedef struct Funcao Funcao;   /* função do programa     (seção 4)   */

const char *tipo_nome(Tipo t);  /* nome como no código-fonte: "inteiro" */
int tipo_numerico(Tipo t);      /* 1 se for inteiro ou real             */

/* ============================================================================
 *  2. ERROS E MEMÓRIA (main.c)
 *
 *  Cada fase tem a sua função de erro, para que a mensagem diga em que etapa
 *  o problema foi encontrado. Todas escrevem em stderr no formato
 *  "<Categoria> na linha <N>: <mensagem>" e encerram o programa (código 1).
 *  Os erros SINTÁTICOS são relatados pelo Bison (yyreport_syntax_error,
 *  em sintatico.y).
 * ========================================================================== */

void erro_lexico(int linha, const char *formato, ...);
void erro_semantico(int linha, const char *formato, ...);
void erro_execucao(int linha, const char *formato, ...);

/* calloc que encerra o programa se faltar memória (nunca devolve NULL) */
void *alocar(size_t tamanho);

/* ============================================================================
 *  3. ÁRVORE SINTÁTICA ABSTRATA - AST (ast.c)
 *
 *  Cada regra da gramática monta um pedaço desta árvore. Exemplo:
 *  a expressão  a + 2 * b  vira
 *
 *                 (+)
 *                /   \
 *              a     (*)
 *                   /   \
 *                  2     b
 *
 *  Listas (de comandos ou de argumentos) são encadeadas pelo campo "prox".
 * ========================================================================== */

typedef enum {
    /* ---- Expressões (produzem um valor) ---- */
    N_LITERAL,       /* valor constante: 10, 2.5, verdadeiro, "ola"          */
    N_VARIAVEL,      /* leitura do valor de uma variável                     */
    N_BINARIO,       /* operação com dois operandos: a + b, x > y, p e q     */
    N_UNARIO,        /* operação com um operando: -x, nao p                  */
    N_CONVERSAO,     /* conversão automática de inteiro para real            */
    N_CHAMADA,       /* chamada de função: fatorial(5)                       */

    /* ---- Comandos (executam uma ação) ---- */
    N_DECLARACAO,    /* seja x: inteiro = 10;                                */
    N_ATRIBUICAO,    /* x = x + 1;                                           */
    N_ESCREVA,       /* escreva("x =", x);                                   */
    N_LEIA,          /* leia(x);                                             */
    N_SE,            /* se (cond) { ... } senao { ... }                      */
    N_ENQUANTO,      /* enquanto (cond) { ... }                              */
    N_PARA,          /* para i de 1 ate 10 passo 2 { ... }                   */
    N_RETORNE        /* retorne expr;                                        */
} TipoNo;

/* Operadores usados nos nós N_BINARIO e N_UNARIO */
typedef enum {
    OP_SOMA, OP_SUBTRACAO, OP_MULTIPLICACAO, OP_DIVISAO, OP_RESTO, OP_POTENCIA,
    OP_IGUAL, OP_DIFERENTE, OP_MENOR, OP_MENOR_IGUAL, OP_MAIOR, OP_MAIOR_IGUAL,
    OP_E, OP_OU,
    OP_NEGATIVO,     /* menos unário: -x   */
    OP_NAO           /* negação lógica     */
} Operador;

/* Valor em tempo de execução (também guarda os literais).
 * Apenas o campo correspondente ao "tipo" é utilizado. */
typedef struct {
    Tipo   tipo;
    long   inteiro;
    double real;
    int    logico;   /* 1 = verdadeiro, 0 = falso */
    char  *texto;
} Valor;

/*
 *  Nó da árvore. Os filhos a, b, c e d mudam de significado conforme a
 *  categoria do nó:
 *
 *    N_BINARIO     a = operando esquerdo,  b = operando direito
 *    N_UNARIO      a = operando
 *    N_CONVERSAO   a = expressão inteira a ser convertida
 *    N_CHAMADA     a = lista de argumentos
 *    N_DECLARACAO  a = valor inicial (ou NULL)
 *    N_ATRIBUICAO  a = expressão atribuída
 *    N_ESCREVA     a = lista de expressões a imprimir
 *    N_SE          a = condição,  b = bloco "entao",  c = bloco "senao" (ou NULL)
 *    N_ENQUANTO    a = condição,  b = corpo
 *    N_PARA        a = início,  b = fim,  c = passo (ou NULL),  d = corpo
 *    N_RETORNE     a = expressão devolvida (ou NULL)
 */
struct No {
    TipoNo   categoria;
    Tipo     tipo;        /* tipo do valor produzido (expressões) ou da variável */
    Operador op;          /* operador (N_BINARIO / N_UNARIO)                       */
    Valor    literal;     /* valor constante (N_LITERAL)                           */
    char    *nome;        /* nome da variável ou função (para mensagens/árvore)    */
    int      posicao;     /* posição da variável no quadro de memória da função    */
    Funcao  *funcao;      /* função chamada (N_CHAMADA)                            */
    No      *a, *b, *c, *d;
    No      *prox;        /* próximo elemento da lista (comando ou argumento)      */
    int      linha;       /* linha do código-fonte, usada nas mensagens de erro    */
};

/* Construção de nós (sem verificar tipos; isso é papel da seção 5) */
No *no_novo(TipoNo categoria, int linha);
No *no_literal_inteiro(long valor, int linha);
No *no_literal_real(double valor, int linha);
No *no_literal_logico(int valor, int linha);
No *no_literal_texto(char *valor, int linha);
No *lista_anexar(No *lista, No *item);      /* acrescenta item ao final da lista */

/* Impressão */
void ast_imprimir(No *lista, int nivel);    /* usada pela opção --arvore         */
const char *operador_nome(Operador op);     /* OP_SOMA -> "+"                    */
void valor_escrever(FILE *saida, Valor v);  /* usada pela árvore e pelo escreva  */

/* ============================================================================
 *  4. TABELA DE SÍMBOLOS (tabela.c)
 *
 *  Guarda tudo o que foi declarado, para saber se um nome existe, qual o seu
 *  tipo e em que posição da memória ele fica.
 *
 *  - Cada FUNÇÃO tem a sua lista de símbolos (parâmetros e variáveis). Não há
 *    variáveis globais. O bloco "inicio" é uma função especial sem parâmetros.
 *  - ESCOPO DE BLOCO: uma variável declarada dentro de { } some no "}" que
 *    fecha aquele bloco (campos "nivel" e "ativo").
 *  - Cada símbolo recebe uma POSIÇÃO fixa. Na execução, cada chamada de função
 *    cria um vetor de valores (o "quadro") com uma casa por posição. Assim a
 *    recursão funciona: cada chamada tem o seu próprio quadro.
 * ========================================================================== */

#define MAX_PARAMETROS 16

/* Uma variável ou parâmetro */
typedef struct {
    char *nome;
    Tipo  tipo;
    int   nivel;    /* profundidade do bloco onde foi declarado (0 = parâmetros) */
    int   ativo;    /* 1 enquanto o bloco onde foi declarado não foi fechado     */
    int   linha;    /* linha da declaração                                       */
} Simbolo;

/* Uma função do programa (ou o bloco principal "inicio") */
struct Funcao {
    char *nome;
    Tipo  retorno;                          /* T_VAZIO se não devolve valor */
    int   linha;

    int   num_parametros;                   /* parâmetros ocupam as posições */
    Tipo  tipos_parametros[MAX_PARAMETROS]; /* 0 .. num_parametros-1         */

    Simbolo *simbolos;                      /* vetor dinâmico de símbolos      */
    int      num_simbolos;                  /* = tamanho do quadro de execução */
    int      capacidade;

    int   nivel_atual;                      /* usado apenas durante a análise */
    No   *corpo;                            /* lista de comandos da função    */
};

/* Função cujo corpo está sendo analisado neste momento */
extern Funcao *funcao_atual;

Funcao  *funcao_criar(char *nome, int linha);    /* declara e torna atual    */
Funcao  *funcao_principal_criar(int linha);      /* cria o bloco "inicio"    */
Funcao  *funcao_principal(void);
Funcao  *funcao_buscar(const char *nome);        /* NULL se não existir      */
int      funcao_total(void);
Funcao  *funcao_na_posicao(int indice);
void     funcao_adicionar_parametro(char *nome, Tipo tipo, int linha);

void     escopo_abrir(void);                     /* ao encontrar "{"         */
void     escopo_fechar(void);                    /* ao encontrar "}"         */
int      escopo_declarar(char *nome, Tipo tipo, int linha);  /* devolve posição */
Simbolo *escopo_buscar(const char *nome, int *posicao);      /* NULL se não achar */

/* ============================================================================
 *  5. ANÁLISE SEMÂNTICA (semantico.c)
 *
 *  O Bison garante que o programa está ESCRITO certo; estas funções garantem
 *  que ele FAZ SENTIDO: nomes declarados, tipos compatíveis, condições
 *  lógicas, argumentos corretos e retorno do tipo certo. Cada uma é chamada
 *  por uma ação da gramática e devolve o nó da árvore já verificado.
 *
 *  Sempre que um inteiro é usado onde se espera um real, um nó N_CONVERSAO
 *  é inserido na árvore.
 * ========================================================================== */

/* Expressões */
No *sem_variavel(char *nome, int linha);
No *sem_binario(Operador op, No *esquerda, No *direita, int linha);
No *sem_unario(Operador op, No *operando, int linha);
No *sem_chamada(char *nome, No *argumentos, int como_comando, int linha);

/* Comandos */
No *sem_declaracao(char *nome, Tipo tipo, No *valor_inicial, int linha);
No *sem_atribuicao(char *nome, No *expressao, int linha);
No *sem_escreva(No *argumentos, int linha);
No *sem_leia(char *nome, int linha);
No *sem_se(No *condicao, No *entao, No *senao, int linha);
No *sem_enquanto(No *condicao, No *corpo, int linha);
No *sem_para(char *nome, No *inicio, No *fim, No *passo, No *corpo, int linha);
No *sem_retorne(No *expressao, int linha);

/* Guarda o corpo da função atual depois que ele foi totalmente analisado */
void sem_finalizar_funcao(No *corpo);

/* ============================================================================
 *  6. INTERPRETADOR (interpretador.c)
 *
 *  Percorre a árvore já verificada e executa o programa: avaliar() calcula
 *  expressões e executar() realiza comandos.
 * ========================================================================== */

void interpretar(Funcao *principal);   /* executa o bloco "inicio" */

#endif /* AURORA_H */
