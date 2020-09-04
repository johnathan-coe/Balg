%{

/*
 * Lexer.l file
 * To generate the lexical analyzer run: "flex Lexer.l"
 */

#include "../AST/Expression.h"
#include "../Parser/Parser.h"
#include "Track.h"

#include <stdio.h>
#include "string.h"

char varOrder[] = "";
void varToken(char* a);
%}

%option outfile="Lexer.c" header-file="Lexer.h"
%option warn nodefault

%option reentrant noyywrap never-interactive nounistd
%option bison-bridge

%%

[ \r\n\t]*   { continue; /* Skip blanks. */ }
[a-z]        { yylval->value=yytext[0]; varToken(yytext); return TOKEN_NUMBER; }

"->"         { return TOKEN_IMPLY; }
"+"          { return TOKEN_OR; }
"."          { return TOKEN_AND; }
"!"          { return TOKEN_NOT; }
"("          { return TOKEN_LPAREN; }
")"          { return TOKEN_RPAREN; }

.            { continue; /* Ignore unexpected characters. */}

%%

int yyerror(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    return 0;
}

// As we encounter variables, build a string of them in the order they appear
void varToken(char* a) {
	if (strchr(varOrder, a[0]) == NULL) {	
		strcat(varOrder, a);
	}
}

