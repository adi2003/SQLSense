#ifndef SCHEMA_CACHE_H
#define SCHEMA_CACHE_H

#include <bits/stdc++.h>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <mutex>
#include <chrono>

using namespace std;

// Forward declaration
struct ColumnInfo;
struct TableInfo;
struct DatabaseInfo;
struct FunctionInfo;

enum class DataType {
    INTEGER, BIGINT, SMALLINT, TINYINT,
    DECIMAL, FLOAT, DOUBLE,
    VARCHAR, CHAR, TEXT, LONGTEXT,
    DATE, TIME, DATETIME, TIMESTAMP,
    BOOLEAN, BINARY, JSON,
    UNKNOWN
};

enum class ConstraintType {
    PRIMARY_KEY,
    FOREIGN_KEY, 
    UNIQUE,
    CHECK,
    NOT_NULL,
    DEFAULT_VALUE
};

struct ConstraintInfo {
    ConstraintType type;
    string name;
    string referencedTable;
    string referencedColumn;
    string checkExpression;
    string defaultValue;
};

struct ColumnInfo {
    string name;
    DataType dataType;
    string rawDataType;  // Original MySQL type string
    bool isNullable;
    bool isPrimaryKey;
    bool isAutoIncrement;
    vector<ConstraintInfo> constraints;
    int ordinalPosition;
    
    ColumnInfo() : isNullable(true), isPrimaryKey(false), isAutoIncrement(false), ordinalPosition(0) {}
};

struct IndexInfo {
    string name;
    string type;  // PRIMARY, UNIQUE, INDEX
    vector<string> columns;
    bool isUnique;
};

struct TableInfo {
    string name;
    string type;  // TABLE, VIEW
    string engine;
    map<string, ColumnInfo> columns;
    vector<IndexInfo> indexes;
    vector<string> primaryKeys;
    map<string, string> foreignKeys;  // column -> referenced_table.referenced_column
    
    TableInfo() = default;
};

struct FunctionInfo {
    string name;
    string type;  // FUNCTION, PROCEDURE
    vector<string> parameters;
    string returnType;
};

struct DatabaseInfo {
    string name;
    map<string, TableInfo> tables;
    vector<FunctionInfo> functions;
    chrono::steady_clock::time_point lastUpdated;
    
    DatabaseInfo() = default;
};

struct UserPrivileges {
    map<string, map<string, set<string>>> databaseTablePrivileges;  // db -> table -> privileges
    set<string> globalPrivileges;
};

class SchemaCache {
public:
    sql::Driver* driver;
    sql::Connection* connection;
    
    map<string, DatabaseInfo> databases;
    UserPrivileges userPrivileges;
    
    mutable mutex cacheMutex;
    
    string connectionHost;
    int connectionPort;
    string username;
    string password;
    
    chrono::minutes cacheExpiryTime;
    
    // Helper methods
    DataType parseDataType(const string& mysqlType);
    void loadDatabaseList();
    void loadTableInfo(const string& databaseName);
    void loadColumnInfo(const string& databaseName, const string& tableName);
    void loadIndexInfo(const string& databaseName, const string& tableName);
    void loadFunctionInfo(const string& databaseName);
    void loadUserPrivileges();
    bool isExpired(const chrono::steady_clock::time_point& lastUpdated);

    SchemaCache(const string& host = "127.0.0.1", const int port = 3306, 
                const string& user = "schema_reader", const string& pass = "schema_password");
    ~SchemaCache();
    
    // Connection management
    bool connect();
    void disconnect();
    bool isConnected();
    
    // Cache management
    void refreshCache();
    void refreshDatabase(const string& databaseName);
    void clearCache();
    void setCacheExpiry(chrono::minutes expiry);
    
    // Schema querying
    vector<string> getDatabases();
    bool databaseExists(const string& databaseName);
    bool tableExists(const string& databaseName, const string& tableName);
    bool columnExists(const string& databaseName, const string& tableName, const string& columnName);
    
    // Detailed information retrieval
    const DatabaseInfo* getDatabaseInfo(const string& databaseName);
    const TableInfo* getTableInfo(const string& databaseName, const string& tableName);
    const ColumnInfo* getColumnInfo(const string& databaseName, const string& tableName, const string& columnName);
    
    // Type compatibility checking
    bool areTypesCompatible(DataType type1, DataType type2);
    bool canCompareTypes(DataType type1, DataType type2);
    DataType getColumnDataType(const string& databaseName, const string& tableName, const string& columnName);
    
    // Constraint validation
    bool isColumnNullable(const string& databaseName, const string& tableName, const string& columnName);
    vector<ConstraintInfo> getColumnConstraints(const string& databaseName, const string& tableName, const string& columnName);
    
    // Function validation
    bool functionExists(const string& databaseName, const string& functionName);
    vector<string> getAvailableFunctions(const string& databaseName = "");
    
    // Privilege checking
    bool hasPrivilege(const string& privilege, const string& databaseName = "", const string& tableName = "");
    set<string> getUserPrivileges(const string& databaseName = "", const string& tableName = "");
    
    // Debug and statistics
    void printCacheStats();
    size_t getCacheSize();
};

#endif // SCHEMA_CACHE_H