# Makefile

FILES	= Lexer/Lexer.c Parser/Parser.c AST/Expression.c main.c
CC	= g++
CFLAGS	= -g -ansi

test:		$(FILES)
		$(CC) $(CFLAGS) $(FILES) -o test

Lexer/Lexer.c:	Lexer/Lexer.l
		cd Lexer; flex Lexer.l

Parser/Parser.c:	Parser/Parser.y Lexer/Lexer.c
		cd Parser; bison Parser.y

clean:
		rm -f *.o *~ Lexer.c Lexer.h Parser.c Parser.h test

