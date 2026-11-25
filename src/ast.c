/*
 * ============================================================================
 *  ast.c - Construção e impressão da Árvore Sintática Abstrata (ver seção 3 de aurora.h)
 * ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include "aurora.h"

/* ===========================================================================
 *  Funções auxiliares sobre tipos (seção 1 de aurora.h)
 * ========================================================================= */

const char *tipo_nome(Tipo t)
{
    switch (t) {
    case T_INTEIRO: return "inteiro";
    case T_REAL:    return "real";
    case T_LOGICO:  return "logico";
    case T_TEXTO:   return "texto";
    case T_VAZIO:   return "vazio";
    }
    return "?";
}

int tipo_numerico(Tipo t)
{
    return t == T_INTEIRO || t == T_REAL;
}

/* ===========================================================================
 *  Construção de nós
 * ========================================================================= */

/* Cria um nó vazio da categoria pedida; todos os outros campos começam em 0 */
No *no_novo(TipoNo categoria, int linha)
{
    No *no = alocar(sizeof(No));
    no->categoria = categoria;
    no->linha     = linha;
    return no;
}

No *no_literal_inteiro(long valor, int linha)
{
    No *no = no_novo(N_LITERAL, linha);
    no->tipo = no->literal.tipo = T_INTEIRO;
    no->literal.inteiro = valor;
    return no;
}

No *no_literal_real(double valor, int linha)
{
    No *no = no_novo(N_LITERAL, linha);
    no->tipo = no->literal.tipo = T_REAL;
    no->literal.real = valor;
    return no;
}

No *no_literal_logico(int valor, int linha)
{
    No *no = no_novo(N_LITERAL, linha);
    no->tipo = no->literal.tipo = T_LOGICO;
    no->literal.logico = valor;
    return no;
}

No *no_literal_texto(char *valor, int linha)
{
    No *no = no_novo(N_LITERAL, linha);
    no->tipo = no->literal.tipo = T_TEXTO;
    no->literal.texto = valor;
    return no;
}

/* Percorre a lista até o último elemento e liga o novo item nele */
No *lista_anexar(No *lista, No *item)
{
    if (lista == NULL)
        return item;

    No *ultimo = lista;
    while (ultimo->prox != NULL)
        ultimo = ultimo->prox;
    ultimo->prox = item;
    return lista;
}

/* ===========================================================================
 *  Impressão
 * ========================================================================= */

const char *operador_nome(Operador op)
{
    switch (op) {
    case OP_SOMA:          return "+";
    case OP_SUBTRACAO:     return "-";
    case OP_MULTIPLICACAO: return "*";
    case OP_DIVISAO:       return "/";
    case OP_RESTO:         return "%";
    case OP_POTENCIA:      return "^";
    case OP_IGUAL:         return "==";
    case OP_DIFERENTE:     return "!=";
    case OP_MENOR:         return "<";
    case OP_MENOR_IGUAL:   return "<=";
    case OP_MAIOR:         return ">";
    case OP_MAIOR_IGUAL:   return ">=";
    case OP_E:             return "e";
    case OP_OU:            return "ou";
    case OP_NEGATIVO:      return "-";
    case OP_NAO:           return "nao";
    }
    return "?";
}

/*
 * Escreve um valor. Números reais sempre aparecem com ponto decimal
 * (3.0 em vez de 3) para que fique visível a diferença entre real e inteiro.
 */
void valor_escrever(FILE *saida, Valor v)
{
    switch (v.tipo) {
    case T_INTEIRO:
        fprintf(saida, "%ld", v.inteiro);
        break;
    case T_REAL: {
        char buffer[64];
        snprintf(buffer, sizeof buffer, "%.10g", v.real);
        /* se o número não tem ponto nem expoente, acrescenta ".0" */
        if (strpbrk(buffer, ".eEna") == NULL)
            strcat(buffer, ".0");
        fputs(buffer, saida);
        break;
    }
    case T_LOGICO:
        fputs(v.logico ? "verdadeiro" : "falso", saida);
        break;
    case T_TEXTO:
        fputs(v.texto ? v.texto : "", saida);
        break;
    case T_VAZIO:
        break;
    }
}

/* Imprime "nivel" pares de espaços (indentação) */
static void indentar(int nivel)
{
    for (int i = 0; i < nivel; i++)
        printf("  ");
}

/* Imprime um rótulo (ex.: "condicao:") e, abaixo dele, uma sub-árvore */
static void imprimir_secao(const char *rotulo, No *lista, int nivel)
{
    indentar(nivel);
    printf("%s\n", rotulo);
    ast_imprimir(lista, nivel + 1);
}

/*
 * Imprime todos os nós de uma lista, um por linha, com os filhos
 * indentados um nível abaixo do pai.
 */
void ast_imprimir(No *lista, int nivel)
{
    for (No *no = lista; no != NULL; no = no->prox) {
        indentar(nivel);

        switch (no->categoria) {
        case N_LITERAL:
            printf("Literal ");
            if (no->tipo == T_TEXTO) printf("\"");
            valor_escrever(stdout, no->literal);
            if (no->tipo == T_TEXTO) printf("\"");
            printf(" : %s\n", tipo_nome(no->tipo));
            break;

        case N_VARIAVEL:
            printf("Variavel %s : %s\n", no->nome, tipo_nome(no->tipo));
            break;

        case N_BINARIO:
            printf("Operacao '%s' : %s\n", operador_nome(no->op), tipo_nome(no->tipo));
            ast_imprimir(no->a, nivel + 1);
            ast_imprimir(no->b, nivel + 1);
            break;

        case N_UNARIO:
            printf("Operacao unaria '%s' : %s\n", operador_nome(no->op), tipo_nome(no->tipo));
            ast_imprimir(no->a, nivel + 1);
            break;

        case N_CONVERSAO:
            printf("Conversao inteiro -> real\n");
            ast_imprimir(no->a, nivel + 1);
            break;

        case N_CHAMADA:
            printf("Chamada %s : %s\n", no->nome, tipo_nome(no->tipo));
            if (no->a) imprimir_secao("argumentos:", no->a, nivel + 1);
            break;

        case N_DECLARACAO:
            printf("Declaracao %s : %s\n", no->nome, tipo_nome(no->tipo));
            if (no->a) imprimir_secao("valor inicial:", no->a, nivel + 1);
            break;

        case N_ATRIBUICAO:
            printf("Atribuicao %s\n", no->nome);
            ast_imprimir(no->a, nivel + 1);
            break;

        case N_ESCREVA:
            printf("Escreva\n");
            ast_imprimir(no->a, nivel + 1);
            break;

        case N_LEIA:
            printf("Leia %s : %s\n", no->nome, tipo_nome(no->tipo));
            break;

        case N_SE:
            printf("Se\n");
            imprimir_secao("condicao:", no->a, nivel + 1);
            imprimir_secao("entao:", no->b, nivel + 1);
            if (no->c) imprimir_secao("senao:", no->c, nivel + 1);
            break;

        case N_ENQUANTO:
            printf("Enquanto\n");
            imprimir_secao("condicao:", no->a, nivel + 1);
            imprimir_secao("corpo:", no->b, nivel + 1);
            break;

        case N_PARA:
            printf("Para %s\n", no->nome);
            imprimir_secao("de:", no->a, nivel + 1);
            imprimir_secao("ate:", no->b, nivel + 1);
            if (no->c) imprimir_secao("passo:", no->c, nivel + 1);
            imprimir_secao("corpo:", no->d, nivel + 1);
            break;

        case N_RETORNE:
            printf("Retorne\n");
            ast_imprimir(no->a, nivel + 1);
            break;
        }
    }
}
