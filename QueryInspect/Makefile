# Enhanced Makefile for SQLSense Project
CXX      = g++
LEX      = flex  
YACC     = bison
YFLAGS   = -d

# Updated libraries and flags
LIBS     = -lmysqlcppconn -ljsoncpp -lpthread
CFLAGS   = -std=c++17 -Iinclude -I/usr/include/cppconn -I/usr/include/jsoncpp -Wall -Wextra

# Directories
SRC_DIR  = src
INCLUDE_DIR = include
BIN_DIR  = bin
GRAMMAR_DIR = grammars

# Targets
SERVER_TARGET = $(BIN_DIR)/sqlsense_server
TEST_TARGET   = $(BIN_DIR)/sqlsense_test

# Core source files (shared between server and test)
CORE_SRCS = $(SRC_DIR)/QueryInspect.cpp $(SRC_DIR)/SyntaxAnalyzer.cpp $(SRC_DIR)/SchemaCache.cpp $(SRC_DIR)/SemanticAnalyzer.cpp

# Server-specific sources
SERVER_SRCS = server_main.cpp SQLSenseServer.cpp $(CORE_SRCS)

# Test-specific sources (your original main)
TEST_SRCS = $(SRC_DIR)/main.cpp $(CORE_SRCS)

# Grammar files
BISON_SRC = $(GRAMMAR_DIR)/mysql.y
FLEX_SRC  = $(GRAMMAR_DIR)/mysql.l

# Generated parser files
PARSER_OBJS = mysql.tab.o mysql.yy.o

# Object files
SERVER_OBJS = server_main.o SQLSenseServer.o QueryInspect.o SyntaxAnalyzer.o SchemaCache.o SemanticAnalyzer.o $(PARSER_OBJS)
TEST_OBJS   = main.o QueryInspect.o SyntaxAnalyzer.o SchemaCache.o SemanticAnalyzer.o $(PARSER_OBJS)

# Default target - build both server and test
all: directories check_deps $(SERVER_TARGET) $(TEST_TARGET)

# Build only server (for production)
server: directories check_deps $(SERVER_TARGET)

# Build only test executable
test: directories check_deps $(TEST_TARGET)

# Create necessary directories
directories:
	@mkdir -p $(BIN_DIR)

# Enhanced dependency check
check_deps:
	@echo "🔍 Checking dependencies..."
	@echo "  MySQL Connector/C++..."
	@which mysql_config > /dev/null || (echo "❌ MySQL dev tools missing. Install: sudo apt install libmysqlcppconn-dev" && exit 1)
	@test -f /usr/include/cppconn/driver.h || (echo "❌ MySQL Connector headers missing. Install: sudo apt install libmysqlcppconn-dev" && exit 1)
	@echo "  JSON library..."
	@test -f /usr/include/jsoncpp/json/json.h || (echo "❌ JsonCpp missing. Install: sudo apt install libjsoncpp-dev" && exit 1)
	@echo "  HTTP library..."
	@test -f /usr/include/httplib.h || (echo "⚠️  httplib.h not found. Will use local copy or install: sudo apt install libhttplib-dev" && echo "   You can also download from: https://github.com/yhirose/cpp-httplib")
	@echo "  Flex/Bison..."
	@which flex > /dev/null || (echo "❌ Flex missing. Install: sudo apt install flex" && exit 1)
	@which bison > /dev/null || (echo "❌ Bison missing. Install: sudo apt install bison" && exit 1)
	@echo "✅ All dependencies OK"

# Install missing dependencies
install-deps:
	@echo "📦 Installing system dependencies..."
	sudo apt-get update
	sudo apt-get install -y build-essential
	sudo apt-get install -y libmysqlcppconn-dev
	sudo apt-get install -y libjsoncpp-dev  
	sudo apt-get install -y flex bison
	@echo "📥 Installing httplib..."
	@if [ ! -f /usr/include/httplib.h ]; then \
		wget -O httplib.h https://raw.githubusercontent.com/yhirose/cpp-httplib/master/httplib.h; \
		sudo cp httplib.h /usr/include/; \
		rm httplib.h; \
	fi
	@echo "✅ Dependencies installed"

# Grammar compilation
mysql.tab.c mysql.tab.h: $(BISON_SRC)
	@echo "🔨 Generating parser with Bison..."
	$(YACC) $(YFLAGS) -o mysql.tab.c $(BISON_SRC)

mysql.yy.c: $(FLEX_SRC) mysql.tab.h  
	@echo "🔨 Generating lexer with Flex..."
	$(LEX) -o mysql.yy.c $(FLEX_SRC)

mysql.tab.o: mysql.tab.c mysql.yy.c
	@echo "🔨 Compiling parser..."
	$(CXX) $(CFLAGS) -Wno-unused-function -Wno-unused-variable -Wno-sign-compare -c mysql.tab.c

mysql.yy.o: mysql.yy.c mysql.tab.h
	@echo "🔨 Compiling lexer..."
	$(CXX) $(CFLAGS) -Wno-unused-function -Wno-sign-compare -Wno-unused-variable -c mysql.yy.c

# Core object files
QueryInspect.o: $(SRC_DIR)/QueryInspect.cpp $(INCLUDE_DIR)/QueryInspect.h $(INCLUDE_DIR)/SyntaxAnalyzer.h $(INCLUDE_DIR)/SchemaCache.h $(INCLUDE_DIR)/SemanticAnalyzer.h
	@echo "🔨 Compiling QueryInspect..."
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/QueryInspect.cpp -o QueryInspect.o

SyntaxAnalyzer.o: $(SRC_DIR)/SyntaxAnalyzer.cpp $(INCLUDE_DIR)/SyntaxAnalyzer.h mysql.tab.h
	@echo "🔨 Compiling SyntaxAnalyzer..."
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/SyntaxAnalyzer.cpp -o SyntaxAnalyzer.o

SchemaCache.o: $(SRC_DIR)/SchemaCache.cpp $(INCLUDE_DIR)/SchemaCache.h
	@echo "🔨 Compiling SchemaCache..."
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/SchemaCache.cpp -o SchemaCache.o

SemanticAnalyzer.o: $(SRC_DIR)/SemanticAnalyzer.cpp $(INCLUDE_DIR)/SemanticAnalyzer.h $(INCLUDE_DIR)/SchemaCache.h
	@echo "🔨 Compiling SemanticAnalyzer..."
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/SemanticAnalyzer.cpp -o SemanticAnalyzer.o

# Server-specific files
server_main.o: server_main.cpp SQLSenseServer.h $(INCLUDE_DIR)/QueryInspect.h
	@echo "🔨 Compiling server main..."
	$(CXX) $(CFLAGS) -c server_main.cpp -o server_main.o

SQLSenseServer.o: SQLSenseServer.cpp SQLSenseServer.h $(INCLUDE_DIR)/QueryInspect.h
	@echo "🔨 Compiling SQLSenseServer..."
	$(CXX) $(CFLAGS) -c SQLSenseServer.cpp -o SQLSenseServer.o

# Test executable (your original main)
main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/QueryInspect.h
	@echo "🔨 Compiling test main..."
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/main.cpp -o main.o

# Link server executable
$(SERVER_TARGET): $(SERVER_OBJS)
	@echo "🔗 Linking server executable..."
	$(CXX) $(CFLAGS) $(SERVER_OBJS) $(LIBS) -o $(SERVER_TARGET)
	@echo "✅ Server built: $(SERVER_TARGET)"

# Link test executable  
$(TEST_TARGET): $(TEST_OBJS)
	@echo "🔗 Linking test executable..."
	$(CXX) $(CFLAGS) $(TEST_OBJS) $(LIBS) -o $(TEST_TARGET)
	@echo "✅ Test executable built: $(TEST_TARGET)"

# Run targets
run-server: $(SERVER_TARGET)
	@echo "🚀 Starting SQLSense server..."
	./$(SERVER_TARGET)

run-test: $(TEST_TARGET)  
	@echo "🧪 Running test executable..."
	./$(TEST_TARGET)

# Server management
start-server: $(SERVER_TARGET)
	@echo "🚀 Starting server in background..."
	nohup ./$(SERVER_TARGET) > server.log 2>&1 &
	@echo "📊 Server started. Check server.log for output"

status:
	@echo "🔍 Server status check..."
	@curl -s http://localhost:8080/health | jq . || echo "❌ Server not responding"

# Clean targets
clean:
	@echo "🧹 Cleaning build files..."
	rm -f *.o mysql.tab.* mysql.yy.c
	rm -rf $(BIN_DIR)
	@echo "✅ Clean complete"

clean-all: clean
	@echo "🧹 Deep clean (including logs)..."
	rm -f *.log nohup.out

# Help target
help:
	@echo "SQLSense Build System"
	@echo "===================="
	@echo "Main targets:"
	@echo "  all           - Build both server and test executables"
	@echo "  server        - Build server only"
	@echo "  test          - Build test executable only"
	@echo ""
	@echo "Development:"
	@echo "  run-server    - Build and run server"
	@echo "  run-test      - Build and run test"
	@echo "  production    - Optimized production build"
	@echo ""
	@echo "Server management:"
	@echo "  start-server  - Start server in background"
	@echo "  stop-server   - Stop background server"
	@echo "  status        - Check server health"
	@echo ""
	@echo "Maintenance:"
	@echo "  install-deps  - Install system dependencies"
	@echo "  clean         - Clean build files"
	@echo "  clean-all     - Deep clean including logs"
	@echo "  help          - Show this help"

.PHONY: all server test directories check_deps install-deps run-server run-test debug-server debug-test production start-server stop-server status clean clean-all help
