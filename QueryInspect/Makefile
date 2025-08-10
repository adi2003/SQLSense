CXX      = g++
LEX      = flex
YACC     = bison
YFLAGS   = -d
CFLAGS   = -std=c++17 -Iinclude

TARGET   = queryinspect

# Source/grammar files
SRCS     = src/main.cpp src/QueryInspect.cpp src/SyntaxAnalyzer.cpp
BISON_SRC= grammars/mysql.y
FLEX_SRC = grammars/mysql.l

# Output/object files
OBJS     = main.o QueryInspect.o SyntaxAnalyzer.o mysql.tab.o mysql.yy.o

# Build everything
all: $(TARGET)

# Bison parser
mysql.tab.c mysql.tab.h: $(BISON_SRC)
	$(YACC) $(YFLAGS) -o mysql.tab.c $(BISON_SRC)

# Flex scanner (requires bison header)
mysql.yy.c: $(FLEX_SRC) mysql.tab.h
	$(LEX) $(FLEX_SRC)
	mv lex.yy.c mysql.yy.c

# Compile objects
mysql.tab.o: mysql.tab.c
	$(CXX) $(CFLAGS) -c mysql.tab.c

mysql.yy.o: mysql.yy.c
	$(CXX) $(CFLAGS) -c mysql.yy.c

main.o: src/main.cpp
	$(CXX) $(CFLAGS) -c src/main.cpp -o main.o

QueryInspect.o: src/QueryInspect.cpp
	$(CXX) $(CFLAGS) -c src/QueryInspect.cpp -o QueryInspect.o

SyntaxAnalyzer.o: src/SyntaxAnalyzer.cpp
	$(CXX) $(CFLAGS) -c src/SyntaxAnalyzer.cpp -o SyntaxAnalyzer.o

# Link final executable
$(TARGET): $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o $(TARGET)

# Clean target
clean:
	rm -f $(TARGET) *.o grammars/mysql.tab.* grammars/mysql.yy.c
