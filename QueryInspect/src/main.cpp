#include <bits/stdc++.h>
#include "../include/QueryInspect.h"

using namespace std;

int main(int argc, char* argv[]) {
    cout << "SQL Parser Test - Processing queries from input...\n";
    cout << "================================================\n";
    
    string line;
    string currentStatement;
    int queryCount = 0;
    int successCount = 0;
    int errorCount = 0;
    
    QueryInspect inspector;
    
    while (getline(cin, line)) {
        // Skip empty lines
        if (line.empty()) continue;
        
        // Skip comment lines (starting with --)
        string trimmed = line;
        trimmed.erase(0, trimmed.find_first_not_of(" \t"));
        if (trimmed.find("--") == 0) continue;
        
        // Add line to current statement
        currentStatement += line + "\n";
        
        // Check if statement is complete (contains semicolon)
        if (line.find(';') != string::npos) {
            queryCount++;
            
            // Clean up the statement - remove extra whitespace and empty lines
            string cleanedStatement;
            istringstream iss(currentStatement);
            string statementLine;
            while (getline(iss, statementLine)) {
                string trimmedLine = statementLine;
                trimmedLine.erase(0, trimmedLine.find_first_not_of(" \t"));
                trimmedLine.erase(trimmedLine.find_last_not_of(" \t") + 1);
                
                if (!trimmedLine.empty() && trimmedLine.find("--") != 0) {
                    if (!cleanedStatement.empty()) cleanedStatement += " ";
                    cleanedStatement += trimmedLine;
                }
            }
            
            if (!cleanedStatement.empty() && cleanedStatement != ";") {
                cout << "\n--- Query #" << queryCount << " ---\n";
                cout << "Testing: " << cleanedStatement << "\n";
                
                // Analyze the SQL statement
                auto syntaxResult = inspector.syntaxAnalyze(cleanedStatement);
                
                if (syntaxResult.status == SyntaxStatus::VALID) {
                    cout << "✓ PASSED - Syntax Valid!\n";
                    successCount++;
                } else if (syntaxResult.status == SyntaxStatus::INCOMPLETE) {
                    cout << "✗ FAILED - Incomplete statement: " << syntaxResult.errorMessage << "\n";
                    cout << "  At line " << syntaxResult.errorLine << ", column " << syntaxResult.errorColumn << "\n";
                    errorCount++;
                } else {
                    cout << "✗ FAILED - Syntax Error: " << syntaxResult.errorMessage << "\n";
                    cout << "  At line " << syntaxResult.errorLine << ", column " << syntaxResult.errorColumn << "\n";
                    errorCount++;
                }
            } else {
                queryCount--; // Don't count empty statements
            }
            
            // Reset for next statement
            currentStatement = "";
        }
    }
    
    // Handle case where last statement doesn't end with semicolon
    if (!currentStatement.empty()) {
        queryCount++;
        cout << "\n--- Query #" << queryCount << " (missing semicolon) ---\n";
        cout << "Testing: " << currentStatement << "\n";
        
        auto syntaxResult = inspector.syntaxAnalyze(currentStatement);
        
        if (syntaxResult.status == SyntaxStatus::VALID) {
            cout << "✓ PASSED - Syntax Valid!\n";
            successCount++;
        } else {
            cout << "✗ FAILED - Parse Error\n";
            errorCount++;
        }
    }
    
    // Print summary
    cout << "\n================================================\n";
    cout << "TEST SUMMARY:\n";
    cout << "Total queries processed: " << queryCount << "\n";
    cout << "Successful parses: " << successCount << "\n";
    cout << "Failed parses: " << errorCount << "\n";
    if (queryCount > 0) {
        cout << "Success rate: " << (successCount * 100 / queryCount) << "%\n";
    }
    cout << "================================================\n";
    
    return 0;
}