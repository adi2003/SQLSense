# SQLSense: Real-Time SQL Query Analysis for VS Code

SQLSense is a Visual Studio Code extension designed to provide real-time analysis of SQL queries. It performs both syntactic and semantic analysis to detect query errors before execution, allowing developers to write and validate SQL more efficiently. The tool integrates seamlessly with MySQL and provides immediate feedback inside the VS Code environment.

## Introduction

Modern database-driven applications rely heavily on accurate and optimized SQL queries. However, syntax or semantic mistakes are often caught only at runtime, which can lead to costly debugging. SQLSense addresses this challenge by embedding an intelligent SQL validation system directly inside the code editor. It continuously analyzes SQL queries as the user types, offering instant feedback on syntax and semantic correctness.

The key idea behind this project is to combine traditional compiler techniques with database schema awareness. By integrating a parser built using Flex and Bison with an in-memory schema caching mechanism, we can analyze SQL queries not only for grammatical accuracy but also for semantic validity relative to the connected database.

## System Overview

The system consists of two major components: the frontend VS Code extension and the backend SQLSense engine. The frontend captures SQL queries in real time and communicates with the backend for analysis. The backend, written in C++, performs both syntactic and semantic checks and returns structured results to be displayed inside the editor.

When the user logs into their MySQL server, the system fetches the complete database schema—including tables, columns, and relationships—and loads it into an in-memory cache. This cached schema acts as the foundation for semantic validation. When a query is typed, the backend uses Flex and Bison to parse it into an abstract syntax tree (AST). If the query passes syntactic validation, the AST is analyzed against the cached schema to check whether referenced tables and columns exist, whether data types match, and whether operations are semantically valid.

## Syntactic Analysis

The syntactic analysis in SQLSense is implemented using Flex (for lexical analysis) and Bison (for parsing). Flex tokenizes the query into SQL keywords, identifiers, literals, and operators. These tokens are then fed into Bison, which applies a context-free grammar of SQL defined in `.y` files to build an Abstract Syntax Tree (AST).

This AST represents the structural meaning of the query. If the query violates grammar rules—such as missing keywords, misplaced clauses, or invalid expressions—the parser detects and reports the specific syntactic error. This step ensures that only structurally valid SQL statements proceed to the semantic analysis phase.

## Semantic Analysis

While syntactic analysis ensures that the query follows SQL grammar, semantic analysis ensures that it makes sense in the context of the connected database. For this, SQLSense uses an in-memory caching mechanism. When the user connects to their MySQL server, the backend loads the entire database schema into a cache. This includes table names, column names, data types, and constraints.

During query evaluation, the engine checks every identifier in the query against this cache. If a query refers to a non-existent table or column, or performs invalid operations such as type mismatches, the system immediately flags the issue. Since all schema information is stored in memory, semantic checks are performed efficiently without repeatedly querying the database.

## Design and Implementation

The backend is implemented in C++ and organized into modular components: syntax analysis (handled by the Flex/Bison-generated parser), semantic analysis, schema caching, and communication with the VS Code frontend. The frontend is developed in TypeScript using the VS Code extension API. It captures SQL queries from the editor, sends them to the backend for validation, and displays the results inline.

The Makefile automates compilation of all components, including lexer and parser generation, object file linking, and executable creation. The final executable, `sqlsense`, serves as the analysis engine communicating with the extension.

## Workflow

When a user opens an SQL file in VS Code, the extension monitors query inputs. Upon detecting a query, it sends the text to the backend engine. The engine first passes it through the Flex lexer and Bison parser to perform syntactic validation. If the query is grammatically correct, the system uses the cached schema for semantic validation. The results are then returned to the extension, which highlights errors or confirms query validity in real time.