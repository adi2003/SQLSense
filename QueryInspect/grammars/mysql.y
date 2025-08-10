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

%token <strVal> SELECT FROM WHERE IDENTIFIER INTVAL STRINGVAL LOGICOP COMPOP
%left LOGICOP
%left COMPOP
%token '*'

%destructor { free($$); } <strVal>

%%

entry
    : statement
    ;

statement
    : query ';'
    ;

query
    : SELECT column_list FROM table_ref opt_where
    ;

column_list
    : '*'
    | IDENTIFIER { free($1); }
    | column_list ',' IDENTIFIER { free($3); }
    ;

table_ref
    : IDENTIFIER { free($1); }
    ;

opt_where
    : /* empty */
    | WHERE condition
    ;

condition
    : IDENTIFIER COMPOP literal { free($1); free($2); }
    | condition LOGICOP condition { free($2); }
    | '(' condition ')'
    ;

literal
    : INTVAL { free($1); }
    | STRINGVAL { free($1); }
    ;

%%

void yyerror(const char* s) {
    syntaxError = s;
    errorLine = currLine;
    errorColumn = currCol;
}