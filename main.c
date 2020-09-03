/*
 * main.c file
 */

#include "Expression.h"
#include "Parser.h"
#include "Lexer.h"

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

int evaluate(SExpression *e, int input)
{
    switch (e->type) {
        case eVALUE:
	    return ((1 << (e->value - 97)) & input) != 0;
        case eOR:
            return evaluate(e->left, input) || evaluate(e->right, input);
        case eAND:
            return evaluate(e->left, input) && evaluate(e->right, input);
	case eNOT:
            return !evaluate(e->left, input);
	case eIMPLY:
	    if (evaluate(e->left, input)) {
	        return evaluate(e->right, input);
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

    printf("c b a =\n");

    for (int i = 0; i < 8; i++) {
	    int result = evaluate(e, i);
	    printf("%d %d %d %d\n", (4 & i) != 0, (2 & i) != 0, (1 & i) != 0, result);
    }

    deleteExpression(e);
    return 0;
}
