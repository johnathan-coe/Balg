#include "Util.h"
#include "Expression.h"
#include "../Parser/Parser.h"
#include "../Lexer/Lexer.h"

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
	    return (symbols[e->value - 97] & input) != 0;
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

