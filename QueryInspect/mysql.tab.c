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




/* First part of user prologue.  */
#line 1 "grammars/mysql.y"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;

extern int yylex();
extern int yyparse();
extern int currLine, currCol;
extern FILE* yyin;

// Import error handling functions from lexer
extern void setSyntaxError(const std::string& msg, int line, int col);

void yyerror(const char *s);

#line 89 "mysql.tab.c"

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

#include "mysql.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_STRINGVAL = 4,                  /* STRINGVAL  */
  YYSYMBOL_DATATYPE = 5,                   /* DATATYPE  */
  YYSYMBOL_FUNCTION = 6,                   /* FUNCTION  */
  YYSYMBOL_INTVAL = 7,                     /* INTVAL  */
  YYSYMBOL_FLOATVAL = 8,                   /* FLOATVAL  */
  YYSYMBOL_SELECT = 9,                     /* SELECT  */
  YYSYMBOL_FROM = 10,                      /* FROM  */
  YYSYMBOL_WHERE = 11,                     /* WHERE  */
  YYSYMBOL_AS = 12,                        /* AS  */
  YYSYMBOL_AND = 13,                       /* AND  */
  YYSYMBOL_OR = 14,                        /* OR  */
  YYSYMBOL_NOT = 15,                       /* NOT  */
  YYSYMBOL_INSERT = 16,                    /* INSERT  */
  YYSYMBOL_INTO = 17,                      /* INTO  */
  YYSYMBOL_VALUES = 18,                    /* VALUES  */
  YYSYMBOL_UPDATE = 19,                    /* UPDATE  */
  YYSYMBOL_SET = 20,                       /* SET  */
  YYSYMBOL_DELETE = 21,                    /* DELETE  */
  YYSYMBOL_CREATE = 22,                    /* CREATE  */
  YYSYMBOL_DROP = 23,                      /* DROP  */
  YYSYMBOL_ALTER = 24,                     /* ALTER  */
  YYSYMBOL_TABLE = 25,                     /* TABLE  */
  YYSYMBOL_DATABASE = 26,                  /* DATABASE  */
  YYSYMBOL_SCHEMA = 27,                    /* SCHEMA  */
  YYSYMBOL_INDEX = 28,                     /* INDEX  */
  YYSYMBOL_VIEW = 29,                      /* VIEW  */
  YYSYMBOL_JOIN = 30,                      /* JOIN  */
  YYSYMBOL_INNER = 31,                     /* INNER  */
  YYSYMBOL_LEFT = 32,                      /* LEFT  */
  YYSYMBOL_RIGHT = 33,                     /* RIGHT  */
  YYSYMBOL_FULL = 34,                      /* FULL  */
  YYSYMBOL_OUTER = 35,                     /* OUTER  */
  YYSYMBOL_CROSS = 36,                     /* CROSS  */
  YYSYMBOL_ON = 37,                        /* ON  */
  YYSYMBOL_USING = 38,                     /* USING  */
  YYSYMBOL_GROUP = 39,                     /* GROUP  */
  YYSYMBOL_BY = 40,                        /* BY  */
  YYSYMBOL_HAVING = 41,                    /* HAVING  */
  YYSYMBOL_ORDER = 42,                     /* ORDER  */
  YYSYMBOL_ASC = 43,                       /* ASC  */
  YYSYMBOL_DESC = 44,                      /* DESC  */
  YYSYMBOL_DISTINCT = 45,                  /* DISTINCT  */
  YYSYMBOL_ALL = 46,                       /* ALL  */
  YYSYMBOL_UNION = 47,                     /* UNION  */
  YYSYMBOL_INTERSECT = 48,                 /* INTERSECT  */
  YYSYMBOL_EXCEPT = 49,                    /* EXCEPT  */
  YYSYMBOL_LIMIT = 50,                     /* LIMIT  */
  YYSYMBOL_OFFSET = 51,                    /* OFFSET  */
  YYSYMBOL_TOP = 52,                       /* TOP  */
  YYSYMBOL_IS = 53,                        /* IS  */
  YYSYMBOL_NULLSYM = 54,                   /* NULLSYM  */
  YYSYMBOL_LIKE = 55,                      /* LIKE  */
  YYSYMBOL_ILIKE = 56,                     /* ILIKE  */
  YYSYMBOL_IN = 57,                        /* IN  */
  YYSYMBOL_BETWEEN = 58,                   /* BETWEEN  */
  YYSYMBOL_EXISTS = 59,                    /* EXISTS  */
  YYSYMBOL_CASE = 60,                      /* CASE  */
  YYSYMBOL_WHEN = 61,                      /* WHEN  */
  YYSYMBOL_THEN = 62,                      /* THEN  */
  YYSYMBOL_ELSE = 63,                      /* ELSE  */
  YYSYMBOL_END = 64,                       /* END  */
  YYSYMBOL_PRIMARY = 65,                   /* PRIMARY  */
  YYSYMBOL_KEY = 66,                       /* KEY  */
  YYSYMBOL_FOREIGN = 67,                   /* FOREIGN  */
  YYSYMBOL_REFERENCES = 68,                /* REFERENCES  */
  YYSYMBOL_UNIQUE = 69,                    /* UNIQUE  */
  YYSYMBOL_CHECK = 70,                     /* CHECK  */
  YYSYMBOL_DEFAULT = 71,                   /* DEFAULT  */
  YYSYMBOL_AUTO_INCREMENT = 72,            /* AUTO_INCREMENT  */
  YYSYMBOL_NOT_NULL = 73,                  /* NOT_NULL  */
  YYSYMBOL_ADD = 74,                       /* ADD  */
  YYSYMBOL_MODIFY = 75,                    /* MODIFY  */
  YYSYMBOL_EQ = 76,                        /* EQ  */
  YYSYMBOL_NE = 77,                        /* NE  */
  YYSYMBOL_LT = 78,                        /* LT  */
  YYSYMBOL_LE = 79,                        /* LE  */
  YYSYMBOL_GT = 80,                        /* GT  */
  YYSYMBOL_GE = 81,                        /* GE  */
  YYSYMBOL_PLUS = 82,                      /* PLUS  */
  YYSYMBOL_MINUS = 83,                     /* MINUS  */
  YYSYMBOL_ASTERISK = 84,                  /* ASTERISK  */
  YYSYMBOL_DIVIDE = 85,                    /* DIVIDE  */
  YYSYMBOL_MODULO = 86,                    /* MODULO  */
  YYSYMBOL_CONCAT_OP = 87,                 /* CONCAT_OP  */
  YYSYMBOL_COMMA = 88,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 89,                 /* SEMICOLON  */
  YYSYMBOL_LPAREN = 90,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 91,                    /* RPAREN  */
  YYSYMBOL_DOT = 92,                       /* DOT  */
  YYSYMBOL_QUESTION = 93,                  /* QUESTION  */
  YYSYMBOL_UMINUS = 94,                    /* UMINUS  */
  YYSYMBOL_UPLUS = 95,                     /* UPLUS  */
  YYSYMBOL_YYACCEPT = 96,                  /* $accept  */
  YYSYMBOL_sql_statement_list = 97,        /* sql_statement_list  */
  YYSYMBOL_sql_statement = 98,             /* sql_statement  */
  YYSYMBOL_statement = 99,                 /* statement  */
  YYSYMBOL_select_statement = 100,         /* select_statement  */
  YYSYMBOL_select_clause = 101,            /* select_clause  */
  YYSYMBOL_opt_distinct = 102,             /* opt_distinct  */
  YYSYMBOL_select_list = 103,              /* select_list  */
  YYSYMBOL_select_item_list = 104,         /* select_item_list  */
  YYSYMBOL_select_item = 105,              /* select_item  */
  YYSYMBOL_expression = 106,               /* expression  */
  YYSYMBOL_primary_expression = 107,       /* primary_expression  */
  YYSYMBOL_function_call = 108,            /* function_call  */
  YYSYMBOL_opt_expression_list = 109,      /* opt_expression_list  */
  YYSYMBOL_expression_list = 110,          /* expression_list  */
  YYSYMBOL_case_expression = 111,          /* case_expression  */
  YYSYMBOL_when_list = 112,                /* when_list  */
  YYSYMBOL_when_list_simple = 113,         /* when_list_simple  */
  YYSYMBOL_opt_else_clause = 114,          /* opt_else_clause  */
  YYSYMBOL_opt_alias = 115,                /* opt_alias  */
  YYSYMBOL_from_clause_opt = 116,          /* from_clause_opt  */
  YYSYMBOL_from_clause = 117,              /* from_clause  */
  YYSYMBOL_table_reference_list = 118,     /* table_reference_list  */
  YYSYMBOL_table_reference = 119,          /* table_reference  */
  YYSYMBOL_table_factor = 120,             /* table_factor  */
  YYSYMBOL_join_list_opt = 121,            /* join_list_opt  */
  YYSYMBOL_join_clause = 122,              /* join_clause  */
  YYSYMBOL_join_type = 123,                /* join_type  */
  YYSYMBOL_opt_outer = 124,                /* opt_outer  */
  YYSYMBOL_join_condition_opt = 125,       /* join_condition_opt  */
  YYSYMBOL_identifier_list = 126,          /* identifier_list  */
  YYSYMBOL_where_clause_opt = 127,         /* where_clause_opt  */
  YYSYMBOL_condition = 128,                /* condition  */
  YYSYMBOL_predicate = 129,                /* predicate  */
  YYSYMBOL_comparison_operator = 130,      /* comparison_operator  */
  YYSYMBOL_group_clause_opt = 131,         /* group_clause_opt  */
  YYSYMBOL_having_clause_opt = 132,        /* having_clause_opt  */
  YYSYMBOL_order_clause_opt = 133,         /* order_clause_opt  */
  YYSYMBOL_order_item_list = 134,          /* order_item_list  */
  YYSYMBOL_order_item = 135,               /* order_item  */
  YYSYMBOL_opt_order_direction = 136,      /* opt_order_direction  */
  YYSYMBOL_limit_clause_opt = 137,         /* limit_clause_opt  */
  YYSYMBOL_insert_statement = 138,         /* insert_statement  */
  YYSYMBOL_opt_column_list = 139,          /* opt_column_list  */
  YYSYMBOL_value_list_list = 140,          /* value_list_list  */
  YYSYMBOL_update_statement = 141,         /* update_statement  */
  YYSYMBOL_assignment_list = 142,          /* assignment_list  */
  YYSYMBOL_assignment = 143,               /* assignment  */
  YYSYMBOL_delete_statement = 144,         /* delete_statement  */
  YYSYMBOL_create_statement = 145,         /* create_statement  */
  YYSYMBOL_create_table_statement = 146,   /* create_table_statement  */
  YYSYMBOL_column_definition_list = 147,   /* column_definition_list  */
  YYSYMBOL_column_definition = 148,        /* column_definition  */
  YYSYMBOL_opt_column_constraints = 149,   /* opt_column_constraints  */
  YYSYMBOL_column_constraints = 150,       /* column_constraints  */
  YYSYMBOL_column_constraint = 151,        /* column_constraint  */
  YYSYMBOL_create_database_statement = 152, /* create_database_statement  */
  YYSYMBOL_create_index_statement = 153,   /* create_index_statement  */
  YYSYMBOL_opt_unique = 154,               /* opt_unique  */
  YYSYMBOL_create_view_statement = 155,    /* create_view_statement  */
  YYSYMBOL_drop_statement = 156,           /* drop_statement  */
  YYSYMBOL_alter_statement = 157,          /* alter_statement  */
  YYSYMBOL_alter_table_action = 158        /* alter_table_action  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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
typedef yytype_int16 yy_state_t;

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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  41
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   458

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  96
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  174
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  340

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   350


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    65,    65,    66,    69,    70,    73,    74,    75,    76,
      77,    78,    79,    83,    87,    90,    91,    92,    95,    96,
      99,   100,   103,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   120,   121,   122,   123,   124,
     125,   126,   129,   130,   131,   134,   135,   138,   139,   143,
     144,   148,   149,   153,   154,   157,   158,   161,   162,   163,
     167,   168,   171,   174,   175,   178,   181,   182,   185,   186,
     189,   192,   193,   194,   195,   196,   197,   200,   201,   204,
     205,   206,   209,   210,   214,   215,   218,   219,   220,   221,
     222,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   240,   240,   240,   240,   240,   240,
     244,   245,   248,   249,   253,   254,   257,   258,   261,   264,
     265,   266,   270,   271,   272,   273,   277,   278,   279,   282,
     283,   286,   287,   291,   294,   295,   298,   302,   306,   307,
     308,   309,   312,   315,   316,   319,   322,   323,   326,   327,
     330,   331,   332,   333,   334,   335,   336,   337,   340,   341,
     344,   347,   348,   351,   355,   356,   357,   358,   359,   363,
     366,   367,   368,   369,   370
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "STRINGVAL", "DATATYPE", "FUNCTION", "INTVAL", "FLOATVAL", "SELECT",
  "FROM", "WHERE", "AS", "AND", "OR", "NOT", "INSERT", "INTO", "VALUES",
  "UPDATE", "SET", "DELETE", "CREATE", "DROP", "ALTER", "TABLE",
  "DATABASE", "SCHEMA", "INDEX", "VIEW", "JOIN", "INNER", "LEFT", "RIGHT",
  "FULL", "OUTER", "CROSS", "ON", "USING", "GROUP", "BY", "HAVING",
  "ORDER", "ASC", "DESC", "DISTINCT", "ALL", "UNION", "INTERSECT",
  "EXCEPT", "LIMIT", "OFFSET", "TOP", "IS", "NULLSYM", "LIKE", "ILIKE",
  "IN", "BETWEEN", "EXISTS", "CASE", "WHEN", "THEN", "ELSE", "END",
  "PRIMARY", "KEY", "FOREIGN", "REFERENCES", "UNIQUE", "CHECK", "DEFAULT",
  "AUTO_INCREMENT", "NOT_NULL", "ADD", "MODIFY", "EQ", "NE", "LT", "LE",
  "GT", "GE", "PLUS", "MINUS", "ASTERISK", "DIVIDE", "MODULO", "CONCAT_OP",
  "COMMA", "SEMICOLON", "LPAREN", "RPAREN", "DOT", "QUESTION", "UMINUS",
  "UPLUS", "$accept", "sql_statement_list", "sql_statement", "statement",
  "select_statement", "select_clause", "opt_distinct", "select_list",
  "select_item_list", "select_item", "expression", "primary_expression",
  "function_call", "opt_expression_list", "expression_list",
  "case_expression", "when_list", "when_list_simple", "opt_else_clause",
  "opt_alias", "from_clause_opt", "from_clause", "table_reference_list",
  "table_reference", "table_factor", "join_list_opt", "join_clause",
  "join_type", "opt_outer", "join_condition_opt", "identifier_list",
  "where_clause_opt", "condition", "predicate", "comparison_operator",
  "group_clause_opt", "having_clause_opt", "order_clause_opt",
  "order_item_list", "order_item", "opt_order_direction",
  "limit_clause_opt", "insert_statement", "opt_column_list",
  "value_list_list", "update_statement", "assignment_list", "assignment",
  "delete_statement", "create_statement", "create_table_statement",
  "column_definition_list", "column_definition", "opt_column_constraints",
  "column_constraints", "column_constraint", "create_database_statement",
  "create_index_statement", "opt_unique", "create_view_statement",
  "drop_statement", "alter_statement", "alter_table_action", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-261)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-72)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     288,    25,     9,    33,    44,   144,   182,    72,   397,  -261,
     -43,  -261,    51,  -261,  -261,  -261,  -261,  -261,  -261,  -261,
    -261,  -261,  -261,  -261,  -261,   183,   121,   112,   136,   140,
     161,   164,   180,  -261,   160,   191,   193,   200,   213,   215,
     224,  -261,  -261,  -261,     0,   218,  -261,   141,  -261,   157,
    -261,  -261,  -261,   198,   268,   268,  -261,   268,  -261,   165,
    -261,    19,  -261,  -261,  -261,    -2,   227,   218,   166,  -261,
    -261,   220,   251,  -261,  -261,  -261,  -261,  -261,    35,    21,
     246,   172,  -261,  -261,    76,   222,    11,     3,    76,   208,
     -21,  -261,  -261,   340,   268,  -261,   261,   268,   268,   268,
     268,   268,   268,  -261,   188,   267,    16,   203,    -7,  -261,
    -261,   279,   246,   247,     2,    24,   280,  -261,  -261,   195,
       0,   368,   138,   197,    76,   299,   142,  -261,   249,   257,
    -261,  -261,   268,   209,   277,   210,   211,    30,   268,   113,
      76,   268,   239,  -261,  -261,  -261,    94,    94,  -261,  -261,
    -261,    94,   268,   217,  -261,   -50,   188,  -261,   268,   227,
    -261,   301,   -41,  -261,  -261,   310,  -261,   250,   316,   263,
     318,    21,  -261,  -261,   295,   295,   295,  -261,  -261,   303,
     241,  -261,   246,   262,     5,   103,    -3,   268,   268,   244,
     268,  -261,  -261,  -261,  -261,  -261,  -261,   268,    76,    76,
     268,    76,   293,   350,  -261,  -261,   268,   268,   309,   268,
     272,    46,   277,  -261,   -36,   282,   334,  -261,   217,   277,
    -261,   170,   279,  -261,   284,  -261,   170,   298,   170,  -261,
    -261,  -261,  -261,  -261,     0,   246,   312,  -261,   300,   268,
     319,  -261,   277,   277,   242,    36,   277,  -261,   376,   211,
     142,   365,   149,  -261,   277,   277,   268,   325,  -261,   268,
    -261,   268,  -261,   360,  -261,   349,   414,  -261,   338,   268,
    -261,  -261,   170,  -261,  -261,   267,  -261,   267,  -261,   185,
     339,  -261,   242,    65,  -261,   347,   -23,   268,   268,   422,
     432,  -261,   277,   268,   277,    37,  -261,  -261,   352,    76,
     277,  -261,    38,    43,    76,   353,  -261,  -261,   354,    49,
     268,  -261,  -261,   277,   283,   356,  -261,   389,  -261,   277,
    -261,  -261,     7,  -261,  -261,   142,   267,  -261,  -261,   277,
    -261,  -261,  -261,   268,   439,  -261,    66,  -261,  -261,  -261
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    15,     0,     0,     0,   161,     0,     0,     0,     2,
       5,     6,    60,     7,     8,     9,    10,   138,   139,   140,
     141,    11,    12,    16,    17,     0,     0,     0,     0,     0,
       0,     0,     0,   162,     0,     0,     0,     0,     0,     0,
       0,     1,     3,     4,     0,    84,    61,    35,    40,     0,
      38,    39,    41,     0,     0,     0,    18,     0,    14,    19,
      20,    57,    23,    33,    34,   129,     0,    84,     0,   158,
     159,     0,     0,   164,   165,   166,   167,   168,     0,    57,
       0,    62,    63,    68,     0,   110,     0,    45,     0,     0,
      55,    30,    31,     0,     0,    59,     0,     0,     0,     0,
       0,     0,     0,    22,     0,     0,     0,     0,    84,   134,
     137,     0,     0,     0,     0,     0,     0,   169,    66,     0,
       0,    65,     0,     0,     0,     0,    85,    90,     0,   112,
      36,    37,     0,     0,    47,     0,    46,     0,     0,    55,
       0,     0,     0,    32,    21,    58,    24,    25,    26,    27,
      28,    29,     0,   128,    82,     0,     0,   127,     0,     0,
     133,     0,     0,   143,   163,     0,   171,     0,     0,     0,
       0,    57,    64,    72,    77,    77,    77,    76,    69,     0,
       0,    88,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   104,   105,   106,   107,   108,   109,     0,     0,     0,
       0,     0,   114,     0,    43,    42,     0,     0,     0,     0,
       0,     0,    56,    49,     0,     0,     0,   130,   126,   136,
     135,   146,     0,   142,     0,   174,   146,     0,   146,    67,
      78,    73,    74,    75,     0,     0,     0,    89,     0,     0,
       0,    92,    94,    95,     0,     0,    91,    87,    86,   111,
     113,     0,   122,    44,    48,    51,     0,     0,    50,     0,
     131,     0,    83,     0,   151,     0,     0,   153,     0,     0,
     154,   145,   147,   148,   144,     0,   170,     0,   172,    79,
       0,   102,     0,     0,    93,     0,     0,     0,     0,     0,
       0,    13,    53,     0,    52,     0,   150,   152,   129,     0,
     155,   149,     0,     0,     0,     0,    70,   102,     0,     0,
       0,    97,    96,   100,   119,   115,   116,   123,   125,    54,
     132,   157,     0,   160,   173,    80,     0,    99,    98,   101,
     120,   121,   118,     0,     0,   156,     0,   117,   124,    81
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -261,  -261,   440,  -261,   -67,  -261,  -261,  -261,  -261,   355,
     -25,  -261,  -261,  -261,  -144,  -261,  -261,  -261,   308,   -77,
    -261,  -261,  -261,   330,   219,  -261,  -261,  -261,    50,  -261,
    -260,   -44,   -87,  -261,  -261,  -261,  -261,  -261,  -261,   118,
    -261,  -261,  -261,   154,   302,  -261,  -261,   296,  -261,  -261,
    -261,  -261,   232,   -33,  -261,   184,  -261,  -261,  -261,  -261,
    -261,  -261,  -261
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     8,     9,    10,    11,    12,    25,    58,    59,    60,
     125,    62,    63,   135,   136,    64,    90,   139,   142,   103,
      45,    46,    81,    82,    83,   121,   178,   179,   231,   306,
     155,    85,   126,   127,   197,   129,   202,   252,   315,   316,
     332,   291,    13,   106,   153,    14,   108,   109,    15,    16,
      17,   162,   163,   271,   272,   273,    18,    19,    34,    20,
      21,    22,   117
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      61,   137,   118,    79,    84,   166,    47,    48,   214,    49,
      50,    51,   240,   119,   130,   302,   104,   303,   198,   199,
     198,   199,    95,   110,    95,     1,    26,   168,    89,    91,
      92,    96,    93,    96,   156,   181,    27,   184,   216,   157,
     140,   217,   141,   198,   199,   164,    43,   222,   132,   287,
     223,   241,   206,   211,    28,   260,   249,    52,   114,   198,
     199,    44,   134,    53,   160,   206,   336,   167,   312,    61,
      23,    24,   146,   147,   148,   149,   150,   151,   310,    47,
      48,   159,    49,    50,    51,    54,    55,   133,   105,   169,
      80,   122,   207,    57,   229,   131,   237,    40,   335,   183,
     286,    97,    98,    99,   100,   101,   102,   203,   259,   115,
     116,   247,   248,   208,   250,   236,   212,   295,    97,    98,
      99,   100,   101,   102,    65,   206,   216,   134,   320,   323,
      52,   216,    66,   219,   324,   123,    53,   206,   309,    67,
     328,    47,    48,    68,    49,    50,    51,    97,    98,    99,
     100,   101,   102,   122,   216,   198,   199,   339,    54,    55,
     238,   239,   242,   243,    69,   245,   124,    70,   280,    29,
      30,    31,   246,    32,   209,   134,   141,   285,    99,   100,
     101,   254,   255,    71,   257,   263,    47,    48,    72,    49,
      50,    51,    52,   276,    73,   278,    74,   180,    53,   289,
     290,    47,    48,    75,    49,    50,    51,    35,    36,    37,
      38,    39,   322,    33,   283,   308,    76,   325,    77,   134,
      54,    55,   304,   305,   264,   232,   233,    78,   124,    84,
     107,   292,   112,    86,   294,   265,   134,    52,   266,   267,
     268,   269,   270,    53,   300,    47,    48,    87,    49,    50,
      51,     1,    52,    94,   113,     1,   111,   134,    53,    88,
     120,   128,   313,   314,   145,    54,    55,    56,   319,   138,
     154,    47,    48,    57,    49,    50,    51,   185,   152,   158,
      54,    55,   161,   170,   165,   329,   171,   182,    57,   200,
      97,    98,    99,   100,   101,   102,    52,     1,   201,   206,
     204,   205,    53,   213,     2,   215,   221,     3,   314,     4,
       5,     6,     7,   224,   185,   186,   225,   187,   188,   189,
     190,   226,    52,   228,    54,    55,   330,   331,    53,   227,
     230,   235,    57,   234,   244,   251,   258,   262,   191,   192,
     193,   194,   195,   196,    97,    98,    99,   100,   101,   102,
      54,    55,   186,   143,   187,   188,   189,   190,    57,    97,
      98,    99,   100,   101,   102,    97,    98,    99,   100,   101,
     102,   256,   261,   284,   275,   191,   192,   193,   194,   195,
     196,    97,    98,    99,   100,   101,   102,   293,   277,   198,
     282,    97,    98,    99,   100,   101,   102,    41,   -71,   173,
     174,   175,   176,   281,   177,   288,     1,    97,    98,    99,
     100,   101,   102,     2,   296,   297,     3,   298,     4,     5,
       6,     7,    97,    98,    99,   100,   101,   102,   299,   317,
     307,   143,    97,    98,    99,   100,   101,   102,   311,   318,
     334,   253,   105,   326,   333,   327,   338,   210,    42,   144,
     172,   337,   321,   279,   274,   220,   301,     0,   218
};

static const yytype_int16 yycheck[] =
{
      25,    88,    79,     3,    11,     3,     3,     4,   152,     6,
       7,     8,    15,    80,     3,   275,    18,   277,    13,    14,
      13,    14,     3,    67,     3,     9,    17,     3,    53,    54,
      55,    12,    57,    12,    18,   122,     3,   124,    88,   106,
      61,    91,    63,    13,    14,   112,    89,    88,    45,    13,
      91,    54,    88,   140,    10,    91,   200,    54,    23,    13,
      14,    10,    87,    60,   108,    88,   326,    65,    91,    94,
      45,    46,    97,    98,    99,   100,   101,   102,    13,     3,
       4,    88,     6,     7,     8,    82,    83,    84,    90,    65,
      90,    15,    62,    90,   171,    84,    91,    25,    91,   124,
     244,    82,    83,    84,    85,    86,    87,   132,    62,    74,
      75,   198,   199,   138,   201,   182,   141,   261,    82,    83,
      84,    85,    86,    87,     3,    88,    88,   152,    91,    91,
      54,    88,    20,   158,    91,    59,    60,    88,   282,     3,
      91,     3,     4,     3,     6,     7,     8,    82,    83,    84,
      85,    86,    87,    15,    88,    13,    14,    91,    82,    83,
      57,    58,   187,   188,     3,   190,    90,     3,   235,    25,
      26,    27,   197,    29,    61,   200,    63,   244,    84,    85,
      86,   206,   207,     3,   209,    15,     3,     4,    28,     6,
       7,     8,    54,   226,     3,   228,     3,    59,    60,    50,
      51,     3,     4,     3,     6,     7,     8,    25,    26,    27,
      28,    29,   299,    69,   239,   282,     3,   304,     3,   244,
      82,    83,    37,    38,    54,   175,   176,     3,    90,    11,
       3,   256,    12,    92,   259,    65,   261,    54,    68,    69,
      70,    71,    72,    60,   269,     3,     4,    90,     6,     7,
       8,     9,    54,    88,     3,     9,    90,   282,    60,    61,
      88,    39,   287,   288,     3,    82,    83,    84,   293,    61,
       3,     3,     4,    90,     6,     7,     8,    15,    90,    76,
      82,    83,     3,     3,    37,   310,    91,    90,    90,    40,
      82,    83,    84,    85,    86,    87,    54,     9,    41,    88,
      91,    91,    60,    64,    16,    88,     5,    19,   333,    21,
      22,    23,    24,     3,    15,    53,    66,    55,    56,    57,
      58,     5,    54,     5,    82,    83,    43,    44,    60,    66,
      35,    90,    90,    30,    90,    42,    64,     3,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      82,    83,    53,    91,    55,    56,    57,    58,    90,    82,
      83,    84,    85,    86,    87,    82,    83,    84,    85,    86,
      87,    62,    90,    54,    90,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    62,    90,    13,
      90,    82,    83,    84,    85,    86,    87,     0,    30,    31,
      32,    33,    34,    91,    36,    40,     9,    82,    83,    84,
      85,    86,    87,    16,    54,    66,    19,     3,    21,    22,
      23,    24,    82,    83,    84,    85,    86,    87,    90,     7,
      91,    91,    82,    83,    84,    85,    86,    87,    91,     7,
      51,    91,    90,    90,    88,    91,     7,   139,     8,    94,
     120,   333,   298,   234,   222,   159,   272,    -1,   156
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    16,    19,    21,    22,    23,    24,    97,    98,
      99,   100,   101,   138,   141,   144,   145,   146,   152,   153,
     155,   156,   157,    45,    46,   102,    17,     3,    10,    25,
      26,    27,    29,    69,   154,    25,    26,    27,    28,    29,
      25,     0,    98,    89,    10,   116,   117,     3,     4,     6,
       7,     8,    54,    60,    82,    83,    84,    90,   103,   104,
     105,   106,   107,   108,   111,     3,    20,     3,     3,     3,
       3,     3,    28,     3,     3,     3,     3,     3,     3,     3,
      90,   118,   119,   120,    11,   127,    92,    90,    61,   106,
     112,   106,   106,   106,    88,     3,    12,    82,    83,    84,
      85,    86,    87,   115,    18,    90,   139,     3,   142,   143,
     127,    90,    12,     3,    23,    74,    75,   158,   115,   100,
      88,   121,    15,    59,    90,   106,   128,   129,    39,   131,
       3,    84,    45,    84,   106,   109,   110,   128,    61,   113,
      61,    63,   114,    91,   105,     3,   106,   106,   106,   106,
     106,   106,    90,   140,     3,   126,    18,   100,    76,    88,
     127,     3,   147,   148,   100,    37,     3,    65,     3,    65,
       3,    91,   119,    31,    32,    33,    34,    36,   122,   123,
      59,   128,    90,   106,   128,    15,    53,    55,    56,    57,
      58,    76,    77,    78,    79,    80,    81,   130,    13,    14,
      40,    41,   132,   106,    91,    91,    88,    62,   106,    61,
     114,   128,   106,    64,   110,    88,    88,    91,   140,   106,
     143,     5,    88,    91,     3,    66,     5,    66,     5,   115,
      35,   124,   124,   124,    30,    90,   100,    91,    57,    58,
      15,    54,   106,   106,    90,   106,   106,   128,   128,   110,
     128,    42,   133,    91,   106,   106,    62,   106,    64,    62,
      91,    90,     3,    15,    54,    65,    68,    69,    70,    71,
      72,   149,   150,   151,   148,    90,   149,    90,   149,   120,
     100,    91,    90,   106,    54,   100,   110,    13,    40,    50,
      51,   137,   106,    62,   106,   110,    54,    66,     3,    90,
     106,   151,   126,   126,    37,    38,   125,    91,   100,   110,
      13,    91,    91,   106,   106,   134,   135,     7,     7,   106,
      91,   139,   128,    91,    91,   128,    90,    91,    91,   106,
      43,    44,   136,    88,    51,    91,   126,   135,     7,    91
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    96,    97,    97,    98,    98,    99,    99,    99,    99,
      99,    99,    99,   100,   101,   102,   102,   102,   103,   103,
     104,   104,   105,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   107,   107,   107,   107,   107,
     107,   107,   108,   108,   108,   109,   109,   110,   110,   111,
     111,   112,   112,   113,   113,   114,   114,   115,   115,   115,
     116,   116,   117,   118,   118,   119,   120,   120,   121,   121,
     122,   123,   123,   123,   123,   123,   123,   124,   124,   125,
     125,   125,   126,   126,   127,   127,   128,   128,   128,   128,
     128,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   130,   130,   130,   130,   130,   130,
     131,   131,   132,   132,   133,   133,   134,   134,   135,   136,
     136,   136,   137,   137,   137,   137,   138,   138,   138,   139,
     139,   140,   140,   141,   142,   142,   143,   144,   145,   145,
     145,   145,   146,   147,   147,   148,   149,   149,   150,   150,
     151,   151,   151,   151,   151,   151,   151,   151,   152,   152,
     153,   154,   154,   155,   156,   156,   156,   156,   156,   157,
     158,   158,   158,   158,   158
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     7,     3,     0,     1,     1,     1,     1,
       1,     3,     2,     1,     3,     3,     3,     3,     3,     3,
       2,     2,     3,     1,     1,     1,     3,     3,     1,     1,
       1,     1,     4,     4,     5,     0,     1,     1,     3,     4,
       5,     4,     5,     4,     5,     0,     2,     0,     2,     1,
       0,     1,     2,     1,     3,     2,     2,     4,     0,     2,
       4,     0,     1,     2,     2,     2,     1,     0,     1,     0,
       2,     4,     1,     3,     0,     2,     3,     3,     2,     3,
       1,     3,     3,     4,     3,     3,     5,     5,     6,     6,
       5,     6,     4,     5,     1,     1,     1,     1,     1,     1,
       0,     3,     0,     2,     0,     3,     1,     3,     2,     0,
       1,     1,     0,     2,     4,     2,     6,     5,     5,     0,
       3,     3,     5,     5,     1,     3,     3,     4,     1,     1,
       1,     1,     6,     1,     3,     3,     0,     1,     1,     2,
       2,     1,     2,     1,     1,     2,     4,     3,     3,     3,
       9,     0,     1,     5,     3,     3,     3,     3,     3,     4,
       4,     2,     4,     6,     3
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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 4: /* sql_statement: statement SEMICOLON  */
#line 69 "grammars/mysql.y"
                                        { printf("Statement parsed successfully\n"); }
#line 1511 "mysql.tab.c"
    break;

  case 5: /* sql_statement: statement  */
#line 70 "grammars/mysql.y"
                                        { printf("Statement parsed (missing semicolon)\n"); }
#line 1517 "mysql.tab.c"
    break;

  case 6: /* statement: select_statement  */
#line 73 "grammars/mysql.y"
                                        { printf("Parsed SELECT statement\n"); }
#line 1523 "mysql.tab.c"
    break;

  case 7: /* statement: insert_statement  */
#line 74 "grammars/mysql.y"
                                        { printf("Parsed INSERT statement\n"); }
#line 1529 "mysql.tab.c"
    break;

  case 8: /* statement: update_statement  */
#line 75 "grammars/mysql.y"
                                        { printf("Parsed UPDATE statement\n"); }
#line 1535 "mysql.tab.c"
    break;

  case 9: /* statement: delete_statement  */
#line 76 "grammars/mysql.y"
                                        { printf("Parsed DELETE statement\n"); }
#line 1541 "mysql.tab.c"
    break;

  case 10: /* statement: create_statement  */
#line 77 "grammars/mysql.y"
                                        { printf("Parsed CREATE statement\n"); }
#line 1547 "mysql.tab.c"
    break;

  case 11: /* statement: drop_statement  */
#line 78 "grammars/mysql.y"
                                        { printf("Parsed DROP statement\n"); }
#line 1553 "mysql.tab.c"
    break;

  case 12: /* statement: alter_statement  */
#line 79 "grammars/mysql.y"
                                        { printf("Parsed ALTER statement\n"); }
#line 1559 "mysql.tab.c"
    break;


#line 1563 "mysql.tab.c"

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
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 373 "grammars/mysql.y"


void yyerror(const char *s) {
    // Use the lexer's error reporting system
    std::string error_msg = "Parse error: ";
    error_msg += s;
    setSyntaxError(error_msg, currLine, currCol);
    fprintf(stderr, "Parse error: %s at line %d, column %d\n", s, currLine, currCol);
}
