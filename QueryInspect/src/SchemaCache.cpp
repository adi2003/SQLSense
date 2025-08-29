#include "../include/SchemaCache.h"
#include <algorithm>
#include <sstream>

SchemaCache::SchemaCache(const string& host, int port, const string& user, const string& pass)
    : driver(nullptr), connection(nullptr), connectionHost(host), connectionPort(port),
      username(user), password(pass), cacheExpiryTime(chrono::minutes(60)) {
    
    driver = get_driver_instance();
}

SchemaCache::~SchemaCache() {
    disconnect();
}

bool SchemaCache::connect() {
    try {
        if (connection && !connection->isClosed()) {
            return true;
        }
        
        string connectionString = "tcp://" + connectionHost + ":" + to_string(connectionPort);
        connection = driver->connect(connectionString, username, password);
        connection->setSchema("information_schema");
        
        return true;
    } catch (sql::SQLException& e) {
        cerr << "Schema cache connection failed: " << e.what() << endl;
        return false;
    }
}

void SchemaCache::disconnect() {
    if (connection) {
        delete connection;
        connection = nullptr;
    }
}

bool SchemaCache::isConnected() {
    return connection && !connection->isClosed();
}

DataType SchemaCache::parseDataType(const string& mysqlType) {
    string type = mysqlType;
    transform(type.begin(), type.end(), type.begin(), ::tolower);
    
    if (type.find("int") != string::npos) {
        if (type.find("bigint") != string::npos) return DataType::BIGINT;
        if (type.find("smallint") != string::npos) return DataType::SMALLINT;
        if (type.find("tinyint") != string::npos) return DataType::TINYINT;
        return DataType::INTEGER;
    }
    
    if (type.find("decimal") != string::npos || type.find("numeric") != string::npos) {
        return DataType::DECIMAL;
    }
    
    if (type.find("float") != string::npos) return DataType::FLOAT;
    if (type.find("double") != string::npos) return DataType::DOUBLE;
    
    if (type.find("varchar") != string::npos) return DataType::VARCHAR;
    if (type.find("char") != string::npos && type.find("varchar") == string::npos) return DataType::CHAR;
    if (type.find("text") != string::npos) {
        if (type.find("longtext") != string::npos) return DataType::LONGTEXT;
        return DataType::TEXT;
    }
    
    if (type.find("date") != string::npos) return DataType::DATE;
    if (type.find("time") != string::npos) {
        if (type.find("datetime") != string::npos) return DataType::DATETIME;
        if (type.find("timestamp") != string::npos) return DataType::TIMESTAMP;
        return DataType::TIME;
    }
    
    if (type.find("boolean") != string::npos || type.find("bool") != string::npos) {
        return DataType::BOOLEAN;
    }
    
    if (type.find("binary") != string::npos || type.find("blob") != string::npos) {
        return DataType::BINARY;
    }
    
    if (type.find("json") != string::npos) return DataType::JSON;
    
    return DataType::UNKNOWN;
}

void SchemaCache::loadDatabaseList() {
    if (!isConnected() && !connect()) return;
    
    try {
        sql::PreparedStatement* pstmt = connection->prepareStatement(
            "SELECT SCHEMA_NAME FROM SCHEMATA "
            "WHERE SCHEMA_NAME NOT IN ('information_schema', 'performance_schema', 'mysql', 'sys') "
            "ORDER BY SCHEMA_NAME"
        );
        
        sql::ResultSet* res = pstmt->executeQuery();
        
        while (res->next()) {
            string dbName = res->getString("SCHEMA_NAME");
            if (databases.find(dbName) == databases.end()) {
                databases[dbName] = DatabaseInfo();
                databases[dbName].name = dbName;
                databases[dbName].lastUpdated = chrono::steady_clock::now();
            }
        }
        
        delete res;
        delete pstmt;
    } catch (sql::SQLException& e) {
        cerr << "Error loading database list: " << e.what() << endl;
    }
}

void SchemaCache::loadTableInfo(const string& databaseName) {
    if (!isConnected() && !connect()) return;
    
    try {
        sql::PreparedStatement* pstmt = connection->prepareStatement(
            "SELECT TABLE_NAME, TABLE_TYPE, ENGINE "
            "FROM TABLES "
            "WHERE TABLE_SCHEMA = ? "
            "ORDER BY TABLE_NAME"
        );
        
        pstmt->setString(1, databaseName);
        sql::ResultSet* res = pstmt->executeQuery();
        
        while (res->next()) {
            string tableName = res->getString("TABLE_NAME");
            
            TableInfo& tableInfo = databases[databaseName].tables[tableName];
            tableInfo.name = tableName;
            tableInfo.type = res->getString("TABLE_TYPE");
            tableInfo.engine = res->isNull("ENGINE") ? "N/A" : res->getString("ENGINE");
            
            // Load column information for this table
            loadColumnInfo(databaseName, tableName);
            loadIndexInfo(databaseName, tableName);
        }
        
        delete res;
        delete pstmt;
    } catch (sql::SQLException& e) {
        cerr << "Error loading table info for " << databaseName << ": " << e.what() << endl;
    }
}

void SchemaCache::loadColumnInfo(const string& databaseName, const string& tableName) {
    if (!isConnected() && !connect()) return;
    
    try {
        sql::PreparedStatement* pstmt = connection->prepareStatement(
            "SELECT "
            "    COLUMN_NAME, DATA_TYPE, IS_NULLABLE, "
            "    COLUMN_DEFAULT, COLUMN_KEY, EXTRA, ORDINAL_POSITION "
            "FROM COLUMNS "
            "WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ? "
            "ORDER BY ORDINAL_POSITION"
        );
        
        pstmt->setString(1, databaseName);
        pstmt->setString(2, tableName);
        
        sql::ResultSet* res = pstmt->executeQuery();
        
        while (res->next()) {
            ColumnInfo column;
            column.name = res->getString("COLUMN_NAME");
            column.rawDataType = res->getString("DATA_TYPE");
            column.dataType = parseDataType(column.rawDataType);
            column.isNullable = (res->getString("IS_NULLABLE") == "YES");
            column.isPrimaryKey = (res->getString("COLUMN_KEY") == "PRI");
            column.isAutoIncrement = (res->getString("EXTRA").find("auto_increment") != string::npos);
            column.ordinalPosition = res->getInt("ORDINAL_POSITION");
            
            // Add constraints
            if (!column.isNullable) {
                ConstraintInfo constraint;
                constraint.type = ConstraintType::NOT_NULL;
                constraint.name = "NOT_NULL_" + column.name;
                column.constraints.push_back(constraint);
            }
            
            if (column.isPrimaryKey) {
                ConstraintInfo constraint;
                constraint.type = ConstraintType::PRIMARY_KEY;
                constraint.name = "PRIMARY_" + column.name;
                column.constraints.push_back(constraint);
                
                databases[databaseName].tables[tableName].primaryKeys.push_back(column.name);
            }
            
            string defaultValue = res->getString("COLUMN_DEFAULT");
            if (!res->isNull("COLUMN_DEFAULT")) {
                ConstraintInfo constraint;
                constraint.type = ConstraintType::DEFAULT_VALUE;
                constraint.defaultValue = defaultValue;
                constraint.name = "DEFAULT_" + column.name;
                column.constraints.push_back(constraint);
            }
            
            databases[databaseName].tables[tableName].columns[column.name] = column;
        }
        
        delete res;
        delete pstmt;
    } catch (sql::SQLException& e) {
        cerr << "Error loading column info for " << databaseName << "." << tableName << ": " << e.what() << endl;
    }
}

void SchemaCache::loadIndexInfo(const string& databaseName, const string& tableName) {
    if (!isConnected() && !connect()) return;
    
    try {
        sql::PreparedStatement* pstmt = connection->prepareStatement(
            "SELECT "
            "    CONSTRAINT_NAME, CONSTRAINT_TYPE, COLUMN_NAME, "
            "    REFERENCED_TABLE_SCHEMA, REFERENCED_TABLE_NAME, REFERENCED_COLUMN_NAME "
            "FROM KEY_COLUMN_USAGE "
            "WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ? "
            "ORDER BY CONSTRAINT_NAME, ORDINAL_POSITION"
        );
        
        pstmt->setString(1, databaseName);
        pstmt->setString(2, tableName);
        
        sql::ResultSet* res = pstmt->executeQuery();
        
        while (res->next()) {
            string constraintName = res->getString("CONSTRAINT_NAME");
            string constraintType = res->getString("CONSTRAINT_TYPE");
            string columnName = res->getString("COLUMN_NAME");
            
            if (!res->isNull("REFERENCED_TABLE_NAME")) {
                // Foreign key constraint
                string refTable = res->getString("REFERENCED_TABLE_NAME");
                string refColumn = res->getString("REFERENCED_COLUMN_NAME");
                string refSchema = res->getString("REFERENCED_TABLE_SCHEMA");
                
                databases[databaseName].tables[tableName].foreignKeys[columnName] = 
                    refSchema + "." + refTable + "." + refColumn;
                
                // Add foreign key constraint to column
                auto& column = databases[databaseName].tables[tableName].columns[columnName];
                ConstraintInfo constraint;
                constraint.type = ConstraintType::FOREIGN_KEY;
                constraint.name = constraintName;
                constraint.referencedTable = refTable;
                constraint.referencedColumn = refColumn;
                column.constraints.push_back(constraint);
            }
        }
        
        delete res;
        delete pstmt;
    } catch (sql::SQLException& e) {
        cerr << "Error loading index info for " << databaseName << "." << tableName << ": " << e.what() << endl;
    }
}

void SchemaCache::loadFunctionInfo(const string& databaseName) {
    // Basic implementation - can be expanded
    if (!isConnected() && !connect()) return;
    
    try {
        sql::PreparedStatement* pstmt = connection->prepareStatement(
            "SELECT ROUTINE_NAME, ROUTINE_TYPE FROM ROUTINES WHERE ROUTINE_SCHEMA = ?"
        );
        
        pstmt->setString(1, databaseName);
        sql::ResultSet* res = pstmt->executeQuery();
        
        while (res->next()) {
            FunctionInfo func;
            func.name = res->getString("ROUTINE_NAME");
            func.type = res->getString("ROUTINE_TYPE");
            databases[databaseName].functions.push_back(func);
        }
        
        delete res;
        delete pstmt;
    } catch (sql::SQLException& e) {
        // Ignore errors for now - functions are optional
    }
}

void SchemaCache::loadUserPrivileges() {
    // Basic implementation - can be expanded
    // For now, assume schema_reader has SELECT privileges
    userPrivileges.globalPrivileges.insert("SELECT");
}

void SchemaCache::refreshCache() {
    lock_guard<mutex> lock(cacheMutex);
    
    databases.clear();
    loadDatabaseList();
    
    for (auto& [dbName, dbInfo] : databases) {
        loadTableInfo(dbName);
        loadFunctionInfo(dbName);
    }
    
    loadUserPrivileges();
    
    cout << "✅ Schema cache refreshed for " << databases.size() << " databases" << endl;
}

void SchemaCache::refreshDatabase(const string& databaseName) {
    lock_guard<mutex> lock(cacheMutex);
    
    if (databases.find(databaseName) != databases.end()) {
        databases[databaseName].tables.clear();
        databases[databaseName].functions.clear();
    } else {
        databases[databaseName] = DatabaseInfo();
        databases[databaseName].name = databaseName;
    }
    
    loadTableInfo(databaseName);
    loadFunctionInfo(databaseName);
    databases[databaseName].lastUpdated = chrono::steady_clock::now();
    
    cout << "✅ Refreshed schema cache for database: " << databaseName << endl;
}

void SchemaCache::clearCache() {
    lock_guard<mutex> lock(cacheMutex);
    databases.clear();
}

void SchemaCache::setCacheExpiry(chrono::minutes expiry) {
    cacheExpiryTime = expiry;
}

vector<string> SchemaCache::getDatabases() {
    lock_guard<mutex> lock(cacheMutex);
    
    if (databases.empty()) {
        loadDatabaseList();
    }
    
    vector<string> result;
    for (const auto& [name, info] : databases) {
        result.push_back(name);
    }
    return result;
}

bool SchemaCache::databaseExists(const string& databaseName) {
    lock_guard<mutex> lock(cacheMutex);
    
    if (databases.empty()) {
        loadDatabaseList();
    }
    
    return databases.find(databaseName) != databases.end();
}

bool SchemaCache::tableExists(const string& databaseName, const string& tableName) {
    lock_guard<mutex> lock(cacheMutex);
    
    auto dbIt = databases.find(databaseName);
    if (dbIt == databases.end()) {
        if (databaseExists(databaseName)) {
            loadTableInfo(databaseName);
            dbIt = databases.find(databaseName);
        } else {
            return false;
        }
    }
    
    if (dbIt->second.tables.empty() || isExpired(dbIt->second.lastUpdated)) {
        loadTableInfo(databaseName);
    }
    
    return dbIt->second.tables.find(tableName) != dbIt->second.tables.end();
}

bool SchemaCache::columnExists(const string& databaseName, const string& tableName, const string& columnName) {
    lock_guard<mutex> lock(cacheMutex);
    
    if (!tableExists(databaseName, tableName)) {
        return false;
    }
    
    auto& table = databases[databaseName].tables[tableName];
    return table.columns.find(columnName) != table.columns.end();
}

const DatabaseInfo* SchemaCache::getDatabaseInfo(const string& databaseName) {
    lock_guard<mutex> lock(cacheMutex);
    
    auto it = databases.find(databaseName);
    if (it != databases.end()) {
        return &it->second;
    }
    return nullptr;
}

const TableInfo* SchemaCache::getTableInfo(const string& databaseName, const string& tableName) {
    lock_guard<mutex> lock(cacheMutex);
    
    if (!tableExists(databaseName, tableName)) {
        return nullptr;
    }
    
    return &databases[databaseName].tables[tableName];
}

const ColumnInfo* SchemaCache::getColumnInfo(const string& databaseName, const string& tableName, const string& columnName) {
    lock_guard<mutex> lock(cacheMutex);
    
    if (!columnExists(databaseName, tableName, columnName)) {
        return nullptr;
    }
    
    return &databases[databaseName].tables[tableName].columns[columnName];
}

bool SchemaCache::areTypesCompatible(DataType type1, DataType type2) {
    if (type1 == type2) return true;
    
    // Numeric type compatibility
    set<DataType> numericTypes = {
        DataType::INTEGER, DataType::BIGINT, DataType::SMALLINT, DataType::TINYINT,
        DataType::DECIMAL, DataType::FLOAT, DataType::DOUBLE
    };
    
    if (numericTypes.count(type1) && numericTypes.count(type2)) {
        return true;
    }
    
    // String type compatibility
    set<DataType> stringTypes = {
        DataType::VARCHAR, DataType::CHAR, DataType::TEXT, DataType::LONGTEXT
    };
    
    if (stringTypes.count(type1) && stringTypes.count(type2)) {
        return true;
    }
    
    // Date/time compatibility
    set<DataType> dateTimeTypes = {
        DataType::DATE, DataType::TIME, DataType::DATETIME, DataType::TIMESTAMP
    };
    
    if (dateTimeTypes.count(type1) && dateTimeTypes.count(type2)) {
        return true;
    }
    
    return false;
}

bool SchemaCache::canCompareTypes(DataType type1, DataType type2) {
    return areTypesCompatible(type1, type2);
}

DataType SchemaCache::getColumnDataType(const string& databaseName, const string& tableName, const string& columnName) {
    lock_guard<mutex> lock(cacheMutex);
    
    if (!columnExists(databaseName, tableName, columnName)) {
        return DataType::UNKNOWN;
    }
    
    return databases[databaseName].tables[tableName].columns[columnName].dataType;
}

bool SchemaCache::isColumnNullable(const string& databaseName, const string& tableName, const string& columnName) {
    lock_guard<mutex> lock(cacheMutex);
    
    if (!columnExists(databaseName, tableName, columnName)) {
        return false;
    }
    
    return databases[databaseName].tables[tableName].columns[columnName].isNullable;
}

vector<ConstraintInfo> SchemaCache::getColumnConstraints(const string& databaseName, const string& tableName, const string& columnName) {
    lock_guard<mutex> lock(cacheMutex);
    
    if (!columnExists(databaseName, tableName, columnName)) {
        return vector<ConstraintInfo>();
    }
    
    return databases[databaseName].tables[tableName].columns[columnName].constraints;
}

bool SchemaCache::functionExists(const string& databaseName, const string& functionName) {
    lock_guard<mutex> lock(cacheMutex);
    
    auto dbIt = databases.find(databaseName);
    if (dbIt == databases.end()) {
        return false;
    }
    
    for (const auto& func : dbIt->second.functions) {
        if (func.name == functionName) {
            return true;
        }
    }
    return false;
}

vector<string> SchemaCache::getAvailableFunctions(const string& databaseName) {
    lock_guard<mutex> lock(cacheMutex);
    
    vector<string> functions;
    
    if (databaseName.empty()) {
        // Return global functions
        return functions;
    }
    
    auto dbIt = databases.find(databaseName);
    if (dbIt != databases.end()) {
        for (const auto& func : dbIt->second.functions) {
            functions.push_back(func.name);
        }
    }
    
    return functions;
}

bool SchemaCache::hasPrivilege(const string& privilege, const string& databaseName, const string& tableName) {
    // Simple implementation - assume schema_reader has SELECT privilege
    return privilege == "SELECT";
}

set<string> SchemaCache::getUserPrivileges(const string& databaseName, const string& tableName) {
    return userPrivileges.globalPrivileges;
}

void SchemaCache::printCacheStats() {
    lock_guard<mutex> lock(cacheMutex);
    
    cout << "\n📊 Schema Cache Statistics:" << endl;
    cout << "=========================" << endl;
    cout << "Databases cached: " << databases.size() << endl;
    
    int totalTables = 0, totalColumns = 0;
    for (const auto& [dbName, dbInfo] : databases) {
        totalTables += dbInfo.tables.size();
        for (const auto& [tableName, tableInfo] : dbInfo.tables) {
            totalColumns += tableInfo.columns.size();
        }
    }
    
    cout << "Total tables: " << totalTables << endl;
    cout << "Total columns: " << totalColumns << endl;
    cout << "Cache expiry: " << cacheExpiryTime.count() << " minutes" << endl;
    cout << "=========================" << endl;
}

size_t SchemaCache::getCacheSize() {
    lock_guard<mutex> lock(cacheMutex);
    return databases.size();
}

bool SchemaCache::isExpired(const chrono::steady_clock::time_point& lastUpdated) {
    auto now = chrono::steady_clock::now();
    auto elapsed = chrono::duration_cast<chrono::minutes>(now - lastUpdated);
    return elapsed >= cacheExpiryTime;
}