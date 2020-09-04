%{

/*
 * Lexer.l file
 * To generate the lexical analyzer run: "flex Lexer.l"
 */

#include "../AST/Expression.h"
#include "../Parser/Parser.h"

#include <stdio.h>

%}

%option outfile="Lexer.c" header-file="Lexer.h"
%option warn nodefault

%option reentrant noyywrap never-interactive nounistd
%option bison-bridge

%%

[ \r\n\t]*   { continue; /* Skip blanks. */ }
[a-z]*       { yylval->value=yytext[0]; return TOKEN_NUMBER; }

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

