/*
 * main.c file
 */

#include "AST/Expression.h"
#include "Parser/Parser.h"
#include "Lexer/Lexer.h"

#include <stdio.h>

int yyparse(SExpression **expression, yyscan_t scanner);

SExpression *getAST(const char *expr)
{
    SExpression *expression;
    yyscan_t scanner;
    YY_BUFFER_STATE state;

    if (yylex_init(&scanner)) {
        /* could not initialize */
        return NULL;
    }

    state = yy_scan_string(expr, scanner);

    if (yyparse(&expression, scanner)) {
        /* error parsing */
        return NULL;
    }

    yy_delete_buffer(state, scanner);

    yylex_destroy(scanner);

    return expression;
}

int evaluate(SExpression *e, int input, int symbols[])
{
    switch (e->type) {
        case eVALUE:
	    if (symbols[e->value - 97] == -1) {
		    printf("FATAL: %c not mapped! Specify a position for %c in the second argument\n", e->value, e->value);
		    exit(0);
	    }

	    return ((1 << symbols[e->value - 97]) & input) != 0;
        case eOR:
            return evaluate(e->left, input, symbols) || evaluate(e->right, input, symbols);
        case eAND:
            return evaluate(e->left, input, symbols) && evaluate(e->right, input, symbols);
	case eNOT:
            return !evaluate(e->left, input, symbols);
	case eIMPLY:
	    if (evaluate(e->left, input, symbols)) {
	        return evaluate(e->right, input, symbols);
	    } else {
		return 1;
	    }
        default:
            /* should not be here */
            return 0;
    }
}

int main(int argc, char *args[])
{
    SExpression *e = getAST(args[1]);
	
    // Mapping of symbols to position in input integer
    int symbols[26];
    for (int i = 0; i < 26; i++) { symbols[i] = -1; }
 
    int numSymbols = strlen(args[2]);

    // Populate symbol table, this maps each letter to a bit in input
    for (int i = 0; i <= numSymbols; i++) {
	    symbols[args[2][i] - 97] = numSymbols - 1 - i;
    }
 
    int rows = (1 << (numSymbols));

    // Print header
    for (int i = 0; i < numSymbols; i++) {
	printf("%c ", args[2][i]);
    }

    printf("\n");

    // Generate truth table
    for (int i = 0; i < rows; i++) {
	    int result = evaluate(e, i, symbols);
	
	    for (int s = numSymbols - 1; s >= 0; s--) {
		printf("%d ", ((1 << s) & i) != 0);
	    }

	    printf("%d\n", result);
    }
	
    // Free memory
    deleteExpression(e);
    return 0;
}
