#include "inst/translate.h"
#include "ast/check.h"
#include <fmt/core.h>
#include <iostream>
#include <fstream>
extern int yyparse();
extern FILE* yyin;

Root_ptr root;
bool error = false;

int main(int argc, char **argv) {
    yyin = fopen(argv[1], "r");
    yyparse();

    /*******lab2********/
    check_root(root);
    if(error)
        return 1;
    
    /*******lab3********/
    std::ofstream outfile;
	outfile.open(argv[2]);
    trans_root(root, outfile);
    
    //fmt::print("Complete\n!");
    return 0;
}
