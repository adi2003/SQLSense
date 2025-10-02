#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <memory>
#include <bits/stdc++.h>

// Forward declarations
class ASTNode;
class Expression;
class Statement;

// Smart pointer types for memory management
using ASTNodePtr = std::unique_ptr<ASTNode>;
using ExpressionPtr = std::unique_ptr<Expression>;
using StatementPtr = std::unique_ptr<Statement>;

// Enum for node types
enum class NodeType {
    // Statements
    SELECT_STMT,
    INSERT_STMT,
    UPDATE_STMT,
    DELETE_STMT,
    CREATE_TABLE_STMT,
    CREATE_DATABASE_STMT,
    CREATE_INDEX_STMT,
    CREATE_VIEW_STMT,
    DROP_STMT,
    ALTER_STMT,
    
    // Expressions
    IDENTIFIER_EXPR,
    LITERAL_EXPR,
    BINARY_OP_EXPR,
    UNARY_OP_EXPR,
    FUNCTION_CALL_EXPR,
    CASE_EXPR,
    
    // Clauses
    FROM_CLAUSE,
    WHERE_CLAUSE,
    GROUP_BY_CLAUSE,
    HAVING_CLAUSE,
    ORDER_BY_CLAUSE,
    
    // Other constructs
    TABLE_REF,
    JOIN_CLAUSE,
    COLUMN_DEF,
    SELECT_ITEM,
    ASSIGNMENT
};

//enum for datatypes
enum class DataType;


// Base AST Node class
class ASTNode {
public:
    NodeType nodeType;
    int line;
    int column;
    
    ASTNode(NodeType type, int line = 0, int col = 0) 
        : nodeType(type), line(line), column(col) {}
    virtual ~ASTNode() = default;
    
    // Virtual method for type checking
    virtual bool isExpression() const { return false; }
    virtual bool isStatement() const { return false; }
};

// Expression base class
class Expression : public ASTNode {
public:
    Expression(NodeType type, int line = 0, int col = 0) 
        : ASTNode(type, line, col) {}

    bool isExpression() const override { return true; }

    // === Fields expected by grammar ===

    // Function call arguments
    std::vector<std::unique_ptr<Expression>> arguments;

    // For SELECT ... DISTINCT or function calls with DISTINCT
    bool isDistinct = false;

    // For COUNT(*) and similar cases
    bool hasAsterisk = false;

    // CASE expression components
    std::unique_ptr<Expression> caseExpr;   // Expression after "CASE"
    std::vector<std::pair<std::unique_ptr<Expression>, std::unique_ptr<Expression>>> whenClauses; // WHEN expr THEN expr
    std::unique_ptr<Expression> elseExpr;   // ELSE expr

    // === Convenience ===
    void addArgument(std::unique_ptr<Expression> arg) {
        arguments.push_back(std::move(arg));
    }

    void addWhenClause(std::unique_ptr<Expression> whenExpr,
                       std::unique_ptr<Expression> thenExpr) {
        whenClauses.emplace_back(std::move(whenExpr), std::move(thenExpr));
    }
};


// Statement base class
class Statement : public ASTNode {
public:
    Statement(NodeType type, int line = 0, int col = 0) 
        : ASTNode(type, line, col) {}
    bool isStatement() const override { return true; }
};

// Identifier Expression
class IdentifierExpr : public Expression {
public:
    std::string name;
    std::string table; // For qualified identifiers like table.column
    
    IdentifierExpr(const std::string& name, int line = 0, int col = 0)
        : Expression(NodeType::IDENTIFIER_EXPR, line, col), name(name) {}
        
    IdentifierExpr(const std::string& table, const std::string& name, int line = 0, int col = 0)
        : Expression(NodeType::IDENTIFIER_EXPR, line, col), name(name), table(table) {}
};

// Literal Expression
class LiteralExpr : public Expression {
public:
    enum LiteralType { STRING, INTEGER, FLOAT, NULL_VAL, BOOLEAN, DECIMAL, DATE, TIME, DATETIME};
    LiteralType literalType;
    std::string value;
    
    LiteralExpr(LiteralType type, const std::string& val, int line = 0, int col = 0)
        : Expression(NodeType::LITERAL_EXPR, line, col), literalType(type), value(val) {}
};

// Binary Operation Expression
class BinaryOpExpr : public Expression {
public:
    std::string operator_;
    ExpressionPtr left;
    ExpressionPtr right;
    
    BinaryOpExpr(const std::string& op, ExpressionPtr l, ExpressionPtr r, int line = 0, int col = 0)
        : Expression(NodeType::BINARY_OP_EXPR, line, col), operator_(op), 
          left(std::move(l)), right(std::move(r)) {}
};

// Unary Operation Expression
class UnaryOpExpr : public Expression {
public:
    std::string operator_;
    ExpressionPtr operand;
    
    UnaryOpExpr(const std::string& op, ExpressionPtr operand, int line = 0, int col = 0)
        : Expression(NodeType::UNARY_OP_EXPR, line, col), operator_(op), 
          operand(std::move(operand)) {}
};

// Function Call Expression
class FunctionCallExpr : public Expression {
public:
    std::string functionName;
    std::vector<ExpressionPtr> arguments;
    bool isDistinct;
    bool hasAsterisk;
    
    FunctionCallExpr(const std::string& name, int line = 0, int col = 0)
        : Expression(NodeType::FUNCTION_CALL_EXPR, line, col), functionName(name), 
          isDistinct(false), hasAsterisk(false) {}
};

// Case Expression
class CaseExpr : public Expression {
public:
    ExpressionPtr caseExpr; // For simple CASE, null for searched CASE
    std::vector<std::pair<ExpressionPtr, ExpressionPtr>> whenClauses; // condition/value, result
    ExpressionPtr elseExpr;
    
    CaseExpr(int line = 0, int col = 0)
        : Expression(NodeType::CASE_EXPR, line, col) {}
};

// Table Reference
class TableRef : public ASTNode {
public:
    std::string tableName;
    std::string alias;
    StatementPtr subquery; // For subqueries
    std::vector<std::unique_ptr<ASTNode>> joins;
    
    TableRef(const std::string& name, int line = 0, int col = 0)
        : ASTNode(NodeType::TABLE_REF, line, col), tableName(name) {}
};

// Join Clause
class JoinClause : public ASTNode {
public:
    enum JoinType { INNER, LEFT, RIGHT, FULL, CROSS };
    JoinType joinType;
    bool isOuter;
    std::unique_ptr<TableRef> table;
    ExpressionPtr onCondition;
    std::vector<std::string> usingColumns;
    
    JoinClause(JoinType type, std::unique_ptr<TableRef> table, int line = 0, int col = 0)
        : ASTNode(NodeType::JOIN_CLAUSE, line, col), joinType(type), isOuter(false), 
          table(std::move(table)) {}
};

// Select Item (for SELECT clause)
class SelectItem : public ASTNode {
public:
    ExpressionPtr expression;
    std::string alias;
    bool isAsterisk;
    
    SelectItem(ExpressionPtr expr, int line = 0, int col = 0)
        : ASTNode(NodeType::SELECT_ITEM, line, col), expression(std::move(expr)), isAsterisk(false) {}
        
    SelectItem(bool asterisk, int line = 0, int col = 0) // For SELECT *
        : ASTNode(NodeType::SELECT_ITEM, line, col), isAsterisk(asterisk) {}
};

// Column Definition (for CREATE TABLE)
class ColumnDef : public ASTNode {
public:
    std::string columnName;
    std::string dataType;
    bool isPrimaryKey;
    bool isUnique;
    bool isNotNull;
    bool isAutoIncrement;
    ExpressionPtr defaultValue;
    std::string foreignKeyTable;
    std::vector<std::string> foreignKeyColumns;
    
    ColumnDef(const std::string& name, const std::string& type, int line = 0, int col = 0)
        : ASTNode(NodeType::COLUMN_DEF, line, col), columnName(name), dataType(type),
          isPrimaryKey(false), isUnique(false), isNotNull(false), isAutoIncrement(false) {}
};

// Assignment (for UPDATE)
class Assignment : public ASTNode {
public:
    std::string columnName;
    ExpressionPtr value;
    
    Assignment(const std::string& col, ExpressionPtr val, int line = 0, int colm = 0)
        : ASTNode(NodeType::ASSIGNMENT, line, colm), columnName(col), value(std::move(val)) {}
};

// SELECT Statement
class SelectStmt : public Statement {
public:
    bool isDistinct;
    std::vector<std::unique_ptr<SelectItem>> selectList;
    std::vector<std::unique_ptr<TableRef>> fromList;
    ExpressionPtr whereClause;
    std::vector<ExpressionPtr> groupByList;
    std::vector<ExpressionPtr> groupByClause;
    std::vector<ExpressionPtr> fromClause;
    ExpressionPtr havingClause;
    std::vector<std::pair<ExpressionPtr, bool>> orderByList; // expression, isAsc
    int limitCount;
    int offsetCount;
    
    SelectStmt(int line = 0, int col = 0)
        : Statement(NodeType::SELECT_STMT, line, col), isDistinct(false), 
          limitCount(-1), offsetCount(-1) {}
};

// INSERT Statement
class InsertStmt : public Statement {
public:
    std::string tableName;
    std::vector<std::string> columnList;
    std::vector<std::vector<ExpressionPtr>> valuesList;
    StatementPtr selectStmt; // For INSERT ... SELECT
    
    InsertStmt(const std::string& table, int line = 0, int col = 0)
        : Statement(NodeType::INSERT_STMT, line, col), tableName(table) {}
};

// UPDATE Statement
class UpdateStmt : public Statement {
public:
    std::string tableName;
    std::vector<std::unique_ptr<Assignment>> assignments;
    ExpressionPtr whereClause;
    
    UpdateStmt(const std::string& table, int line = 0, int col = 0)
        : Statement(NodeType::UPDATE_STMT, line, col), tableName(table) {}
};

// DELETE Statement
class DeleteStmt : public Statement {
public:
    std::string tableName;
    ExpressionPtr whereClause;
    
    DeleteStmt(const std::string& table, int line = 0, int col = 0)
        : Statement(NodeType::DELETE_STMT, line, col), tableName(table) {}
};

// CREATE TABLE Statement
class CreateTableStmt : public Statement {
public:
    std::string tableName;
    std::vector<std::unique_ptr<ColumnDef>> columns;
    
    CreateTableStmt(const std::string& table, int line = 0, int col = 0)
        : Statement(NodeType::CREATE_TABLE_STMT, line, col), tableName(table) {}
};

// CREATE DATABASE Statement
class CreateDatabaseStmt : public Statement {
public:
    std::string databaseName;
    
    CreateDatabaseStmt(const std::string& db, int line = 0, int col = 0)
        : Statement(NodeType::CREATE_DATABASE_STMT, line, col), databaseName(db) {}
};

// CREATE INDEX Statement
class CreateIndexStmt : public Statement {
public:
    std::string indexName;
    std::string tableName;
    std::vector<std::string> columns;
    bool isUnique;
    
    CreateIndexStmt(const std::string& index, const std::string& table, int line = 0, int col = 0)
        : Statement(NodeType::CREATE_INDEX_STMT, line, col), indexName(index), 
          tableName(table), isUnique(false) {}
};

// CREATE VIEW Statement
class CreateViewStmt : public Statement {
public:
    std::string viewName;
    StatementPtr selectStmt;
    
    CreateViewStmt(const std::string& view, StatementPtr select, int line = 0, int col = 0)
        : Statement(NodeType::CREATE_VIEW_STMT, line, col), viewName(view), 
          selectStmt(std::move(select)) {}
};

// DROP Statement
class DropStmt : public Statement {
public:
    enum DropType { TABLE, DATABASE, SCHEMA, INDEX, VIEW };
    DropType dropType;
    std::string objectName;
    
    DropStmt(DropType type, const std::string& name, int line = 0, int col = 0)
        : Statement(NodeType::DROP_STMT, line, col), dropType(type), objectName(name) {}
};

// ALTER TABLE Statement
class AlterStmt : public Statement {
public:
    enum AlterType { ADD_COLUMN, DROP_COLUMN, MODIFY_COLUMN, ADD_PRIMARY_KEY, DROP_PRIMARY_KEY };
    std::string tableName;
    AlterType alterType;
    std::unique_ptr<ColumnDef> columnDef; // For ADD/MODIFY
    std::string columnName; // For DROP
    std::vector<std::string> primaryKeyColumns; // For ADD PRIMARY KEY
    
    AlterStmt(const std::string& table, AlterType type, int line = 0, int col = 0)
        : Statement(NodeType::ALTER_STMT, line, col), tableName(table), alterType(type) {}
};

// Root AST node containing all statements
class SqlProgram : public ASTNode {
public:
    std::vector<StatementPtr> statements;
    
    SqlProgram() : ASTNode(NodeType::SELECT_STMT) {} // Dummy type, not used
};

// External declaration for the root AST
extern std::unique_ptr<SqlProgram> sqlProgram;

#endif // AST_H