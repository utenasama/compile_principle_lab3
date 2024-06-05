#include "ast/ast.h"
#include "ast/check.h"
#include <fmt/core.h>

extern int yyparse();
extern FILE *yyin;

Root_ptr root;
bool error = false;

int main(int argc, char **argv)
{
    yyin = fopen(argv[1], "r");
    yyparse();

    // lab2
    check_root(root);

    if (error)
        return 1;

    return 0;
}
