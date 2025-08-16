%{
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
%}

%union {
    char* strVal;
    int intVal;
    double floatVal;
}

/* Tokens with semantic values */
%token <strVal> IDENTIFIER STRINGVAL DATATYPE FUNCTION
%token <strVal> INTVAL FLOATVAL

/* SQL Keywords */
%token SELECT FROM WHERE AS AND OR NOT
%token INSERT INTO VALUES UPDATE SET DELETE
%token CREATE DROP ALTER TABLE DATABASE SCHEMA INDEX VIEW
%token JOIN INNER LEFT RIGHT FULL OUTER CROSS ON USING
%token GROUP BY HAVING ORDER ASC DESC DISTINCT ALL
%token UNION INTERSECT EXCEPT
%token LIMIT OFFSET TOP
%token IS NULLSYM LIKE ILIKE IN BETWEEN EXISTS
%token CASE WHEN THEN ELSE END
%token PRIMARY KEY FOREIGN REFERENCES UNIQUE CHECK DEFAULT AUTO_INCREMENT NOT_NULL
%token ADD MODIFY

/* Operators */
%token <strVal> EQ NE LT LE GT GE
%token <strVal> PLUS MINUS ASTERISK DIVIDE MODULO CONCAT_OP

/* Delimiters */
%token COMMA SEMICOLON LPAREN RPAREN DOT QUESTION

/* Precedence and Associativity */
%left OR
%left AND
%right NOT
%left EQ NE LT LE GT GE
%left LIKE ILIKE IN BETWEEN
%left PLUS MINUS CONCAT_OP
%left ASTERISK DIVIDE MODULO
%right UMINUS UPLUS
%left DOT

%start sql_statement_list

%%

/* ---------------- Top Level ---------------- */
sql_statement_list : sql_statement
                   | sql_statement_list sql_statement
                   ;

sql_statement : statement SEMICOLON     { printf("Statement parsed successfully\n"); }
              | statement               { printf("Statement parsed (missing semicolon)\n"); }
              ;

statement : select_statement            { printf("Parsed SELECT statement\n"); }
          | insert_statement            { printf("Parsed INSERT statement\n"); }
          | update_statement            { printf("Parsed UPDATE statement\n"); }
          | delete_statement            { printf("Parsed DELETE statement\n"); }
          | create_statement            { printf("Parsed CREATE statement\n"); }
          | drop_statement              { printf("Parsed DROP statement\n"); }
          | alter_statement             { printf("Parsed ALTER statement\n"); }
          ;

/* ---------------- SELECT Statement ---------------- */
select_statement : select_clause from_clause_opt where_clause_opt 
                   group_clause_opt having_clause_opt order_clause_opt limit_clause_opt
                 ;

select_clause : SELECT opt_distinct select_list
              ;

opt_distinct : /* empty */
             | DISTINCT
             | ALL
             ;

select_list : ASTERISK
            | select_item_list
            ;

select_item_list : select_item
                 | select_item_list COMMA select_item
                 ;

select_item : expression opt_alias
            ;

expression : primary_expression
           | expression PLUS expression
           | expression MINUS expression
           | expression ASTERISK expression
           | expression DIVIDE expression
           | expression MODULO expression
           | expression CONCAT_OP expression
           | PLUS expression %prec UPLUS
           | MINUS expression %prec UMINUS
           | LPAREN expression RPAREN
           | function_call
           | case_expression
           ;

primary_expression : IDENTIFIER
                   | IDENTIFIER DOT IDENTIFIER
                   | IDENTIFIER DOT ASTERISK
                   | INTVAL
                   | FLOATVAL
                   | STRINGVAL
                   | NULLSYM
                   ;

function_call : FUNCTION LPAREN opt_expression_list RPAREN
              | FUNCTION LPAREN ASTERISK RPAREN
              | FUNCTION LPAREN DISTINCT expression RPAREN
              ;

opt_expression_list : /* empty */
                    | expression_list
                    ;

expression_list : expression
                | expression_list COMMA expression
                ;

/* Fixed CASE expression to support both simple and searched CASE */
case_expression : CASE when_list opt_else_clause END
                | CASE expression when_list_simple opt_else_clause END
                ;

/* Searched CASE: CASE WHEN condition THEN value ... */
when_list : WHEN condition THEN expression
          | when_list WHEN condition THEN expression
          ;

/* Simple CASE: CASE expr WHEN value THEN result ... */
when_list_simple : WHEN expression THEN expression
                 | when_list_simple WHEN expression THEN expression
                 ;

opt_else_clause : /* empty */
                | ELSE expression
                ;

opt_alias : /* empty */
          | AS IDENTIFIER
          | IDENTIFIER
          ;

/* ---------------- FROM Clause ---------------- */
from_clause_opt : /* empty */
                | from_clause
                ;

from_clause : FROM table_reference_list
            ;

table_reference_list : table_reference
                     | table_reference_list COMMA table_reference
                     ;

table_reference : table_factor join_list_opt
                ;

table_factor : IDENTIFIER opt_alias
             | LPAREN select_statement RPAREN opt_alias
             ;

join_list_opt : /* empty */
              | join_list_opt join_clause
              ;

join_clause : join_type JOIN table_factor join_condition_opt
            ;

join_type : /* empty */      /* INNER JOIN */
          | INNER
          | LEFT opt_outer
          | RIGHT opt_outer
          | FULL opt_outer
          | CROSS
          ;

opt_outer : /* empty */
          | OUTER
          ;

join_condition_opt : /* empty */
                   | ON condition
                   | USING LPAREN identifier_list RPAREN
                   ;

identifier_list : IDENTIFIER
                | identifier_list COMMA IDENTIFIER
                ;

/* ---------------- WHERE Clause ---------------- */
where_clause_opt : /* empty */
                 | WHERE condition
                 ;

condition : condition OR condition
          | condition AND condition
          | NOT condition
          | LPAREN condition RPAREN
          | predicate
          ;

predicate : expression comparison_operator expression
          | expression IS NULLSYM
          | expression IS NOT NULLSYM
          | expression LIKE expression
          | expression ILIKE expression
          | expression IN LPAREN expression_list RPAREN
          | expression IN LPAREN select_statement RPAREN
          | expression NOT IN LPAREN expression_list RPAREN
          | expression NOT IN LPAREN select_statement RPAREN
          | expression BETWEEN expression AND expression
          | expression NOT BETWEEN expression AND expression
          | EXISTS LPAREN select_statement RPAREN
          | NOT EXISTS LPAREN select_statement RPAREN
          ;

comparison_operator : EQ | NE | LT | LE | GT | GE
                    ;

/* ---------------- GROUP BY Clause ---------------- */
group_clause_opt : /* empty */
                 | GROUP BY expression_list
                 ;

having_clause_opt : /* empty */
                  | HAVING condition
                  ;

/* ---------------- ORDER BY Clause ---------------- */
order_clause_opt : /* empty */
                 | ORDER BY order_item_list
                 ;

order_item_list : order_item
                | order_item_list COMMA order_item
                ;

order_item : expression opt_order_direction
           ;

opt_order_direction : /* empty */
                    | ASC
                    | DESC
                    ;

/* ---------------- LIMIT Clause ---------------- */
limit_clause_opt : /* empty */
                 | LIMIT INTVAL
                 | LIMIT INTVAL OFFSET INTVAL
                 | OFFSET INTVAL
                 ;

/* ---------------- INSERT Statement ---------------- */
insert_statement : INSERT INTO IDENTIFIER opt_column_list VALUES value_list_list
                 | INSERT INTO IDENTIFIER opt_column_list select_statement
                 | INSERT INTO IDENTIFIER VALUES value_list_list  /* No column list */
                 ;

opt_column_list : /* empty */
                | LPAREN identifier_list RPAREN
                ;

value_list_list : LPAREN expression_list RPAREN
                | value_list_list COMMA LPAREN expression_list RPAREN
                ;

/* ---------------- UPDATE Statement ---------------- */
update_statement : UPDATE IDENTIFIER SET assignment_list where_clause_opt
                 ;

assignment_list : assignment
                | assignment_list COMMA assignment
                ;

assignment : IDENTIFIER EQ expression
           ;

/* ---------------- DELETE Statement ---------------- */
delete_statement : DELETE FROM IDENTIFIER where_clause_opt
                 ;

/* ---------------- CREATE Statements ---------------- */
create_statement : create_table_statement
                 | create_database_statement
                 | create_index_statement
                 | create_view_statement
                 ;

create_table_statement : CREATE TABLE IDENTIFIER LPAREN column_definition_list RPAREN
                       ;

column_definition_list : column_definition
                       | column_definition_list COMMA column_definition
                       ;

column_definition : IDENTIFIER DATATYPE opt_column_constraints
                  ;

opt_column_constraints : /* empty */
                       | column_constraints
                       ;

column_constraints : column_constraint
                   | column_constraints column_constraint
                   ;

column_constraint : NOT NULLSYM
                  | NULLSYM
                  | PRIMARY KEY
                  | UNIQUE
                  | AUTO_INCREMENT
                  | DEFAULT expression
                  | CHECK LPAREN condition RPAREN
                  | REFERENCES IDENTIFIER opt_column_list
                  ;

create_database_statement : CREATE DATABASE IDENTIFIER
                          | CREATE SCHEMA IDENTIFIER
                          ;

create_index_statement : CREATE opt_unique INDEX IDENTIFIER ON IDENTIFIER LPAREN identifier_list RPAREN
                       ;

opt_unique : /* empty */
           | UNIQUE
           ;

create_view_statement : CREATE VIEW IDENTIFIER AS select_statement
                      ;

/* ---------------- DROP Statements ---------------- */
drop_statement : DROP TABLE IDENTIFIER
               | DROP DATABASE IDENTIFIER
               | DROP SCHEMA IDENTIFIER
               | DROP INDEX IDENTIFIER
               | DROP VIEW IDENTIFIER
               ;

/* ---------------- ALTER Statements ---------------- */
alter_statement : ALTER TABLE IDENTIFIER alter_table_action
                ;

alter_table_action : ADD IDENTIFIER DATATYPE opt_column_constraints
                   | DROP IDENTIFIER
                   | MODIFY IDENTIFIER DATATYPE opt_column_constraints
                   | ADD PRIMARY KEY LPAREN identifier_list RPAREN
                   | DROP PRIMARY KEY
                   ;

%%

void yyerror(const char *s) {
    // Use the lexer's error reporting system
    std::string error_msg = "Parse error: ";
    error_msg += s;
    setSyntaxError(error_msg, currLine, currCol);
    fprintf(stderr, "Parse error: %s at line %d, column %d\n", s, currLine, currCol);
}