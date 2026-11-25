/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1





# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "sintatico.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROGRAMA = 3,                   /* "programa"  */
  YYSYMBOL_INICIO = 4,                     /* "inicio"  */
  YYSYMBOL_FUNCAO = 5,                     /* "funcao"  */
  YYSYMBOL_RETORNE = 6,                    /* "retorne"  */
  YYSYMBOL_SEJA = 7,                       /* "seja"  */
  YYSYMBOL_TIPO_INTEIRO = 8,               /* "inteiro"  */
  YYSYMBOL_TIPO_REAL = 9,                  /* "real"  */
  YYSYMBOL_TIPO_LOGICO = 10,               /* "logico"  */
  YYSYMBOL_TIPO_TEXTO = 11,                /* "texto"  */
  YYSYMBOL_ESCREVA = 12,                   /* "escreva"  */
  YYSYMBOL_LEIA = 13,                      /* "leia"  */
  YYSYMBOL_SE = 14,                        /* "se"  */
  YYSYMBOL_SENAO = 15,                     /* "senao"  */
  YYSYMBOL_ENQUANTO = 16,                  /* "enquanto"  */
  YYSYMBOL_PARA = 17,                      /* "para"  */
  YYSYMBOL_DE = 18,                        /* "de"  */
  YYSYMBOL_ATE = 19,                       /* "ate"  */
  YYSYMBOL_PASSO = 20,                     /* "passo"  */
  YYSYMBOL_E = 21,                         /* "e"  */
  YYSYMBOL_OU = 22,                        /* "ou"  */
  YYSYMBOL_NAO = 23,                       /* "nao"  */
  YYSYMBOL_VERDADEIRO = 24,                /* "verdadeiro"  */
  YYSYMBOL_FALSO = 25,                     /* "falso"  */
  YYSYMBOL_IGUAL = 26,                     /* "=="  */
  YYSYMBOL_DIFERENTE = 27,                 /* "!="  */
  YYSYMBOL_MENOR_IGUAL = 28,               /* "<="  */
  YYSYMBOL_MAIOR_IGUAL = 29,               /* ">="  */
  YYSYMBOL_LIT_INTEIRO = 30,               /* "numero inteiro"  */
  YYSYMBOL_LIT_REAL = 31,                  /* "numero real"  */
  YYSYMBOL_LIT_TEXTO = 32,                 /* "texto entre aspas"  */
  YYSYMBOL_ID = 33,                        /* "identificador"  */
  YYSYMBOL_34_ = 34,                       /* '<'  */
  YYSYMBOL_35_ = 35,                       /* '>'  */
  YYSYMBOL_36_ = 36,                       /* '+'  */
  YYSYMBOL_37_ = 37,                       /* '-'  */
  YYSYMBOL_38_ = 38,                       /* '*'  */
  YYSYMBOL_39_ = 39,                       /* '/'  */
  YYSYMBOL_40_ = 40,                       /* '%'  */
  YYSYMBOL_MENOS_UNARIO = 41,              /* MENOS_UNARIO  */
  YYSYMBOL_42_ = 42,                       /* '^'  */
  YYSYMBOL_43_ = 43,                       /* '{'  */
  YYSYMBOL_44_ = 44,                       /* '}'  */
  YYSYMBOL_45_ = 45,                       /* '('  */
  YYSYMBOL_46_ = 46,                       /* ')'  */
  YYSYMBOL_47_ = 47,                       /* ','  */
  YYSYMBOL_48_ = 48,                       /* ':'  */
  YYSYMBOL_49_ = 49,                       /* ';'  */
  YYSYMBOL_50_ = 50,                       /* '='  */
  YYSYMBOL_YYACCEPT = 51,                  /* $accept  */
  YYSYMBOL_programa = 52,                  /* programa  */
  YYSYMBOL_lista_funcoes = 53,             /* lista_funcoes  */
  YYSYMBOL_bloco_principal = 54,           /* bloco_principal  */
  YYSYMBOL_55_1 = 55,                      /* $@1  */
  YYSYMBOL_funcao = 56,                    /* funcao  */
  YYSYMBOL_57_2 = 57,                      /* $@2  */
  YYSYMBOL_parametros_opcionais = 58,      /* parametros_opcionais  */
  YYSYMBOL_lista_parametros = 59,          /* lista_parametros  */
  YYSYMBOL_parametro = 60,                 /* parametro  */
  YYSYMBOL_retorno_opcional = 61,          /* retorno_opcional  */
  YYSYMBOL_tipo = 62,                      /* tipo  */
  YYSYMBOL_bloco = 63,                     /* bloco  */
  YYSYMBOL_64_3 = 64,                      /* $@3  */
  YYSYMBOL_lista_comandos = 65,            /* lista_comandos  */
  YYSYMBOL_comando = 66,                   /* comando  */
  YYSYMBOL_declaracao = 67,                /* declaracao  */
  YYSYMBOL_atribuicao = 68,                /* atribuicao  */
  YYSYMBOL_escrita = 69,                   /* escrita  */
  YYSYMBOL_leitura = 70,                   /* leitura  */
  YYSYMBOL_chamada_comando = 71,           /* chamada_comando  */
  YYSYMBOL_retorno = 72,                   /* retorno  */
  YYSYMBOL_condicional = 73,               /* condicional  */
  YYSYMBOL_senao_opcional = 74,            /* senao_opcional  */
  YYSYMBOL_repeticao_enquanto = 75,        /* repeticao_enquanto  */
  YYSYMBOL_repeticao_para = 76,            /* repeticao_para  */
  YYSYMBOL_passo_opcional = 77,            /* passo_opcional  */
  YYSYMBOL_expressao = 78,                 /* expressao  */
  YYSYMBOL_chamada_expressao = 79,         /* chamada_expressao  */
  YYSYMBOL_argumentos_opcionais = 80,      /* argumentos_opcionais  */
  YYSYMBOL_lista_argumentos = 81           /* lista_argumentos  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;



/* Unqualified %code blocks.  */
#line 38 "src\\sintatico.y"

    #include <stdio.h>
    #include <stdlib.h>

    int  yylex(void);
    void yyerror(const char *mensagem);

    /* Nome do programa, informado em "programa <Nome> { ... }" */
    char *nome_programa = NULL;

#line 196 "gerados\\sintatico.tab.c"

#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   269

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  149

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   289


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    40,     2,     2,
      45,    46,    38,    36,    47,    37,     2,    39,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    48,    49,
      34,    50,    35,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    42,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    43,     2,    44,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    41
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   167,   167,   172,   173,   179,   178,   195,   194,   201,
     202,   206,   207,   211,   216,   217,   221,   222,   223,   224,
     233,   232,   239,   240,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   261,   263,   269,   275,   281,   287,   293,
     294,   307,   312,   313,   314,   324,   329,   334,   335,   344,
     345,   346,   347,   348,   349,   350,   351,   354,   355,   356,
     357,   358,   359,   360,   364,   365,   366,   367,   368,   369,
     372,   373,   374,   379,   384,   385,   389,   390
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  static const char *const yy_sname[] =
  {
  "end of file", "error", "invalid token", "programa", "inicio", "funcao",
  "retorne", "seja", "inteiro", "real", "logico", "texto", "escreva",
  "leia", "se", "senao", "enquanto", "para", "de", "ate", "passo", "e",
  "ou", "nao", "verdadeiro", "falso", "==", "!=", "<=", ">=",
  "numero inteiro", "numero real", "texto entre aspas", "identificador",
  "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "MENOS_UNARIO", "'^'",
  "'{'", "'}'", "'('", "')'", "','", "':'", "';'", "'='", "$accept",
  "programa", "lista_funcoes", "bloco_principal", "$@1", "funcao", "$@2",
  "parametros_opcionais", "lista_parametros", "parametro",
  "retorno_opcional", "tipo", "bloco", "$@3", "lista_comandos", "comando",
  "declaracao", "atribuicao", "escrita", "leitura", "chamada_comando",
  "retorno", "condicional", "senao_opcional", "repeticao_enquanto",
  "repeticao_para", "passo_opcional", "expressao", "chamada_expressao",
  "argumentos_opcionais", "lista_argumentos", YY_NULLPTR
  };
  return yy_sname[yysymbol];
}
#endif

#define YYPACT_NINF (-73)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       3,   -17,    20,   -16,   -73,   -73,    14,   -73,    -7,   -13,
     -73,   -10,   -73,   -73,   -73,   -73,    11,   -73,     1,    -5,
      10,    -8,   -12,   -73,   177,    42,    31,    32,    33,    38,
      49,   -40,   -73,   -73,    40,    43,    51,    53,    55,    57,
     -73,   -73,   -73,    37,    60,     1,   177,   -73,   -73,   -73,
     -73,   -73,    46,   177,   177,   190,   -73,    61,   177,    74,
     177,   177,    95,   177,   177,   -73,   -73,   -73,   -73,   -73,
     -73,   -73,   -73,   -73,   -73,   -73,    37,   -10,   -73,    15,
     177,    73,    59,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,    37,   190,   -23,
      76,    90,   112,   177,    77,    84,   190,   -73,   -73,    89,
     -73,    15,   210,   227,   227,   227,   227,   227,   227,   -25,
     -25,    73,    73,    73,    73,    70,   -73,   177,   -73,   -10,
     -10,   134,   -73,   -73,   177,   190,   122,   -73,   177,   190,
     -11,   -73,   157,   -73,   -73,   177,   -10,   190,   -73
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     3,     0,     5,     0,     0,
       4,     0,     7,     2,    20,     6,     0,    22,     9,     0,
       0,     0,    10,    11,    40,     0,     0,     0,     0,     0,
       0,     0,    21,    23,     0,     0,     0,     0,     0,     0,
      30,    31,    32,     0,    14,     0,     0,    52,    53,    49,
      50,    51,    54,     0,     0,    39,    55,     0,     0,     0,
       0,     0,     0,    74,     0,    24,    25,    26,    27,    28,
      29,    16,    17,    18,    19,    13,     0,     0,    12,    72,
      74,    63,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    76,     0,
       0,     0,     0,     0,     0,    75,    35,    15,     8,     0,
      56,    70,    71,    64,    65,    67,    69,    66,    68,    57,
      58,    59,    60,    61,    62,    33,    36,     0,    37,     0,
       0,     0,    38,    73,     0,    77,    42,    45,     0,    34,
       0,    41,    47,    43,    44,     0,     0,    48,    46
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,    97,
     -73,   -72,   -56,   -73,   -73,   -73,   -73,   -73,   -73,   -73,
     -73,   -73,     4,   -73,   -73,   -73,   -73,   -24,   -73,    63,
      87
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     6,     9,    11,    10,    16,    21,    22,    23,
      77,    75,    15,    17,    19,    33,    34,    35,    36,    37,
      38,    39,    40,   141,    41,    42,   146,    98,    56,   104,
     105
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      55,    24,    25,    28,   107,    63,     1,    26,    27,    28,
      64,    29,    30,    93,    94,    95,     3,    96,     7,     8,
       4,   108,    79,   126,   127,   125,    12,     5,    31,    81,
      82,    13,    14,    14,    20,    45,   101,   102,    44,    32,
     106,    85,    86,    87,    88,    71,    72,    73,    74,    89,
      90,    91,    92,    93,    94,    95,    18,    96,    43,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   136,   137,    57,    58,    59,    60,   131,
      83,    84,    62,    61,   143,    85,    86,    87,    88,    65,
     148,    80,    66,    89,    90,    91,    92,    93,    94,    95,
      67,    96,    68,   135,    69,   110,    70,   100,    76,    97,
     139,    83,    84,   103,   142,    96,    85,    86,    87,    88,
     134,   147,   128,   132,    89,    90,    91,    92,    93,    94,
      95,   127,    96,    83,    84,   133,   129,   140,    85,    86,
      87,    88,    78,   109,   144,    99,    89,    90,    91,    92,
      93,    94,    95,   138,    96,    83,    84,     0,   130,     0,
      85,    86,    87,    88,     0,     0,     0,     0,    89,    90,
      91,    92,    93,    94,    95,     0,    96,   145,    83,    84,
       0,     0,     0,    85,    86,    87,    88,     0,     0,     0,
       0,    89,    90,    91,    92,    93,    94,    95,     0,    96,
      46,    47,    48,     0,     0,     0,     0,    49,    50,    51,
      52,    83,    84,     0,    53,     0,    85,    86,    87,    88,
       0,     0,    54,     0,    89,    90,    91,    92,    93,    94,
      95,    83,    96,     0,     0,     0,    85,    86,    87,    88,
       0,     0,     0,     0,    89,    90,    91,    92,    93,    94,
      95,     0,    96,    -1,    -1,    -1,    -1,     0,     0,     0,
       0,    -1,    -1,    91,    92,    93,    94,    95,     0,    96
};

static const yytype_int16 yycheck[] =
{
      24,     6,     7,    14,    76,    45,     3,    12,    13,    14,
      50,    16,    17,    38,    39,    40,    33,    42,     4,     5,
       0,    77,    46,    46,    47,    97,    33,    43,    33,    53,
      54,    44,    43,    43,    33,    47,    60,    61,    46,    44,
      64,    26,    27,    28,    29,     8,     9,    10,    11,    34,
      35,    36,    37,    38,    39,    40,    45,    42,    48,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,   129,   130,    33,    45,    45,    45,   103,
      21,    22,    33,    45,   140,    26,    27,    28,    29,    49,
     146,    45,    49,    34,    35,    36,    37,    38,    39,    40,
      49,    42,    49,   127,    49,    46,    49,    33,    48,    48,
     134,    21,    22,    18,   138,    42,    26,    27,    28,    29,
      50,   145,    46,    46,    34,    35,    36,    37,    38,    39,
      40,    47,    42,    21,    22,    46,    46,    15,    26,    27,
      28,    29,    45,    80,   140,    58,    34,    35,    36,    37,
      38,    39,    40,    19,    42,    21,    22,    -1,    46,    -1,
      26,    27,    28,    29,    -1,    -1,    -1,    -1,    34,    35,
      36,    37,    38,    39,    40,    -1,    42,    20,    21,    22,
      -1,    -1,    -1,    26,    27,    28,    29,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    38,    39,    40,    -1,    42,
      23,    24,    25,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    21,    22,    -1,    37,    -1,    26,    27,    28,    29,
      -1,    -1,    45,    -1,    34,    35,    36,    37,    38,    39,
      40,    21,    42,    -1,    -1,    -1,    26,    27,    28,    29,
      -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,    39,
      40,    -1,    42,    26,    27,    28,    29,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    38,    39,    40,    -1,    42
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    52,    33,     0,    43,    53,     4,     5,    54,
      56,    55,    33,    44,    43,    63,    57,    64,    45,    65,
      33,    58,    59,    60,     6,     7,    12,    13,    14,    16,
      17,    33,    44,    66,    67,    68,    69,    70,    71,    72,
      73,    75,    76,    48,    46,    47,    23,    24,    25,    30,
      31,    32,    33,    37,    45,    78,    79,    33,    45,    45,
      45,    45,    33,    45,    50,    49,    49,    49,    49,    49,
      49,     8,     9,    10,    11,    62,    48,    61,    60,    78,
      45,    78,    78,    21,    22,    26,    27,    28,    29,    34,
      35,    36,    37,    38,    39,    40,    42,    48,    78,    81,
      33,    78,    78,    18,    80,    81,    78,    62,    63,    80,
      46,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    62,    46,    47,    46,    46,
      46,    78,    46,    46,    50,    78,    63,    63,    19,    78,
      15,    74,    78,    63,    73,    20,    77,    78,    63
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    51,    52,    53,    53,    55,    54,    57,    56,    58,
      58,    59,    59,    60,    61,    61,    62,    62,    62,    62,
      64,    63,    65,    65,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    67,    67,    68,    69,    70,    71,    72,
      72,    73,    74,    74,    74,    75,    76,    77,    77,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    79,    80,    80,    81,    81
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     6,     0,     2,     0,     3,     0,     8,     0,
       1,     1,     3,     3,     0,     2,     1,     1,     1,     1,
       0,     4,     0,     2,     2,     2,     2,     2,     2,     2,
       1,     1,     1,     4,     6,     3,     4,     4,     4,     2,
       1,     6,     0,     2,     2,     5,     8,     0,     2,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     4,     0,     1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




/* The kind of the lookahead of this context.  */
static yysymbol_kind_t
yypcontext_token (const yypcontext_t *yyctx) YY_ATTRIBUTE_UNUSED;

static yysymbol_kind_t
yypcontext_token (const yypcontext_t *yyctx)
{
  return yyctx->yytoken;
}

/* The location of the lookahead of this context.  */
static YYLTYPE *
yypcontext_location (const yypcontext_t *yyctx) YY_ATTRIBUTE_UNUSED;

static YYLTYPE *
yypcontext_location (const yypcontext_t *yyctx)
{
  return yyctx->yylloc;
}

/* User defined function to report a syntax error.  */
static int
yyreport_syntax_error (const yypcontext_t *yyctx);

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* programa: "programa" "identificador" '{' lista_funcoes bloco_principal '}'  */
#line 168 "src\\sintatico.y"
        { nome_programa = (yyvsp[-4].texto); }
#line 1456 "gerados\\sintatico.tab.c"
    break;

  case 5: /* $@1: %empty  */
#line 179 "src\\sintatico.y"
        { funcao_principal_criar((yylsp[0]).first_line); }
#line 1462 "gerados\\sintatico.tab.c"
    break;

  case 6: /* bloco_principal: "inicio" $@1 bloco  */
#line 181 "src\\sintatico.y"
        { sem_finalizar_funcao((yyvsp[0].no)); }
#line 1468 "gerados\\sintatico.tab.c"
    break;

  case 7: /* $@2: %empty  */
#line 195 "src\\sintatico.y"
        { funcao_criar((yyvsp[0].texto), (yylsp[0]).first_line); }
#line 1474 "gerados\\sintatico.tab.c"
    break;

  case 8: /* funcao: "funcao" "identificador" $@2 '(' parametros_opcionais ')' retorno_opcional bloco  */
#line 197 "src\\sintatico.y"
        { sem_finalizar_funcao((yyvsp[0].no)); }
#line 1480 "gerados\\sintatico.tab.c"
    break;

  case 13: /* parametro: "identificador" ':' tipo  */
#line 212 "src\\sintatico.y"
        { funcao_adicionar_parametro((yyvsp[-2].texto), (yyvsp[0].tipo), (yylsp[-2]).first_line); }
#line 1486 "gerados\\sintatico.tab.c"
    break;

  case 14: /* retorno_opcional: %empty  */
#line 216 "src\\sintatico.y"
                    { funcao_atual->retorno = T_VAZIO; }
#line 1492 "gerados\\sintatico.tab.c"
    break;

  case 15: /* retorno_opcional: ':' tipo  */
#line 217 "src\\sintatico.y"
                    { funcao_atual->retorno = (yyvsp[0].tipo); }
#line 1498 "gerados\\sintatico.tab.c"
    break;

  case 16: /* tipo: "inteiro"  */
#line 221 "src\\sintatico.y"
                    { (yyval.tipo) = T_INTEIRO; }
#line 1504 "gerados\\sintatico.tab.c"
    break;

  case 17: /* tipo: "real"  */
#line 222 "src\\sintatico.y"
                    { (yyval.tipo) = T_REAL; }
#line 1510 "gerados\\sintatico.tab.c"
    break;

  case 18: /* tipo: "logico"  */
#line 223 "src\\sintatico.y"
                    { (yyval.tipo) = T_LOGICO; }
#line 1516 "gerados\\sintatico.tab.c"
    break;

  case 19: /* tipo: "texto"  */
#line 224 "src\\sintatico.y"
                    { (yyval.tipo) = T_TEXTO; }
#line 1522 "gerados\\sintatico.tab.c"
    break;

  case 20: /* $@3: %empty  */
#line 233 "src\\sintatico.y"
        { escopo_abrir(); }
#line 1528 "gerados\\sintatico.tab.c"
    break;

  case 21: /* bloco: '{' $@3 lista_comandos '}'  */
#line 235 "src\\sintatico.y"
        { escopo_fechar(); (yyval.no) = (yyvsp[-1].no); }
#line 1534 "gerados\\sintatico.tab.c"
    break;

  case 22: /* lista_comandos: %empty  */
#line 239 "src\\sintatico.y"
                                { (yyval.no) = NULL; }
#line 1540 "gerados\\sintatico.tab.c"
    break;

  case 23: /* lista_comandos: lista_comandos comando  */
#line 240 "src\\sintatico.y"
                                { (yyval.no) = lista_anexar((yyvsp[-1].no), (yyvsp[0].no)); }
#line 1546 "gerados\\sintatico.tab.c"
    break;

  case 24: /* comando: declaracao ';'  */
#line 245 "src\\sintatico.y"
                                { (yyval.no) = (yyvsp[-1].no); }
#line 1552 "gerados\\sintatico.tab.c"
    break;

  case 25: /* comando: atribuicao ';'  */
#line 246 "src\\sintatico.y"
                                { (yyval.no) = (yyvsp[-1].no); }
#line 1558 "gerados\\sintatico.tab.c"
    break;

  case 26: /* comando: escrita ';'  */
#line 247 "src\\sintatico.y"
                                { (yyval.no) = (yyvsp[-1].no); }
#line 1564 "gerados\\sintatico.tab.c"
    break;

  case 27: /* comando: leitura ';'  */
#line 248 "src\\sintatico.y"
                                { (yyval.no) = (yyvsp[-1].no); }
#line 1570 "gerados\\sintatico.tab.c"
    break;

  case 28: /* comando: chamada_comando ';'  */
#line 249 "src\\sintatico.y"
                                { (yyval.no) = (yyvsp[-1].no); }
#line 1576 "gerados\\sintatico.tab.c"
    break;

  case 29: /* comando: retorno ';'  */
#line 250 "src\\sintatico.y"
                                { (yyval.no) = (yyvsp[-1].no); }
#line 1582 "gerados\\sintatico.tab.c"
    break;

  case 30: /* comando: condicional  */
#line 251 "src\\sintatico.y"
                                { (yyval.no) = (yyvsp[0].no); }
#line 1588 "gerados\\sintatico.tab.c"
    break;

  case 31: /* comando: repeticao_enquanto  */
#line 252 "src\\sintatico.y"
                                { (yyval.no) = (yyvsp[0].no); }
#line 1594 "gerados\\sintatico.tab.c"
    break;

  case 32: /* comando: repeticao_para  */
#line 253 "src\\sintatico.y"
                                { (yyval.no) = (yyvsp[0].no); }
#line 1600 "gerados\\sintatico.tab.c"
    break;

  case 33: /* declaracao: "seja" "identificador" ':' tipo  */
#line 262 "src\\sintatico.y"
        { (yyval.no) = sem_declaracao((yyvsp[-2].texto), (yyvsp[0].tipo), NULL, (yylsp[-3]).first_line); }
#line 1606 "gerados\\sintatico.tab.c"
    break;

  case 34: /* declaracao: "seja" "identificador" ':' tipo '=' expressao  */
#line 264 "src\\sintatico.y"
        { (yyval.no) = sem_declaracao((yyvsp[-4].texto), (yyvsp[-2].tipo), (yyvsp[0].no), (yylsp[-5]).first_line); }
#line 1612 "gerados\\sintatico.tab.c"
    break;

  case 35: /* atribuicao: "identificador" '=' expressao  */
#line 270 "src\\sintatico.y"
        { (yyval.no) = sem_atribuicao((yyvsp[-2].texto), (yyvsp[0].no), (yylsp[-2]).first_line); }
#line 1618 "gerados\\sintatico.tab.c"
    break;

  case 36: /* escrita: "escreva" '(' lista_argumentos ')'  */
#line 276 "src\\sintatico.y"
        { (yyval.no) = sem_escreva((yyvsp[-1].no), (yylsp[-3]).first_line); }
#line 1624 "gerados\\sintatico.tab.c"
    break;

  case 37: /* leitura: "leia" '(' "identificador" ')'  */
#line 282 "src\\sintatico.y"
        { (yyval.no) = sem_leia((yyvsp[-1].texto), (yylsp[-3]).first_line); }
#line 1630 "gerados\\sintatico.tab.c"
    break;

  case 38: /* chamada_comando: "identificador" '(' argumentos_opcionais ')'  */
#line 288 "src\\sintatico.y"
        { (yyval.no) = sem_chamada((yyvsp[-3].texto), (yyvsp[-1].no), 1, (yylsp[-3]).first_line); }
#line 1636 "gerados\\sintatico.tab.c"
    break;

  case 39: /* retorno: "retorne" expressao  */
#line 293 "src\\sintatico.y"
                            { (yyval.no) = sem_retorne((yyvsp[0].no), (yylsp[-1]).first_line); }
#line 1642 "gerados\\sintatico.tab.c"
    break;

  case 40: /* retorno: "retorne"  */
#line 294 "src\\sintatico.y"
                            { (yyval.no) = sem_retorne(NULL, (yylsp[0]).first_line); }
#line 1648 "gerados\\sintatico.tab.c"
    break;

  case 41: /* condicional: "se" '(' expressao ')' bloco senao_opcional  */
#line 308 "src\\sintatico.y"
        { (yyval.no) = sem_se((yyvsp[-3].no), (yyvsp[-1].no), (yyvsp[0].no), (yylsp[-5]).first_line); }
#line 1654 "gerados\\sintatico.tab.c"
    break;

  case 42: /* senao_opcional: %empty  */
#line 312 "src\\sintatico.y"
                            { (yyval.no) = NULL; }
#line 1660 "gerados\\sintatico.tab.c"
    break;

  case 43: /* senao_opcional: "senao" bloco  */
#line 313 "src\\sintatico.y"
                            { (yyval.no) = (yyvsp[0].no); }
#line 1666 "gerados\\sintatico.tab.c"
    break;

  case 44: /* senao_opcional: "senao" condicional  */
#line 314 "src\\sintatico.y"
                            { (yyval.no) = (yyvsp[0].no); }
#line 1672 "gerados\\sintatico.tab.c"
    break;

  case 45: /* repeticao_enquanto: "enquanto" '(' expressao ')' bloco  */
#line 325 "src\\sintatico.y"
        { (yyval.no) = sem_enquanto((yyvsp[-2].no), (yyvsp[0].no), (yylsp[-4]).first_line); }
#line 1678 "gerados\\sintatico.tab.c"
    break;

  case 46: /* repeticao_para: "para" "identificador" "de" expressao "ate" expressao passo_opcional bloco  */
#line 330 "src\\sintatico.y"
        { (yyval.no) = sem_para((yyvsp[-6].texto), (yyvsp[-4].no), (yyvsp[-2].no), (yyvsp[-1].no), (yyvsp[0].no), (yylsp[-7]).first_line); }
#line 1684 "gerados\\sintatico.tab.c"
    break;

  case 47: /* passo_opcional: %empty  */
#line 334 "src\\sintatico.y"
                            { (yyval.no) = NULL; }
#line 1690 "gerados\\sintatico.tab.c"
    break;

  case 48: /* passo_opcional: "passo" expressao  */
#line 335 "src\\sintatico.y"
                            { (yyval.no) = (yyvsp[0].no); }
#line 1696 "gerados\\sintatico.tab.c"
    break;

  case 49: /* expressao: "numero inteiro"  */
#line 344 "src\\sintatico.y"
                            { (yyval.no) = no_literal_inteiro((yyvsp[0].inteiro), (yylsp[0]).first_line); }
#line 1702 "gerados\\sintatico.tab.c"
    break;

  case 50: /* expressao: "numero real"  */
#line 345 "src\\sintatico.y"
                            { (yyval.no) = no_literal_real((yyvsp[0].real), (yylsp[0]).first_line); }
#line 1708 "gerados\\sintatico.tab.c"
    break;

  case 51: /* expressao: "texto entre aspas"  */
#line 346 "src\\sintatico.y"
                            { (yyval.no) = no_literal_texto((yyvsp[0].texto), (yylsp[0]).first_line); }
#line 1714 "gerados\\sintatico.tab.c"
    break;

  case 52: /* expressao: "verdadeiro"  */
#line 347 "src\\sintatico.y"
                            { (yyval.no) = no_literal_logico(1, (yylsp[0]).first_line); }
#line 1720 "gerados\\sintatico.tab.c"
    break;

  case 53: /* expressao: "falso"  */
#line 348 "src\\sintatico.y"
                            { (yyval.no) = no_literal_logico(0, (yylsp[0]).first_line); }
#line 1726 "gerados\\sintatico.tab.c"
    break;

  case 54: /* expressao: "identificador"  */
#line 349 "src\\sintatico.y"
                            { (yyval.no) = sem_variavel((yyvsp[0].texto), (yylsp[0]).first_line); }
#line 1732 "gerados\\sintatico.tab.c"
    break;

  case 55: /* expressao: chamada_expressao  */
#line 350 "src\\sintatico.y"
                            { (yyval.no) = (yyvsp[0].no); }
#line 1738 "gerados\\sintatico.tab.c"
    break;

  case 56: /* expressao: '(' expressao ')'  */
#line 351 "src\\sintatico.y"
                            { (yyval.no) = (yyvsp[-1].no); }
#line 1744 "gerados\\sintatico.tab.c"
    break;

  case 57: /* expressao: expressao '+' expressao  */
#line 354 "src\\sintatico.y"
                                { (yyval.no) = sem_binario(OP_SOMA,          (yyvsp[-2].no), (yyvsp[0].no), (yylsp[-1]).first_line); }
#line 1750 "gerados\\sintatico.tab.c"
    break;

  case 58: /* expressao: expressao '-' expressao  */
#line 355 "src\\sintatico.y"
                                { (yyval.no) = sem_binario(OP_SUBTRACAO,     (yyvsp[-2].no), (yyvsp[0].no), (yylsp[-1]).first_line); }
#line 1756 "gerados\\sintatico.tab.c"
    break;

  case 59: /* expressao: expressao '*' expressao  */
#line 356 "src\\sintatico.y"
                                { (yyval.no) = sem_binario(OP_MULTIPLICACAO, (yyvsp[-2].no), (yyvsp[0].no), (yylsp[-1]).first_line); }
#line 1762 "gerados\\sintatico.tab.c"
    break;

  case 60: /* expressao: expressao '/' expressao  */
#line 357 "src\\sintatico.y"
                                { (yyval.no) = sem_binario(OP_DIVISAO,       (yyvsp[-2].no), (yyvsp[0].no), (yylsp[-1]).first_line); }
#line 1768 "gerados\\sintatico.tab.c"
    break;

  case 61: /* expressao: expressao '%' expressao  */
#line 358 "src\\sintatico.y"
                                { (yyval.no) = sem_binario(OP_RESTO,         (yyvsp[-2].no), (yyvsp[0].no), (yylsp[-1]).first_line); }
#line 1774 "gerados\\sintatico.tab.c"
    break;

  case 62: /* expressao: expressao '^' expressao  */
#line 359 "src\\sintatico.y"
                                { (yyval.no) = sem_binario(OP_POTENCIA,      (yyvsp[-2].no), (yyvsp[0].no), (yylsp[-1]).first_line); }
#line 1780 "gerados\\sintatico.tab.c"
    break;

  case 63: /* expressao: '-' expressao  */
#line 361 "src\\sintatico.y"
                                { (yyval.no) = sem_unario(OP_NEGATIVO, (yyvsp[0].no), (yylsp[-1]).first_line); }
#line 1786 "gerados\\sintatico.tab.c"
    break;

  case 64: /* expressao: expressao "==" expressao  */
#line 364 "src\\sintatico.y"
                                      { (yyval.no) = sem_binario(OP_IGUAL,       (yyvsp[-2].no), (yyvsp[0].no), (yylsp[-1]).first_line); }
#line 1792 "gerados\\sintatico.tab.c"
    break;

  case 65: /* expressao: expressao "!=" expressao  */
#line 365 "src\\sintatico.y"
                                      { (yyval.no) = sem_binario(OP_DIFERENTE,   (yyvsp[-2].no), (yyvsp[0].no), (yylsp[-1]).first_line); }
#line 1798 "gerados\\sintatico.tab.c"
    break;

  case 66: /* expressao: expressao '<' expressao  */
#line 366 "src\\sintatico.y"
                                      { (yyval.no) = sem_binario(OP_MENOR,       (yyvsp[-2].no), (yyvsp[0].no), (yylsp[-1]).first_line); }
#line 1804 "gerados\\sintatico.tab.c"
    break;

  case 67: /* expressao: expressao "<=" expressao  */
#line 367 "src\\sintatico.y"
                                      { (yyval.no) = sem_binario(OP_MENOR_IGUAL, (yyvsp[-2].no), (yyvsp[0].no), (yylsp[-1]).first_line); }
#line 1810 "gerados\\sintatico.tab.c"
    break;

  case 68: /* expressao: expressao '>' expressao  */
#line 368 "src\\sintatico.y"
                                      { (yyval.no) = sem_binario(OP_MAIOR,       (yyvsp[-2].no), (yyvsp[0].no), (yylsp[-1]).first_line); }
#line 1816 "gerados\\sintatico.tab.c"
    break;

  case 69: /* expressao: expressao ">=" expressao  */
#line 369 "src\\sintatico.y"
                                      { (yyval.no) = sem_binario(OP_MAIOR_IGUAL, (yyvsp[-2].no), (yyvsp[0].no), (yylsp[-1]).first_line); }
#line 1822 "gerados\\sintatico.tab.c"
    break;

  case 70: /* expressao: expressao "e" expressao  */
#line 372 "src\\sintatico.y"
                                { (yyval.no) = sem_binario(OP_E,  (yyvsp[-2].no), (yyvsp[0].no), (yylsp[-1]).first_line); }
#line 1828 "gerados\\sintatico.tab.c"
    break;

  case 71: /* expressao: expressao "ou" expressao  */
#line 373 "src\\sintatico.y"
                                { (yyval.no) = sem_binario(OP_OU, (yyvsp[-2].no), (yyvsp[0].no), (yylsp[-1]).first_line); }
#line 1834 "gerados\\sintatico.tab.c"
    break;

  case 72: /* expressao: "nao" expressao  */
#line 374 "src\\sintatico.y"
                                { (yyval.no) = sem_unario(OP_NAO, (yyvsp[0].no), (yylsp[-1]).first_line); }
#line 1840 "gerados\\sintatico.tab.c"
    break;

  case 73: /* chamada_expressao: "identificador" '(' argumentos_opcionais ')'  */
#line 380 "src\\sintatico.y"
        { (yyval.no) = sem_chamada((yyvsp[-3].texto), (yyvsp[-1].no), 0, (yylsp[-3]).first_line); }
#line 1846 "gerados\\sintatico.tab.c"
    break;

  case 74: /* argumentos_opcionais: %empty  */
#line 384 "src\\sintatico.y"
                            { (yyval.no) = NULL; }
#line 1852 "gerados\\sintatico.tab.c"
    break;

  case 75: /* argumentos_opcionais: lista_argumentos  */
#line 385 "src\\sintatico.y"
                            { (yyval.no) = (yyvsp[0].no); }
#line 1858 "gerados\\sintatico.tab.c"
    break;

  case 76: /* lista_argumentos: expressao  */
#line 389 "src\\sintatico.y"
                                        { (yyval.no) = (yyvsp[0].no); }
#line 1864 "gerados\\sintatico.tab.c"
    break;

  case 77: /* lista_argumentos: lista_argumentos ',' expressao  */
#line 390 "src\\sintatico.y"
                                        { (yyval.no) = lista_anexar((yyvsp[-2].no), (yyvsp[0].no)); }
#line 1870 "gerados\\sintatico.tab.c"
    break;


#line 1874 "gerados\\sintatico.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        if (yyreport_syntax_error (&yyctx) == 2)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 393 "src\\sintatico.y"


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
