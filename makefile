
lexer: main.c lexer.c lexer.h
	gcc main.c lexer.c -o lexer

run: lexer
	./lexer input.c

clean:
	rm -f lexer
