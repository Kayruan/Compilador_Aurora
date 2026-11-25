/*
 * ============================================================================
 *  tabela.c - Implementação da tabela de símbolos (ver seção 4 de aurora.h)
 * ============================================================================
 */

#include <stdlib.h>
#include <string.h>
#include "aurora.h"

#define MAX_FUNCOES 128

/* Todas as funções declaradas pelo usuário, na ordem em que aparecem */
static Funcao *funcoes[MAX_FUNCOES];
static int     num_funcoes = 0;

/* O bloco "inicio" fica separado, pois não pode ser chamado como função */
static Funcao *principal = NULL;

Funcao *funcao_atual = NULL;

/* ===========================================================================
 *  Funções
 * ========================================================================= */

/* Cria a estrutura de uma função vazia */
static Funcao *funcao_nova(char *nome, int linha)
{
    Funcao *f = alocar(sizeof(Funcao));
    f->nome    = nome;
    f->linha   = linha;
    f->retorno = T_VAZIO;
    return f;
}

/*
 * Chamada pelo analisador sintático logo após ler "funcao <nome>".
 * A função é registrada ANTES de o corpo ser analisado; por isso ela pode
 * chamar a si mesma (recursão).
 */
Funcao *funcao_criar(char *nome, int linha)
{
    if (funcao_buscar(nome) != NULL)
        erro_semantico(linha, "a funcao '%s' ja foi declarada", nome);
    if (num_funcoes >= MAX_FUNCOES)
        erro_semantico(linha, "limite de %d funcoes atingido", MAX_FUNCOES);

    Funcao *f = funcao_nova(nome, linha);
    funcoes[num_funcoes++] = f;
    funcao_atual = f;
    return f;
}

Funcao *funcao_principal_criar(int linha)
{
    principal    = funcao_nova("inicio", linha);
    funcao_atual = principal;
    return principal;
}

Funcao *funcao_principal(void)
{
    return principal;
}

Funcao *funcao_buscar(const char *nome)
{
    for (int i = 0; i < num_funcoes; i++)
        if (strcmp(funcoes[i]->nome, nome) == 0)
            return funcoes[i];
    return NULL;
}

int funcao_total(void)
{
    return num_funcoes;
}

Funcao *funcao_na_posicao(int indice)
{
    return funcoes[indice];
}

/* Parâmetros são símbolos comuns (nível 0) cujo tipo também fica anotado
 * em tipos_parametros, para conferir os argumentos nas chamadas */
void funcao_adicionar_parametro(char *nome, Tipo tipo, int linha)
{
    Funcao *f = funcao_atual;
    if (f->num_parametros >= MAX_PARAMETROS)
        erro_semantico(linha, "a funcao '%s' tem mais de %d parametros", f->nome, MAX_PARAMETROS);

    escopo_declarar(nome, tipo, linha);
    f->tipos_parametros[f->num_parametros++] = tipo;
}

/* ===========================================================================
 *  Escopo de blocos
 * ========================================================================= */

void escopo_abrir(void)
{
    funcao_atual->nivel_atual++;
}

/* Desativa todas as variáveis declaradas no bloco que está sendo fechado.
 * Elas continuam no vetor (a posição delas no quadro não muda), mas não
 * podem mais ser encontradas pelo nome. */
void escopo_fechar(void)
{
    Funcao *f = funcao_atual;
    for (int i = 0; i < f->num_simbolos; i++)
        if (f->simbolos[i].ativo && f->simbolos[i].nivel == f->nivel_atual)
            f->simbolos[i].ativo = 0;
    f->nivel_atual--;
}

/*
 * Declara uma variável no bloco atual e devolve a sua posição no quadro.
 * Não é permitido declarar um nome que já esteja visível (no mesmo bloco ou
 * em um bloco externo), para evitar confusão entre variáveis homônimas.
 */
int escopo_declarar(char *nome, Tipo tipo, int linha)
{
    Funcao *f = funcao_atual;
    int posicao;
    Simbolo *existente = escopo_buscar(nome, &posicao);
    if (existente != NULL)
        erro_semantico(linha, "a variavel '%s' ja foi declarada na linha %d", nome, existente->linha);

    /* aumenta o vetor de símbolos quando necessário */
    if (f->num_simbolos == f->capacidade) {
        f->capacidade = f->capacidade ? f->capacidade * 2 : 8;
        f->simbolos = realloc(f->simbolos, f->capacidade * sizeof(Simbolo));
        if (f->simbolos == NULL)
            erro_semantico(linha, "memoria insuficiente");
    }

    Simbolo *s = &f->simbolos[f->num_simbolos];
    s->nome  = nome;
    s->tipo  = tipo;
    s->nivel = f->nivel_atual;
    s->ativo = 1;
    s->linha = linha;
    return f->num_simbolos++;
}

/* Procura um símbolo ATIVO com o nome dado, na função atual */
Simbolo *escopo_buscar(const char *nome, int *posicao)
{
    Funcao *f = funcao_atual;
    for (int i = f->num_simbolos - 1; i >= 0; i--) {
        if (f->simbolos[i].ativo && strcmp(f->simbolos[i].nome, nome) == 0) {
            *posicao = i;
            return &f->simbolos[i];
        }
    }
    return NULL;
}
