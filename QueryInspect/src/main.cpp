#include <bits/stdc++.h>
#include "../include/QueryInspect.h"

using namespace std;

void printWelcome() {
    cout << "SQLSense - Enhanced SQL Query Analyzer\n";
    cout << "======================================\n";
    cout << "Features:\n";
    cout << "  ✓ Syntax Analysis (Flex/Bison parser)\n";
    cout << "  ✓ Semantic Analysis (Schema validation)\n";
    cout << "  ✓ Type Compatibility Checking\n";
    cout << "  ✓ Table/Column Existence Validation\n";
    cout << "======================================\n\n";
}

int main(int argc, char* argv[]) {
    printWelcome();
    
    cout << "🔧 Initializing SQLSense...\n";
    
    QueryInspect inspector;
    // This initializes the cache at startup
    bool semanticEnabled = inspector.initializeSemanticAnalysis();
    
    if (semanticEnabled) {
        cout << "✅ Semantic analysis ready!\n";
        
        // Show available databases
        auto databases = inspector.getAvailableDatabases();
        if (!databases.empty()) {
            cout << "📂 Available databases: ";
            for (size_t i = 0; i < databases.size(); ++i) {
                cout << databases[i];
                if (i < databases.size() - 1) cout << ", ";
            }
            cout << "\n";
            
            // Set first database as default if available
            inspector.setDefaultDatabase(databases[0]);
            cout << "🎯 Default database: " << databases[0] << "\n";
        }
    } else {
        cout << "⚠️  Semantic analysis unavailable (syntax-only mode)\n";
    }
    
    cout << "\nSQL Parser Test - Processing queries from input...\n";
    cout << "================================================\n";
    
    string line;
    string currentStatement;
    int queryCount = 0;
    int successCount = 0;
    int syntaxErrorCount = 0;
    int semanticErrorCount = 0;
    
    while (getline(cin, line)) {
        // Handle special commands
        string trimmed = line;
        trimmed.erase(0, trimmed.find_first_not_of(" \t"));
        
        if (trimmed == "help") {
            cout << "\nCommands:\n";
            cout << "  help       - Show this help\n";
            cout << "  databases  - List available databases\n";
            cout << "  use <db>   - Set default database\n";
            cout << "  refresh    - Refresh schema cache\n";
            cout << "  stats      - Show statistics\n\n";
            continue;
        } else if (trimmed == "databases" && semanticEnabled) {
            auto dbs = inspector.getAvailableDatabases();
            cout << "\n📂 Available databases:\n";
            for (const auto& db : dbs) {
                cout << "  • " << db << "\n";
            }
            cout << "\n";
            continue;
        } else if (trimmed.substr(0, 4) == "use " && semanticEnabled) {
            string db = trimmed.substr(4);
            inspector.setDefaultDatabase(db);
            cout << "🎯 Default database set to: " << db << "\n\n";
            continue;
        } else if (trimmed == "refresh" && semanticEnabled) {
            cout << "🔄 Refreshing schema cache...\n";
            inspector.refreshSchemaCache();
            cout << "✅ Schema cache refreshed!\n\n";
            continue;
        } else if (trimmed == "stats") {
            cout << "\n📊 Analysis Statistics:\n";
            cout << "======================\n";
            cout << "Total queries: " << queryCount << "\n";
            cout << "Successful: " << successCount << "\n";
            cout << "Syntax errors: " << syntaxErrorCount << "\n";
            if (semanticEnabled) {
                cout << "Semantic errors: " << semanticErrorCount << "\n";
                cout << "Overall success rate: " << (queryCount > 0 ? (successCount * 100 / queryCount) : 0) << "%\n";
            } else {
                cout << "Syntax success rate: " << (queryCount > 0 ? ((successCount + semanticErrorCount) * 100 / queryCount) : 0) << "%\n";
            }
            cout << "======================\n\n";
            continue;
        }
        
        // Skip empty lines
        if (line.empty()) continue;
        
        // Skip comment lines (starting with --)
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
                cout << "\n" << string(60, '=') << "\n";
                cout << "Query #" << queryCount << ": " << cleanedStatement << "\n";
                cout << string(60, '=') << "\n";
                
                // Perform comprehensive analysis
                auto result = inspector.analyzeComplete(cleanedStatement);
                
                // Display syntax results
                cout << "📝 SYNTAX: ";
                if (result.syntaxResult.status == SyntaxStatus::VALID) {
                    cout << "✅ VALID\n";
                } else if (result.syntaxResult.status == SyntaxStatus::INCOMPLETE) {
                    cout << "⚠️  INCOMPLETE - " << result.syntaxResult.errorMessage << "\n";
                    cout << "   Location: Line " << result.syntaxResult.errorLine 
                         << ", Column " << result.syntaxResult.errorColumn << "\n";
                    syntaxErrorCount++;
                } else {
                    cout << "❌ INVALID - " << result.syntaxResult.errorMessage << "\n";
                    cout << "   Location: Line " << result.syntaxResult.errorLine 
                         << ", Column " << result.syntaxResult.errorColumn << "\n";
                    syntaxErrorCount++;
                }
                
                // Display semantic results if available
                if (semanticEnabled && result.syntaxResult.status == SyntaxStatus::VALID) {
                    cout << "🧠 SEMANTIC: ";
                    if (result.semanticResult.isValid) {
                        cout << "✅ VALID\n";
                    } else {
                        cout << "❌ INVALID\n";
                        for (const auto& issue : result.semanticResult.issues) {
                            cout << "   ⚠️  " << issue.message << "\n";
                            if (!issue.suggestion.empty()) {
                                cout << "      💡 Suggestion: " << issue.suggestion << "\n";
                            }
                        }
                        semanticErrorCount++;
                    }
                    
                    // Show warnings
                    if (!result.semanticResult.warnings.empty()) {
                        cout << "⚠️  WARNINGS:\n";
                        for (const auto& warning : result.semanticResult.warnings) {
                            cout << "   ⚠️  " << warning << "\n";
                        }
                    }
                } else if (semanticEnabled) {
                    cout << "🧠 SEMANTIC: ⏭️  SKIPPED (syntax errors)\n";
                } else {
                    cout << "🧠 SEMANTIC: ❌ NOT AVAILABLE\n";
                }
                
                // Overall result
                cout << "🎯 OVERALL: ";
                if (result.overallValid) {
                    cout << "✅ QUERY VALID\n";
                    successCount++;
                } else {
                    cout << "❌ QUERY INVALID\n";
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
        cout << "\n" << string(60, '=') << "\n";
        cout << "Query #" << queryCount << " (missing semicolon): " << currentStatement << "\n";
        cout << string(60, '=') << "\n";
        
        auto result = inspector.analyzeComplete(currentStatement);
        
        cout << "📝 SYNTAX: ";
        if (result.syntaxResult.status == SyntaxStatus::VALID) {
            cout << "✅ VALID\n";
            if (semanticEnabled) {
                cout << "🧠 SEMANTIC: " << (result.semanticResult.isValid ? "✅ VALID" : "❌ INVALID") << "\n";
            }
            if (result.overallValid) {
                successCount++;
            } else {
                semanticErrorCount++;
            }
        } else {
            cout << "❌ INVALID - Parse Error\n";
            syntaxErrorCount++;
        }
    }
    
    // Print comprehensive summary
    cout << "\n" << string(80, '=') << "\n";
    cout << "FINAL ANALYSIS SUMMARY\n";
    cout << string(80, '=') << "\n";
    cout << "Total queries processed: " << queryCount << "\n";
    cout << "✅ Valid queries: " << successCount << "\n";
    cout << "❌ Syntax errors: " << syntaxErrorCount << "\n";
    
    if (semanticEnabled) {
        cout << "❌ Semantic errors: " << semanticErrorCount << "\n";
        cout << "📊 Overall success rate: " << (queryCount > 0 ? (successCount * 100 / queryCount) : 0) << "%\n";
        cout << "🧠 Semantic analysis: ✅ ENABLED\n";
    } else {
        cout << "📊 Syntax success rate: " << (queryCount > 0 ? ((queryCount - syntaxErrorCount) * 100 / queryCount) : 0) << "%\n";
        cout << "🧠 Semantic analysis: ❌ DISABLED\n";
    }
    
    cout << string(80, '=') << "\n";
    cout << "\n🎉 Analysis complete! Thank you for using SQLSense.\n";
    
    return 0;
}