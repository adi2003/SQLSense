%{
#include <string>
#include <cstring>
#include <iostream>

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

%union {
    char* strVal;
}

/* Tokens with values */
%token <strVal> SELECT FROM WHERE IDENTIFIER INTVAL STRINGVAL LOGICOP COMPOP
%token AS
%token '*'

%left LOGICOP
%left COMPOP

%destructor { free($$); } <strVal>

/* Explicitly declare types for non-terminals */
%type <strVal> entry statement query column_list table_ref opt_alias condition literal
%type <strVal> opt_where

%%

entry
    : statement { $$ = $1; }
    ;

statement
    : query ';' { $$ = $1; }
    ;

query
    : SELECT column_list FROM table_ref opt_where 
      { 
        // We don’t really use $$ now, so set to nullptr to avoid warnings
        $$ = nullptr; 
      }
    ;

column_list
    : '*' { $$ = nullptr; }
    | IDENTIFIER opt_alias 
      { free($1); if ($2) free($2); $$ = nullptr; }
    | column_list ',' IDENTIFIER opt_alias 
      { free($3); if ($4) free($4); $$ = nullptr; }
    ;

table_ref
    : IDENTIFIER opt_alias 
      { free($1); if ($2) free($2); $$ = nullptr; }
    ;

opt_alias
    : /* empty */ { $$ = nullptr; }
    | AS IDENTIFIER { $$ = $2; }
    | IDENTIFIER    { $$ = $1; }
    ;

opt_where
    : /* empty */ { $$ = nullptr; }
    | WHERE condition { $$ = $2; }
    ;

condition
    : IDENTIFIER COMPOP literal 
      { free($1); free($2); free($3); $$ = nullptr; }
    | condition LOGICOP condition 
      { free($2); $$ = nullptr; }
    | '(' condition ')' 
      { $$ = $2; }
    ;

literal
    : INTVAL     { free($1); $$ = nullptr; }
    | STRINGVAL  { free($1); $$ = nullptr; }
    ;

%%

void yyerror(const char* s) {
    syntaxError = s;
    errorLine = currLine;
    errorColumn = currCol;
}
