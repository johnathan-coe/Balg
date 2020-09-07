# Makefile

FILES	= Lexer/Lexer.c Parser/Parser.c AST/Expression.c AST/Util.c Table/Table.c Optimiser/Optimiser.c main.c
CC	= g++
CFLAGS	= -g -ansi

balg:		$(FILES)
		$(CC) $(CFLAGS) $(FILES) -o balg

Lexer/Lexer.c:	Lexer/Lexer.l
		cd Lexer; flex Lexer.l

Parser/Parser.c:	Parser/Parser.y Lexer/Lexer.c
		cd Parser; bison Parser.y

clean:
		rm -f *.o *~ Lexer/Lexer.c Lexer/Lexer.h Parser/Parser.c Parser/Parser.h balg

