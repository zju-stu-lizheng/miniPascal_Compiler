#include "ast/AST.hpp"
#include "pascal.y.hpp"

int main() {
    if (yyparse() != 0) {
        std::cout << "failed to parse this code!" << std::endl;
        return 1;
    }
    return 0;
}