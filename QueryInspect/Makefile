CXX      = g++
LEX      = flex
YACC     = bison
YFLAGS   = -d
CFLAGS   = -std=c++17 -Iinclude -Wall

TARGET   = queryinspect

# Source/grammar files
SRCS     = src/main.cpp src/QueryInspect.cpp src/SyntaxAnalyzer.cpp
BISON_SRC= grammars/mysql.y
FLEX_SRC = grammars/mysql.l

# Output/object files
OBJS     = main.o QueryInspect.o SyntaxAnalyzer.o mysql.tab.o mysql.yy.o

# Build everything
all: $(TARGET)

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

# Compile main source files
main.o: src/main.cpp
	$(CXX) $(CFLAGS) -c src/main.cpp -o main.o

QueryInspect.o: src/QueryInspect.cpp
	$(CXX) $(CFLAGS) -c src/QueryInspect.cpp -o QueryInspect.o

SyntaxAnalyzer.o: src/SyntaxAnalyzer.cpp mysql.tab.h
	$(CXX) $(CFLAGS) -c src/SyntaxAnalyzer.cpp -o SyntaxAnalyzer.o

# Link final executable
$(TARGET): $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o $(TARGET)

# Clean target
clean:
	rm -f $(TARGET) *.o mysql.tab.* mysql.yy.c

.PHONY: all clean