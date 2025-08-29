#include "../include/QueryInspect.h"
#include <memory>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

// Simple schema cache implementation
class SimpleSchemaCache {
private:
    sql::Driver* driver;
    sql::Connection* connection;
    map<string, vector<string>> databaseTables;  // database -> tables
    map<string, map<string, vector<string>>> tableColumns;  // database -> table -> columns
    map<string, map<string, map<string, string>>> columnTypes;  // database -> table -> column -> type
    bool connected;
    
public:
    SimpleSchemaCache() : driver(nullptr), connection(nullptr), connected(false) {
        driver = get_driver_instance();
    }
    
    ~SimpleSchemaCache() {
        if (connection) {
            delete connection;
        }
    }
    
    bool connect(const string& host = "127.0.0.1", int port = 3306, 
                const string& user = "schema_reader", const string& password = "schema_password") {
        try {
            string connectionString = "tcp://" + host + ":" + to_string(port);
            connection = driver->connect(connectionString, user, password);
            connection->setSchema("information_schema");
            connected = true;
            return true;
        } catch (sql::SQLException& e) {
            cerr << "Schema cache connection failed: " << e.what() << endl;
            connected = false;
            return false;
        }
    }
    
    void loadDatabases() {
        if (!connected) return;
        
        try {
            sql::PreparedStatement* pstmt = connection->prepareStatement(
                "SELECT SCHEMA_NAME FROM SCHEMATA "
                "WHERE SCHEMA_NAME NOT IN ('information_schema', 'performance_schema', 'mysql', 'sys') "
                "ORDER BY SCHEMA_NAME"
            );
            
            sql::ResultSet* res = pstmt->executeQuery();
            
            while (res->next()) {
                string dbName = res->getString("SCHEMA_NAME");
                if (databaseTables.find(dbName) == databaseTables.end()) {
                    databaseTables[dbName] = vector<string>();
                    loadTablesForDatabase(dbName);
                }
            }
            
            delete res;
            delete pstmt;
        } catch (sql::SQLException& e) {
            cerr << "Error loading databases: " << e.what() << endl;
        }
    }
    
    void loadTablesForDatabase(const string& database) {
        if (!connected) return;
        
        try {
            sql::PreparedStatement* pstmt = connection->prepareStatement(
                "SELECT TABLE_NAME FROM TABLES WHERE TABLE_SCHEMA = ? ORDER BY TABLE_NAME"
            );
            
            pstmt->setString(1, database);
            sql::ResultSet* res = pstmt->executeQuery();
            
            while (res->next()) {
                string tableName = res->getString("TABLE_NAME");
                databaseTables[database].push_back(tableName);
                loadColumnsForTable(database, tableName);
            }
            
            delete res;
            delete pstmt;
        } catch (sql::SQLException& e) {
            cerr << "Error loading tables for " << database << ": " << e.what() << endl;
        }
    }
    
    void loadColumnsForTable(const string& database, const string& table) {
        if (!connected) return;
        
        try {
            sql::PreparedStatement* pstmt = connection->prepareStatement(
                "SELECT COLUMN_NAME, DATA_TYPE FROM COLUMNS "
                "WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ? ORDER BY ORDINAL_POSITION"
            );
            
            pstmt->setString(1, database);
            pstmt->setString(2, table);
            sql::ResultSet* res = pstmt->executeQuery();
            
            while (res->next()) {
                string columnName = res->getString("COLUMN_NAME");
                string dataType = res->getString("DATA_TYPE");
                
                tableColumns[database][table].push_back(columnName);
                columnTypes[database][table][columnName] = dataType;
            }
            
            delete res;
            delete pstmt;
        } catch (sql::SQLException& e) {
            cerr << "Error loading columns for " << database << "." << table << ": " << e.what() << endl;
        }
    }
    
    vector<string> getDatabases() {
        vector<string> databases;
        for (const auto& pair : databaseTables) {
            databases.push_back(pair.first);
        }
        return databases;
    }
    
    bool databaseExists(const string& database) {
        return databaseTables.find(database) != databaseTables.end();
    }
    
    bool tableExists(const string& database, const string& table) {
        if (!databaseExists(database)) return false;
        auto& tables = databaseTables[database];
        return find(tables.begin(), tables.end(), table) != tables.end();
    }
    
    bool columnExists(const string& database, const string& table, const string& column) {
        if (!tableExists(database, table)) return false;
        auto& columns = tableColumns[database][table];
        return find(columns.begin(), columns.end(), column) != columns.end();
    }
    
    bool isConnected() const { return connected; }
};

// QueryInspect implementation
QueryInspect::QueryInspect() : schemaCache(nullptr), semanticEnabled(false) {}

QueryInspect::~QueryInspect() {
    if (schemaCache) {
        delete schemaCache;
    }
}

SyntaxResult QueryInspect::syntaxAnalyze(const string& query) {
    SyntaxAnalyzer analyzer;
    return analyzer.analyze(query);
}

bool QueryInspect::initializeSemanticAnalysis(const string& host, int port, 
                                            const string& user, const string& password) {
    if (schemaCache) {
        delete schemaCache;
    }
    
    schemaCache = new SimpleSchemaCache();
    
    if (!schemaCache->connect(host, port, user, password)) {
        delete schemaCache;
        schemaCache = nullptr;
        semanticEnabled = false;
        return false;
    }
    
    cout << "🔗 Connected to MySQL for semantic analysis\n";
    cout << "📚 Loading schema cache...\n";
    
    schemaCache->loadDatabases();
    semanticEnabled = true;
    
    return true;
}

SimpleSemanticResult QueryInspect::semanticAnalyze(const string& query) {
    SimpleSemanticResult result;
    
    if (!semanticEnabled) {
        result.addIssue(SimpleSemanticIssue("Semantic analysis not initialized"));
        return result;
    }
    
    // Simple semantic analysis - you can expand this
    string upperQuery = query;
    transform(upperQuery.begin(), upperQuery.end(), upperQuery.begin(), ::toupper);
    
    // Check for obvious table references
    if (upperQuery.find("FROM ") != string::npos) {
        size_t fromPos = upperQuery.find("FROM ");
        size_t spaceAfterFrom = upperQuery.find(" ", fromPos + 5);
        if (spaceAfterFrom != string::npos) {
            string tablePart = upperQuery.substr(fromPos + 5, spaceAfterFrom - fromPos - 5);
            
            // Remove common keywords and clean up
            if (tablePart.find("WHERE") != string::npos) {
                tablePart = tablePart.substr(0, tablePart.find("WHERE"));
            }
            if (tablePart.find("ORDER") != string::npos) {
                tablePart = tablePart.substr(0, tablePart.find("ORDER"));
            }
            if (tablePart.find("GROUP") != string::npos) {
                tablePart = tablePart.substr(0, tablePart.find("GROUP"));
            }
            if (tablePart.find("LIMIT") != string::npos) {
                tablePart = tablePart.substr(0, tablePart.find("LIMIT"));
            }
            
            // Clean whitespace
            tablePart.erase(0, tablePart.find_first_not_of(" \t"));
            tablePart.erase(tablePart.find_last_not_of(" \t") + 1);
            
            if (!tablePart.empty()) {
                // Check if table exists in current database
                if (!currentDatabase.empty()) {
                    if (!schemaCache->tableExists(currentDatabase, tablePart)) {
                        // Check if it exists in information_schema (common case)
                        if (schemaCache->tableExists("information_schema", tablePart)) {
                            result.addWarning("Table '" + tablePart + "' found in information_schema");
                        } else {
                            result.addIssue(SimpleSemanticIssue(
                                "Table '" + tablePart + "' does not exist in database '" + currentDatabase + "'",
                                "Check table name spelling or verify database context"
                            ));
                        }
                    }
                }
            }
        }
    }
    
    // Check for potential type mismatches (simple heuristic)
    if (upperQuery.find("WHERE") != string::npos) {
        if (upperQuery.find("NAME >") != string::npos || upperQuery.find("NAME<") != string::npos) {
            result.addIssue(SimpleSemanticIssue(
                "Potential type mismatch: comparing text field 'name' with numeric operator",
                "Use string comparison operators like = or LIKE for text fields"
            ));
        }
    }
    
    // Check for common dangerous operations
    if (upperQuery.find("DROP TABLE") != string::npos) {
        result.addIssue(SimpleSemanticIssue(
            "DROP TABLE operation detected - potentially destructive",
            "Verify you have permission and backup before dropping tables"
        ));
    }
    
    if (upperQuery.find("DELETE FROM") != string::npos && upperQuery.find("WHERE") == string::npos) {
        result.addWarning("DELETE without WHERE clause - will delete all rows");
    }
    
    return result;
}

EnhancedAnalysisResult QueryInspect::analyzeComplete(const string& query) {
    EnhancedAnalysisResult result;
    
    // First perform syntax analysis
    result.syntaxResult = syntaxAnalyze(query);
    result.overallValid = (result.syntaxResult.status == SyntaxStatus::VALID);
    
    // If syntax is valid and semantic analysis is enabled, perform semantic analysis
    if (result.overallValid && semanticEnabled) {
        result.semanticResult = semanticAnalyze(query);
        result.overallValid = result.overallValid && result.semanticResult.isValid;
    }
    
    return result;
}

void QueryInspect::setDefaultDatabase(const string& database) {
    currentDatabase = database;
}

vector<string> QueryInspect::getAvailableDatabases() {
    if (!semanticEnabled || !schemaCache) {
        return vector<string>();
    }
    return schemaCache->getDatabases();
}

void QueryInspect::refreshSchemaCache() {
    if (semanticEnabled && schemaCache) {
        schemaCache->loadDatabases();
        cout << "✅ Schema cache refreshed\n";
    }
}

bool QueryInspect::isSemanticAnalysisEnabled() const {
    return semanticEnabled;
}