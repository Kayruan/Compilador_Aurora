/*
 * ============================================================================
 *  lexico.l - Analisador LÉXICO da linguagem Aurora (Flex)
 * ============================================================================
 *
 *  O analisador léxico lê o código-fonte caractere por caractere e o divide
 *  em TOKENS (as "palavras" da linguagem). Exemplo:
 *
 *      seja x: inteiro = 10;
 *
 *  vira a sequência de tokens:
 *
 *      SEJA  ID(x)  ':'  TIPO_INTEIRO  '='  LIT_INTEIRO(10)  ';'
 *
 *  Espaços em branco e comentários são descartados aqui e nunca chegam ao
 *  analisador sintático. Os códigos de cada token (SEJA, ID, ...) são
 *  definidos no arquivo sintatico.y e exportados pelo Bison no arquivo
 *  sintatico.tab.h.
 *
 *  Estrutura de um arquivo Flex:
 *      %{ código C %}  + definições
 *      %%
 *      regras:  padrão (expressão regular)   { ação em C }
 *      %%
 *      funções auxiliares em C
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aurora.h"
#include "sintatico.tab.h"   /* códigos dos tokens e a variável yylloc */

/*
 * YY_USER_ACTION é executado pelo Flex antes de toda ação.
 * Aqui ele registra a linha do token atual em yylloc, a "localização" que o
 * Bison usa para informar a linha correta nas mensagens de erro.
 */
#define YY_USER_ACTION  yylloc.first_line = yylloc.last_line = yylineno;

static char *processar_texto(const char *bruto);
static int   linha_inicio_comentario;
%}

/* ---------------------------------------------------------------------------
 *  Opções do Flex
 *    noyywrap          -> analisa apenas um arquivo (não precisa de yywrap)
 *    yylineno          -> o Flex conta automaticamente as linhas
 *    nounput / noinput -> não geramos funções que não são usadas
 *    never-interactive -> a entrada é sempre um arquivo, não o teclado
 * ------------------------------------------------------------------------- */
%option noyywrap yylineno nounput noinput never-interactive

/* Estado exclusivo usado enquanto estamos dentro de um comentário de bloco */
%x COMENTARIO

/* ---------------------------------------------------------------------------
 *  Definições regulares (apelidos para expressões regulares)
 * ------------------------------------------------------------------------- */
DIGITO          [0-9]
LETRA           [a-zA-Z_]
IDENTIFICADOR   {LETRA}({LETRA}|{DIGITO})*
INTEIRO         {DIGITO}+
REAL            {DIGITO}+"."{DIGITO}+
TEXTO           \"(\\.|[^"\\\n])*\"
TEXTO_ABERTO    \"(\\.|[^"\\\n])*

%%

 /* ======================= Espaços e comentários ======================= */

[ \t\r\n]+              { /* espaços, tabulações e quebras de linha: ignorados */ }

"//".*                  { /* comentário de linha: ignorado até o fim da linha */ }

"/*"                    { linha_inicio_comentario = yylineno; BEGIN(COMENTARIO); }
<COMENTARIO>"*/"        { BEGIN(INITIAL); }
<COMENTARIO>\n          { /* conta a linha (yylineno) e continua no comentário */ }
<COMENTARIO>.           { /* qualquer outro caractere dentro do comentário */ }
<COMENTARIO><<EOF>>     { erro_lexico(linha_inicio_comentario, "comentario de bloco aberto e nunca fechado"); }

 /* ======================= Palavras reservadas =======================
  * Precisam vir ANTES da regra de identificador: quando duas regras
  * reconhecem o mesmo texto com o mesmo tamanho, o Flex usa a primeira. */

 /* estrutura do programa */
"programa"              { return PROGRAMA; }
"inicio"                { return INICIO; }
"funcao"                { return FUNCAO; }
"retorne"               { return RETORNE; }

 /* declaração e tipos */
"seja"                  { return SEJA; }
"inteiro"               { return TIPO_INTEIRO; }
"real"                  { return TIPO_REAL; }
"logico"                { return TIPO_LOGICO; }
"texto"                 { return TIPO_TEXTO; }

 /* entrada e saída */
"escreva"               { return ESCREVA; }
"leia"                  { return LEIA; }

 /* decisão e repetição */
"se"                    { return SE; }
"senao"                 { return SENAO; }
"enquanto"              { return ENQUANTO; }
"para"                  { return PARA; }
"de"                    { return DE; }
"ate"                   { return ATE; }
"passo"                 { return PASSO; }

 /* lógicos */
"e"                     { return E; }
"ou"                    { return OU; }
"nao"                   { return NAO; }
"verdadeiro"            { return VERDADEIRO; }
"falso"                 { return FALSO; }

 /* ======================= Operadores de dois caracteres ======================= */

"=="                    { return IGUAL; }
"!="                    { return DIFERENTE; }
"<="                    { return MENOR_IGUAL; }
">="                    { return MAIOR_IGUAL; }

 /* ======================= Símbolos de um caractere =======================
  * O próprio caractere é usado como código do token (ex.: '+' vale 43). */

"+"|"-"|"*"|"/"|"%"|"^"     { return yytext[0]; }
"<"|">"|"="                 { return yytext[0]; }
"("|")"|"{"|"}"             { return yytext[0]; }
","|";"|":"                 { return yytext[0]; }

 /* ======================= Literais e identificadores ======================= */

{REAL}                  { yylval.real = strtod(yytext, NULL);     return LIT_REAL; }
{INTEIRO}               { yylval.inteiro = strtol(yytext, NULL, 10); return LIT_INTEIRO; }
{TEXTO}                 { yylval.texto = processar_texto(yytext);  return LIT_TEXTO; }
{TEXTO_ABERTO}          { erro_lexico(yylineno, "texto aberto com \" e nao fechado na mesma linha"); }
{IDENTIFICADOR}         { yylval.texto = strdup(yytext);           return ID; }

 /* ======================= Qualquer outra coisa é erro ======================= */

.                       { erro_lexico(yylineno, "simbolo invalido '%s'", yytext); }

%%

/*
 * Converte o texto como escrito no código ("ola\n") para o texto real:
 * remove as aspas e troca as sequências de escape pelos caracteres.
 *     \n -> quebra de linha     \t -> tabulação
 *     \" -> aspas               \\ -> barra invertida
 */
static char *processar_texto(const char *bruto)
{
    size_t tamanho = strlen(bruto);
    char  *resultado = alocar(tamanho);   /* o resultado nunca é maior que a entrada */
    size_t j = 0;

    /* começa em 1 e para antes do último caractere para pular as aspas */
    for (size_t i = 1; i < tamanho - 1; i++) {
        if (bruto[i] == '\\') {
            i++;
            switch (bruto[i]) {
            case 'n':  resultado[j++] = '\n'; break;
            case 't':  resultado[j++] = '\t'; break;
            case '"':  resultado[j++] = '"';  break;
            case '\\': resultado[j++] = '\\'; break;
            default:
                erro_lexico(yylineno, "sequencia de escape invalida '\\%c'", bruto[i]);
            }
        } else {
            resultado[j++] = bruto[i];
        }
    }
    resultado[j] = '\0';
    return resultado;
}
