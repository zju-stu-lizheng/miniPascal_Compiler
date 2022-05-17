#include "ast/AST.hpp"
#include "pascal.y.hpp"
#include "contents/Contents.hpp"

std::string input_fname = "test.pas"; 

int main() {
    int fd = open(input_fname.c_str(), O_RDONLY);
    if (fd < 0) {
        std::cout << "cannot open file " << input_fname << std::endl;
        return 1;
    }
    if (dup2(fd, 0) < 0) {
        std::cout << "cannot dup file into stdin " << input_fname << std::endl;
    }
    
    if (yyparse() != 0) {
        std::cout << "failed to parse this code!" << std::endl;
        return 1;
    }
    // Generator *gen = new Generator();
    using namespace Contents;
    std::cout << "new!" << std::endl;
    ast_root->CodeGenerate();
    std::cout << "accept!" << std::endl;

    std::string output_ll_fname = input_fname + ".ll";
    system(("rm "+output_ll_fname).c_str());
    Save(output_ll_fname);

    return 0;
}