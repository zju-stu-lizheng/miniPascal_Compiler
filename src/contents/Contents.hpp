#pragma once

#include "../type/type.hpp"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/DerivedTypes.h>
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
                    return_type(_return_type), Procedure_Information(_name_list, _type_list, _is_var_list){};
};

class Error_Information{
    public:
    std::string error_info;
    std::pair<int, int> error_location;

    Error_Information(std::string _error_info, std::pair<int, int> _error_location):
            error_info(_error_info), error_location(_error_location){};
};

class Error_Information_Record{
    public:
        std::vector<Error_Information> record;

        Error_Information_Record() = default;
        void Add_Error_Information(std::string _error_info, std::pair<int, int> _error_location)
        {
            record.emplace_back(_error_info, _error_location);
        }
};

class CodeBlock{
    public:
    // std::string codeblock_id;
    std::map<std::string, llvm::Value *> names_2_values; //variables
    std::map<std::string, Our_Type::Pascal_Type*> names_2_ourtype;
    std::map<std::string, FuncSign*> names_2_funcsign; //function or procedure
    std::map<std::string, llvm::Function*> names_2_functions;
    std::map<std::shared_ptr<Label_Type>, llvm::BasicBlock*> label_2_block; //goto
    std::vector<llvm::BasicBlock*> loop_return_blocks; // for multiple loop break
    
    std::string block_name;
    bool is_function;

    bool isType(std::string id, bool check_defined = false) {
        return names_2_ourtype.find(id) != names_2_ourtype.end() &&
               (names_2_values.find(id) == names_2_values.end() || check_defined);
    }

    bool isValue(std::string id) {
        return names_2_values.find(id) != names_2_values.end();
    }

    //返回LLVM function指针
    llvm::Function* Find_Function(std::string id){
        if(names_2_functions.find(id) == names_2_functions.end()){
            return nullptr;
        }
        return names_2_functions[id];
    }

    //返回函数特征
    FuncSign * Find_FuncSign(std::string id){
        if(names_2_funcsign.find(id) == names_2_funcsign.end()){
            return nullptr;
        }
        return names_2_funcsign[id];
    }

    void Set_Function(std::string id,llvm::Function *function,FuncSign *func_sign){
        names_2_funcsign[id] = func_sign;
        names_2_functions[id] = function;
    }
};

namespace Contents{
    extern int temp_variable_count;

    extern llvm::LLVMContext context;
    extern llvm::IRBuilder<> builder;
    extern std::unique_ptr<llvm::Module> module;
    extern std::map<std::string, llvm::Constant* > names_2_constants; // global constants
    extern std::vector<CodeBlock* > codeblock_list;

    extern std::shared_ptr<Error_Information_Record> error_record;

    // extern std::vector<llvm::BasicBlock*> loop_return_blocks;
    // extern std::vector<std::string> error_message;
    // extern std::vector<std::pair<int, int> > error_position;

    bool isConstant(std::string id);

    //保存生成的IR代码
    void Save(std::string path);

    //获取当前CodeBlock
    CodeBlock* GetCurrentBlock(void);

    //获取当前所有局部变量
    std::pair<std::vector<std::string>, std::vector<Our_Type::Pascal_Type *> > GetAllLocalVarNameType();

    //获取变量的类型
    Our_Type::Pascal_Type *GetVarType(std::string id);

    /* 系统调用相关 */

    //判断是否是系统函数
    bool isSysFunc(std::string id) ;

    //生成系统函数，并执行
    llvm::Value* GenSysFunc(std::string id, const std::vector<std::shared_ptr<Value_Result> > &args_list) ;
};

