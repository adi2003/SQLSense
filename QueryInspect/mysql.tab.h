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

#ifndef YY_YY_MYSQL_TAB_H_INCLUDED
# define YY_YY_MYSQL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    STRINGVAL = 259,               /* STRINGVAL  */
    DATATYPE = 260,                /* DATATYPE  */
    FUNCTION = 261,                /* FUNCTION  */
    INTVAL = 262,                  /* INTVAL  */
    FLOATVAL = 263,                /* FLOATVAL  */
    SELECT = 264,                  /* SELECT  */
    FROM = 265,                    /* FROM  */
    WHERE = 266,                   /* WHERE  */
    AS = 267,                      /* AS  */
    AND = 268,                     /* AND  */
    OR = 269,                      /* OR  */
    NOT = 270,                     /* NOT  */
    INSERT = 271,                  /* INSERT  */
    INTO = 272,                    /* INTO  */
    VALUES = 273,                  /* VALUES  */
    UPDATE = 274,                  /* UPDATE  */
    SET = 275,                     /* SET  */
    DELETE = 276,                  /* DELETE  */
    CREATE = 277,                  /* CREATE  */
    DROP = 278,                    /* DROP  */
    ALTER = 279,                   /* ALTER  */
    TABLE = 280,                   /* TABLE  */
    DATABASE = 281,                /* DATABASE  */
    SCHEMA = 282,                  /* SCHEMA  */
    INDEX = 283,                   /* INDEX  */
    VIEW = 284,                    /* VIEW  */
    JOIN = 285,                    /* JOIN  */
    INNER = 286,                   /* INNER  */
    LEFT = 287,                    /* LEFT  */
    RIGHT = 288,                   /* RIGHT  */
    FULL = 289,                    /* FULL  */
    OUTER = 290,                   /* OUTER  */
    CROSS = 291,                   /* CROSS  */
    ON = 292,                      /* ON  */
    USING = 293,                   /* USING  */
    GROUP = 294,                   /* GROUP  */
    BY = 295,                      /* BY  */
    HAVING = 296,                  /* HAVING  */
    ORDER = 297,                   /* ORDER  */
    ASC = 298,                     /* ASC  */
    DESC = 299,                    /* DESC  */
    DISTINCT = 300,                /* DISTINCT  */
    ALL = 301,                     /* ALL  */
    UNION = 302,                   /* UNION  */
    INTERSECT = 303,               /* INTERSECT  */
    EXCEPT = 304,                  /* EXCEPT  */
    LIMIT = 305,                   /* LIMIT  */
    OFFSET = 306,                  /* OFFSET  */
    TOP = 307,                     /* TOP  */
    IS = 308,                      /* IS  */
    NULLSYM = 309,                 /* NULLSYM  */
    LIKE = 310,                    /* LIKE  */
    ILIKE = 311,                   /* ILIKE  */
    IN = 312,                      /* IN  */
    BETWEEN = 313,                 /* BETWEEN  */
    EXISTS = 314,                  /* EXISTS  */
    CASE = 315,                    /* CASE  */
    WHEN = 316,                    /* WHEN  */
    THEN = 317,                    /* THEN  */
    ELSE = 318,                    /* ELSE  */
    END = 319,                     /* END  */
    PRIMARY = 320,                 /* PRIMARY  */
    KEY = 321,                     /* KEY  */
    FOREIGN = 322,                 /* FOREIGN  */
    REFERENCES = 323,              /* REFERENCES  */
    UNIQUE = 324,                  /* UNIQUE  */
    CHECK = 325,                   /* CHECK  */
    DEFAULT = 326,                 /* DEFAULT  */
    AUTO_INCREMENT = 327,          /* AUTO_INCREMENT  */
    NOT_NULL = 328,                /* NOT_NULL  */
    ADD = 329,                     /* ADD  */
    MODIFY = 330,                  /* MODIFY  */
    EQ = 331,                      /* EQ  */
    NE = 332,                      /* NE  */
    LT = 333,                      /* LT  */
    LE = 334,                      /* LE  */
    GT = 335,                      /* GT  */
    GE = 336,                      /* GE  */
    PLUS = 337,                    /* PLUS  */
    MINUS = 338,                   /* MINUS  */
    ASTERISK = 339,                /* ASTERISK  */
    DIVIDE = 340,                  /* DIVIDE  */
    MODULO = 341,                  /* MODULO  */
    CONCAT_OP = 342,               /* CONCAT_OP  */
    COMMA = 343,                   /* COMMA  */
    SEMICOLON = 344,               /* SEMICOLON  */
    LPAREN = 345,                  /* LPAREN  */
    RPAREN = 346,                  /* RPAREN  */
    DOT = 347,                     /* DOT  */
    QUESTION = 348,                /* QUESTION  */
    UMINUS = 349,                  /* UMINUS  */
    UPLUS = 350                    /* UPLUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 19 "grammars/mysql.y"

    char* strVal;
    int intVal;
    double floatVal;

#line 165 "mysql.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_MYSQL_TAB_H_INCLUDED  */
