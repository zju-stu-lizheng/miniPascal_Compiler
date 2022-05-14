#pragma once
#include <iostream>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>
#include "../type/type.hpp"
#include <map>


namespace Contents{
    class CodeBlock{

    };
    int num_of_global_variables = 0;
    int num_of_temp_variables = 0;
    
    llvm::LLVMContext context;
    llvm::IRBuilder<> builder;
    std::unique_ptr<llvm::Module> module;
    std::map<std::string, llvm::Constant* > names_2_constants;
    std::vector<CodeBlock* > codeblock_list;

};
