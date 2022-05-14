debug: pascal.l.cpp pascal.y.cpp ast/AST.cpp
	g++ -std=c++11 -DDEBUG_LEXER -o $@ $^ 

.PHONY : all clean

all: debug clean run

run:
	./debug < ../test/test.pas

clean:
	rm pascal.l.cpp pascal.y.cpp pascal.y.hpp

pascal.l.cpp: 
	lex -o pascal.l.cpp lexer/pascal.l

pascal.y.cpp:
	yacc -d -o pascal.y.cpp parser/pascal.y