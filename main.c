/*
 * main.c file
 */

#include "AST/Util.h"
#include "AST/Expression.h"

#include <stdio.h>
#include <string.h>

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
