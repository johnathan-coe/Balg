#include "../AST/Expression.h"
#include "../AST/Util.h"
#include <stdio.h>
#include <string.h>

int b(int i) { return i ? 1 : 0; }

void printTable(SExpression* e, char* varOrder) {
    int symbols[26];

    // Create bitmasks for each input symbol
    int numSymbols = strlen(varOrder);
    for (int i = 0; i < numSymbols; i++) {
        char var = varOrder[i] - 97;
        symbols[var] = (1 << (numSymbols - 1 - i));
    }

    // Print header
    for (int i = 0; i < numSymbols; i++) { printf("%c ", varOrder[i]); }
    printf("\n");

    // Generate truth table
    for (int i = 0; i < (1 << numSymbols); i++) {
            int result = evaluate(e, i, symbols);

            for (int s = 0; s < numSymbols; s++) {
                printf("%d ", b(i & symbols[varOrder[s]-97]));
            }

            printf("%d\n", result);
    }
}
