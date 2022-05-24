#include "ast/AST.hpp"
#include "pascal.y.hpp"
#include "contents/Contents.hpp"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/IR/LegacyPassManager.h"
#include <string>

std::string input_root = "./";
std::string input_file_name = "test.pas";
std::string output_dot_fname = "";

int main(int argc,char **argv)
{   
    printf("%d\n", argc);
    if( argc == 3){
        input_root = argv[1];
        input_file_name = argv[2];
        printf("%s, %s\n", argv[1], argv[2]);
    }else if( (argc > 3) | (argc == 2)){
        exit(1);
    }
    std::string input_fname = input_root + input_file_name;

    int fd = open(input_fname.c_str(), O_RDONLY);
    if (fd < 0)
    {
        std::cout << "cannot open file " << input_fname << std::endl;
        return 1;
    }
    if (dup2(fd, 0) < 0)
    {
        std::cout << "cannot dup file into stdin " << input_fname << std::endl;
    }

    if (yyparse() != 0)
    {
        std::cout << "failed to parse this code!" << std::endl;
        return 1;
    }
    
    GraphViz *g = new GraphViz();
    ast_root->PrintNode(g);
    if (output_dot_fname == "") output_dot_fname = input_fname + ".dot";
    g->Save(output_dot_fname);

    using namespace Contents;
    std::cout << "new!" << std::endl;
    ast_root->CodeGenerate();
    std::cout << "accept!" << std::endl;

    std::string output_ll_fname = input_file_name + ".ll"; //current directory
    // printf("output_ll_fname = %s", output_ll_fname);
    int sys_ret = system(("rm " + output_ll_fname).c_str());
    Save(output_ll_fname);

    //目标代码生成
    using namespace llvm;
    // Initialize the target registry etc.
    InitializeAllTargetInfos();
    InitializeAllTargets();
    InitializeAllTargetMCs();
    InitializeAllAsmParsers();
    InitializeAllAsmPrinters();

    auto TargetTriple = sys::getDefaultTargetTriple();
    Contents::module->setTargetTriple(TargetTriple);

    std::string Error;
    auto Target = TargetRegistry::lookupTarget(TargetTriple, Error);

    // Print an error and exit if we couldn't find the requested target.
    // This generally occurs if we've forgotten to initialise the
    // TargetRegistry or we have a bogus target triple.
    if (!Target)
    {
        errs() << Error;
        return 1;
    }
    auto CPU = "generic";
    auto Features = "";

    TargetOptions opt;
    auto RM = Optional<Reloc::Model>();
    auto TheTargetMachine =
        Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);

    Contents::module->setDataLayout(TheTargetMachine->createDataLayout());

    auto Filename = input_file_name + ".o"; //current directory
    if(system(("rm " + Filename).c_str()) == -1){
        std::cout << "error in rm .o" << std::endl;
    }
    std::error_code EC;
    raw_fd_ostream dest(Filename, EC, sys::fs::OF_None);

    if (EC)
    {
        errs() << "Could not open file: " << EC.message();
        return 1;
    }

    legacy::PassManager pass;
    auto FileType = CGFT_ObjectFile;

    if (TheTargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType))
    {
        errs() << "TheTargetMachine can't emit a file of this type";
        return 1;
    }

    pass.run((*(Contents::module)));
    dest.flush();

    return 0;
}