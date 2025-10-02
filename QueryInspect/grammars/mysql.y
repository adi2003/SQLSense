%code requires {
    #include <iostream>
    #include <vector>
    #include <string>
    #include <memory>
    #include <utility>
    #include "../include/AST.h"
}

%code {
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
}

%union {
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
}

/* Tokens with semantic values */
%token <strVal> IDENTIFIER STRINGVAL DATATYPE FUNCTION
%token <strVal> INTVAL FLOATVAL

/* SQL Keywords */
%token SELECT FROM WHERE AS AND OR NOT
%token INSERT INTO VALUES UPDATE SET DELETE
%token CREATE DROP ALTER TABLE DATABASE SCHEMA INDEX VIEW COLUMN
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

/* Non-terminal types */
%type <statement> statement
%type <selectStmt> select_statement
%type <insertStmt> insert_statement
%type <updateStmt> update_statement
%type <deleteStmt> delete_statement
%type <createTableStmt> create_table_statement
%type <createDatabaseStmt> create_database_statement
%type <createIndexStmt> create_index_statement
%type <createViewStmt> create_view_statement
%type <dropStmt> drop_statement
%type <alterStmt> alter_statement

%type <expression> expression primary_expression condition predicate
%type <expression> function_call case_expression
%type <tableRef> table_reference
%type <joinClause> join_clause
%type <selectItem> select_item
%type <columnDef> column_definition
%type <assignment> assignment

%type <statementList> statement_list
%type <expressionList> expression_list opt_expression_list
%type <selectItemList> select_list
%type <tableRefList> table_reference_list
%type <columnDefList> column_definition_list
%type <assignmentList> assignment_list
%type <stringList> identifier_list opt_column_list
%type <valuesListList> value_list_list
%type <whenClauseList> when_clause_list
%type <orderByList> order_by_list

%type <intVal> opt_distinct opt_unique opt_join_type opt_asc_desc
%type <tableRefList> opt_from_clause
%type <expression> opt_where_clause opt_having_clause opt_else_clause
%type <expressionList> opt_group_by_clause
%type <orderByList> opt_order_by_clause


/* Operator precedence (lowest to highest) */
%left OR
%left AND
%right NOT
%left EQ NE LT LE GT GE LIKE ILIKE IN BETWEEN IS
%left PLUS MINUS CONCAT_OP
%left ASTERISK DIVIDE MODULO
%right UMINUS UPLUS
%left DOT

/* Start symbol */
%start sql_program

%%

/* ---------------- Root Production ---------------- */
sql_program : statement_list
            {
                sqlProgram = std::make_unique<SqlProgram>();
                if ($1) {
                    sqlProgram->statements = std::move(*$1);
                    delete $1;
                }
            }
            ;

statement_list : statement
               {
                   $$ = new std::vector<StatementPtr>();
                   if ($1) {
                       $$->emplace_back($1);
                   }
               }
               | statement_list statement
               {
                   $$ = $1;
                   if ($2) {
                       $$->emplace_back($2);
                   }
               }
               ;

statement : select_statement SEMICOLON { $$ = $1; }
          | insert_statement SEMICOLON { $$ = $1; }
          | update_statement SEMICOLON { $$ = $1; }
          | delete_statement SEMICOLON { $$ = $1; }
          | create_table_statement SEMICOLON { $$ = $1; }
          | create_database_statement SEMICOLON { $$ = $1; }
          | create_index_statement SEMICOLON { $$ = $1; }
          | create_view_statement SEMICOLON { $$ = $1; }
          | drop_statement SEMICOLON { $$ = $1; }
          | alter_statement SEMICOLON { $$ = $1; }
          | select_statement { $$ = $1; }  /* Allow without semicolon for last statement */
          | insert_statement { $$ = $1; }
          | update_statement { $$ = $1; }
          | delete_statement { $$ = $1; }
          | create_table_statement { $$ = $1; }
          | create_database_statement { $$ = $1; }
          | create_index_statement { $$ = $1; }
          | create_view_statement { $$ = $1; }
          | drop_statement { $$ = $1; }
          | alter_statement { $$ = $1; }
          ;

/* ---------------- SELECT Statement ---------------- */
select_statement : SELECT opt_distinct select_list opt_from_clause opt_where_clause 
                   opt_group_by_clause opt_having_clause opt_order_by_clause opt_limit_clause
                 {
                     $$ = new SelectStmt(currLine, currCol);
                     $$->isDistinct = ($2 != 0);
                     if ($3) {
                         $$->selectList = std::move(*$3);
                         delete $3;
                     }
                     if ($4) {
                         $$->fromList = std::move(*$4);
                         delete $4;
                     }
                     $$->whereClause = ExpressionPtr($5);
                     if ($6) {
                         $$->groupByList = std::move(*$6);
                         delete $6;
                     }
                     $$->havingClause = ExpressionPtr($7);
                     if ($8) {
                         $$->orderByList = std::move(*$8);
                         delete $8;
                     }
                 }
                 ;

opt_distinct : /* empty */ { $$ = 0; }
             | DISTINCT { $$ = 1; }
             | ALL { $$ = 0; }
             ;

select_list : select_item
            {
                $$ = new std::vector<std::unique_ptr<SelectItem>>();
                if ($1) {
                    $$->emplace_back($1);
                }
            }
            | select_list COMMA select_item
            {
                $$ = $1;
                if ($3) {
                    $$->emplace_back($3);
                }
            }
            ;

select_item : ASTERISK
            {
                $$ = new SelectItem(true, currLine, currCol);
            }
            | expression
            {
                $$ = new SelectItem(ExpressionPtr($1), currLine, currCol);
            }
            | expression AS IDENTIFIER
            {
                $$ = new SelectItem(ExpressionPtr($1), currLine, currCol);
                $$->alias = makeString($3);
            }
            | expression IDENTIFIER
            {
                $$ = new SelectItem(ExpressionPtr($1), currLine, currCol);
                $$->alias = makeString($2);
            }
            ;

opt_from_clause : /* empty */ { $$ = nullptr; }
                | FROM table_reference_list { $$ = $2; }
                ;

table_reference_list : table_reference
                     {
                         $$ = new std::vector<std::unique_ptr<TableRef>>();
                         if ($1) {
                             $$->emplace_back($1);
                         }
                     }
                     | table_reference_list COMMA table_reference
                     {
                         $$ = $1;
                         if ($3) {
                             $$->emplace_back($3);
                         }
                     }
                     ;

table_reference : IDENTIFIER
                {
                    $$ = new TableRef(makeString($1), currLine, currCol);
                }
                | IDENTIFIER AS IDENTIFIER
                {
                    $$ = new TableRef(makeString($1), currLine, currCol);
                    $$->alias = makeString($3);
                }
                | IDENTIFIER IDENTIFIER
                {
                    $$ = new TableRef(makeString($1), currLine, currCol);
                    $$->alias = makeString($2);
                }
                | LPAREN select_statement RPAREN AS IDENTIFIER
                {
                    $$ = new TableRef("", currLine, currCol);
                    $$->subquery = StatementPtr($2);
                    $$->alias = makeString($5);
                }
                | table_reference join_clause
                {
                    $$ = $1;
                    if ($2) {
                        $$->joins.emplace_back($2);
                    }
                }
                ;

join_clause : opt_join_type JOIN table_reference ON expression
            {
                $$ = new JoinClause(static_cast<JoinClause::JoinType>($1), 
                                  std::unique_ptr<TableRef>($3), currLine, currCol);
                $$->onCondition = ExpressionPtr($5);
            }
            | opt_join_type JOIN table_reference USING LPAREN identifier_list RPAREN
            {
                $$ = new JoinClause(static_cast<JoinClause::JoinType>($1), 
                                  std::unique_ptr<TableRef>($3), currLine, currCol);
                if ($6) {
                    $$->usingColumns = std::move(*$6);
                    delete $6;
                }
            }
            ;

opt_join_type : /* empty */ { $$ = 0; /* INNER */ }
              | INNER { $$ = 0; }
              | LEFT opt_outer { $$ = 1; }
              | RIGHT opt_outer { $$ = 2; }
              | FULL opt_outer { $$ = 3; }
              | CROSS { $$ = 4; }
              ;

opt_outer : /* empty */
          | OUTER
          ;

opt_where_clause : /* empty */ { $$ = nullptr; }
                 | WHERE expression { $$ = $2; }
                 ;

opt_group_by_clause : /* empty */ { $$ = nullptr; }
                    | GROUP BY expression_list { $$ = $3; }
                    ;

opt_having_clause : /* empty */ { $$ = nullptr; }
                  | HAVING expression { $$ = $2; }
                  ;

opt_order_by_clause : /* empty */ { $$ = nullptr; }
                    | ORDER BY order_by_list { $$ = $3; }
                    ;

order_by_list : expression opt_asc_desc
              {
                  $$ = new std::vector<std::pair<ExpressionPtr, bool>>();
                  $$->emplace_back(ExpressionPtr($1), $2 != 0);
              }
              | order_by_list COMMA expression opt_asc_desc
              {
                  $$ = $1;
                  $$->emplace_back(ExpressionPtr($3), $4 != 0);
              }
              ;

opt_asc_desc : /* empty */ { $$ = 1; /* ASC */ }
             | ASC { $$ = 1; }
             | DESC { $$ = 0; }
             ;

opt_limit_clause : /* empty */
                 | LIMIT INTVAL
                 | LIMIT INTVAL OFFSET INTVAL
                 ;

/* ---------------- INSERT Statement ---------------- */
insert_statement : INSERT INTO IDENTIFIER opt_column_list VALUES value_list_list
                 {
                     $$ = new InsertStmt(makeString($3), currLine, currCol);
                     if ($4) {
                         $$->columnList = std::move(*$4);
                         delete $4;
                     }
                     if ($6) {
                         $$->valuesList = std::move(*$6);
                         delete $6;
                     }
                 }
                 | INSERT INTO IDENTIFIER opt_column_list select_statement
                 {
                     $$ = new InsertStmt(makeString($3), currLine, currCol);
                     if ($4) {
                         $$->columnList = std::move(*$4);
                         delete $4;
                     }
                     $$->selectStmt = StatementPtr($5);
                 }
                 ;

opt_column_list : /* empty */ { $$ = nullptr; }
                | LPAREN identifier_list RPAREN { $$ = $2; }
                ;

value_list_list : LPAREN expression_list RPAREN
                {
                    $$ = new std::vector<std::vector<ExpressionPtr>>();
                    if ($2) {
                        $$->emplace_back(std::move(*$2));
                        delete $2;
                    }
                }
                | value_list_list COMMA LPAREN expression_list RPAREN
                {
                    $$ = $1;
                    if ($4) {
                        $$->emplace_back(std::move(*$4));
                        delete $4;
                    }
                }
                ;

/* ---------------- UPDATE Statement ---------------- */
update_statement : UPDATE IDENTIFIER SET assignment_list opt_where_clause
                 {
                     $$ = new UpdateStmt(makeString($2), currLine, currCol);
                     if ($4) {
                         $$->assignments = std::move(*$4);
                         delete $4;
                     }
                     $$->whereClause = ExpressionPtr($5);
                 }
                 ;

assignment_list : assignment
                {
                    $$ = new std::vector<std::unique_ptr<Assignment>>();
                    if ($1) {
                        $$->emplace_back($1);
                    }
                }
                | assignment_list COMMA assignment
                {
                    $$ = $1;
                    if ($3) {
                        $$->emplace_back($3);
                    }
                }
                ;

assignment : IDENTIFIER EQ expression
           {
               $$ = new Assignment(makeString($1), ExpressionPtr($3), currLine, currCol);
           }
           ;

/* ---------------- DELETE Statement ---------------- */
delete_statement : DELETE FROM IDENTIFIER opt_where_clause
                 {
                     $$ = new DeleteStmt(makeString($3), currLine, currCol);
                     $$->whereClause = ExpressionPtr($4);
                 }
                 ;

/* ---------------- CREATE TABLE Statement ---------------- */
create_table_statement : CREATE TABLE IDENTIFIER LPAREN column_definition_list RPAREN
                       {
                           $$ = new CreateTableStmt(makeString($3), currLine, currCol);
                           if ($5) {
                               $$->columns = std::move(*$5);
                               delete $5;
                           }
                       }
                       ;

column_definition_list : column_definition
                       {
                           $$ = new std::vector<std::unique_ptr<ColumnDef>>();
                           if ($1) {
                               $$->emplace_back($1);
                           }
                       }
                       | column_definition_list COMMA column_definition
                       {
                           $$ = $1;
                           if ($3) {
                               $$->emplace_back($3);
                           }
                       }
                       ;

column_definition : IDENTIFIER DATATYPE opt_column_constraints
                  {
                      $$ = new ColumnDef(makeString($1), makeString($2), currLine, currCol);
                  }
                  ;

opt_column_constraints : /* empty */
                       | opt_column_constraints column_constraint
                       ;

column_constraint : PRIMARY KEY
                  | UNIQUE  
                  | NOT_NULL
                  | AUTO_INCREMENT
                  | DEFAULT expression
                  | FOREIGN KEY REFERENCES IDENTIFIER LPAREN identifier_list RPAREN
                  | REFERENCES IDENTIFIER
                  | CHECK LPAREN expression RPAREN
                  ;

/* ---------------- CREATE DATABASE Statement ---------------- */
create_database_statement : CREATE DATABASE IDENTIFIER
                          {
                              $$ = new CreateDatabaseStmt(makeString($3), currLine, currCol);
                          }
                          | CREATE SCHEMA IDENTIFIER
                          {
                              $$ = new CreateDatabaseStmt(makeString($3), currLine, currCol);
                          }
                          ;

/* ---------------- CREATE INDEX Statement ---------------- */
create_index_statement : CREATE opt_unique INDEX IDENTIFIER ON IDENTIFIER LPAREN identifier_list RPAREN
                       {
                           $$ = new CreateIndexStmt(makeString($4), makeString($6), currLine, currCol);
                           $$->isUnique = ($2 != 0);
                           if ($8) {
                               $$->columns = std::move(*$8);
                               delete $8;
                           }
                       }
                       ;

opt_unique : /* empty */ { $$ = 0; }
           | UNIQUE { $$ = 1; }
           ;

/* ---------------- CREATE VIEW Statement ---------------- */
create_view_statement : CREATE VIEW IDENTIFIER AS select_statement
                      {
                          $$ = new CreateViewStmt(makeString($3), StatementPtr($5), currLine, currCol);
                      }
                      ;

/* ---------------- DROP Statement ---------------- */
drop_statement : DROP TABLE IDENTIFIER
               {
                   $$ = new DropStmt(DropStmt::TABLE, makeString($3), currLine, currCol);
               }
               | DROP DATABASE IDENTIFIER
               {
                   $$ = new DropStmt(DropStmt::DATABASE, makeString($3), currLine, currCol);
               }
               | DROP SCHEMA IDENTIFIER
               {
                   $$ = new DropStmt(DropStmt::DATABASE, makeString($3), currLine, currCol);
               }
               | DROP INDEX IDENTIFIER
               {
                   $$ = new DropStmt(DropStmt::INDEX, makeString($3), currLine, currCol);
               }
               | DROP VIEW IDENTIFIER
               {
                   $$ = new DropStmt(DropStmt::VIEW, makeString($3), currLine, currCol);
               }
               ;

/* ---------------- ALTER Statement ---------------- */
alter_statement : ALTER TABLE IDENTIFIER ADD COLUMN column_definition
                {
                    $$ = new AlterStmt(makeString($3), AlterStmt::ADD_COLUMN, currLine, currCol);
                    $$->columnDef = std::unique_ptr<ColumnDef>($6);
                }
                | ALTER TABLE IDENTIFIER DROP COLUMN IDENTIFIER
                {
                    $$ = new AlterStmt(makeString($3), AlterStmt::DROP_COLUMN, currLine, currCol);
                    $$->columnName = makeString($6);
                }
                | ALTER TABLE IDENTIFIER MODIFY COLUMN column_definition
                {
                    $$ = new AlterStmt(makeString($3), AlterStmt::MODIFY_COLUMN, currLine, currCol);
                    $$->columnDef = std::unique_ptr<ColumnDef>($6);
                }
                ;

/* ---------------- Expressions ---------------- */
expression : primary_expression { $$ = $1; }
           | expression PLUS expression
           {
               $$ = new BinaryOpExpr(makeString($2), ExpressionPtr($1), ExpressionPtr($3), currLine, currCol);
           }
           | expression MINUS expression
           {
               $$ = new BinaryOpExpr(makeString($2), ExpressionPtr($1), ExpressionPtr($3), currLine, currCol);
           }
           | expression ASTERISK expression
           {
               $$ = new BinaryOpExpr(makeString($2), ExpressionPtr($1), ExpressionPtr($3), currLine, currCol);
           }
           | expression DIVIDE expression
           {
               $$ = new BinaryOpExpr(makeString($2), ExpressionPtr($1), ExpressionPtr($3), currLine, currCol);
           }
           | expression MODULO expression
           {
               $$ = new BinaryOpExpr(makeString($2), ExpressionPtr($1), ExpressionPtr($3), currLine, currCol);
           }
           | expression CONCAT_OP expression
           {
               $$ = new BinaryOpExpr(makeString($2), ExpressionPtr($1), ExpressionPtr($3), currLine, currCol);
           }
           | expression EQ expression
           {
               $$ = new BinaryOpExpr(makeString($2), ExpressionPtr($1), ExpressionPtr($3), currLine, currCol);
           }
           | expression NE expression
           {
               $$ = new BinaryOpExpr(makeString($2), ExpressionPtr($1), ExpressionPtr($3), currLine, currCol);
           }
           | expression LT expression
           {
               $$ = new BinaryOpExpr(makeString($2), ExpressionPtr($1), ExpressionPtr($3), currLine, currCol);
           }
           | expression LE expression
           {
               $$ = new BinaryOpExpr(makeString($2), ExpressionPtr($1), ExpressionPtr($3), currLine, currCol);
           }
           | expression GT expression
           {
               $$ = new BinaryOpExpr(makeString($2), ExpressionPtr($1), ExpressionPtr($3), currLine, currCol);
           }
           | expression GE expression
           {
               $$ = new BinaryOpExpr(makeString($2), ExpressionPtr($1), ExpressionPtr($3), currLine, currCol);
           }
           | expression AND expression
           {
               $$ = new BinaryOpExpr("AND", ExpressionPtr($1), ExpressionPtr($3), currLine, currCol);
           }
           | expression OR expression
           {
               $$ = new BinaryOpExpr("OR", ExpressionPtr($1), ExpressionPtr($3), currLine, currCol);
           }
           | expression LIKE expression
           {
               $$ = new BinaryOpExpr("LIKE", ExpressionPtr($1), ExpressionPtr($3), currLine, currCol);
           }
           | expression ILIKE expression
           {
               $$ = new BinaryOpExpr("ILIKE", ExpressionPtr($1), ExpressionPtr($3), currLine, currCol);
           }
           | expression IN LPAREN expression_list RPAREN
           {
               auto inExpr = new BinaryOpExpr("IN", ExpressionPtr($1), nullptr, currLine, currCol);
               // Store the list in a special way - this might need custom handling
               $$ = inExpr;
           }
           | expression BETWEEN expression AND expression
           {
               auto betweenExpr = new BinaryOpExpr("BETWEEN", ExpressionPtr($1), ExpressionPtr($3), currLine, currCol);
               // The third expression ($5) would need special handling in semantic analysis
               $$ = betweenExpr;
           }
           | expression IS NULLSYM
           {
               $$ = new BinaryOpExpr("IS NULL", ExpressionPtr($1), nullptr, currLine, currCol);
           }
           | expression IS NOT NULLSYM
           {
               $$ = new BinaryOpExpr("IS NOT NULL", ExpressionPtr($1), nullptr, currLine, currCol);
           }
           | NOT expression %prec NOT
           {
               $$ = new UnaryOpExpr("NOT", ExpressionPtr($2), currLine, currCol);
           }
           | MINUS expression %prec UMINUS
           {
               $$ = new UnaryOpExpr("-", ExpressionPtr($2), currLine, currCol);
           }
           | PLUS expression %prec UPLUS
           {
               $$ = new UnaryOpExpr("+", ExpressionPtr($2), currLine, currCol);
           }
           | LPAREN expression RPAREN { $$ = $2; }
           | case_expression { $$ = $1; }
           | function_call { $$ = $1; }
           ;

primary_expression : IDENTIFIER
                   {
                       $$ = new IdentifierExpr(makeString($1), currLine, currCol);
                   }
                   | IDENTIFIER DOT IDENTIFIER
                   {
                       $$ = new IdentifierExpr(makeString($1), makeString($3), currLine, currCol);
                   }
                   | STRINGVAL
                   {
                       $$ = new LiteralExpr(LiteralExpr::STRING, makeString($1), currLine, currCol);
                   }
                   | INTVAL
                   {
                       $$ = new LiteralExpr(LiteralExpr::INTEGER, makeString($1), currLine, currCol);
                   }
                   | FLOATVAL
                   {
                       $$ = new LiteralExpr(LiteralExpr::FLOAT, makeString($1), currLine, currCol);
                   }
                   | NULLSYM
                   {
                       $$ = new LiteralExpr(LiteralExpr::NULL_VAL, "NULL", currLine, currCol);
                   }
                   ;

function_call : FUNCTION LPAREN opt_expression_list RPAREN
              {
                  $$ = new FunctionCallExpr(makeString($1), currLine, currCol);
                  if ($3) {
                      $$->arguments = std::move(*$3);
                      delete $3;
                  }
              }
              | FUNCTION LPAREN DISTINCT expression_list RPAREN
              {
                  $$ = new FunctionCallExpr(makeString($1), currLine, currCol);
                  $$->isDistinct = true;
                  if ($4) {
                      $$->arguments = std::move(*$4);
                      delete $4;
                  }
              }
              | FUNCTION LPAREN ASTERISK RPAREN
              {
                  $$ = new FunctionCallExpr(makeString($1), currLine, currCol);
                  $$->hasAsterisk = true;
              }
              ;

case_expression : CASE expression when_clause_list opt_else_clause END
                {
                    $$ = new CaseExpr(currLine, currCol);
                    $$->caseExpr = ExpressionPtr($2);
                    if ($3) {
                        $$->whenClauses = std::move(*$3);
                        delete $3;
                    }
                    $$->elseExpr = ExpressionPtr($4);
                }
                | CASE when_clause_list opt_else_clause END
                {
                    $$ = new CaseExpr(currLine, currCol);
                    if ($2) {
                        $$->whenClauses = std::move(*$2);
                        delete $2;
                    }
                    $$->elseExpr = ExpressionPtr($3);
                }
                ;

when_clause_list : WHEN expression THEN expression
                 {
                     $$ = new std::vector<std::pair<ExpressionPtr, ExpressionPtr>>();
                     $$->emplace_back(ExpressionPtr($2), ExpressionPtr($4));
                 }
                 | when_clause_list WHEN expression THEN expression
                 {
                     $$ = $1;
                     $$->emplace_back(ExpressionPtr($3), ExpressionPtr($5));
                 }
                 ;

opt_else_clause : /* empty */ { $$ = nullptr; }
                | ELSE expression { $$ = $2; }
                ;

/* ---------------- Lists ---------------- */
expression_list : expression
                {
                    $$ = new std::vector<ExpressionPtr>();
                    if ($1) {
                        $$->emplace_back($1);
                    }
                }
                | expression_list COMMA expression
                {
                    $$ = $1;
                    if ($3) {
                        $$->emplace_back($3);
                    }
                }
                ;

opt_expression_list : /* empty */ { $$ = nullptr; }
                    | expression_list { $$ = $1; }
                    ;

identifier_list : IDENTIFIER
                {
                    $$ = new std::vector<std::string>();
                    $$->push_back(makeString($1));
                }
                | identifier_list COMMA IDENTIFIER
                {
                    $$ = $1;
                    $$->push_back(makeString($3));
                }
                ;

%%

void yyerror(const char *s) {
    setSyntaxError(std::string(s), currLine, currCol);
}