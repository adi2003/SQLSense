#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

int main() {
    try {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;

        // Create a connection
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "schema_reader", "schema_password");
        
        // Connect to information_schema database
        con->setSchema("information_schema");
        
        cout << "✅ Connected to MySQL successfully!" << endl;
        
        // Test query
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT VERSION() AS version");
        
        while (res->next()) {
            cout << "MySQL Version: " << res->getString("version") << endl;
        }
        
        // Clean up
        delete res;
        delete stmt;
        delete con;
        
    } catch (sql::SQLException &e) {
        cout << "❌ SQLException: " << e.what() << endl;
        cout << "Error Code: " << e.getErrorCode() << endl;
        cout << "SQLState: " << e.getSQLState() << endl;
        return 1;
    }
    
    return 0;
}
