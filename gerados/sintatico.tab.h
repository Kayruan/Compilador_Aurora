/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_GERADOS_SINTATICO_TAB_H_INCLUDED
# define YY_YY_GERADOS_SINTATICO_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 31 "src\\sintatico.y"

    #include "aurora.h"

#line 53 "gerados\\sintatico.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    PROGRAMA = 258,                /* "programa"  */
    INICIO = 259,                  /* "inicio"  */
    FUNCAO = 260,                  /* "funcao"  */
    RETORNE = 261,                 /* "retorne"  */
    SEJA = 262,                    /* "seja"  */
    TIPO_INTEIRO = 263,            /* "inteiro"  */
    TIPO_REAL = 264,               /* "real"  */
    TIPO_LOGICO = 265,             /* "logico"  */
    TIPO_TEXTO = 266,              /* "texto"  */
    ESCREVA = 267,                 /* "escreva"  */
    LEIA = 268,                    /* "leia"  */
    SE = 269,                      /* "se"  */
    SENAO = 270,                   /* "senao"  */
    ENQUANTO = 271,                /* "enquanto"  */
    PARA = 272,                    /* "para"  */
    DE = 273,                      /* "de"  */
    ATE = 274,                     /* "ate"  */
    PASSO = 275,                   /* "passo"  */
    E = 276,                       /* "e"  */
    OU = 277,                      /* "ou"  */
    NAO = 278,                     /* "nao"  */
    VERDADEIRO = 279,              /* "verdadeiro"  */
    FALSO = 280,                   /* "falso"  */
    IGUAL = 281,                   /* "=="  */
    DIFERENTE = 282,               /* "!="  */
    MENOR_IGUAL = 283,             /* "<="  */
    MAIOR_IGUAL = 284,             /* ">="  */
    LIT_INTEIRO = 285,             /* "numero inteiro"  */
    LIT_REAL = 286,                /* "numero real"  */
    LIT_TEXTO = 287,               /* "texto entre aspas"  */
    ID = 288,                      /* "identificador"  */
    MENOS_UNARIO = 289             /* MENOS_UNARIO  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 62 "src\\sintatico.y"

    long     inteiro;   /* valor de um literal inteiro              */
    double   real;      /* valor de um literal real                 */
    char    *texto;     /* nome de identificador ou literal texto   */
    No      *no;        /* nó (ou lista de nós) da árvore sintática */
    Tipo     tipo;      /* tipo de dado (inteiro, real, ...)        */

#line 112 "gerados\\sintatico.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);


#endif /* !YY_YY_GERADOS_SINTATICO_TAB_H_INCLUDED  */
