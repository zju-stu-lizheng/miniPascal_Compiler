#pragma once

#include "../type/type.hpp"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Module.h>
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>
#include <sys/stat.h>
#include <fstream>

// function or procedure
class Procedure_Information{
    public:
        //int num_of_local_variables = 0; //len of name_list
        // parameters list, for example: x,y,z: integer, var m: integer
        std::vector<std::string> name_list;
        std::vector<Our_Type::Pascal_Type*> type_list;
        std::vector<bool> is_var_list;

        Procedure_Information(std::vector<std::string> _name_list, std::vector<Our_Type::Pascal_Type*> _type_list, std::vector<bool> _is_var_list):
                                            name_list(_name_list), type_list(_type_list), is_var_list(_is_var_list){}

};

class Function_Information : public Procedure_Information{ 
    public:
        // for function
        Our_Type::Pascal_Type* return_type = nullptr;

        Function_Information(std::vector<std::string> _name_list, std::vector<Our_Type::Pascal_Type*> _type_list, std::vector<bool> _is_var_list, Our_Type::Pascal_Type* _return_type = nullptr):
                    return_type(_return_type), Procedure_Information(_name_list, _type_list, _is_var_list){}
};

class Label_Type{
    enum class Label_Group{
        IDENTIFIER,
        INT
    };
    Label_Group label_group;
    std::string identifier_label;
    int int_label;

    Label_Type(std::string _identifier_label):
            identifier_label(_identifier_label), label_group(Label_Group::IDENTIFIER){};
    Label_Type(int _int_label):
            int_label(_int_label), label_group(Label_Group::INT){};
    
};

class CodeBlock{
    public:
    // std::string codeblock_id;
    std::map<std::string, llvm::Value *> names_2_values; //variables
    std::map<std::string, Our_Type::Pascal_Type*> names_2_ourtype;
    std::map<std::string, Function_Information*> names_2_func_info; //function or procedure
    std::map<std::string, llvm::Function*> names_2_functions;
    std::map<Label_Type*, llvm::BasicBlock*> label_2_block; //goto

    std::string block_name;
    bool is_function;

    bool isType(std::string id, bool check_defined = false) {
        return names_2_ourtype.find(id) != names_2_ourtype.end() &&
               (names_2_values.find(id) == names_2_values.end() || check_defined);
    }

    bool isValue(std::string id) {
        return names_2_values.find(id) != names_2_values.end();
    }
};

namespace Contents{
    extern int num_of_global_variables;

    extern llvm::LLVMContext context;
    extern llvm::IRBuilder<> builder;
    extern std::unique_ptr<llvm::Module> module;
    extern std::map<std::string, llvm::Constant* > names_2_constants; // global constants
    extern std::vector<CodeBlock* > codeblock_list;
    extern std::vector<std::string> error_message;
    extern std::vector<std::pair<int, int> > error_position;

    //保存生成的IR代码
    void Save(std::string path);

    //获取当前CodeBlock
    CodeBlock* GetCurrentBlock(void);

    //获取当前所有局部变量
    // std::pair<std::vector<std::string>, std::vector<Our_Type::Pascal_Type *> > GetAllLocalVarNameType();

    //获取变量的类型
    Our_Type::Pascal_Type *GetVarType(std::string id);
};

