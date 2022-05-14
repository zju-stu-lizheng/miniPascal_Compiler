debug: pascal.l.cpp pascal.y.cpp ast/AST.cpp
	# g++ `llvm-config --libs core jit native --cxxflags --ldflags` -std=c++11 -DDEBUG_LEXER -o $@ $^ 
	g++ `llvm-config --libs --cxxflags --ldflags ---fpermissive` -std=c++11 -DDEBUG_LEXER -o $@ $^ 
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