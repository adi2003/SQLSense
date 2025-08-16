%{
#include <string>
#include <cstring>
#include <iostream>
#include <cstdlib>

extern int currLine;
extern int currCol;

// Global variables for error handling
std::string syntaxError;
int errorLine = -1;
int errorColumn = -1;

// Forward declarations
int yylex();
void yyerror(const char* s);

// Functions called from C++ code
std::string getSyntaxError() { return syntaxError; }
int getErrorLine() { return errorLine; }
int getErrorColumn() { return errorColumn; }
%}

/* semantic value: we only carry C strings (char*) for tokens/nonterminals that hold text */
%union {
    char* strVal;
}

/* Tokens carrying string pointers (must match tokens returned by the lexer) */
%token <strVal> SELECT FROM WHERE IDENTIFIER INTVAL STRINGVAL COMPOP
%token <strVal> UPDATE SET INSERT INTO VALUES DELETE CREATE TABLE DROP ALTER ADD
%token <strVal> JOIN INNER LEFT RIGHT FULL OUTER ON GROUPBY ORDERBY ASC DESC DISTINCT
%token <strVal> HAVING LIMIT OFFSET AS PRIMARY KEY FOREIGN REFERENCES NULLVAL DEFAULT
%token <strVal> CHECK UNIQUE MODIFY NOT AND OR

/* Only declare types for nonterminals that actually return values */
%type <strVal> literal data_type

/* FIXED: Proper precedence and associativity for boolean operators */
%left OR
%left AND
%right NOT

/* Only apply destructor to typed nonterminals */
%destructor { free($$); } <strVal>

%%

/* entry point: allow multiple statements */
entry
    : statement_list
    ;

statement_list
    : /* empty */
    | statement_list statement
    ;

statement
    : query ';'                { /* parsed a query */ }
    | query                    { /* allow queries without semicolon */ }
    ;

/* Support all major SQL statement types */
query
    : select_statement
    | insert_statement
    | update_statement
    | delete_statement
    | create_statement
    | drop_statement
    | alter_statement
    ;

/* SELECT statements with full feature support */
select_statement
    : SELECT opt_distinct column_list FROM table_list opt_join_list opt_where opt_group_by opt_having opt_order_by opt_limit
        { free($1); free($4); }
    ;

opt_distinct
    : /* empty */
    | DISTINCT              { free($1); }
    ;

column_list
    : '*'
    | column_spec
    | column_list ',' column_spec
    ;

column_spec
    : IDENTIFIER            { free($1); }
    | IDENTIFIER AS IDENTIFIER { free($1); free($2); free($3); }
    ;

table_list
    : table_ref
    | table_list ',' table_ref
    ;

table_ref
    : IDENTIFIER            { free($1); }
    | IDENTIFIER AS IDENTIFIER { free($1); free($2); free($3); }
    ;

/* JOIN support */
opt_join_list
    : /* empty */
    | join_list
    ;

join_list
    : join_clause
    | join_list join_clause
    ;

join_clause
    : join_type JOIN table_ref ON condition
        { free($2); free($4); }
    | JOIN table_ref ON condition
        { free($1); free($3); }
    ;

join_type
    : INNER                 { free($1); }
    | LEFT                  { free($1); }
    | RIGHT                 { free($1); }
    | FULL                  { free($1); }
    | LEFT OUTER            { free($1); free($2); }
    | RIGHT OUTER           { free($1); free($2); }
    | FULL OUTER            { free($1); free($2); }
    ;

/* WHERE clause */
opt_where
    : /* empty */
    | WHERE condition       { free($1); }
    ;

/* Boolean expressions with proper precedence */
condition
    : condition OR condition    { free($2); }
    | condition AND condition   { free($2); }
    | NOT condition             { free($1); }
    | '(' condition ')'
    | predicate
    ;

predicate
    : IDENTIFIER COMPOP literal
        { free($1); free($2); free($3); }
    | IDENTIFIER COMPOP IDENTIFIER
        { free($1); free($2); free($3); }
    | literal COMPOP IDENTIFIER
        { free($1); free($2); free($3); }
    ;

/* GROUP BY clause */
opt_group_by
    : /* empty */
    | GROUPBY column_ref_list   { free($1); }
    ;

column_ref_list
    : IDENTIFIER            { free($1); }
    | column_ref_list ',' IDENTIFIER { free($3); }
    ;

/* HAVING clause */
opt_having
    : /* empty */
    | HAVING condition      { free($1); }
    ;

/* ORDER BY clause */
opt_order_by
    : /* empty */
    | ORDERBY order_list    { free($1); }
    ;

order_list
    : order_spec
    | order_list ',' order_spec
    ;

order_spec
    : IDENTIFIER            { free($1); }
    | IDENTIFIER ASC        { free($1); free($2); }
    | IDENTIFIER DESC       { free($1); free($2); }
    ;

/* LIMIT clause */
opt_limit
    : /* empty */
    | LIMIT INTVAL          { free($1); free($2); }
    | LIMIT INTVAL OFFSET INTVAL { free($1); free($2); free($3); free($4); }
    ;

/* INSERT statements */
insert_statement
    : INSERT INTO table_ref VALUES '(' value_list ')'
        { free($1); free($2); free($4); }
    | INSERT INTO table_ref '(' column_ref_list ')' VALUES '(' value_list ')'
        { free($1); free($2); free($7); }
    ;

value_list
    : literal               { free($1); }
    | value_list ',' literal { free($3); }
    ;

/* UPDATE statements */
update_statement
    : UPDATE table_ref SET assignment_list opt_where
        { free($1); free($3); }
    ;

assignment_list
    : assignment
    | assignment_list ',' assignment
    ;

assignment
    : IDENTIFIER COMPOP literal
        { free($1); free($2); free($3); }
    ;

/* DELETE statements */
delete_statement
    : DELETE FROM table_ref opt_where
        { free($1); free($2); }
    ;

/* CREATE TABLE statements */
create_statement
    : CREATE TABLE IDENTIFIER '(' column_def_list ')'
        { free($1); free($2); free($3); }
    | CREATE TABLE IDENTIFIER '(' column_def_list ',' constraint_list ')'
        { free($1); free($2); free($3); }
    ;

column_def_list
    : column_def
    | column_def_list ',' column_def
    ;

column_def
    : IDENTIFIER data_type opt_column_constraints
        { free($1); free($2); }
    ;

data_type
    : IDENTIFIER            { $$ = $1; }
    | IDENTIFIER '(' INTVAL ')' { free($3); $$ = $1; }
    | IDENTIFIER '(' INTVAL ',' INTVAL ')' { free($3); free($5); $$ = $1; }
    ;

opt_column_constraints
    : /* empty */
    | column_constraint_list
    ;

column_constraint_list
    : column_constraint
    | column_constraint_list column_constraint
    ;

column_constraint
    : NOT NULLVAL           { free($1); free($2); }
    | NULLVAL               { free($1); }
    | PRIMARY KEY           { free($1); free($2); }
    | UNIQUE                { free($1); }
    | DEFAULT literal       { free($1); free($2); }
    | CHECK '(' condition ')'   { free($1); }
    | REFERENCES IDENTIFIER { free($1); free($2); }
    | REFERENCES IDENTIFIER '(' IDENTIFIER ')' { free($1); free($2); free($4); }
    ;

constraint_list
    : table_constraint
    | constraint_list ',' table_constraint
    ;

table_constraint
    : PRIMARY KEY '(' column_ref_list ')'   { free($1); free($2); }
    | FOREIGN KEY '(' column_ref_list ')' REFERENCES IDENTIFIER '(' column_ref_list ')'
        { free($1); free($2); free($6); free($7); }
    | UNIQUE '(' column_ref_list ')'        { free($1); }
    | CHECK '(' condition ')'               { free($1); }
    ;

/* DROP statements */
drop_statement
    : DROP TABLE IDENTIFIER     { free($1); free($2); free($3); }
    ;

/* ALTER TABLE statements */
alter_statement
    : ALTER TABLE IDENTIFIER ADD IDENTIFIER data_type opt_column_constraints
        { free($1); free($2); free($3); free($4); free($5); free($6); }
    | ALTER TABLE IDENTIFIER ADD '(' column_def_list ')'
        { free($1); free($2); free($3); free($4); }
    | ALTER TABLE IDENTIFIER MODIFY IDENTIFIER data_type opt_column_constraints
        { free($1); free($2); free($3); free($4); free($5); free($6); }
    | ALTER TABLE IDENTIFIER DROP IDENTIFIER
        { free($1); free($2); free($3); free($4); free($5); }
    ;

/* literal returns strdup'd token pointer so callers can free it */
literal
    : INTVAL     { $$ = $1; }    /* transfer ownership */
    | STRINGVAL  { $$ = $1; }    /* transfer ownership */
    | NULLVAL    { $$ = $1; }    /* transfer ownership */
    ;

%%

/* yyerror - capture message and position */
void yyerror(const char* s) {
    syntaxError = s ? s : "syntax error";
    errorLine = currLine;
    errorColumn = currCol;
}
