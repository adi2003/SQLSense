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
  YYSYMBOL_COLUMN = 30,                    /* COLUMN  */
  YYSYMBOL_JOIN = 31,                      /* JOIN  */
  YYSYMBOL_INNER = 32,                     /* INNER  */
  YYSYMBOL_LEFT = 33,                      /* LEFT  */
  YYSYMBOL_RIGHT = 34,                     /* RIGHT  */
  YYSYMBOL_FULL = 35,                      /* FULL  */
  YYSYMBOL_OUTER = 36,                     /* OUTER  */
  YYSYMBOL_CROSS = 37,                     /* CROSS  */
  YYSYMBOL_ON = 38,                        /* ON  */
  YYSYMBOL_USING = 39,                     /* USING  */
  YYSYMBOL_GROUP = 40,                     /* GROUP  */
  YYSYMBOL_BY = 41,                        /* BY  */
  YYSYMBOL_HAVING = 42,                    /* HAVING  */
  YYSYMBOL_ORDER = 43,                     /* ORDER  */
  YYSYMBOL_ASC = 44,                       /* ASC  */
  YYSYMBOL_DESC = 45,                      /* DESC  */
  YYSYMBOL_DISTINCT = 46,                  /* DISTINCT  */
  YYSYMBOL_ALL = 47,                       /* ALL  */
  YYSYMBOL_UNION = 48,                     /* UNION  */
  YYSYMBOL_INTERSECT = 49,                 /* INTERSECT  */
  YYSYMBOL_EXCEPT = 50,                    /* EXCEPT  */
  YYSYMBOL_LIMIT = 51,                     /* LIMIT  */
  YYSYMBOL_OFFSET = 52,                    /* OFFSET  */
  YYSYMBOL_TOP = 53,                       /* TOP  */
  YYSYMBOL_IS = 54,                        /* IS  */
  YYSYMBOL_NULLSYM = 55,                   /* NULLSYM  */
  YYSYMBOL_LIKE = 56,                      /* LIKE  */
  YYSYMBOL_ILIKE = 57,                     /* ILIKE  */
  YYSYMBOL_IN = 58,                        /* IN  */
  YYSYMBOL_BETWEEN = 59,                   /* BETWEEN  */
  YYSYMBOL_EXISTS = 60,                    /* EXISTS  */
  YYSYMBOL_CASE = 61,                      /* CASE  */
  YYSYMBOL_WHEN = 62,                      /* WHEN  */
  YYSYMBOL_THEN = 63,                      /* THEN  */
  YYSYMBOL_ELSE = 64,                      /* ELSE  */
  YYSYMBOL_END = 65,                       /* END  */
  YYSYMBOL_PRIMARY = 66,                   /* PRIMARY  */
  YYSYMBOL_KEY = 67,                       /* KEY  */
  YYSYMBOL_FOREIGN = 68,                   /* FOREIGN  */
  YYSYMBOL_REFERENCES = 69,                /* REFERENCES  */
  YYSYMBOL_UNIQUE = 70,                    /* UNIQUE  */
  YYSYMBOL_CHECK = 71,                     /* CHECK  */
  YYSYMBOL_DEFAULT = 72,                   /* DEFAULT  */
  YYSYMBOL_AUTO_INCREMENT = 73,            /* AUTO_INCREMENT  */
  YYSYMBOL_NOT_NULL = 74,                  /* NOT_NULL  */
  YYSYMBOL_ADD = 75,                       /* ADD  */
  YYSYMBOL_MODIFY = 76,                    /* MODIFY  */
  YYSYMBOL_EQ = 77,                        /* EQ  */
  YYSYMBOL_NE = 78,                        /* NE  */
  YYSYMBOL_LT = 79,                        /* LT  */
  YYSYMBOL_LE = 80,                        /* LE  */
  YYSYMBOL_GT = 81,                        /* GT  */
  YYSYMBOL_GE = 82,                        /* GE  */
  YYSYMBOL_PLUS = 83,                      /* PLUS  */
  YYSYMBOL_MINUS = 84,                     /* MINUS  */
  YYSYMBOL_ASTERISK = 85,                  /* ASTERISK  */
  YYSYMBOL_DIVIDE = 86,                    /* DIVIDE  */
  YYSYMBOL_MODULO = 87,                    /* MODULO  */
  YYSYMBOL_CONCAT_OP = 88,                 /* CONCAT_OP  */
  YYSYMBOL_COMMA = 89,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 90,                 /* SEMICOLON  */
  YYSYMBOL_LPAREN = 91,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 92,                    /* RPAREN  */
  YYSYMBOL_DOT = 93,                       /* DOT  */
  YYSYMBOL_QUESTION = 94,                  /* QUESTION  */
  YYSYMBOL_UMINUS = 95,                    /* UMINUS  */
  YYSYMBOL_UPLUS = 96,                     /* UPLUS  */
  YYSYMBOL_YYACCEPT = 97,                  /* $accept  */
  YYSYMBOL_sql_program = 98,               /* sql_program  */
  YYSYMBOL_statement_list = 99,            /* statement_list  */
  YYSYMBOL_statement = 100,                /* statement  */
  YYSYMBOL_select_statement = 101,         /* select_statement  */
  YYSYMBOL_opt_distinct = 102,             /* opt_distinct  */
  YYSYMBOL_select_list = 103,              /* select_list  */
  YYSYMBOL_select_item = 104,              /* select_item  */
  YYSYMBOL_opt_from_clause = 105,          /* opt_from_clause  */
  YYSYMBOL_table_reference_list = 106,     /* table_reference_list  */
  YYSYMBOL_table_reference = 107,          /* table_reference  */
  YYSYMBOL_join_clause = 108,              /* join_clause  */
  YYSYMBOL_opt_join_type = 109,            /* opt_join_type  */
  YYSYMBOL_opt_outer = 110,                /* opt_outer  */
  YYSYMBOL_opt_where_clause = 111,         /* opt_where_clause  */
  YYSYMBOL_opt_group_by_clause = 112,      /* opt_group_by_clause  */
  YYSYMBOL_opt_having_clause = 113,        /* opt_having_clause  */
  YYSYMBOL_opt_order_by_clause = 114,      /* opt_order_by_clause  */
  YYSYMBOL_order_by_list = 115,            /* order_by_list  */
  YYSYMBOL_opt_asc_desc = 116,             /* opt_asc_desc  */
  YYSYMBOL_opt_limit_clause = 117,         /* opt_limit_clause  */
  YYSYMBOL_insert_statement = 118,         /* insert_statement  */
  YYSYMBOL_opt_column_list = 119,          /* opt_column_list  */
  YYSYMBOL_value_list_list = 120,          /* value_list_list  */
  YYSYMBOL_update_statement = 121,         /* update_statement  */
  YYSYMBOL_assignment_list = 122,          /* assignment_list  */
  YYSYMBOL_assignment = 123,               /* assignment  */
  YYSYMBOL_delete_statement = 124,         /* delete_statement  */
  YYSYMBOL_create_table_statement = 125,   /* create_table_statement  */
  YYSYMBOL_column_definition_list = 126,   /* column_definition_list  */
  YYSYMBOL_column_definition = 127,        /* column_definition  */
  YYSYMBOL_opt_column_constraints = 128,   /* opt_column_constraints  */
  YYSYMBOL_column_constraint = 129,        /* column_constraint  */
  YYSYMBOL_create_database_statement = 130, /* create_database_statement  */
  YYSYMBOL_create_index_statement = 131,   /* create_index_statement  */
  YYSYMBOL_opt_unique = 132,               /* opt_unique  */
  YYSYMBOL_create_view_statement = 133,    /* create_view_statement  */
  YYSYMBOL_drop_statement = 134,           /* drop_statement  */
  YYSYMBOL_alter_statement = 135,          /* alter_statement  */
  YYSYMBOL_expression = 136,               /* expression  */
  YYSYMBOL_primary_expression = 137,       /* primary_expression  */
  YYSYMBOL_function_call = 138,            /* function_call  */
  YYSYMBOL_case_expression = 139,          /* case_expression  */
  YYSYMBOL_when_clause_list = 140,         /* when_clause_list  */
  YYSYMBOL_opt_else_clause = 141,          /* opt_else_clause  */
  YYSYMBOL_expression_list = 142,          /* expression_list  */
  YYSYMBOL_opt_expression_list = 143,      /* opt_expression_list  */
  YYSYMBOL_identifier_list = 144           /* identifier_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;



/* Unqualified %code blocks.  */
#line 10 "grammars/mysql.y"

    #include <cstdlib>
    #include <cstring>
    
    extern int yylex();
    extern int yyparse();
    extern int currLine, currCol;
    extern FILE* yyin;
        
    // Import error handling functions from lexer
    extern void setSyntaxError(const std::string& msg, int line, int col);

    void yyerror(const char *s);

    // Global AST root
    std::unique_ptr<SqlProgram> sqlProgram = nullptr;

    // Helper function to create string
    std::string makeString(char* str) {
        if (str) {
            std::string result(str);
            free(str);
            return result;
        }
        return "";
    }

#line 276 "mysql.tab.c"

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
#define YYFINAL  39
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   577

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  97
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  156
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  301

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   351


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
      95,    96
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   156,   156,   166,   173,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   205,   231,   232,   233,   236,
     243,   252,   256,   260,   265,   272,   273,   276,   283,   292,
     296,   301,   306,   312,   321,   327,   338,   339,   340,   341,
     342,   343,   346,   347,   350,   351,   354,   355,   358,   359,
     362,   363,   366,   371,   378,   379,   380,   383,   384,   385,
     389,   401,   412,   413,   416,   424,   435,   446,   453,   462,
     469,   477,   487,   494,   503,   509,   510,   513,   514,   515,
     516,   517,   518,   519,   520,   524,   528,   535,   546,   547,
     551,   558,   562,   566,   570,   574,   581,   586,   591,   599,
     600,   604,   608,   612,   616,   620,   624,   628,   632,   636,
     640,   644,   648,   652,   656,   660,   664,   670,   676,   680,
     684,   688,   692,   696,   697,   698,   701,   705,   709,   713,
     717,   721,   727,   735,   744,   751,   761,   772,   777,   784,
     785,   789,   796,   805,   806,   809,   814
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
  "DATABASE", "SCHEMA", "INDEX", "VIEW", "COLUMN", "JOIN", "INNER", "LEFT",
  "RIGHT", "FULL", "OUTER", "CROSS", "ON", "USING", "GROUP", "BY",
  "HAVING", "ORDER", "ASC", "DESC", "DISTINCT", "ALL", "UNION",
  "INTERSECT", "EXCEPT", "LIMIT", "OFFSET", "TOP", "IS", "NULLSYM", "LIKE",
  "ILIKE", "IN", "BETWEEN", "EXISTS", "CASE", "WHEN", "THEN", "ELSE",
  "END", "PRIMARY", "KEY", "FOREIGN", "REFERENCES", "UNIQUE", "CHECK",
  "DEFAULT", "AUTO_INCREMENT", "NOT_NULL", "ADD", "MODIFY", "EQ", "NE",
  "LT", "LE", "GT", "GE", "PLUS", "MINUS", "ASTERISK", "DIVIDE", "MODULO",
  "CONCAT_OP", "COMMA", "SEMICOLON", "LPAREN", "RPAREN", "DOT", "QUESTION",
  "UMINUS", "UPLUS", "$accept", "sql_program", "statement_list",
  "statement", "select_statement", "opt_distinct", "select_list",
  "select_item", "opt_from_clause", "table_reference_list",
  "table_reference", "join_clause", "opt_join_type", "opt_outer",
  "opt_where_clause", "opt_group_by_clause", "opt_having_clause",
  "opt_order_by_clause", "order_by_list", "opt_asc_desc",
  "opt_limit_clause", "insert_statement", "opt_column_list",
  "value_list_list", "update_statement", "assignment_list", "assignment",
  "delete_statement", "create_table_statement", "column_definition_list",
  "column_definition", "opt_column_constraints", "column_constraint",
  "create_database_statement", "create_index_statement", "opt_unique",
  "create_view_statement", "drop_statement", "alter_statement",
  "expression", "primary_expression", "function_call", "case_expression",
  "when_clause_list", "opt_else_clause", "expression_list",
  "opt_expression_list", "identifier_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-237)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-123)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     157,    62,    -9,     9,    16,    -8,   133,     3,    30,   157,
    -237,   -56,   -50,   -41,   -35,   -24,   -17,   -14,    22,    54,
      60,  -237,  -237,   114,    94,    79,   167,   168,   169,   171,
     174,  -237,   154,   180,   190,   192,   193,   199,   204,  -237,
    -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,
    -237,   115,  -237,   120,  -237,  -237,   149,  -237,   139,   149,
     149,  -237,   149,     5,  -237,   203,  -237,  -237,  -237,   121,
     206,   207,   123,  -237,  -237,   208,   216,  -237,  -237,  -237,
    -237,  -237,   -16,   218,    50,   489,   149,   313,   -42,  -237,
    -237,   215,     2,   114,   207,  -237,   221,   149,   149,   -13,
     149,   149,   134,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   223,     7,   150,   -10,
    -237,   149,  -237,   228,   225,   197,   209,   211,   212,  -237,
     149,   144,   395,   155,   146,   348,   -42,   149,   149,   181,
    -237,    20,   225,   158,    69,  -237,   210,  -237,   489,   454,
     194,  -237,    40,    40,   149,   407,    40,    40,    40,    40,
      40,    40,    45,    45,  -237,  -237,  -237,    45,  -237,   -65,
     160,  -237,   149,   206,  -237,   395,   243,   -25,  -237,  -237,
     250,   251,   228,   228,   -21,  -237,   149,  -237,   149,   191,
     360,   395,  -237,  -237,   255,   163,     2,  -237,   227,   227,
     227,  -237,  -237,   236,   229,   226,  -237,   -20,   149,   272,
    -237,   149,   187,   395,  -237,  -237,   228,  -237,   186,  -237,
    -237,  -237,  -237,   395,   395,  -237,   149,  -237,   266,    69,
    -237,  -237,  -237,  -237,     2,   149,   149,   261,  -237,   442,
    -237,    18,   188,   118,  -237,   223,   395,   302,    13,   155,
     395,   271,   262,  -237,   149,   249,   253,   314,  -237,   230,
     149,  -237,  -237,  -237,    24,  -237,   149,   231,   149,   311,
    -237,    47,  -237,   254,  -237,   149,   395,  -237,   395,   223,
     235,   301,   267,  -237,   322,   252,    48,   149,  -237,  -237,
    -237,   321,   256,  -237,  -237,   301,  -237,   223,  -237,    59,
    -237
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    26,     0,     0,     0,    98,     0,     0,     0,     2,
       3,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    27,    28,     0,     0,     0,     0,     0,     0,     0,
       0,    99,     0,     0,     0,     0,     0,     0,     0,     1,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,   136,   138,     0,   139,   140,     0,   141,     0,     0,
       0,    31,     0,    35,    29,    32,   109,   135,   134,    72,
       0,    54,     0,    95,    96,     0,     0,   101,   102,   103,
     104,   105,     0,     0,   153,   130,     0,     0,   149,   132,
     131,     0,     0,     0,    54,    34,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    54,
      77,     0,    80,     0,     0,     0,     0,     0,     0,   137,
       0,     0,   151,   154,     0,     0,   149,     0,     0,     0,
     133,    39,     0,    36,    37,    30,    56,    33,   122,   123,
       0,   128,   124,   125,     0,     0,   116,   117,   118,   119,
     120,   121,   110,   111,   112,   113,   114,   115,   155,     0,
       0,    71,     0,     0,    76,    55,     0,     0,    82,   100,
       0,     0,     0,     0,     0,   144,     0,   142,     0,     0,
       0,   150,   146,    41,     0,     0,     0,    47,    52,    52,
      52,    51,    43,     0,     0,    58,   129,     0,     0,     0,
      73,     0,    70,    79,    78,    85,     0,    81,     0,   107,
     106,   108,   143,   152,   147,   145,     0,    40,     0,    38,
      53,    48,    49,    50,     0,     0,     0,    60,   126,   127,
     156,     0,     0,    84,    83,     0,   148,     0,    46,    57,
      59,     0,    67,    74,     0,     0,     0,     0,    88,     0,
       0,    90,    89,    86,     0,    42,     0,     0,     0,     0,
      25,     0,    87,     0,    93,     0,    91,    97,    44,     0,
      61,    64,    68,    75,     0,     0,     0,     0,    65,    66,
      62,     0,     0,    94,    45,    64,    69,     0,    63,     0,
      92
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -237,  -237,  -237,   332,  -111,  -237,  -237,   257,  -237,  -237,
    -193,  -237,  -237,   -32,   -90,  -237,  -237,  -237,  -237,    53,
    -237,  -237,  -237,  -237,  -237,  -237,   170,  -237,  -237,  -237,
    -172,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,   -23,
    -237,  -237,  -237,   264,   213,  -116,  -237,  -236
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     8,     9,    10,    11,    23,    63,    64,    94,   143,
     144,   202,   203,   231,   122,   205,   237,   252,   280,   290,
     270,    12,   117,   212,    13,   119,   120,    14,    15,   177,
     178,   243,   263,    16,    17,    32,    18,    19,    20,   132,
      66,    67,    68,    88,   139,   133,   134,   169
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      65,   121,   150,   229,   146,   141,   171,   126,    24,   264,
     220,   221,    25,   179,   184,    92,     1,    27,    28,    29,
     137,    30,   138,   193,   209,   170,    26,   210,    38,   174,
      39,   195,   194,    85,    41,    87,    89,    90,   207,    91,
      42,   248,   151,   286,   244,   197,   198,   199,   200,    43,
     201,   266,   267,    51,    52,    44,    53,    54,    55,   127,
     128,   299,    31,   135,   216,    56,    45,   217,   186,   186,
      65,   222,   238,    46,   148,   149,    47,   152,   153,   173,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   142,    93,   241,   130,    69,   175,    70,
     -46,   197,   198,   199,   200,    57,   201,   186,    21,    22,
     253,    58,    48,   209,   190,   191,   277,    51,    52,   249,
      53,    54,    55,   110,   111,   112,   113,   114,   115,    56,
     112,   113,   114,    59,    60,   131,   186,   209,   271,   283,
     294,    62,    51,    52,    49,    53,    54,    55,   209,   213,
      50,   300,    51,    52,    56,    53,    54,    55,    33,    34,
      35,    36,    37,   223,    56,   224,     1,   232,   233,    57,
      71,    72,    73,     2,    74,    58,     3,    75,     4,     5,
       6,     7,    76,    77,   255,   239,   256,   257,   258,   259,
     260,   261,   262,    78,    57,    79,    80,    59,    60,    61,
      58,    86,    81,   246,    57,    62,    95,    82,    83,   118,
      58,    84,   116,   250,   123,    96,    97,    98,   121,   125,
     124,   129,    59,    60,   147,   154,   168,   172,    97,    98,
      62,   176,    59,    60,     1,   180,   185,   276,   187,   181,
      62,   182,   183,   278,   186,   281,   192,   196,   215,   206,
     204,   211,   285,   218,   219,   228,   225,    99,   227,   100,
     101,   102,   103,   230,   295,    97,    98,   234,   236,    99,
     235,   100,   101,   102,   103,   240,   242,   245,   247,   254,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   251,   265,    99,   140,   100,   101,
     102,   103,   268,   269,    97,    98,   272,   274,   282,   291,
     273,   275,   279,   284,   287,   292,    97,    98,   296,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,    40,     0,   214,   293,   288,   289,   297,   298,   189,
     145,   136,     0,     0,     0,    99,     0,   100,   101,   102,
     103,    97,    98,     0,     0,     0,     0,    99,     0,   100,
     101,   102,   103,    97,    98,    86,     0,     0,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,    99,     0,   100,   101,   102,   103,    97,    98,
       0,   188,     0,     0,    99,     0,   100,   101,   102,   103,
     208,    98,     0,   226,     0,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,    99,
       0,   100,   101,   102,   103,  -122,  -122,     0,     0,     0,
       0,    99,     0,   100,   101,   102,   103,    97,     0,     0,
       0,     0,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,    99,     0,   100,   101,
     102,   103,     0,     0,     0,     0,     0,     0,    99,     0,
     100,   101,   102,   103,     0,     0,     0,     0,     0,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,    99,     0,   100,   101,   102,   103,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115
};

static const yytype_int16 yycheck[] =
{
      23,    11,    15,   196,    94,     3,   117,    23,    17,   245,
     182,   183,     3,   124,   130,    10,     9,    25,    26,    27,
      62,    29,    64,     3,    89,    18,    10,    92,    25,   119,
       0,   142,    12,    56,    90,    58,    59,    60,   154,    62,
      90,   234,    55,   279,   216,    32,    33,    34,    35,    90,
      37,    38,    39,     3,     4,    90,     6,     7,     8,    75,
      76,   297,    70,    86,    89,    15,    90,    92,    89,    89,
      93,    92,    92,    90,    97,    98,    90,   100,   101,    89,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,    91,    89,   211,    46,     3,   121,    20,
      31,    32,    33,    34,    35,    55,    37,    89,    46,    47,
      92,    61,    90,    89,   137,   138,    92,     3,     4,   235,
       6,     7,     8,    83,    84,    85,    86,    87,    88,    15,
      85,    86,    87,    83,    84,    85,    89,    89,   254,    92,
      92,    91,     3,     4,    90,     6,     7,     8,    89,   172,
      90,    92,     3,     4,    15,     6,     7,     8,    25,    26,
      27,    28,    29,   186,    15,   188,     9,   199,   200,    55,
       3,     3,     3,    16,     3,    61,    19,     3,    21,    22,
      23,    24,    28,     3,    66,   208,    68,    69,    70,    71,
      72,    73,    74,     3,    55,     3,     3,    83,    84,    85,
      61,    62,     3,   226,    55,    91,     3,     3,    93,     3,
      61,    91,    91,   236,    91,    12,    13,    14,    11,     3,
      12,     3,    83,    84,     3,    91,     3,    77,    13,    14,
      91,     3,    83,    84,     9,    38,    92,   260,    92,    30,
      91,    30,    30,   266,    89,   268,    65,    89,     5,    55,
      40,    91,   275,     3,     3,    92,    65,    54,     3,    56,
      57,    58,    59,    36,   287,    13,    14,    31,    42,    54,
      41,    56,    57,    58,    59,     3,    89,    91,    12,    91,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    43,     3,    54,    92,    56,    57,
      58,    59,    41,    51,    13,    14,    67,     3,     7,    52,
      67,    91,    91,    69,    89,     3,    13,    14,     7,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,     9,    -1,   173,    92,    44,    45,    91,   295,   136,
      93,    87,    -1,    -1,    -1,    54,    -1,    56,    57,    58,
      59,    13,    14,    -1,    -1,    -1,    -1,    54,    -1,    56,
      57,    58,    59,    13,    14,    62,    -1,    -1,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    54,    -1,    56,    57,    58,    59,    13,    14,
      -1,    63,    -1,    -1,    54,    -1,    56,    57,    58,    59,
      13,    14,    -1,    63,    -1,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    54,
      -1,    56,    57,    58,    59,    13,    14,    -1,    -1,    -1,
      -1,    54,    -1,    56,    57,    58,    59,    13,    -1,    -1,
      -1,    -1,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    54,    -1,    56,    57,
      58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,
      56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    54,    -1,    56,    57,    58,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    16,    19,    21,    22,    23,    24,    98,    99,
     100,   101,   118,   121,   124,   125,   130,   131,   133,   134,
     135,    46,    47,   102,    17,     3,    10,    25,    26,    27,
      29,    70,   132,    25,    26,    27,    28,    29,    25,     0,
     100,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,     3,     4,     6,     7,     8,    15,    55,    61,    83,
      84,    85,    91,   103,   104,   136,   137,   138,   139,     3,
      20,     3,     3,     3,     3,     3,    28,     3,     3,     3,
       3,     3,     3,    93,    91,   136,    62,   136,   140,   136,
     136,   136,    10,    89,   105,     3,    12,    13,    14,    54,
      56,    57,    58,    59,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    91,   119,     3,   122,
     123,    11,   111,    91,    12,     3,    23,    75,    76,     3,
      46,    85,   136,   142,   143,   136,   140,    62,    64,   141,
      92,     3,    91,   106,   107,   104,   111,     3,   136,   136,
      15,    55,   136,   136,    91,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,     3,   144,
      18,   101,    77,    89,   111,   136,     3,   126,   127,   101,
      38,    30,    30,    30,   142,    92,    89,    92,    63,   141,
     136,   136,    65,     3,    12,   101,    89,    32,    33,    34,
      35,    37,   108,   109,    40,   112,    55,   142,    13,    89,
      92,    91,   120,   136,   123,     5,    89,    92,     3,     3,
     127,   127,    92,   136,   136,    65,    63,     3,    92,   107,
      36,   110,   110,   110,    31,    41,    42,   113,    92,   136,
       3,   142,    89,   128,   127,    91,   136,    12,   107,   142,
     136,    43,   114,    92,    91,    66,    68,    69,    70,    71,
      72,    73,    74,   129,   144,     3,    38,    39,    41,    51,
     117,   142,    67,    67,     3,    91,   136,    92,   136,    91,
     115,   136,     7,    92,    69,   136,   144,    89,    44,    45,
     116,    52,     3,    92,    92,   136,     7,    91,   116,   144,
      92
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    97,    98,    99,    99,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   101,   102,   102,   102,   103,
     103,   104,   104,   104,   104,   105,   105,   106,   106,   107,
     107,   107,   107,   107,   108,   108,   109,   109,   109,   109,
     109,   109,   110,   110,   111,   111,   112,   112,   113,   113,
     114,   114,   115,   115,   116,   116,   116,   117,   117,   117,
     118,   118,   119,   119,   120,   120,   121,   122,   122,   123,
     124,   125,   126,   126,   127,   128,   128,   129,   129,   129,
     129,   129,   129,   129,   129,   130,   130,   131,   132,   132,
     133,   134,   134,   134,   134,   134,   135,   135,   135,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   137,   137,   137,   137,
     137,   137,   138,   138,   138,   139,   139,   140,   140,   141,
     141,   142,   142,   143,   143,   144,   144
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     9,     0,     1,     1,     1,
       3,     1,     1,     3,     2,     0,     2,     1,     3,     1,
       3,     2,     5,     2,     5,     7,     0,     1,     2,     2,
       2,     1,     0,     1,     0,     2,     0,     3,     0,     2,
       0,     3,     2,     4,     0,     1,     1,     0,     2,     4,
       6,     5,     0,     3,     3,     5,     5,     1,     3,     3,
       4,     6,     1,     3,     3,     0,     2,     2,     1,     1,
       1,     2,     7,     2,     4,     3,     3,     9,     0,     1,
       5,     3,     3,     3,     3,     3,     6,     6,     6,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     5,     5,     3,     4,
       2,     2,     2,     3,     1,     1,     1,     3,     1,     1,
       1,     1,     4,     5,     4,     5,     4,     4,     5,     0,
       2,     1,     3,     0,     1,     1,     3
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
  case 2: /* sql_program: statement_list  */
#line 157 "grammars/mysql.y"
            {
                sqlProgram = std::make_unique<SqlProgram>();
                if ((yyvsp[0].statementList)) {
                    sqlProgram->statements = std::move(*(yyvsp[0].statementList));
                    delete (yyvsp[0].statementList);
                }
            }
#line 1515 "mysql.tab.c"
    break;

  case 3: /* statement_list: statement  */
#line 167 "grammars/mysql.y"
               {
                   (yyval.statementList) = new std::vector<StatementPtr>();
                   if ((yyvsp[0].statement)) {
                       (yyval.statementList)->emplace_back((yyvsp[0].statement));
                   }
               }
#line 1526 "mysql.tab.c"
    break;

  case 4: /* statement_list: statement_list statement  */
#line 174 "grammars/mysql.y"
               {
                   (yyval.statementList) = (yyvsp[-1].statementList);
                   if ((yyvsp[0].statement)) {
                       (yyval.statementList)->emplace_back((yyvsp[0].statement));
                   }
               }
#line 1537 "mysql.tab.c"
    break;

  case 5: /* statement: select_statement SEMICOLON  */
#line 182 "grammars/mysql.y"
                                       { (yyval.statement) = (yyvsp[-1].selectStmt); }
#line 1543 "mysql.tab.c"
    break;

  case 6: /* statement: insert_statement SEMICOLON  */
#line 183 "grammars/mysql.y"
                                       { (yyval.statement) = (yyvsp[-1].insertStmt); }
#line 1549 "mysql.tab.c"
    break;

  case 7: /* statement: update_statement SEMICOLON  */
#line 184 "grammars/mysql.y"
                                       { (yyval.statement) = (yyvsp[-1].updateStmt); }
#line 1555 "mysql.tab.c"
    break;

  case 8: /* statement: delete_statement SEMICOLON  */
#line 185 "grammars/mysql.y"
                                       { (yyval.statement) = (yyvsp[-1].deleteStmt); }
#line 1561 "mysql.tab.c"
    break;

  case 9: /* statement: create_table_statement SEMICOLON  */
#line 186 "grammars/mysql.y"
                                             { (yyval.statement) = (yyvsp[-1].createTableStmt); }
#line 1567 "mysql.tab.c"
    break;

  case 10: /* statement: create_database_statement SEMICOLON  */
#line 187 "grammars/mysql.y"
                                                { (yyval.statement) = (yyvsp[-1].createDatabaseStmt); }
#line 1573 "mysql.tab.c"
    break;

  case 11: /* statement: create_index_statement SEMICOLON  */
#line 188 "grammars/mysql.y"
                                             { (yyval.statement) = (yyvsp[-1].createIndexStmt); }
#line 1579 "mysql.tab.c"
    break;

  case 12: /* statement: create_view_statement SEMICOLON  */
#line 189 "grammars/mysql.y"
                                            { (yyval.statement) = (yyvsp[-1].createViewStmt); }
#line 1585 "mysql.tab.c"
    break;

  case 13: /* statement: drop_statement SEMICOLON  */
#line 190 "grammars/mysql.y"
                                     { (yyval.statement) = (yyvsp[-1].dropStmt); }
#line 1591 "mysql.tab.c"
    break;

  case 14: /* statement: alter_statement SEMICOLON  */
#line 191 "grammars/mysql.y"
                                      { (yyval.statement) = (yyvsp[-1].alterStmt); }
#line 1597 "mysql.tab.c"
    break;

  case 15: /* statement: select_statement  */
#line 192 "grammars/mysql.y"
                             { (yyval.statement) = (yyvsp[0].selectStmt); }
#line 1603 "mysql.tab.c"
    break;

  case 16: /* statement: insert_statement  */
#line 193 "grammars/mysql.y"
                             { (yyval.statement) = (yyvsp[0].insertStmt); }
#line 1609 "mysql.tab.c"
    break;

  case 17: /* statement: update_statement  */
#line 194 "grammars/mysql.y"
                             { (yyval.statement) = (yyvsp[0].updateStmt); }
#line 1615 "mysql.tab.c"
    break;

  case 18: /* statement: delete_statement  */
#line 195 "grammars/mysql.y"
                             { (yyval.statement) = (yyvsp[0].deleteStmt); }
#line 1621 "mysql.tab.c"
    break;

  case 19: /* statement: create_table_statement  */
#line 196 "grammars/mysql.y"
                                   { (yyval.statement) = (yyvsp[0].createTableStmt); }
#line 1627 "mysql.tab.c"
    break;

  case 20: /* statement: create_database_statement  */
#line 197 "grammars/mysql.y"
                                      { (yyval.statement) = (yyvsp[0].createDatabaseStmt); }
#line 1633 "mysql.tab.c"
    break;

  case 21: /* statement: create_index_statement  */
#line 198 "grammars/mysql.y"
                                   { (yyval.statement) = (yyvsp[0].createIndexStmt); }
#line 1639 "mysql.tab.c"
    break;

  case 22: /* statement: create_view_statement  */
#line 199 "grammars/mysql.y"
                                  { (yyval.statement) = (yyvsp[0].createViewStmt); }
#line 1645 "mysql.tab.c"
    break;

  case 23: /* statement: drop_statement  */
#line 200 "grammars/mysql.y"
                           { (yyval.statement) = (yyvsp[0].dropStmt); }
#line 1651 "mysql.tab.c"
    break;

  case 24: /* statement: alter_statement  */
#line 201 "grammars/mysql.y"
                            { (yyval.statement) = (yyvsp[0].alterStmt); }
#line 1657 "mysql.tab.c"
    break;

  case 25: /* select_statement: SELECT opt_distinct select_list opt_from_clause opt_where_clause opt_group_by_clause opt_having_clause opt_order_by_clause opt_limit_clause  */
#line 207 "grammars/mysql.y"
                 {
                     (yyval.selectStmt) = new SelectStmt(currLine, currCol);
                     (yyval.selectStmt)->isDistinct = ((yyvsp[-7].intVal) != 0);
                     if ((yyvsp[-6].selectItemList)) {
                         (yyval.selectStmt)->selectList = std::move(*(yyvsp[-6].selectItemList));
                         delete (yyvsp[-6].selectItemList);
                     }
                     if ((yyvsp[-5].tableRefList)) {
                         (yyval.selectStmt)->fromList = std::move(*(yyvsp[-5].tableRefList));
                         delete (yyvsp[-5].tableRefList);
                     }
                     (yyval.selectStmt)->whereClause = ExpressionPtr((yyvsp[-4].expression));
                     if ((yyvsp[-3].expressionList)) {
                         (yyval.selectStmt)->groupByList = std::move(*(yyvsp[-3].expressionList));
                         delete (yyvsp[-3].expressionList);
                     }
                     (yyval.selectStmt)->havingClause = ExpressionPtr((yyvsp[-2].expression));
                     if ((yyvsp[-1].orderByList)) {
                         (yyval.selectStmt)->orderByList = std::move(*(yyvsp[-1].orderByList));
                         delete (yyvsp[-1].orderByList);
                     }
                 }
#line 1684 "mysql.tab.c"
    break;

  case 26: /* opt_distinct: %empty  */
#line 231 "grammars/mysql.y"
                           { (yyval.intVal) = 0; }
#line 1690 "mysql.tab.c"
    break;

  case 27: /* opt_distinct: DISTINCT  */
#line 232 "grammars/mysql.y"
                        { (yyval.intVal) = 1; }
#line 1696 "mysql.tab.c"
    break;

  case 28: /* opt_distinct: ALL  */
#line 233 "grammars/mysql.y"
                   { (yyval.intVal) = 0; }
#line 1702 "mysql.tab.c"
    break;

  case 29: /* select_list: select_item  */
#line 237 "grammars/mysql.y"
            {
                (yyval.selectItemList) = new std::vector<std::unique_ptr<SelectItem>>();
                if ((yyvsp[0].selectItem)) {
                    (yyval.selectItemList)->emplace_back((yyvsp[0].selectItem));
                }
            }
#line 1713 "mysql.tab.c"
    break;

  case 30: /* select_list: select_list COMMA select_item  */
#line 244 "grammars/mysql.y"
            {
                (yyval.selectItemList) = (yyvsp[-2].selectItemList);
                if ((yyvsp[0].selectItem)) {
                    (yyval.selectItemList)->emplace_back((yyvsp[0].selectItem));
                }
            }
#line 1724 "mysql.tab.c"
    break;

  case 31: /* select_item: ASTERISK  */
#line 253 "grammars/mysql.y"
            {
                (yyval.selectItem) = new SelectItem(true, currLine, currCol);
            }
#line 1732 "mysql.tab.c"
    break;

  case 32: /* select_item: expression  */
#line 257 "grammars/mysql.y"
            {
                (yyval.selectItem) = new SelectItem(ExpressionPtr((yyvsp[0].expression)), currLine, currCol);
            }
#line 1740 "mysql.tab.c"
    break;

  case 33: /* select_item: expression AS IDENTIFIER  */
#line 261 "grammars/mysql.y"
            {
                (yyval.selectItem) = new SelectItem(ExpressionPtr((yyvsp[-2].expression)), currLine, currCol);
                (yyval.selectItem)->alias = makeString((yyvsp[0].strVal));
            }
#line 1749 "mysql.tab.c"
    break;

  case 34: /* select_item: expression IDENTIFIER  */
#line 266 "grammars/mysql.y"
            {
                (yyval.selectItem) = new SelectItem(ExpressionPtr((yyvsp[-1].expression)), currLine, currCol);
                (yyval.selectItem)->alias = makeString((yyvsp[0].strVal));
            }
#line 1758 "mysql.tab.c"
    break;

  case 35: /* opt_from_clause: %empty  */
#line 272 "grammars/mysql.y"
                              { (yyval.tableRefList) = nullptr; }
#line 1764 "mysql.tab.c"
    break;

  case 36: /* opt_from_clause: FROM table_reference_list  */
#line 273 "grammars/mysql.y"
                                            { (yyval.tableRefList) = (yyvsp[0].tableRefList); }
#line 1770 "mysql.tab.c"
    break;

  case 37: /* table_reference_list: table_reference  */
#line 277 "grammars/mysql.y"
                     {
                         (yyval.tableRefList) = new std::vector<std::unique_ptr<TableRef>>();
                         if ((yyvsp[0].tableRef)) {
                             (yyval.tableRefList)->emplace_back((yyvsp[0].tableRef));
                         }
                     }
#line 1781 "mysql.tab.c"
    break;

  case 38: /* table_reference_list: table_reference_list COMMA table_reference  */
#line 284 "grammars/mysql.y"
                     {
                         (yyval.tableRefList) = (yyvsp[-2].tableRefList);
                         if ((yyvsp[0].tableRef)) {
                             (yyval.tableRefList)->emplace_back((yyvsp[0].tableRef));
                         }
                     }
#line 1792 "mysql.tab.c"
    break;

  case 39: /* table_reference: IDENTIFIER  */
#line 293 "grammars/mysql.y"
                {
                    (yyval.tableRef) = new TableRef(makeString((yyvsp[0].strVal)), currLine, currCol);
                }
#line 1800 "mysql.tab.c"
    break;

  case 40: /* table_reference: IDENTIFIER AS IDENTIFIER  */
#line 297 "grammars/mysql.y"
                {
                    (yyval.tableRef) = new TableRef(makeString((yyvsp[-2].strVal)), currLine, currCol);
                    (yyval.tableRef)->alias = makeString((yyvsp[0].strVal));
                }
#line 1809 "mysql.tab.c"
    break;

  case 41: /* table_reference: IDENTIFIER IDENTIFIER  */
#line 302 "grammars/mysql.y"
                {
                    (yyval.tableRef) = new TableRef(makeString((yyvsp[-1].strVal)), currLine, currCol);
                    (yyval.tableRef)->alias = makeString((yyvsp[0].strVal));
                }
#line 1818 "mysql.tab.c"
    break;

  case 42: /* table_reference: LPAREN select_statement RPAREN AS IDENTIFIER  */
#line 307 "grammars/mysql.y"
                {
                    (yyval.tableRef) = new TableRef("", currLine, currCol);
                    (yyval.tableRef)->subquery = StatementPtr((yyvsp[-3].selectStmt));
                    (yyval.tableRef)->alias = makeString((yyvsp[0].strVal));
                }
#line 1828 "mysql.tab.c"
    break;

  case 43: /* table_reference: table_reference join_clause  */
#line 313 "grammars/mysql.y"
                {
                    (yyval.tableRef) = (yyvsp[-1].tableRef);
                    if ((yyvsp[0].joinClause)) {
                        (yyval.tableRef)->joins.emplace_back((yyvsp[0].joinClause));
                    }
                }
#line 1839 "mysql.tab.c"
    break;

  case 44: /* join_clause: opt_join_type JOIN table_reference ON expression  */
#line 322 "grammars/mysql.y"
            {
                (yyval.joinClause) = new JoinClause(static_cast<JoinClause::JoinType>((yyvsp[-4].intVal)), 
                                  std::unique_ptr<TableRef>((yyvsp[-2].tableRef)), currLine, currCol);
                (yyval.joinClause)->onCondition = ExpressionPtr((yyvsp[0].expression));
            }
#line 1849 "mysql.tab.c"
    break;

  case 45: /* join_clause: opt_join_type JOIN table_reference USING LPAREN identifier_list RPAREN  */
#line 328 "grammars/mysql.y"
            {
                (yyval.joinClause) = new JoinClause(static_cast<JoinClause::JoinType>((yyvsp[-6].intVal)), 
                                  std::unique_ptr<TableRef>((yyvsp[-4].tableRef)), currLine, currCol);
                if ((yyvsp[-1].stringList)) {
                    (yyval.joinClause)->usingColumns = std::move(*(yyvsp[-1].stringList));
                    delete (yyvsp[-1].stringList);
                }
            }
#line 1862 "mysql.tab.c"
    break;

  case 46: /* opt_join_type: %empty  */
#line 338 "grammars/mysql.y"
                            { (yyval.intVal) = 0; /* INNER */ }
#line 1868 "mysql.tab.c"
    break;

  case 47: /* opt_join_type: INNER  */
#line 339 "grammars/mysql.y"
                      { (yyval.intVal) = 0; }
#line 1874 "mysql.tab.c"
    break;

  case 48: /* opt_join_type: LEFT opt_outer  */
#line 340 "grammars/mysql.y"
                               { (yyval.intVal) = 1; }
#line 1880 "mysql.tab.c"
    break;

  case 49: /* opt_join_type: RIGHT opt_outer  */
#line 341 "grammars/mysql.y"
                                { (yyval.intVal) = 2; }
#line 1886 "mysql.tab.c"
    break;

  case 50: /* opt_join_type: FULL opt_outer  */
#line 342 "grammars/mysql.y"
                               { (yyval.intVal) = 3; }
#line 1892 "mysql.tab.c"
    break;

  case 51: /* opt_join_type: CROSS  */
#line 343 "grammars/mysql.y"
                      { (yyval.intVal) = 4; }
#line 1898 "mysql.tab.c"
    break;

  case 54: /* opt_where_clause: %empty  */
#line 350 "grammars/mysql.y"
                               { (yyval.expression) = nullptr; }
#line 1904 "mysql.tab.c"
    break;

  case 55: /* opt_where_clause: WHERE expression  */
#line 351 "grammars/mysql.y"
                                    { (yyval.expression) = (yyvsp[0].expression); }
#line 1910 "mysql.tab.c"
    break;

  case 56: /* opt_group_by_clause: %empty  */
#line 354 "grammars/mysql.y"
                                  { (yyval.expressionList) = nullptr; }
#line 1916 "mysql.tab.c"
    break;

  case 57: /* opt_group_by_clause: GROUP BY expression_list  */
#line 355 "grammars/mysql.y"
                                               { (yyval.expressionList) = (yyvsp[0].expressionList); }
#line 1922 "mysql.tab.c"
    break;

  case 58: /* opt_having_clause: %empty  */
#line 358 "grammars/mysql.y"
                                { (yyval.expression) = nullptr; }
#line 1928 "mysql.tab.c"
    break;

  case 59: /* opt_having_clause: HAVING expression  */
#line 359 "grammars/mysql.y"
                                      { (yyval.expression) = (yyvsp[0].expression); }
#line 1934 "mysql.tab.c"
    break;

  case 60: /* opt_order_by_clause: %empty  */
#line 362 "grammars/mysql.y"
                                  { (yyval.orderByList) = nullptr; }
#line 1940 "mysql.tab.c"
    break;

  case 61: /* opt_order_by_clause: ORDER BY order_by_list  */
#line 363 "grammars/mysql.y"
                                             { (yyval.orderByList) = (yyvsp[0].orderByList); }
#line 1946 "mysql.tab.c"
    break;

  case 62: /* order_by_list: expression opt_asc_desc  */
#line 367 "grammars/mysql.y"
              {
                  (yyval.orderByList) = new std::vector<std::pair<ExpressionPtr, bool>>();
                  (yyval.orderByList)->emplace_back(ExpressionPtr((yyvsp[-1].expression)), (yyvsp[0].intVal) != 0);
              }
#line 1955 "mysql.tab.c"
    break;

  case 63: /* order_by_list: order_by_list COMMA expression opt_asc_desc  */
#line 372 "grammars/mysql.y"
              {
                  (yyval.orderByList) = (yyvsp[-3].orderByList);
                  (yyval.orderByList)->emplace_back(ExpressionPtr((yyvsp[-1].expression)), (yyvsp[0].intVal) != 0);
              }
#line 1964 "mysql.tab.c"
    break;

  case 64: /* opt_asc_desc: %empty  */
#line 378 "grammars/mysql.y"
                           { (yyval.intVal) = 1; /* ASC */ }
#line 1970 "mysql.tab.c"
    break;

  case 65: /* opt_asc_desc: ASC  */
#line 379 "grammars/mysql.y"
                   { (yyval.intVal) = 1; }
#line 1976 "mysql.tab.c"
    break;

  case 66: /* opt_asc_desc: DESC  */
#line 380 "grammars/mysql.y"
                    { (yyval.intVal) = 0; }
#line 1982 "mysql.tab.c"
    break;

  case 70: /* insert_statement: INSERT INTO IDENTIFIER opt_column_list VALUES value_list_list  */
#line 390 "grammars/mysql.y"
                 {
                     (yyval.insertStmt) = new InsertStmt(makeString((yyvsp[-3].strVal)), currLine, currCol);
                     if ((yyvsp[-2].stringList)) {
                         (yyval.insertStmt)->columnList = std::move(*(yyvsp[-2].stringList));
                         delete (yyvsp[-2].stringList);
                     }
                     if ((yyvsp[0].valuesListList)) {
                         (yyval.insertStmt)->valuesList = std::move(*(yyvsp[0].valuesListList));
                         delete (yyvsp[0].valuesListList);
                     }
                 }
#line 1998 "mysql.tab.c"
    break;

  case 71: /* insert_statement: INSERT INTO IDENTIFIER opt_column_list select_statement  */
#line 402 "grammars/mysql.y"
                 {
                     (yyval.insertStmt) = new InsertStmt(makeString((yyvsp[-2].strVal)), currLine, currCol);
                     if ((yyvsp[-1].stringList)) {
                         (yyval.insertStmt)->columnList = std::move(*(yyvsp[-1].stringList));
                         delete (yyvsp[-1].stringList);
                     }
                     (yyval.insertStmt)->selectStmt = StatementPtr((yyvsp[0].selectStmt));
                 }
#line 2011 "mysql.tab.c"
    break;

  case 72: /* opt_column_list: %empty  */
#line 412 "grammars/mysql.y"
                              { (yyval.stringList) = nullptr; }
#line 2017 "mysql.tab.c"
    break;

  case 73: /* opt_column_list: LPAREN identifier_list RPAREN  */
#line 413 "grammars/mysql.y"
                                                { (yyval.stringList) = (yyvsp[-1].stringList); }
#line 2023 "mysql.tab.c"
    break;

  case 74: /* value_list_list: LPAREN expression_list RPAREN  */
#line 417 "grammars/mysql.y"
                {
                    (yyval.valuesListList) = new std::vector<std::vector<ExpressionPtr>>();
                    if ((yyvsp[-1].expressionList)) {
                        (yyval.valuesListList)->emplace_back(std::move(*(yyvsp[-1].expressionList)));
                        delete (yyvsp[-1].expressionList);
                    }
                }
#line 2035 "mysql.tab.c"
    break;

  case 75: /* value_list_list: value_list_list COMMA LPAREN expression_list RPAREN  */
#line 425 "grammars/mysql.y"
                {
                    (yyval.valuesListList) = (yyvsp[-4].valuesListList);
                    if ((yyvsp[-1].expressionList)) {
                        (yyval.valuesListList)->emplace_back(std::move(*(yyvsp[-1].expressionList)));
                        delete (yyvsp[-1].expressionList);
                    }
                }
#line 2047 "mysql.tab.c"
    break;

  case 76: /* update_statement: UPDATE IDENTIFIER SET assignment_list opt_where_clause  */
#line 436 "grammars/mysql.y"
                 {
                     (yyval.updateStmt) = new UpdateStmt(makeString((yyvsp[-3].strVal)), currLine, currCol);
                     if ((yyvsp[-1].assignmentList)) {
                         (yyval.updateStmt)->assignments = std::move(*(yyvsp[-1].assignmentList));
                         delete (yyvsp[-1].assignmentList);
                     }
                     (yyval.updateStmt)->whereClause = ExpressionPtr((yyvsp[0].expression));
                 }
#line 2060 "mysql.tab.c"
    break;

  case 77: /* assignment_list: assignment  */
#line 447 "grammars/mysql.y"
                {
                    (yyval.assignmentList) = new std::vector<std::unique_ptr<Assignment>>();
                    if ((yyvsp[0].assignment)) {
                        (yyval.assignmentList)->emplace_back((yyvsp[0].assignment));
                    }
                }
#line 2071 "mysql.tab.c"
    break;

  case 78: /* assignment_list: assignment_list COMMA assignment  */
#line 454 "grammars/mysql.y"
                {
                    (yyval.assignmentList) = (yyvsp[-2].assignmentList);
                    if ((yyvsp[0].assignment)) {
                        (yyval.assignmentList)->emplace_back((yyvsp[0].assignment));
                    }
                }
#line 2082 "mysql.tab.c"
    break;

  case 79: /* assignment: IDENTIFIER EQ expression  */
#line 463 "grammars/mysql.y"
           {
               (yyval.assignment) = new Assignment(makeString((yyvsp[-2].strVal)), ExpressionPtr((yyvsp[0].expression)), currLine, currCol);
           }
#line 2090 "mysql.tab.c"
    break;

  case 80: /* delete_statement: DELETE FROM IDENTIFIER opt_where_clause  */
#line 470 "grammars/mysql.y"
                 {
                     (yyval.deleteStmt) = new DeleteStmt(makeString((yyvsp[-1].strVal)), currLine, currCol);
                     (yyval.deleteStmt)->whereClause = ExpressionPtr((yyvsp[0].expression));
                 }
#line 2099 "mysql.tab.c"
    break;

  case 81: /* create_table_statement: CREATE TABLE IDENTIFIER LPAREN column_definition_list RPAREN  */
#line 478 "grammars/mysql.y"
                       {
                           (yyval.createTableStmt) = new CreateTableStmt(makeString((yyvsp[-3].strVal)), currLine, currCol);
                           if ((yyvsp[-1].columnDefList)) {
                               (yyval.createTableStmt)->columns = std::move(*(yyvsp[-1].columnDefList));
                               delete (yyvsp[-1].columnDefList);
                           }
                       }
#line 2111 "mysql.tab.c"
    break;

  case 82: /* column_definition_list: column_definition  */
#line 488 "grammars/mysql.y"
                       {
                           (yyval.columnDefList) = new std::vector<std::unique_ptr<ColumnDef>>();
                           if ((yyvsp[0].columnDef)) {
                               (yyval.columnDefList)->emplace_back((yyvsp[0].columnDef));
                           }
                       }
#line 2122 "mysql.tab.c"
    break;

  case 83: /* column_definition_list: column_definition_list COMMA column_definition  */
#line 495 "grammars/mysql.y"
                       {
                           (yyval.columnDefList) = (yyvsp[-2].columnDefList);
                           if ((yyvsp[0].columnDef)) {
                               (yyval.columnDefList)->emplace_back((yyvsp[0].columnDef));
                           }
                       }
#line 2133 "mysql.tab.c"
    break;

  case 84: /* column_definition: IDENTIFIER DATATYPE opt_column_constraints  */
#line 504 "grammars/mysql.y"
                  {
                      (yyval.columnDef) = new ColumnDef(makeString((yyvsp[-2].strVal)), makeString((yyvsp[-1].strVal)), currLine, currCol);
                  }
#line 2141 "mysql.tab.c"
    break;

  case 95: /* create_database_statement: CREATE DATABASE IDENTIFIER  */
#line 525 "grammars/mysql.y"
                          {
                              (yyval.createDatabaseStmt) = new CreateDatabaseStmt(makeString((yyvsp[0].strVal)), currLine, currCol);
                          }
#line 2149 "mysql.tab.c"
    break;

  case 96: /* create_database_statement: CREATE SCHEMA IDENTIFIER  */
#line 529 "grammars/mysql.y"
                          {
                              (yyval.createDatabaseStmt) = new CreateDatabaseStmt(makeString((yyvsp[0].strVal)), currLine, currCol);
                          }
#line 2157 "mysql.tab.c"
    break;

  case 97: /* create_index_statement: CREATE opt_unique INDEX IDENTIFIER ON IDENTIFIER LPAREN identifier_list RPAREN  */
#line 536 "grammars/mysql.y"
                       {
                           (yyval.createIndexStmt) = new CreateIndexStmt(makeString((yyvsp[-5].strVal)), makeString((yyvsp[-3].strVal)), currLine, currCol);
                           (yyval.createIndexStmt)->isUnique = ((yyvsp[-7].intVal) != 0);
                           if ((yyvsp[-1].stringList)) {
                               (yyval.createIndexStmt)->columns = std::move(*(yyvsp[-1].stringList));
                               delete (yyvsp[-1].stringList);
                           }
                       }
#line 2170 "mysql.tab.c"
    break;

  case 98: /* opt_unique: %empty  */
#line 546 "grammars/mysql.y"
                         { (yyval.intVal) = 0; }
#line 2176 "mysql.tab.c"
    break;

  case 99: /* opt_unique: UNIQUE  */
#line 547 "grammars/mysql.y"
                    { (yyval.intVal) = 1; }
#line 2182 "mysql.tab.c"
    break;

  case 100: /* create_view_statement: CREATE VIEW IDENTIFIER AS select_statement  */
#line 552 "grammars/mysql.y"
                      {
                          (yyval.createViewStmt) = new CreateViewStmt(makeString((yyvsp[-2].strVal)), StatementPtr((yyvsp[0].selectStmt)), currLine, currCol);
                      }
#line 2190 "mysql.tab.c"
    break;

  case 101: /* drop_statement: DROP TABLE IDENTIFIER  */
#line 559 "grammars/mysql.y"
               {
                   (yyval.dropStmt) = new DropStmt(DropStmt::TABLE, makeString((yyvsp[0].strVal)), currLine, currCol);
               }
#line 2198 "mysql.tab.c"
    break;

  case 102: /* drop_statement: DROP DATABASE IDENTIFIER  */
#line 563 "grammars/mysql.y"
               {
                   (yyval.dropStmt) = new DropStmt(DropStmt::DATABASE, makeString((yyvsp[0].strVal)), currLine, currCol);
               }
#line 2206 "mysql.tab.c"
    break;

  case 103: /* drop_statement: DROP SCHEMA IDENTIFIER  */
#line 567 "grammars/mysql.y"
               {
                   (yyval.dropStmt) = new DropStmt(DropStmt::DATABASE, makeString((yyvsp[0].strVal)), currLine, currCol);
               }
#line 2214 "mysql.tab.c"
    break;

  case 104: /* drop_statement: DROP INDEX IDENTIFIER  */
#line 571 "grammars/mysql.y"
               {
                   (yyval.dropStmt) = new DropStmt(DropStmt::INDEX, makeString((yyvsp[0].strVal)), currLine, currCol);
               }
#line 2222 "mysql.tab.c"
    break;

  case 105: /* drop_statement: DROP VIEW IDENTIFIER  */
#line 575 "grammars/mysql.y"
               {
                   (yyval.dropStmt) = new DropStmt(DropStmt::VIEW, makeString((yyvsp[0].strVal)), currLine, currCol);
               }
#line 2230 "mysql.tab.c"
    break;

  case 106: /* alter_statement: ALTER TABLE IDENTIFIER ADD COLUMN column_definition  */
#line 582 "grammars/mysql.y"
                {
                    (yyval.alterStmt) = new AlterStmt(makeString((yyvsp[-3].strVal)), AlterStmt::ADD_COLUMN, currLine, currCol);
                    (yyval.alterStmt)->columnDef = std::unique_ptr<ColumnDef>((yyvsp[0].columnDef));
                }
#line 2239 "mysql.tab.c"
    break;

  case 107: /* alter_statement: ALTER TABLE IDENTIFIER DROP COLUMN IDENTIFIER  */
#line 587 "grammars/mysql.y"
                {
                    (yyval.alterStmt) = new AlterStmt(makeString((yyvsp[-3].strVal)), AlterStmt::DROP_COLUMN, currLine, currCol);
                    (yyval.alterStmt)->columnName = makeString((yyvsp[0].strVal));
                }
#line 2248 "mysql.tab.c"
    break;

  case 108: /* alter_statement: ALTER TABLE IDENTIFIER MODIFY COLUMN column_definition  */
#line 592 "grammars/mysql.y"
                {
                    (yyval.alterStmt) = new AlterStmt(makeString((yyvsp[-3].strVal)), AlterStmt::MODIFY_COLUMN, currLine, currCol);
                    (yyval.alterStmt)->columnDef = std::unique_ptr<ColumnDef>((yyvsp[0].columnDef));
                }
#line 2257 "mysql.tab.c"
    break;

  case 109: /* expression: primary_expression  */
#line 599 "grammars/mysql.y"
                                { (yyval.expression) = (yyvsp[0].expression); }
#line 2263 "mysql.tab.c"
    break;

  case 110: /* expression: expression PLUS expression  */
#line 601 "grammars/mysql.y"
           {
               (yyval.expression) = new BinaryOpExpr(makeString((yyvsp[-1].strVal)), ExpressionPtr((yyvsp[-2].expression)), ExpressionPtr((yyvsp[0].expression)), currLine, currCol);
           }
#line 2271 "mysql.tab.c"
    break;

  case 111: /* expression: expression MINUS expression  */
#line 605 "grammars/mysql.y"
           {
               (yyval.expression) = new BinaryOpExpr(makeString((yyvsp[-1].strVal)), ExpressionPtr((yyvsp[-2].expression)), ExpressionPtr((yyvsp[0].expression)), currLine, currCol);
           }
#line 2279 "mysql.tab.c"
    break;

  case 112: /* expression: expression ASTERISK expression  */
#line 609 "grammars/mysql.y"
           {
               (yyval.expression) = new BinaryOpExpr(makeString((yyvsp[-1].strVal)), ExpressionPtr((yyvsp[-2].expression)), ExpressionPtr((yyvsp[0].expression)), currLine, currCol);
           }
#line 2287 "mysql.tab.c"
    break;

  case 113: /* expression: expression DIVIDE expression  */
#line 613 "grammars/mysql.y"
           {
               (yyval.expression) = new BinaryOpExpr(makeString((yyvsp[-1].strVal)), ExpressionPtr((yyvsp[-2].expression)), ExpressionPtr((yyvsp[0].expression)), currLine, currCol);
           }
#line 2295 "mysql.tab.c"
    break;

  case 114: /* expression: expression MODULO expression  */
#line 617 "grammars/mysql.y"
           {
               (yyval.expression) = new BinaryOpExpr(makeString((yyvsp[-1].strVal)), ExpressionPtr((yyvsp[-2].expression)), ExpressionPtr((yyvsp[0].expression)), currLine, currCol);
           }
#line 2303 "mysql.tab.c"
    break;

  case 115: /* expression: expression CONCAT_OP expression  */
#line 621 "grammars/mysql.y"
           {
               (yyval.expression) = new BinaryOpExpr(makeString((yyvsp[-1].strVal)), ExpressionPtr((yyvsp[-2].expression)), ExpressionPtr((yyvsp[0].expression)), currLine, currCol);
           }
#line 2311 "mysql.tab.c"
    break;

  case 116: /* expression: expression EQ expression  */
#line 625 "grammars/mysql.y"
           {
               (yyval.expression) = new BinaryOpExpr(makeString((yyvsp[-1].strVal)), ExpressionPtr((yyvsp[-2].expression)), ExpressionPtr((yyvsp[0].expression)), currLine, currCol);
           }
#line 2319 "mysql.tab.c"
    break;

  case 117: /* expression: expression NE expression  */
#line 629 "grammars/mysql.y"
           {
               (yyval.expression) = new BinaryOpExpr(makeString((yyvsp[-1].strVal)), ExpressionPtr((yyvsp[-2].expression)), ExpressionPtr((yyvsp[0].expression)), currLine, currCol);
           }
#line 2327 "mysql.tab.c"
    break;

  case 118: /* expression: expression LT expression  */
#line 633 "grammars/mysql.y"
           {
               (yyval.expression) = new BinaryOpExpr(makeString((yyvsp[-1].strVal)), ExpressionPtr((yyvsp[-2].expression)), ExpressionPtr((yyvsp[0].expression)), currLine, currCol);
           }
#line 2335 "mysql.tab.c"
    break;

  case 119: /* expression: expression LE expression  */
#line 637 "grammars/mysql.y"
           {
               (yyval.expression) = new BinaryOpExpr(makeString((yyvsp[-1].strVal)), ExpressionPtr((yyvsp[-2].expression)), ExpressionPtr((yyvsp[0].expression)), currLine, currCol);
           }
#line 2343 "mysql.tab.c"
    break;

  case 120: /* expression: expression GT expression  */
#line 641 "grammars/mysql.y"
           {
               (yyval.expression) = new BinaryOpExpr(makeString((yyvsp[-1].strVal)), ExpressionPtr((yyvsp[-2].expression)), ExpressionPtr((yyvsp[0].expression)), currLine, currCol);
           }
#line 2351 "mysql.tab.c"
    break;

  case 121: /* expression: expression GE expression  */
#line 645 "grammars/mysql.y"
           {
               (yyval.expression) = new BinaryOpExpr(makeString((yyvsp[-1].strVal)), ExpressionPtr((yyvsp[-2].expression)), ExpressionPtr((yyvsp[0].expression)), currLine, currCol);
           }
#line 2359 "mysql.tab.c"
    break;

  case 122: /* expression: expression AND expression  */
#line 649 "grammars/mysql.y"
           {
               (yyval.expression) = new BinaryOpExpr("AND", ExpressionPtr((yyvsp[-2].expression)), ExpressionPtr((yyvsp[0].expression)), currLine, currCol);
           }
#line 2367 "mysql.tab.c"
    break;

  case 123: /* expression: expression OR expression  */
#line 653 "grammars/mysql.y"
           {
               (yyval.expression) = new BinaryOpExpr("OR", ExpressionPtr((yyvsp[-2].expression)), ExpressionPtr((yyvsp[0].expression)), currLine, currCol);
           }
#line 2375 "mysql.tab.c"
    break;

  case 124: /* expression: expression LIKE expression  */
#line 657 "grammars/mysql.y"
           {
               (yyval.expression) = new BinaryOpExpr("LIKE", ExpressionPtr((yyvsp[-2].expression)), ExpressionPtr((yyvsp[0].expression)), currLine, currCol);
           }
#line 2383 "mysql.tab.c"
    break;

  case 125: /* expression: expression ILIKE expression  */
#line 661 "grammars/mysql.y"
           {
               (yyval.expression) = new BinaryOpExpr("ILIKE", ExpressionPtr((yyvsp[-2].expression)), ExpressionPtr((yyvsp[0].expression)), currLine, currCol);
           }
#line 2391 "mysql.tab.c"
    break;

  case 126: /* expression: expression IN LPAREN expression_list RPAREN  */
#line 665 "grammars/mysql.y"
           {
               auto inExpr = new BinaryOpExpr("IN", ExpressionPtr((yyvsp[-4].expression)), nullptr, currLine, currCol);
               // Store the list in a special way - this might need custom handling
               (yyval.expression) = inExpr;
           }
#line 2401 "mysql.tab.c"
    break;

  case 127: /* expression: expression BETWEEN expression AND expression  */
#line 671 "grammars/mysql.y"
           {
               auto betweenExpr = new BinaryOpExpr("BETWEEN", ExpressionPtr((yyvsp[-4].expression)), ExpressionPtr((yyvsp[-2].expression)), currLine, currCol);
               // The third expression ($5) would need special handling in semantic analysis
               (yyval.expression) = betweenExpr;
           }
#line 2411 "mysql.tab.c"
    break;

  case 128: /* expression: expression IS NULLSYM  */
#line 677 "grammars/mysql.y"
           {
               (yyval.expression) = new BinaryOpExpr("IS NULL", ExpressionPtr((yyvsp[-2].expression)), nullptr, currLine, currCol);
           }
#line 2419 "mysql.tab.c"
    break;

  case 129: /* expression: expression IS NOT NULLSYM  */
#line 681 "grammars/mysql.y"
           {
               (yyval.expression) = new BinaryOpExpr("IS NOT NULL", ExpressionPtr((yyvsp[-3].expression)), nullptr, currLine, currCol);
           }
#line 2427 "mysql.tab.c"
    break;

  case 130: /* expression: NOT expression  */
#line 685 "grammars/mysql.y"
           {
               (yyval.expression) = new UnaryOpExpr("NOT", ExpressionPtr((yyvsp[0].expression)), currLine, currCol);
           }
#line 2435 "mysql.tab.c"
    break;

  case 131: /* expression: MINUS expression  */
#line 689 "grammars/mysql.y"
           {
               (yyval.expression) = new UnaryOpExpr("-", ExpressionPtr((yyvsp[0].expression)), currLine, currCol);
           }
#line 2443 "mysql.tab.c"
    break;

  case 132: /* expression: PLUS expression  */
#line 693 "grammars/mysql.y"
           {
               (yyval.expression) = new UnaryOpExpr("+", ExpressionPtr((yyvsp[0].expression)), currLine, currCol);
           }
#line 2451 "mysql.tab.c"
    break;

  case 133: /* expression: LPAREN expression RPAREN  */
#line 696 "grammars/mysql.y"
                                      { (yyval.expression) = (yyvsp[-1].expression); }
#line 2457 "mysql.tab.c"
    break;

  case 134: /* expression: case_expression  */
#line 697 "grammars/mysql.y"
                             { (yyval.expression) = (yyvsp[0].expression); }
#line 2463 "mysql.tab.c"
    break;

  case 135: /* expression: function_call  */
#line 698 "grammars/mysql.y"
                           { (yyval.expression) = (yyvsp[0].expression); }
#line 2469 "mysql.tab.c"
    break;

  case 136: /* primary_expression: IDENTIFIER  */
#line 702 "grammars/mysql.y"
                   {
                       (yyval.expression) = new IdentifierExpr(makeString((yyvsp[0].strVal)), currLine, currCol);
                   }
#line 2477 "mysql.tab.c"
    break;

  case 137: /* primary_expression: IDENTIFIER DOT IDENTIFIER  */
#line 706 "grammars/mysql.y"
                   {
                       (yyval.expression) = new IdentifierExpr(makeString((yyvsp[-2].strVal)), makeString((yyvsp[0].strVal)), currLine, currCol);
                   }
#line 2485 "mysql.tab.c"
    break;

  case 138: /* primary_expression: STRINGVAL  */
#line 710 "grammars/mysql.y"
                   {
                       (yyval.expression) = new LiteralExpr(LiteralExpr::STRING, makeString((yyvsp[0].strVal)), currLine, currCol);
                   }
#line 2493 "mysql.tab.c"
    break;

  case 139: /* primary_expression: INTVAL  */
#line 714 "grammars/mysql.y"
                   {
                       (yyval.expression) = new LiteralExpr(LiteralExpr::INTEGER, makeString((yyvsp[0].strVal)), currLine, currCol);
                   }
#line 2501 "mysql.tab.c"
    break;

  case 140: /* primary_expression: FLOATVAL  */
#line 718 "grammars/mysql.y"
                   {
                       (yyval.expression) = new LiteralExpr(LiteralExpr::FLOAT, makeString((yyvsp[0].strVal)), currLine, currCol);
                   }
#line 2509 "mysql.tab.c"
    break;

  case 141: /* primary_expression: NULLSYM  */
#line 722 "grammars/mysql.y"
                   {
                       (yyval.expression) = new LiteralExpr(LiteralExpr::NULL_VAL, "NULL", currLine, currCol);
                   }
#line 2517 "mysql.tab.c"
    break;

  case 142: /* function_call: FUNCTION LPAREN opt_expression_list RPAREN  */
#line 728 "grammars/mysql.y"
              {
                  (yyval.expression) = new FunctionCallExpr(makeString((yyvsp[-3].strVal)), currLine, currCol);
                  if ((yyvsp[-1].expressionList)) {
                      (yyval.expression)->arguments = std::move(*(yyvsp[-1].expressionList));
                      delete (yyvsp[-1].expressionList);
                  }
              }
#line 2529 "mysql.tab.c"
    break;

  case 143: /* function_call: FUNCTION LPAREN DISTINCT expression_list RPAREN  */
#line 736 "grammars/mysql.y"
              {
                  (yyval.expression) = new FunctionCallExpr(makeString((yyvsp[-4].strVal)), currLine, currCol);
                  (yyval.expression)->isDistinct = true;
                  if ((yyvsp[-1].expressionList)) {
                      (yyval.expression)->arguments = std::move(*(yyvsp[-1].expressionList));
                      delete (yyvsp[-1].expressionList);
                  }
              }
#line 2542 "mysql.tab.c"
    break;

  case 144: /* function_call: FUNCTION LPAREN ASTERISK RPAREN  */
#line 745 "grammars/mysql.y"
              {
                  (yyval.expression) = new FunctionCallExpr(makeString((yyvsp[-3].strVal)), currLine, currCol);
                  (yyval.expression)->hasAsterisk = true;
              }
#line 2551 "mysql.tab.c"
    break;

  case 145: /* case_expression: CASE expression when_clause_list opt_else_clause END  */
#line 752 "grammars/mysql.y"
                {
                    (yyval.expression) = new CaseExpr(currLine, currCol);
                    (yyval.expression)->caseExpr = ExpressionPtr((yyvsp[-3].expression));
                    if ((yyvsp[-2].whenClauseList)) {
                        (yyval.expression)->whenClauses = std::move(*(yyvsp[-2].whenClauseList));
                        delete (yyvsp[-2].whenClauseList);
                    }
                    (yyval.expression)->elseExpr = ExpressionPtr((yyvsp[-1].expression));
                }
#line 2565 "mysql.tab.c"
    break;

  case 146: /* case_expression: CASE when_clause_list opt_else_clause END  */
#line 762 "grammars/mysql.y"
                {
                    (yyval.expression) = new CaseExpr(currLine, currCol);
                    if ((yyvsp[-2].whenClauseList)) {
                        (yyval.expression)->whenClauses = std::move(*(yyvsp[-2].whenClauseList));
                        delete (yyvsp[-2].whenClauseList);
                    }
                    (yyval.expression)->elseExpr = ExpressionPtr((yyvsp[-1].expression));
                }
#line 2578 "mysql.tab.c"
    break;

  case 147: /* when_clause_list: WHEN expression THEN expression  */
#line 773 "grammars/mysql.y"
                 {
                     (yyval.whenClauseList) = new std::vector<std::pair<ExpressionPtr, ExpressionPtr>>();
                     (yyval.whenClauseList)->emplace_back(ExpressionPtr((yyvsp[-2].expression)), ExpressionPtr((yyvsp[0].expression)));
                 }
#line 2587 "mysql.tab.c"
    break;

  case 148: /* when_clause_list: when_clause_list WHEN expression THEN expression  */
#line 778 "grammars/mysql.y"
                 {
                     (yyval.whenClauseList) = (yyvsp[-4].whenClauseList);
                     (yyval.whenClauseList)->emplace_back(ExpressionPtr((yyvsp[-2].expression)), ExpressionPtr((yyvsp[0].expression)));
                 }
#line 2596 "mysql.tab.c"
    break;

  case 149: /* opt_else_clause: %empty  */
#line 784 "grammars/mysql.y"
                              { (yyval.expression) = nullptr; }
#line 2602 "mysql.tab.c"
    break;

  case 150: /* opt_else_clause: ELSE expression  */
#line 785 "grammars/mysql.y"
                                  { (yyval.expression) = (yyvsp[0].expression); }
#line 2608 "mysql.tab.c"
    break;

  case 151: /* expression_list: expression  */
#line 790 "grammars/mysql.y"
                {
                    (yyval.expressionList) = new std::vector<ExpressionPtr>();
                    if ((yyvsp[0].expression)) {
                        (yyval.expressionList)->emplace_back((yyvsp[0].expression));
                    }
                }
#line 2619 "mysql.tab.c"
    break;

  case 152: /* expression_list: expression_list COMMA expression  */
#line 797 "grammars/mysql.y"
                {
                    (yyval.expressionList) = (yyvsp[-2].expressionList);
                    if ((yyvsp[0].expression)) {
                        (yyval.expressionList)->emplace_back((yyvsp[0].expression));
                    }
                }
#line 2630 "mysql.tab.c"
    break;

  case 153: /* opt_expression_list: %empty  */
#line 805 "grammars/mysql.y"
                                  { (yyval.expressionList) = nullptr; }
#line 2636 "mysql.tab.c"
    break;

  case 154: /* opt_expression_list: expression_list  */
#line 806 "grammars/mysql.y"
                                      { (yyval.expressionList) = (yyvsp[0].expressionList); }
#line 2642 "mysql.tab.c"
    break;

  case 155: /* identifier_list: IDENTIFIER  */
#line 810 "grammars/mysql.y"
                {
                    (yyval.stringList) = new std::vector<std::string>();
                    (yyval.stringList)->push_back(makeString((yyvsp[0].strVal)));
                }
#line 2651 "mysql.tab.c"
    break;

  case 156: /* identifier_list: identifier_list COMMA IDENTIFIER  */
#line 815 "grammars/mysql.y"
                {
                    (yyval.stringList) = (yyvsp[-2].stringList);
                    (yyval.stringList)->push_back(makeString((yyvsp[0].strVal)));
                }
#line 2660 "mysql.tab.c"
    break;


#line 2664 "mysql.tab.c"

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

#line 821 "grammars/mysql.y"


void yyerror(const char *s) {
    setSyntaxError(std::string(s), currLine, currCol);
}
