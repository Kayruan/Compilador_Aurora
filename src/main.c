/*
 * ============================================================================
 *  main.c - Programa principal do compilador/interpretador Aurora
 * ============================================================================
 *
 *  Uso:
 *      aurora <arquivo>             analisa e executa o programa
 *      aurora --arvore <arquivo>    também mostra a árvore sintática
 *
 *  Fluxo completo:
 *
 *    arquivo-fonte
 *         |
 *         v
 *    [ Analisador léxico ]      lexico.l      -> tokens
 *         |
 *         v
 *    [ Analisador sintático ]   sintatico.y   -> confere a gramática
 *         |                                      e monta a árvore
 *         v
 *    [ Análise semântica ]      semantico.c   -> confere tipos e nomes
 *         |                                      (feita junto com a sintática)
 *         v
 *    [ Interpretador ]          interpretador.c -> executa a árvore
 *
 *  Este arquivo também contém as funções de relato de erro usadas por
 *  todas as fases (declaradas na seção 2 de aurora.h).
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "aurora.h"

/* Definidos pelos arquivos gerados pelo Flex e pelo Bison */
extern FILE *yyin;
extern char *nome_programa;
int yyparse(void);

/* ===========================================================================
 *  Relato de erros
 * ========================================================================= */

/*
 * Função interna usada por todas as funções de erro.
 * Formato da mensagem:  "<Categoria> na linha <N>: <mensagem>"
 * Recebe uma va_list para repassar os argumentos no estilo printf.
 */
static void reportar(const char *categoria, int linha, const char *formato, va_list argumentos)
{
    fprintf(stderr, "%s na linha %d: ", categoria, linha);
    vfprintf(stderr, formato, argumentos);
    fprintf(stderr, "\n");
}

void erro_lexico(int linha, const char *formato, ...)
{
    va_list argumentos;
    va_start(argumentos, formato);
    reportar("Erro lexico", linha, formato, argumentos);
    va_end(argumentos);
    exit(EXIT_FAILURE);
}

void erro_semantico(int linha, const char *formato, ...)
{
    va_list argumentos;
    va_start(argumentos, formato);
    reportar("Erro semantico", linha, formato, argumentos);
    va_end(argumentos);
    exit(EXIT_FAILURE);
}

void erro_execucao(int linha, const char *formato, ...)
{
    va_list argumentos;
    va_start(argumentos, formato);
    reportar("Erro de execucao", linha, formato, argumentos);
    va_end(argumentos);
    exit(EXIT_FAILURE);
}

void *alocar(size_t tamanho)
{
    /* calloc já devolve a memória zerada, o que simplifica a criação de nós */
    void *memoria = calloc(1, tamanho);
    if (memoria == NULL) {
        fprintf(stderr, "Erro fatal: memoria insuficiente\n");
        exit(EXIT_FAILURE);
    }
    return memoria;
}

/* ===========================================================================
 *  Programa principal
 * ========================================================================= */

/* Mostra a árvore de todas as funções e do bloco principal */
static void mostrar_arvore(void)
{
    printf("===== Arvore sintatica do programa '%s' =====\n", nome_programa);

    for (int i = 0; i < funcao_total(); i++) {
        Funcao *f = funcao_na_posicao(i);
        printf("Funcao %s(", f->nome);
        for (int p = 0; p < f->num_parametros; p++)
            printf("%s%s: %s", p ? ", " : "", f->simbolos[p].nome, tipo_nome(f->simbolos[p].tipo));
        printf(") : %s\n", tipo_nome(f->retorno));
        ast_imprimir(f->corpo, 1);
    }

    printf("Inicio\n");
    ast_imprimir(funcao_principal()->corpo, 1);
    printf("===== Execucao =====\n");
}

int main(int argc, char **argv)
{
    int         exibir_arvore = 0;
    const char *caminho = NULL;

    /* lê os argumentos da linha de comando */
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--arvore") == 0)
            exibir_arvore = 1;
        else
            caminho = argv[i];
    }

    if (caminho == NULL) {
        fprintf(stderr, "Uso: %s [--arvore] <arquivo>\n", argv[0]);
        return 1;
    }

    yyin = fopen(caminho, "r");
    if (yyin == NULL) {
        fprintf(stderr, "Nao foi possivel abrir o arquivo '%s'\n", caminho);
        return 1;
    }

    /* Fases léxica, sintática e semântica. yyparse devolve 0 se o
     * programa foi reconhecido sem erros. (Erros léxicos e semânticos
     * encerram o programa imediatamente, dentro de yyparse.) */
    int resultado = yyparse();
    fclose(yyin);
    if (resultado != 0)
        return 1;

    if (exibir_arvore)
        mostrar_arvore();

    /* Fase de execução */
    interpretar(funcao_principal());
    return 0;
}
