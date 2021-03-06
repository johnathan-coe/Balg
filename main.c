/*
 * main.c file
 */

#include "AST/Expression.h"
#include "AST/Util.h"
#include "Table/Table.h"
#include "Optimiser/Optimiser.h"
#include <stdio.h>
#include <string.h>

// Defines varOrder which is a list of variables in order of
// appearance in args[1]
#include "Lexer/Track.h"

void usage(char* name) {
	printf("Usage: %s [OPERATION]... [EXPRESSION]\n"
	       "Analyse and optimise boolean expressions\n"
	       "\n"
	       "Operations (Completed in order):\n"
	       " -t, --truth-table\tCreate a truth table from the expression specified\n"
	       " -o, --optimise\t\tOptimise and output the expression provided\n"
	       "\n"
	       "If no operations are specified, a truth table is generated by default\n"
	       "\n"
	       "The expression provided should be a string containing the following:\n"
	       " Vars\tCharacters from a-z\n"
	       " !\tNot operator\n"
	       " .\tAnd operator\n"
	       " ->\tLogical implication\n"
	       "\n"
	       "Bash expansion will interfere with a number of expressions,\n"
	       "when specifying from a shell, surround with single quotes.\n",
	       name);
}

int main(int argc, char *args[]) {
    // No argument specified, print usage
    if (argc == 1) {
        usage(args[0]); 
	return 1;
    }
 
    // Generate AST
    SExpression *e = getAST(args[argc-1]);

    // No operations specified, make a truth table
    if (argc == 2) {
        printTable(e, varOrder);
        deleteExpression(e);
	
	return 0; 
    }

    for (int i = 1; i < (argc-1); i++) {
        if (!(strcmp("-t", args[i]) && strcmp("--truth-table", args[i]))) {
            // Spit out a truth table
            printTable(e, varOrder);
	} else if (!(strcmp("-o", args[i]) || !strcmp("--optimise", args[i]))) {
            // Optimise the AST
            optimise(e);
	}
    }
	
    // Free memory
    deleteExpression(e);
    return 0;
}
