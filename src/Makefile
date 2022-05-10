cal: pascal.l.cpp pascal.y.cpp
	gcc -o $@ $^ 

pascal.l.cpp: 
	lex -o pascal.l.cpp lexer/pascal.l

pascal.y.cpp:
	yacc -d -o pascal.y.cpp parser/pascal.y