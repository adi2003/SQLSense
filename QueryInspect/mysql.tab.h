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
/* "%code requires" blocks.  */
#line 1 "grammars/mysql.y"

    #include <iostream>
    #include <vector>
    #include <string>
    #include <memory>
    #include <utility>
    #include "../include/AST.h"

#line 58 "mysql.tab.h"

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
    COLUMN = 285,                  /* COLUMN  */
    JOIN = 286,                    /* JOIN  */
    INNER = 287,                   /* INNER  */
    LEFT = 288,                    /* LEFT  */
    RIGHT = 289,                   /* RIGHT  */
    FULL = 290,                    /* FULL  */
    OUTER = 291,                   /* OUTER  */
    CROSS = 292,                   /* CROSS  */
    ON = 293,                      /* ON  */
    USING = 294,                   /* USING  */
    GROUP = 295,                   /* GROUP  */
    BY = 296,                      /* BY  */
    HAVING = 297,                  /* HAVING  */
    ORDER = 298,                   /* ORDER  */
    ASC = 299,                     /* ASC  */
    DESC = 300,                    /* DESC  */
    DISTINCT = 301,                /* DISTINCT  */
    ALL = 302,                     /* ALL  */
    UNION = 303,                   /* UNION  */
    INTERSECT = 304,               /* INTERSECT  */
    EXCEPT = 305,                  /* EXCEPT  */
    LIMIT = 306,                   /* LIMIT  */
    OFFSET = 307,                  /* OFFSET  */
    TOP = 308,                     /* TOP  */
    IS = 309,                      /* IS  */
    NULLSYM = 310,                 /* NULLSYM  */
    LIKE = 311,                    /* LIKE  */
    ILIKE = 312,                   /* ILIKE  */
    IN = 313,                      /* IN  */
    BETWEEN = 314,                 /* BETWEEN  */
    EXISTS = 315,                  /* EXISTS  */
    CASE = 316,                    /* CASE  */
    WHEN = 317,                    /* WHEN  */
    THEN = 318,                    /* THEN  */
    ELSE = 319,                    /* ELSE  */
    END = 320,                     /* END  */
    PRIMARY = 321,                 /* PRIMARY  */
    KEY = 322,                     /* KEY  */
    FOREIGN = 323,                 /* FOREIGN  */
    REFERENCES = 324,              /* REFERENCES  */
    UNIQUE = 325,                  /* UNIQUE  */
    CHECK = 326,                   /* CHECK  */
    DEFAULT = 327,                 /* DEFAULT  */
    AUTO_INCREMENT = 328,          /* AUTO_INCREMENT  */
    NOT_NULL = 329,                /* NOT_NULL  */
    ADD = 330,                     /* ADD  */
    MODIFY = 331,                  /* MODIFY  */
    EQ = 332,                      /* EQ  */
    NE = 333,                      /* NE  */
    LT = 334,                      /* LT  */
    LE = 335,                      /* LE  */
    GT = 336,                      /* GT  */
    GE = 337,                      /* GE  */
    PLUS = 338,                    /* PLUS  */
    MINUS = 339,                   /* MINUS  */
    ASTERISK = 340,                /* ASTERISK  */
    DIVIDE = 341,                  /* DIVIDE  */
    MODULO = 342,                  /* MODULO  */
    CONCAT_OP = 343,               /* CONCAT_OP  */
    COMMA = 344,                   /* COMMA  */
    SEMICOLON = 345,               /* SEMICOLON  */
    LPAREN = 346,                  /* LPAREN  */
    RPAREN = 347,                  /* RPAREN  */
    DOT = 348,                     /* DOT  */
    QUESTION = 349,                /* QUESTION  */
    UMINUS = 350,                  /* UMINUS  */
    UPLUS = 351                    /* UPLUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 38 "grammars/mysql.y"

    char* strVal;
    int intVal;
    double floatVal;
    
    // AST node pointers
    ASTNode* astNode;
    Expression* expression;
    Statement* statement;
    SelectStmt* selectStmt;
    InsertStmt* insertStmt;
    UpdateStmt* updateStmt;
    DeleteStmt* deleteStmt;
    CreateTableStmt* createTableStmt;
    CreateDatabaseStmt* createDatabaseStmt;
    CreateIndexStmt* createIndexStmt;
    CreateViewStmt* createViewStmt;
    DropStmt* dropStmt;
    AlterStmt* alterStmt;
    
    TableRef* tableRef;
    JoinClause* joinClause;
    SelectItem* selectItem;
    ColumnDef* columnDef;
    Assignment* assignment;
    
    // Vector pointers for lists
    std::vector<StatementPtr>* statementList;
    std::vector<ExpressionPtr>* expressionList;
    std::vector<std::unique_ptr<SelectItem>>* selectItemList;
    std::vector<std::unique_ptr<TableRef>>* tableRefList;
    std::vector<std::unique_ptr<ColumnDef>>* columnDefList;
    std::vector<std::unique_ptr<Assignment>>* assignmentList;
    std::vector<std::string>* stringList;
    std::vector<std::vector<ExpressionPtr>>* valuesListList;
    std::vector<std::pair<ExpressionPtr, ExpressionPtr>>* whenClauseList;
    std::vector<std::pair<ExpressionPtr, bool>>* orderByList;

#line 210 "mysql.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_MYSQL_TAB_H_INCLUDED  */
