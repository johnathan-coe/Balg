%{

/*
 * Parser.y file
 * To generate the parser run: "bison Parser.y"
 */

#include "../AST/Expression.h"
#include "../Parser/Parser.h"
#include "../Lexer/Lexer.h"

int yyerror(SExpression **expression, yyscan_t scanner, const char *msg) {
    /* Add error handling routine as needed */
}

%}

%code requires {
  typedef void* yyscan_t;
}

%output  "Parser.c"
%defines "Parser.h"

%define api.pure
%lex-param   { yyscan_t scanner }
%parse-param { SExpression **expression }
%parse-param { yyscan_t scanner }

%union {
    int value;
    SExpression *expression;
}

%token TOKEN_LPAREN   "("
%token TOKEN_RPAREN   ")"
%token TOKEN_OR       "+"
%token TOKEN_AND      "."
%token TOKEN_IMPLY    "->"
%token TOKEN_NOT      "!"
%token <value> TOKEN_NUMBER "number"

%type <expression> expr

/* Precedence (increasing) and associativity:
   a+b+c is (a+b)+c: left associativity
   a+b*c is a+(b*c): the precedence of "*" is higher than that of "+". */
%left "->"
%left "+"
%left "."
%left "!"

%%

input
    : expr { *expression = $1; }
    ;

expr
    : expr[L] "->" expr[R] { $$ = createOperation( eIMPLY, $L, $R ); }
    | expr[L] "." expr[R] { $$ = createOperation( eAND, $L, $R ); }
    | expr[L] "+" expr[R] { $$ = createOperation( eOR, $L, $R ); }
    | "!" expr[E]         { $$ = createOperation( eNOT, $E, NULL ); }
    | "(" expr[E] ")"     { $$ = $E; }
    | "number"            { $$ = createNumber($1); }
    ;

%%
