/*
 * ============================================================================
 *  semantico.c - Implementação da análise semântica (ver seção 5 de aurora.h)
 * ============================================================================
 */

#include <stdio.h>
#include "aurora.h"

/* ===========================================================================
 *  Funções auxiliares de tipos
 * ========================================================================= */

/* Envolve uma expressão inteira em um nó de conversão para real */
static No *converter_para_real(No *expressao)
{
    No *no = no_novo(N_CONVERSAO, expressao->linha);
    no->tipo = T_REAL;
    no->a    = expressao;
    return no;
}

/*
 * Garante que "expressao" pode ser usada onde se espera o tipo "destino".
 *   - mesmo tipo               -> devolve a própria expressão
 *   - inteiro onde cabe real   -> insere a conversão automática
 *   - qualquer outro caso      -> erro semântico
 * "contexto" descreve onde o valor está sendo usado, para a mensagem de erro.
 */
static No *ajustar_tipo(No *expressao, Tipo destino, const char *contexto, int linha)
{
    if (expressao->tipo == destino)
        return expressao;

    if (destino == T_REAL && expressao->tipo == T_INTEIRO)
        return converter_para_real(expressao);

    erro_semantico(linha, "%s: esperado tipo %s, mas foi encontrado %s",
                   contexto, tipo_nome(destino), tipo_nome(expressao->tipo));
    return NULL; /* nunca chega aqui: erro_semantico encerra o programa */
}

/* Tipo resultante ao combinar dois números: real se algum deles for real */
static Tipo tipo_numerico_comum(Tipo a, Tipo b)
{
    return (a == T_REAL || b == T_REAL) ? T_REAL : T_INTEIRO;
}

/* Cria um nó binário já com o tipo do resultado definido */
static No *novo_binario(Operador op, No *esquerda, No *direita, Tipo resultado, int linha)
{
    No *no = no_novo(N_BINARIO, linha);
    no->op   = op;
    no->a    = esquerda;
    no->b    = direita;
    no->tipo = resultado;
    return no;
}

/* Procura uma variável visível; se não existir, é erro */
static Simbolo *buscar_variavel(const char *nome, int *posicao, int linha)
{
    Simbolo *s = escopo_buscar(nome, posicao);
    if (s == NULL)
        erro_semantico(linha, "a variavel '%s' nao foi declarada", nome);
    return s;
}

/* ===========================================================================
 *  Expressões
 * ========================================================================= */

No *sem_variavel(char *nome, int linha)
{
    int posicao;
    Simbolo *s = buscar_variavel(nome, &posicao, linha);

    No *no = no_novo(N_VARIAVEL, linha);
    no->nome    = nome;
    no->tipo    = s->tipo;
    no->posicao = posicao;
    return no;
}

/*
 * Regras de tipos dos operadores binários:
 *
 *   + - * /      números -> inteiro se ambos inteiros, senão real
 *                (a divisão entre dois inteiros é uma divisão inteira)
 *   ^            números -> sempre real
 *   %            inteiro com inteiro -> inteiro
 *   < <= > >=    números -> logico
 *   == !=        dois números, dois logicos ou dois textos -> logico
 *   e ou         logico com logico -> logico
 */
No *sem_binario(Operador op, No *esq, No *dir, int linha)
{
    const char *simbolo = operador_nome(op);

    switch (op) {
    case OP_SOMA:
    case OP_SUBTRACAO:
    case OP_MULTIPLICACAO:
    case OP_DIVISAO:
    case OP_POTENCIA: {
        if (!tipo_numerico(esq->tipo) || !tipo_numerico(dir->tipo))
            erro_semantico(linha, "o operador '%s' so aceita numeros (recebeu %s e %s)",
                           simbolo, tipo_nome(esq->tipo), tipo_nome(dir->tipo));

        Tipo resultado = (op == OP_POTENCIA) ? T_REAL
                                             : tipo_numerico_comum(esq->tipo, dir->tipo);
        esq = ajustar_tipo(esq, resultado, "operando", linha);
        dir = ajustar_tipo(dir, resultado, "operando", linha);
        return novo_binario(op, esq, dir, resultado, linha);
    }

    case OP_RESTO:
        if (esq->tipo != T_INTEIRO || dir->tipo != T_INTEIRO)
            erro_semantico(linha, "o operador '%%' so aceita inteiros (recebeu %s e %s)",
                           tipo_nome(esq->tipo), tipo_nome(dir->tipo));
        return novo_binario(op, esq, dir, T_INTEIRO, linha);

    case OP_MENOR:
    case OP_MENOR_IGUAL:
    case OP_MAIOR:
    case OP_MAIOR_IGUAL: {
        if (!tipo_numerico(esq->tipo) || !tipo_numerico(dir->tipo))
            erro_semantico(linha, "o operador '%s' so compara numeros (recebeu %s e %s)",
                           simbolo, tipo_nome(esq->tipo), tipo_nome(dir->tipo));
        Tipo comum = tipo_numerico_comum(esq->tipo, dir->tipo);
        esq = ajustar_tipo(esq, comum, "operando", linha);
        dir = ajustar_tipo(dir, comum, "operando", linha);
        return novo_binario(op, esq, dir, T_LOGICO, linha);
    }

    case OP_IGUAL:
    case OP_DIFERENTE:
        if (tipo_numerico(esq->tipo) && tipo_numerico(dir->tipo)) {
            Tipo comum = tipo_numerico_comum(esq->tipo, dir->tipo);
            esq = ajustar_tipo(esq, comum, "operando", linha);
            dir = ajustar_tipo(dir, comum, "operando", linha);
        } else if (esq->tipo != dir->tipo) {
            erro_semantico(linha, "o operador '%s' nao compara %s com %s",
                           simbolo, tipo_nome(esq->tipo), tipo_nome(dir->tipo));
        }
        return novo_binario(op, esq, dir, T_LOGICO, linha);

    case OP_E:
    case OP_OU:
        if (esq->tipo != T_LOGICO || dir->tipo != T_LOGICO)
            erro_semantico(linha, "o operador '%s' so aceita valores logicos (recebeu %s e %s)",
                           simbolo, tipo_nome(esq->tipo), tipo_nome(dir->tipo));
        return novo_binario(op, esq, dir, T_LOGICO, linha);

    default:
        erro_semantico(linha, "operador binario invalido");
    }
    return NULL;
}

/* Menos unário exige número; "nao" exige logico. O tipo é preservado. */
No *sem_unario(Operador op, No *operando, int linha)
{
    if (op == OP_NEGATIVO && !tipo_numerico(operando->tipo))
        erro_semantico(linha, "o sinal de negativo so pode ser usado com numeros");
    if (op == OP_NAO && operando->tipo != T_LOGICO)
        erro_semantico(linha, "o operador 'nao' so aceita valores logicos");

    No *no = no_novo(N_UNARIO, linha);
    no->op   = op;
    no->a    = operando;
    no->tipo = operando->tipo;
    return no;
}

/*
 * Chamada de função: confere se a função existe, a quantidade de argumentos
 * e o tipo de cada um (com conversão automática inteiro -> real).
 * "como_comando" indica se a chamada aparece sozinha como comando
 * (ex.: imprimir_linha();) ou dentro de uma expressão (ex.: x = dobro(2);).
 */
No *sem_chamada(char *nome, No *argumentos, int como_comando, int linha)
{
    Funcao *f = funcao_buscar(nome);
    if (f == NULL)
        erro_semantico(linha, "a funcao '%s' nao foi declarada", nome);

    if (!como_comando && f->retorno == T_VAZIO)
        erro_semantico(linha, "a funcao '%s' nao devolve valor e nao pode ser usada em uma expressao", nome);

    /* percorre os argumentos, ajustando o tipo de cada um e reconstruindo a
     * lista (o ajuste pode trocar um argumento por um nó de conversão) */
    No *lista_ajustada = NULL;
    int quantidade = 0;
    No *arg = argumentos;
    while (arg != NULL) {
        No *seguinte = arg->prox;
        arg->prox = NULL;

        if (quantidade < f->num_parametros) {
            char contexto[96];
            snprintf(contexto, sizeof contexto, "argumento %d da funcao '%s'", quantidade + 1, nome);
            arg = ajustar_tipo(arg, f->tipos_parametros[quantidade], contexto, linha);
        }
        lista_ajustada = lista_anexar(lista_ajustada, arg);
        quantidade++;
        arg = seguinte;
    }

    if (quantidade != f->num_parametros)
        erro_semantico(linha, "a funcao '%s' espera %d argumento(s), mas recebeu %d",
                       nome, f->num_parametros, quantidade);

    No *no = no_novo(N_CHAMADA, linha);
    no->nome   = nome;
    no->funcao = f;
    no->a      = lista_ajustada;
    no->tipo   = f->retorno;
    return no;
}

/* ===========================================================================
 *  Comandos
 * ========================================================================= */

/*
 * Declaração: o valor inicial é verificado ANTES de a variável ser
 * registrada, portanto "seja x: inteiro = x + 1;" é um erro (x ainda não
 * existe dentro da própria inicialização).
 */
No *sem_declaracao(char *nome, Tipo tipo, No *valor_inicial, int linha)
{
    if (valor_inicial != NULL)
        valor_inicial = ajustar_tipo(valor_inicial, tipo, "valor inicial da variavel", linha);

    No *no = no_novo(N_DECLARACAO, linha);
    no->nome    = nome;
    no->tipo    = tipo;
    no->a       = valor_inicial;
    no->posicao = escopo_declarar(nome, tipo, linha);
    return no;
}

No *sem_atribuicao(char *nome, No *expressao, int linha)
{
    int posicao;
    Simbolo *s = buscar_variavel(nome, &posicao, linha);

    No *no = no_novo(N_ATRIBUICAO, linha);
    no->nome    = nome;
    no->tipo    = s->tipo;
    no->posicao = posicao;
    no->a       = ajustar_tipo(expressao, s->tipo, "atribuicao", linha);
    return no;
}

/* escreva aceita valores de qualquer tipo, exceto chamadas sem retorno */
No *sem_escreva(No *argumentos, int linha)
{
    for (No *arg = argumentos; arg != NULL; arg = arg->prox)
        if (arg->tipo == T_VAZIO)
            erro_semantico(linha, "escreva recebeu uma expressao sem valor");

    No *no = no_novo(N_ESCREVA, linha);
    no->a = argumentos;
    return no;
}

No *sem_leia(char *nome, int linha)
{
    int posicao;
    Simbolo *s = buscar_variavel(nome, &posicao, linha);

    No *no = no_novo(N_LEIA, linha);
    no->nome    = nome;
    no->tipo    = s->tipo;
    no->posicao = posicao;
    return no;
}

No *sem_se(No *condicao, No *entao, No *senao, int linha)
{
    if (condicao->tipo != T_LOGICO)
        erro_semantico(linha, "a condicao do 'se' deve ser logica, mas e %s", tipo_nome(condicao->tipo));

    No *no = no_novo(N_SE, linha);
    no->a = condicao;
    no->b = entao;
    no->c = senao;
    return no;
}

No *sem_enquanto(No *condicao, No *corpo, int linha)
{
    if (condicao->tipo != T_LOGICO)
        erro_semantico(linha, "a condicao do 'enquanto' deve ser logica, mas e %s", tipo_nome(condicao->tipo));

    No *no = no_novo(N_ENQUANTO, linha);
    no->a = condicao;
    no->b = corpo;
    return no;
}

/* para <var> de <inicio> ate <fim> [passo <passo>] { ... }
 * A variável de controle precisa ter sido declarada antes e ser numérica. */
No *sem_para(char *nome, No *inicio, No *fim, No *passo, No *corpo, int linha)
{
    int posicao;
    Simbolo *s = buscar_variavel(nome, &posicao, linha);
    if (!tipo_numerico(s->tipo))
        erro_semantico(linha, "a variavel de controle '%s' do 'para' deve ser numerica", nome);

    No *no = no_novo(N_PARA, linha);
    no->nome    = nome;
    no->tipo    = s->tipo;
    no->posicao = posicao;
    no->a = ajustar_tipo(inicio, s->tipo, "valor inicial do 'para'", linha);
    no->b = ajustar_tipo(fim,    s->tipo, "valor final do 'para'",   linha);
    no->c = passo ? ajustar_tipo(passo, s->tipo, "passo do 'para'", linha) : NULL;
    no->d = corpo;
    return no;
}

/* retorne precisa combinar com o tipo de retorno declarado na função */
No *sem_retorne(No *expressao, int linha)
{
    Funcao *f = funcao_atual;

    if (f->retorno == T_VAZIO && expressao != NULL)
        erro_semantico(linha, "'%s' nao declara tipo de retorno, entao 'retorne' nao pode devolver valor", f->nome);
    if (f->retorno != T_VAZIO && expressao == NULL)
        erro_semantico(linha, "a funcao '%s' deve retornar um valor do tipo %s", f->nome, tipo_nome(f->retorno));

    No *no = no_novo(N_RETORNE, linha);
    if (expressao != NULL)
        no->a = ajustar_tipo(expressao, f->retorno, "valor de retorno", linha);
    return no;
}

void sem_finalizar_funcao(No *corpo)
{
    funcao_atual->corpo = corpo;
}
