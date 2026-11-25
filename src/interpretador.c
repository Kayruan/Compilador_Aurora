/*
 * ============================================================================
 *  interpretador.c - Execução da árvore sintática (ver seção 6 de aurora.h)
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "aurora.h"

/* Limite de chamadas aninhadas, para evitar estouro de pilha em recursões
 * infinitas (ex.: uma função que chama a si mesma sem condição de parada) */
#define MAX_PROFUNDIDADE 2000

/*
 * Quadro de ativação: a memória de UMA chamada de função.
 *   variaveis -> um Valor para cada parâmetro/variável da função
 *   retorno   -> valor devolvido pelo comando "retorne"
 */
typedef struct {
    Valor *variaveis;
    Valor  retorno;
} Quadro;

/* Resultado da execução de um comando: segue normalmente ou um "retorne"
 * foi executado e a função precisa ser encerrada imediatamente */
typedef enum {
    CONTINUAR,
    RETORNOU
} Estado;

static int profundidade = 0;

/* Protótipos (as funções se chamam mutuamente) */
static Valor  avaliar(No *no, Quadro *quadro);
static Estado executar_lista(No *lista, Quadro *quadro);

/* ===========================================================================
 *  Funções auxiliares para criar valores
 * ========================================================================= */

static Valor valor_inteiro(long n)   { Valor v = {0}; v.tipo = T_INTEIRO; v.inteiro = n; return v; }
static Valor valor_real(double n)    { Valor v = {0}; v.tipo = T_REAL;    v.real    = n; return v; }
static Valor valor_logico(int b)     { Valor v = {0}; v.tipo = T_LOGICO;  v.logico  = b != 0; return v; }
static Valor valor_texto(char *s)    { Valor v = {0}; v.tipo = T_TEXTO;   v.texto   = s; return v; }

/* Valor inicial de uma variável declarada sem "= valor" */
static Valor valor_padrao(Tipo tipo)
{
    switch (tipo) {
    case T_INTEIRO: return valor_inteiro(0);
    case T_REAL:    return valor_real(0.0);
    case T_LOGICO:  return valor_logico(0);
    case T_TEXTO:   return valor_texto("");
    default:        { Valor v = {0}; return v; }
    }
}

/* Lê um número (inteiro ou real) como double; usado pelo comando "para" */
static double como_real(Valor v)
{
    return v.tipo == T_INTEIRO ? (double)v.inteiro : v.real;
}

/* Cria um número do tipo pedido a partir de um double */
static Valor numero_do_tipo(Tipo tipo, double n)
{
    return tipo == T_INTEIRO ? valor_inteiro((long)n) : valor_real(n);
}

/* ===========================================================================
 *  Avaliação de expressões
 * ========================================================================= */

/*
 * Operações aritméticas e comparações entre dois números.
 * A análise semântica já garantiu que os dois operandos têm o MESMO tipo
 * (inteiro com inteiro ou real com real), então basta olhar o tipo de "x".
 */
static Valor operar_numeros(Operador op, Valor x, Valor y, int linha)
{
    if (x.tipo == T_INTEIRO) {
        long a = x.inteiro, b = y.inteiro;
        switch (op) {
        case OP_SOMA:          return valor_inteiro(a + b);
        case OP_SUBTRACAO:     return valor_inteiro(a - b);
        case OP_MULTIPLICACAO: return valor_inteiro(a * b);
        case OP_DIVISAO:
            if (b == 0) erro_execucao(linha, "divisao por zero");
            return valor_inteiro(a / b);          /* divisão inteira */
        case OP_RESTO:
            if (b == 0) erro_execucao(linha, "resto de divisao por zero");
            return valor_inteiro(a % b);
        case OP_IGUAL:         return valor_logico(a == b);
        case OP_DIFERENTE:     return valor_logico(a != b);
        case OP_MENOR:         return valor_logico(a <  b);
        case OP_MENOR_IGUAL:   return valor_logico(a <= b);
        case OP_MAIOR:         return valor_logico(a >  b);
        case OP_MAIOR_IGUAL:   return valor_logico(a >= b);
        default: break;
        }
    } else {
        double a = x.real, b = y.real;
        switch (op) {
        case OP_SOMA:          return valor_real(a + b);
        case OP_SUBTRACAO:     return valor_real(a - b);
        case OP_MULTIPLICACAO: return valor_real(a * b);
        case OP_DIVISAO:
            if (b == 0.0) erro_execucao(linha, "divisao por zero");
            return valor_real(a / b);
        case OP_POTENCIA:      return valor_real(pow(a, b));
        case OP_IGUAL:         return valor_logico(a == b);
        case OP_DIFERENTE:     return valor_logico(a != b);
        case OP_MENOR:         return valor_logico(a <  b);
        case OP_MENOR_IGUAL:   return valor_logico(a <= b);
        case OP_MAIOR:         return valor_logico(a >  b);
        case OP_MAIOR_IGUAL:   return valor_logico(a >= b);
        default: break;
        }
    }
    erro_execucao(linha, "operacao numerica invalida");
    return valor_padrao(T_VAZIO);
}

static Valor avaliar_binario(No *no, Quadro *quadro)
{
    /* "e" e "ou" usam avaliação em curto-circuito: o lado direito só é
     * calculado se for necessário para decidir o resultado */
    if (no->op == OP_E)
        return valor_logico(avaliar(no->a, quadro).logico && avaliar(no->b, quadro).logico);
    if (no->op == OP_OU)
        return valor_logico(avaliar(no->a, quadro).logico || avaliar(no->b, quadro).logico);

    Valor x = avaliar(no->a, quadro);
    Valor y = avaliar(no->b, quadro);

    /* igualdade entre logicos ou entre textos */
    if (x.tipo == T_LOGICO || x.tipo == T_TEXTO) {
        int iguais = (x.tipo == T_LOGICO) ? (x.logico == y.logico)
                                          : (strcmp(x.texto, y.texto) == 0);
        return valor_logico(no->op == OP_IGUAL ? iguais : !iguais);
    }

    return operar_numeros(no->op, x, y, no->linha);
}

/*
 * Chamada de função:
 *   1. calcula os argumentos usando o quadro de quem chamou;
 *   2. cria um quadro novo e copia os argumentos para os parâmetros;
 *   3. executa o corpo da função;
 *   4. devolve o valor do "retorne".
 */
static Valor chamar_funcao(No *chamada, Quadro *quadro_chamador)
{
    Funcao *f = chamada->funcao;

    if (++profundidade > MAX_PROFUNDIDADE)
        erro_execucao(chamada->linha, "recursao muito profunda na funcao '%s'", f->nome);

    Quadro quadro;
    quadro.variaveis = alocar((f->num_simbolos + 1) * sizeof(Valor));
    quadro.retorno   = valor_padrao(T_VAZIO);
    for (int i = 0; i < f->num_simbolos; i++)
        quadro.variaveis[i] = valor_padrao(f->simbolos[i].tipo);

    int i = 0;
    for (No *arg = chamada->a; arg != NULL; arg = arg->prox)
        quadro.variaveis[i++] = avaliar(arg, quadro_chamador);

    Estado estado = executar_lista(f->corpo, &quadro);

    if (f->retorno != T_VAZIO && estado != RETORNOU)
        erro_execucao(chamada->linha, "a funcao '%s' terminou sem executar 'retorne'", f->nome);

    Valor resultado = quadro.retorno;
    free(quadro.variaveis);
    profundidade--;
    return resultado;
}

/* Calcula o valor de uma expressão */
static Valor avaliar(No *no, Quadro *quadro)
{
    switch (no->categoria) {
    case N_LITERAL:
        return no->literal;

    case N_VARIAVEL:
        return quadro->variaveis[no->posicao];

    case N_CONVERSAO:
        return valor_real((double)avaliar(no->a, quadro).inteiro);

    case N_UNARIO: {
        Valor v = avaliar(no->a, quadro);
        if (no->op == OP_NAO)
            return valor_logico(!v.logico);
        return v.tipo == T_INTEIRO ? valor_inteiro(-v.inteiro) : valor_real(-v.real);
    }

    case N_BINARIO:
        return avaliar_binario(no, quadro);

    case N_CHAMADA:
        return chamar_funcao(no, quadro);

    default:
        erro_execucao(no->linha, "expressao invalida");
    }
    return valor_padrao(T_VAZIO);
}

/* ===========================================================================
 *  Execução de comandos
 * ========================================================================= */

/* Lê um valor do teclado de acordo com o tipo da variável */
static Valor ler_valor(Tipo tipo, int linha)
{
    char buffer[1024];
    char *fim;

    if (scanf("%1023s", buffer) != 1)
        erro_execucao(linha, "nao ha dados para o comando 'leia'");

    switch (tipo) {
    case T_INTEIRO: {
        long n = strtol(buffer, &fim, 10);
        if (*fim != '\0') erro_execucao(linha, "'%s' nao e um numero inteiro", buffer);
        return valor_inteiro(n);
    }
    case T_REAL: {
        double n = strtod(buffer, &fim);
        if (*fim != '\0') erro_execucao(linha, "'%s' nao e um numero real", buffer);
        return valor_real(n);
    }
    case T_LOGICO:
        if (strcmp(buffer, "verdadeiro") == 0) return valor_logico(1);
        if (strcmp(buffer, "falso") == 0)      return valor_logico(0);
        erro_execucao(linha, "'%s' nao e um valor logico (use verdadeiro ou falso)", buffer);
        break;
    case T_TEXTO: {
        char *copia = alocar(strlen(buffer) + 1);
        strcpy(copia, buffer);
        return valor_texto(copia);
    }
    default:
        break;
    }
    return valor_padrao(T_VAZIO);
}

/* para var de inicio ate fim passo p { corpo }
 * Os limites e o passo são calculados uma única vez, antes da repetição. */
static Estado executar_para(No *no, Quadro *quadro)
{
    double atual = como_real(avaliar(no->a, quadro));
    double fim   = como_real(avaliar(no->b, quadro));
    double passo = no->c ? como_real(avaliar(no->c, quadro)) : 1.0;

    if (passo == 0.0)
        erro_execucao(no->linha, "o passo do 'para' nao pode ser zero");

    /* passo positivo conta para cima; passo negativo conta para baixo */
    while ((passo > 0 && atual <= fim) || (passo < 0 && atual >= fim)) {
        quadro->variaveis[no->posicao] = numero_do_tipo(no->tipo, atual);

        if (executar_lista(no->d, quadro) == RETORNOU)
            return RETORNOU;

        /* relê a variável: o corpo pode ter alterado o seu valor */
        atual = como_real(quadro->variaveis[no->posicao]) + passo;
    }
    return CONTINUAR;
}

/* Executa um único comando */
static Estado executar(No *no, Quadro *quadro)
{
    switch (no->categoria) {
    case N_DECLARACAO:
        quadro->variaveis[no->posicao] = no->a ? avaliar(no->a, quadro)
                                               : valor_padrao(no->tipo);
        return CONTINUAR;

    case N_ATRIBUICAO:
        quadro->variaveis[no->posicao] = avaliar(no->a, quadro);
        return CONTINUAR;

    case N_ESCREVA:
        /* os valores são separados por um espaço e terminam com quebra de linha */
        for (No *arg = no->a; arg != NULL; arg = arg->prox) {
            if (arg != no->a) putchar(' ');
            valor_escrever(stdout, avaliar(arg, quadro));
        }
        putchar('\n');
        return CONTINUAR;

    case N_LEIA:
        fflush(stdout);
        quadro->variaveis[no->posicao] = ler_valor(no->tipo, no->linha);
        return CONTINUAR;

    case N_SE:
        if (avaliar(no->a, quadro).logico)
            return executar_lista(no->b, quadro);
        return executar_lista(no->c, quadro);   /* lista vazia se não há senao */

    case N_ENQUANTO:
        while (avaliar(no->a, quadro).logico)
            if (executar_lista(no->b, quadro) == RETORNOU)
                return RETORNOU;
        return CONTINUAR;

    case N_PARA:
        return executar_para(no, quadro);

    case N_RETORNE:
        if (no->a)
            quadro->retorno = avaliar(no->a, quadro);
        return RETORNOU;

    case N_CHAMADA:
        /* chamada usada como comando: o valor devolvido (se houver) é descartado */
        chamar_funcao(no, quadro);
        return CONTINUAR;

    default:
        erro_execucao(no->linha, "comando invalido");
    }
    return CONTINUAR;
}

/* Executa uma lista de comandos em sequência, parando se houver "retorne" */
static Estado executar_lista(No *lista, Quadro *quadro)
{
    for (No *no = lista; no != NULL; no = no->prox)
        if (executar(no, quadro) == RETORNOU)
            return RETORNOU;
    return CONTINUAR;
}

/* ===========================================================================
 *  Ponto de entrada
 * ========================================================================= */

void interpretar(Funcao *principal)
{
    Quadro quadro;
    quadro.variaveis = alocar((principal->num_simbolos + 1) * sizeof(Valor));
    quadro.retorno   = valor_padrao(T_VAZIO);
    for (int i = 0; i < principal->num_simbolos; i++)
        quadro.variaveis[i] = valor_padrao(principal->simbolos[i].tipo);

    executar_lista(principal->corpo, &quadro);

    free(quadro.variaveis);
}
