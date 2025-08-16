%{
#include "mysql.tab.h"
#include <string>
#include <cstring>
#include <iostream>

int currLine = 1;
int currCol = 1;

// Global error state
std::string syntaxError;
int errorLine = -1;
int errorColumn = -1;

// Setter function to report errors
void setSyntaxError(const std::string& msg, int line, int col) {
    syntaxError = msg;
    errorLine = line;
    errorColumn = col;
}

// Getters (so SyntaxAnalyzer.cpp can use them)
std::string getSyntaxError() { return syntaxError; }
int getErrorLine() { return errorLine; }
int getErrorColumn() { return errorColumn; }

// Buffer for query string input
std::string inputBuffer;
size_t inputIndex = 0;

void setInputString(const std::string& input) {
    inputBuffer = input;
    inputIndex = 0;
    currLine = 1;
    currCol = 1;
    // Clear previous error state
    syntaxError = "";
    errorLine = -1;
    errorColumn = -1;
}

// Custom input function for Flex
#define YY_INPUT(buf,result,max_size) \
    { \
        if (inputIndex >= inputBuffer.size()) { \
            result = YY_NULL; \
        } else { \
            size_t n = std::min((size_t)max_size, inputBuffer.size() - inputIndex); \
            memcpy(buf, inputBuffer.c_str() + inputIndex, n); \
            inputIndex += n; \
            result = n; \
            for (size_t i = 0; i < n; i++) { \
                if (buf[i] == '\n') { currLine++; currCol = 1; } \
                else currCol++; \
            } \
        } \
    }
%}

%option noinput nounput noyywrap

%%

[ \t\r]+                    { /* skip whitespace */ }
\n                          { currLine++; currCol = 1; }
"--".*                      { /* skip SQL comments */ }
"/*"([^*]|\*+[^*/])*\*+"/"  { /* skip C-style comments */ }

(?i:SELECT)                 { return SELECT; }
(?i:FROM)                   { return FROM; }
(?i:WHERE)                  { return WHERE; }
(?i:AS)                     { return AS; }
(?i:AND)                    { return AND; }
(?i:OR)                     { return OR; }
(?i:NOT)                    { return NOT; }
(?i:CREATE)                 { return CREATE; }
(?i:DROP)                   { return DROP; }
(?i:ALTER)                  { return ALTER; }
(?i:TABLE)                  { return TABLE; }
(?i:DATABASE)               { return DATABASE; }
(?i:SCHEMA)                 { return SCHEMA; }
(?i:INDEX)                  { return INDEX; }
(?i:VIEW)                   { return VIEW; }
(?i:INSERT)                 { return INSERT; }
(?i:INTO)                   { return INTO; }
(?i:VALUES)                 { return VALUES; }
(?i:UPDATE)                 { return UPDATE; }
(?i:SET)                    { return SET; }
(?i:DELETE)                 { return DELETE; }

(?i:JOIN)                   { return JOIN; }
(?i:INNER)                  { return INNER; }
(?i:LEFT)                   { return LEFT; }
(?i:RIGHT)                  { return RIGHT; }
(?i:FULL)                   { return FULL; }
(?i:OUTER)                  { return OUTER; }
(?i:CROSS)                  { return CROSS; }
(?i:ON)                     { return ON; }
(?i:USING)                  { return USING; }

(?i:GROUP)                  { return GROUP; }
(?i:BY)                     { return BY; }
(?i:HAVING)                 { return HAVING; }
(?i:ORDER)                  { return ORDER; }
(?i:ASC)                    { return ASC; }
(?i:DESC)                   { return DESC; }
(?i:DISTINCT)               { return DISTINCT; }
(?i:ALL)                    { return ALL; }

(?i:UNION)                  { return UNION; }
(?i:INTERSECT)              { return INTERSECT; }
(?i:EXCEPT)                 { return EXCEPT; }
(?i:ADD)                    { return ADD; }
(?i:MODIFY)                 { return MODIFY; }

(?i:LIMIT)                  { return LIMIT; }
(?i:OFFSET)                 { return OFFSET; }
(?i:TOP)                    { return TOP; }

(?i:IS)                     { return IS; }
(?i:NULL)                   { return NULLSYM; }
(?i:LIKE)                   { return LIKE; }
(?i:ILIKE)                  { return ILIKE; }
(?i:IN)                     { return IN; }
(?i:BETWEEN)                { return BETWEEN; }
(?i:EXISTS)                 { return EXISTS; }
(?i:CASE)                   { return CASE; }
(?i:WHEN)                   { return WHEN; }
(?i:THEN)                   { return THEN; }
(?i:ELSE)                   { return ELSE; }
(?i:END)                    { return END; }

(?i:INT|INTEGER)            { yylval.strVal = strdup(yytext); return DATATYPE; }
(?i:VARCHAR)                { yylval.strVal = strdup(yytext); return DATATYPE; }
(?i:CHAR)                   { yylval.strVal = strdup(yytext); return DATATYPE; }
(?i:TEXT)                   { yylval.strVal = strdup(yytext); return DATATYPE; }
(?i:DECIMAL|NUMERIC)        { yylval.strVal = strdup(yytext); return DATATYPE; }
(?i:FLOAT|REAL)             { yylval.strVal = strdup(yytext); return DATATYPE; }
(?i:DOUBLE)                 { yylval.strVal = strdup(yytext); return DATATYPE; }
(?i:BOOLEAN|BOOL)           { yylval.strVal = strdup(yytext); return DATATYPE; }
(?i:DATE)                   { yylval.strVal = strdup(yytext); return DATATYPE; }
(?i:TIME)                   { yylval.strVal = strdup(yytext); return DATATYPE; }
(?i:DATETIME|TIMESTAMP)     { yylval.strVal = strdup(yytext); return DATATYPE; }
(?i:BLOB)                   { yylval.strVal = strdup(yytext); return DATATYPE; }

(?i:PRIMARY)                { return PRIMARY; }
(?i:KEY)                    { return KEY; }
(?i:FOREIGN)                { return FOREIGN; }
(?i:REFERENCES)             { return REFERENCES; }
(?i:UNIQUE)                 { return UNIQUE; }
(?i:CHECK)                  { return CHECK; }
(?i:DEFAULT)                { return DEFAULT; }
(?i:AUTO_INCREMENT)         { return AUTO_INCREMENT; }
(?i:NOT_NULL)               { return NOT_NULL; }

(?i:COUNT)                  { yylval.strVal = strdup(yytext); return FUNCTION; }
(?i:SUM)                    { yylval.strVal = strdup(yytext); return FUNCTION; }
(?i:AVG)                    { yylval.strVal = strdup(yytext); return FUNCTION; }
(?i:MIN)                    { yylval.strVal = strdup(yytext); return FUNCTION; }
(?i:MAX)                    { yylval.strVal = strdup(yytext); return FUNCTION; }
(?i:UPPER)                  { yylval.strVal = strdup(yytext); return FUNCTION; }
(?i:LOWER)                  { yylval.strVal = strdup(yytext); return FUNCTION; }
(?i:LENGTH|LEN)             { yylval.strVal = strdup(yytext); return FUNCTION; }
(?i:SUBSTRING|SUBSTR)       { yylval.strVal = strdup(yytext); return FUNCTION; }
(?i:TRIM)                   { yylval.strVal = strdup(yytext); return FUNCTION; }
(?i:CONCAT)                 { yylval.strVal = strdup(yytext); return FUNCTION; }
(?i:NOW)                    { yylval.strVal = strdup(yytext); return FUNCTION; }
(?i:CURRENT_DATE)           { yylval.strVal = strdup(yytext); return FUNCTION; }
(?i:CURRENT_TIME)           { yylval.strVal = strdup(yytext); return FUNCTION; }
(?i:CURRENT_TIMESTAMP)      { yylval.strVal = strdup(yytext); return FUNCTION; }

[a-zA-Z_][a-zA-Z0-9_]*      { yylval.strVal = strdup(yytext); return IDENTIFIER; }
`[^`]+`                     { yylval.strVal = strdup(yytext); return IDENTIFIER; }
\"[^\"]+\"                  { yylval.strVal = strdup(yytext); return IDENTIFIER; }
\[[^\]]+\]                  { yylval.strVal = strdup(yytext); return IDENTIFIER; }

[0-9]+                      { yylval.strVal = strdup(yytext); return INTVAL; }
[0-9]*\.[0-9]+              { yylval.strVal = strdup(yytext); return FLOATVAL; }
[0-9]+\.[0-9]*              { yylval.strVal = strdup(yytext); return FLOATVAL; }

\'([^\']|\'\')*\'           { yylval.strVal = strdup(yytext); return STRINGVAL; }
\"([^\"]|\"\")*\"           { yylval.strVal = strdup(yytext); return STRINGVAL; }

"="                         { yylval.strVal = strdup(yytext); return EQ; }
"<>"                        { yylval.strVal = strdup(yytext); return NE; }
"!="                        { yylval.strVal = strdup(yytext); return NE; }
"<"                         { yylval.strVal = strdup(yytext); return LT; }
"<="                        { yylval.strVal = strdup(yytext); return LE; }
">"                         { yylval.strVal = strdup(yytext); return GT; }
">="                        { yylval.strVal = strdup(yytext); return GE; }
"+"                         { yylval.strVal = strdup(yytext); return PLUS; }
"-"                         { yylval.strVal = strdup(yytext); return MINUS; }
"*"                         { yylval.strVal = strdup(yytext); return ASTERISK; }
"/"                         { yylval.strVal = strdup(yytext); return DIVIDE; }
"%"                         { yylval.strVal = strdup(yytext); return MODULO; }
"||"                        { yylval.strVal = strdup(yytext); return CONCAT_OP; }


","                         { return COMMA; }
";"                         { return SEMICOLON; }
"("                         { return LPAREN; }
")"                         { return RPAREN; }
"."                         { return DOT; }
"?"                         { return QUESTION; }

.                           {
                                // Invalid token
                                std::string msg = "Unexpected token: ";
                                msg += yytext;
                                setSyntaxError(msg, currLine, currCol);
                                return yytext[0];
                            }

%%