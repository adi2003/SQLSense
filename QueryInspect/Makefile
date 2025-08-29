CXX      = g++
LEX      = flex
YACC     = bison
YFLAGS   = -d
LIBS     = -lmysqlcppconn
CFLAGS   = -std=c++17 -Iinclude -I/usr/include/cppconn -Wall

TARGET   = queryinspect

# Source/grammar files
SRCS     = src/main.cpp src/QueryInspect.cpp src/SyntaxAnalyzer.cpp src/SchemaCache.cpp src/SemanticAnalyzer.cpp
BISON_SRC= grammars/mysql.y
FLEX_SRC = grammars/mysql.l

# Output/object files
OBJS     = main.o QueryInspect.o SyntaxAnalyzer.o SchemaCache.o SemanticAnalyzer.o mysql.tab.o mysql.yy.o

# Build everything
all: check_deps $(TARGET)

# Check dependencies
check_deps:
	@echo "🔍 Checking MySQL Connector/C++ dependencies..."
	@which mysql_config > /dev/null || (echo "❌ Install with: sudo apt install libmysqlcppconn-dev" && exit 1)
	@echo "✅ Dependencies OK"

# Bison parser - generate both .c and .h files
mysql.tab.c mysql.tab.h: $(BISON_SRC)
	$(YACC) $(YFLAGS) -o mysql.tab.c $(BISON_SRC)

# Flex lexer - depends on bison header
mysql.yy.c: $(FLEX_SRC) mysql.tab.h
	$(LEX) -o mysql.yy.c $(FLEX_SRC)

# Compile bison output - suppress warnings for generated code
mysql.tab.o: mysql.tab.c mysql.yy.c
	$(CXX) $(CFLAGS) -Wno-unused-function -Wno-unused-variable -Wno-sign-compare -c mysql.tab.c

# Compile flex output - suppress warnings for generated code  
mysql.yy.o: mysql.yy.c mysql.tab.h
	$(CXX) $(CFLAGS) -Wno-unused-function -Wno-sign-compare -Wno-unused-variable -c mysql.yy.c

# Compile main source files with proper dependencies
main.o: src/main.cpp include/QueryInspect.h
	$(CXX) $(CFLAGS) -c src/main.cpp -o main.o

QueryInspect.o: src/QueryInspect.cpp include/QueryInspect.h include/SyntaxAnalyzer.h include/SchemaCache.h include/SemanticAnalyzer.h
	$(CXX) $(CFLAGS) -c src/QueryInspect.cpp -o QueryInspect.o

SyntaxAnalyzer.o: src/SyntaxAnalyzer.cpp include/SyntaxAnalyzer.h mysql.tab.h
	$(CXX) $(CFLAGS) -c src/SyntaxAnalyzer.cpp -o SyntaxAnalyzer.o

SchemaCache.o: src/SchemaCache.cpp include/SchemaCache.h
	$(CXX) $(CFLAGS) -c src/SchemaCache.cpp -o SchemaCache.o

SemanticAnalyzer.o: src/SemanticAnalyzer.cpp include/SemanticAnalyzer.h include/SchemaCache.h
	$(CXX) $(CFLAGS) -c src/SemanticAnalyzer.cpp -o SemanticAnalyzer.o

# Link final executable
$(TARGET): $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET)

# Clean target
clean:
	rm -f $(TARGET) *.o mysql.tab.* mysql.yy.c

.PHONY: all clean check_deps
