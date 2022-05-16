#include "ast/AST.hpp"
#include "pascal.y.hpp"
#include "contents/Contents.hpp"

int main() {
    if (yyparse() != 0) {
        std::cout << "failed to parse this code!" << std::endl;
        return 1;
    }
    // Generator *gen = new Generator();
    using namespace Contents;
    std::cout << "new!" << std::endl;
    ast_root->CodeGenerate();
    std::cout << "accept!" << std::endl;
    std::string output_ll_fname = "test.ll";
    system(("rm "+output_ll_fname).c_str());
    Save(output_ll_fname);

    return 0;
}