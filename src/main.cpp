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

std::string input_fname = "test.pas";

int main()
{
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
    // Generator *gen = new Generator();
    using namespace Contents;
    std::cout << "new!" << std::endl;
    ast_root->CodeGenerate();
    std::cout << "accept!" << std::endl;

    std::string output_ll_fname = input_fname + ".ll";
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

    auto Filename = input_fname + ".o";
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