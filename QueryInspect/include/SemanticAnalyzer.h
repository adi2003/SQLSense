#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include <bits/stdc++.h>
#include "SchemaCache.h"
#include "SyntaxAnalyzer.h"
#include "AST.h"
using namespace std;

enum class SemanticStatus {
    VALID,
    TYPE_MISMATCH,
    UNKNOWN_DATABASE,
    UNKNOWN_TABLE,
    UNKNOWN_COLUMN,
    PERMISSION_DENIED,
    CONSTRAINT_VIOLATION,
    UNKNOWN_FUNCTION,
    NULL_CONSTRAINT_VIOLATION,
    AMBIGUOUS_COLUMN,
    CIRCULAR_REFERENCE,
    INVALID_AGGREGATION,
    INVALID_GROUP_BY,
    DUPLICATE_COLUMN,
    FOREIGN_KEY_VIOLATION,
    PRIMARY_KEY_VIOLATION
};

struct SemanticIssue {
    SemanticStatus status;
    string message;
    string database;
    string table;
    string column;
    string function;
    int line;
    int column_pos;
    string suggestion;
    
    SemanticIssue(SemanticStatus stat, const string& msg, const string& db = "", 
                  const string& tbl = "", const string& col = "", int ln = -1, int cp = -1)
        : status(stat), message(msg), database(db), table(tbl), column(col), 
          line(ln), column_pos(cp) {}
};

struct SemanticResult {
    bool isValid;
    vector<SemanticIssue> issues;
    vector<string> warnings;
    
    SemanticResult() : isValid(true) {}
    
    void addIssue(const SemanticIssue& issue) {
        issues.push_back(issue);
        if (issue.status != SemanticStatus::VALID) {
            isValid = false;
        }
    }
    
    void addWarning(const string& warning) {
        warnings.push_back(warning);
    }
    
    void merge(const SemanticResult& other) {
        if (!other.isValid) {
            isValid = false;
        }
        issues.insert(issues.end(), other.issues.begin(), other.issues.end());
        warnings.insert(warnings.end(), other.warnings.begin(), other.warnings.end());
    }
};

// Context for tracking available tables and columns during analysis
struct AnalysisContext {
    map<string, string> tableAliases;  // alias -> actual table name
    vector<string> availableTables;     // tables in current scope
    map<string, DataType> columnTypes;  // qualified column name -> data type
    bool inAggregateContext;            // true if inside aggregate function
    bool inGroupByContext;              // true if GROUP BY is present
    vector<string> groupByColumns;      // columns in GROUP BY clause
    
    AnalysisContext() : inAggregateContext(false), inGroupByContext(false) {}
    
    void reset() {
        tableAliases.clear();
        availableTables.clear();
        columnTypes.clear();
        inAggregateContext = false;
        inGroupByContext = false;
        groupByColumns.clear();
    }
};

class SemanticAnalyzer {
private:
    SchemaCache* schemaCache;  
    string currentDatabase;
    AnalysisContext context;
    
    // AST analysis methods
    SemanticResult analyzeStatement(const Statement* stmt);
    SemanticResult analyzeSelectStatement(const SelectStmt* stmt);
    SemanticResult analyzeInsertStatement(const InsertStmt* stmt);
    SemanticResult analyzeUpdateStatement(const UpdateStmt* stmt);
    SemanticResult analyzeDeleteStatement(const DeleteStmt* stmt);
    SemanticResult analyzeCreateTableStatement(const CreateTableStmt* stmt);
    SemanticResult analyzeCreateDatabaseStatement(const CreateDatabaseStmt* stmt);
    SemanticResult analyzeCreateIndexStatement(const CreateIndexStmt* stmt);
    SemanticResult analyzeCreateViewStatement(const CreateViewStmt* stmt);
    SemanticResult analyzeDropStatement(const DropStmt* stmt);
    SemanticResult analyzeAlterStatement(const AlterStmt* stmt);
    
    // Expression analysis
    SemanticResult analyzeExpression(const Expression* expr, DataType& resultType);
    SemanticResult analyzeIdentifierExpression(const IdentifierExpr* expr, DataType& resultType);
    SemanticResult analyzeLiteralExpression(const LiteralExpr* expr, DataType& resultType);
    SemanticResult analyzeBinaryOpExpression(const BinaryOpExpr* expr, DataType& resultType);
    SemanticResult analyzeUnaryOpExpression(const UnaryOpExpr* expr, DataType& resultType);
    SemanticResult analyzeFunctionCallExpression(const FunctionCallExpr* expr, DataType& resultType);
    SemanticResult analyzeCaseExpression(const CaseExpr* expr, DataType& resultType);
    
    // Component analysis
    SemanticResult analyzeFromClause(const vector<unique_ptr<TableRef>>& fromList);
    SemanticResult analyzeTableReference(const TableRef* tableRef);
    SemanticResult analyzeJoinClause(const JoinClause* join);
    SemanticResult analyzeSelectList(const vector<unique_ptr<SelectItem>>& selectList);
    SemanticResult analyzeWhereClause(const Expression* whereExpr);
    SemanticResult analyzeGroupByClause(const vector<ExpressionPtr>& groupByList);
    SemanticResult analyzeHavingClause(const Expression* havingExpr);
    SemanticResult analyzeOrderByClause(const vector<pair<ExpressionPtr, bool>>& orderByList);
    SemanticResult analyzeOrderByList(const vector<pair<ExpressionPtr, bool>>& orderByList);
    
    // Legacy analysis methods (for backward compatibility)
    void analyzeTableReferences(const QueryComponents& components, SemanticResult& result);
    void analyzeColumnReferences(const QueryComponents& components, SemanticResult& result);
    void analyzeTypeCompatibility(const QueryComponents& components, SemanticResult& result);
    void analyzeConstraints(const QueryComponents& components, SemanticResult& result);
    void analyzePermissions(const QueryComponents& components, SemanticResult& result);
    void analyzeFunctions(const QueryComponents& components, SemanticResult& result);
    void analyzeJoins(const QueryComponents& components, SemanticResult& result);
    
    // Helper methods
    string resolveTableName(const string& tableName, const vector<TableReference>& tables);
    string resolveTableNameFromContext(const string& tableName);
    string resolveColumnName(const string& columnName, const string& tableName = "");
    bool isValidComparison(DataType leftType, DataType rightType, const string& operator_);
    DataType inferExpressionType(const string& expression, const QueryComponents& components);
    DataType getColumnDataType(const string& database, const string& table, const string& column);
    DataType literalToDataType(const LiteralExpr* literal);
    DataType getCompatibleType(DataType type1, DataType type2);
    DataType getBinaryOpResultType(const string& op, DataType leftType, DataType rightType);
    
    bool isAggregateFunction(const string& functionName);
    bool isNumericType(DataType type);
    bool isStringType(DataType type);
    bool isDateTimeType(DataType type);
    bool isValidCast(DataType fromType, DataType toType);
    
    vector<string> getSimilarNames(const string& name, const vector<string>& candidates);
    void addContextualSuggestion(SemanticIssue& issue, const string& type);
    
    // Validation helpers
    bool validateTableExists(const string& tableName, SemanticResult& result, int line = -1, int col = -1);
    bool validateColumnExists(const string& tableName, const string& columnName, 
                             SemanticResult& result, int line = -1, int col = -1);
    void validateColumnAmbiguity(const string& columnName, SemanticResult& result, int line = -1, int col = -1);
    void validateGroupByRules(const Expression* expr, SemanticResult& result);
    void validateAggregateUsage(const Expression* expr, SemanticResult& result);
    
public:
    SemanticAnalyzer(SchemaCache* cache);
    ~SemanticAnalyzer() = default;
    
    // Main analysis methods
    SemanticResult analyze(const QueryComponents& components);  // Legacy method
    SemanticResult analyze(const SqlProgram* program);          // New AST-based method
    SemanticResult analyze(const Statement* statement);        // Single statement analysis
    
    // Individual validation methods
    SemanticResult validateDatabaseExists(const string& database);
    SemanticResult validateTableExists(const string& database, const string& table);
    SemanticResult validateColumnExists(const string& database, const string& table, const string& column);
    SemanticResult validateTypeCompatibility(const ColumnReference& col1, const ColumnReference& col2, const string& operator_);
    SemanticResult validateNullConstraints(const ColumnReference& column, const string& value);
    SemanticResult validatePermissions(const string& operation, const string& database, const string& table);
    SemanticResult validateFunction(const FunctionCall& function);
    SemanticResult validateFunction(const string& functionName, const vector<DataType>& argTypes, 
                                   int line = -1, int col = -1);
    
    // Type checking
    SemanticResult validateAssignment(const string& columnName, const Expression* valueExpr, 
                                     const string& tableName);
    SemanticResult validateInsertValues(const string& tableName, const vector<string>& columns,
                                       const vector<ExpressionPtr>& values);
    SemanticResult validateJoinCondition(const Expression* condition);
    
    // Configuration
    void setCurrentDatabase(const string& database);
    void setSchemaCache(SchemaCache* cache);
    void resetContext();
    
    // Utility methods
    vector<string> suggestSimilarTables(const string& database, const string& tableName);
    vector<string> suggestSimilarColumns(const string& database, const string& table, const string& columnName);
    vector<string> suggestSimilarFunctions(const string& functionName);
    
    // Context management
    void pushTableToContext(const string& tableName, const string& alias = "");
    void addColumnToContext(const string& qualifiedColumnName, DataType type);
    bool isColumnInContext(const string& columnName, const string& tableName = "");
    
    // Debug utilities
    void printContext() const;
    void printAnalysisResult(const SemanticResult& result) const;
};

// Built-in function information
struct Functioninfo {
    string name;
    vector<DataType> parameterTypes;
    DataType returnType;
    bool isAggregate;
    bool acceptsVariableArgs;
    int minParams;
    int maxParams; // -1 for unlimited

    // default constructor

    Functioninfo()
        : name(""), returnType(DataType::UNKNOWN), isAggregate(false),
          acceptsVariableArgs(false), minParams(0), maxParams(-1) {}

    // param constructor
    
    Functioninfo(const string& n, DataType ret, bool agg = false, int minP = 0, int maxP = -1)
        : name(n), returnType(ret), isAggregate(agg), acceptsVariableArgs(maxP == -1), 
          minParams(minP), maxParams(maxP) {}
};

// Function registry for built-in functions
class FunctionRegistry {
private:
    static map<string, Functioninfo> functions;
    static bool initialized;
    static void initializeBuiltinFunctions();
    
public:
    static void initialize();
    static bool isValidFunction(const string& name);
    static const Functioninfo* getFunction(const string& name);
    static vector<string> getAllFunctionNames();
    static void registerFunction(const Functioninfo& func);
};

#endif // SEMANTIC_ANALYZER_H