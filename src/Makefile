debug: pascal.l.cpp pascal.y.cpp
	g++ -DDEBUG_LEXER -o $@ $^ 

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