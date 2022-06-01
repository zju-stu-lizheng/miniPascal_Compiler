#include "Contents.hpp"
#include <cstdio>

#include <iostream>
#include <vector>
#include <map>

llvm::Value *GenSysWrite(const std::vector<std::shared_ptr<Value_Result>> &args_list, bool new_line, bool c_printf = false)
{
    static llvm::Function *llvm_printf = nullptr;
    if (llvm_printf == nullptr)
    {
        // register printf
        std::vector<llvm::Type *> arg_types = {llvm::Type::getInt8PtrTy(Contents::context)};
        llvm::FunctionType *func_type = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(Contents::context),
            arg_types,
            true);
        llvm::Function *func = llvm::Function::Create(
            func_type,
            llvm::Function::ExternalLinkage,
            "printf",
            &*(Contents::module));
        func->setCallingConv(llvm::CallingConv::C);
        llvm_printf = func;
    }
    std::string format;
    std::vector<llvm::Value *> printf_args;
    
    if (c_printf)
    {
        printf_args.emplace_back(nullptr);
        for (auto arg : args_list)
        {
            Our_Type::Pascal_Type *tp = arg->GetType();
            if (tp->isIntegerTy())
            {
                format += "%10d";
                printf_args.emplace_back(arg->GetValue());
            }
            else if (tp->isFloatingPointTy())
            {
                format += "%.1lf";
                printf_args.emplace_back(arg->GetValue());
            }
            else if (tp->isCharTy())
            {
                format += "%c";
                printf_args.emplace_back(arg->GetValue());
            }
            else if (tp->isString())
            {
                format += "%s";
                printf_args.emplace_back(arg->GetMemory());
            }
            else
            {
                std::cerr << "[write/writeln] Unsupported type" << std::endl;
                return nullptr;
            }
        }
        if (new_line)
        {
            format += "\n";
        }
        printf_args[0] = Contents::builder.CreateGlobalStringPtr(format, "printf_format");
    }
    else
    {
        printf_args.emplace_back(nullptr);
        for (auto arg : args_list)
        {
            Our_Type::Pascal_Type *tp = arg->GetType();
            if (tp->isIntegerTy())
            {
                format += "%d";
                printf_args.emplace_back(arg->GetValue());
            }
            else if (tp->isFloatingPointTy())
            {
                format += "%.1lf";
                printf_args.emplace_back(arg->GetValue());
            }
            else if (tp->isBoolean())
            {
                format += "%d";
                printf_args.emplace_back(arg->GetValue());
            }
            else if (tp->isCharTy())
            {
                format += "%c";
                printf_args.emplace_back(arg->GetValue());
            }
            else if (tp->isString())
            {
                format += "%s";
                printf_args.emplace_back(arg->GetMemory());
            }
            else
            {
                std::cerr << "[write/writeln] Unsupported type" << std::endl;
                return nullptr;
            }
        }
        if (new_line)
        {
            format += "\n";
        }
        printf_args[0] = Contents::builder.CreateGlobalStringPtr(format, "printf_format");
    }
    return Contents::builder.CreateCall(llvm_printf, printf_args, "call_printf");
}

llvm::Value *GenSysRead(const std::vector<std::shared_ptr<Value_Result>> &args_list, bool new_line, bool c_scanf = false)
{
    static llvm::Function *llvm_scanf = nullptr;
    if (llvm_scanf == nullptr)
    {
        // register printf
        std::vector<llvm::Type *> arg_types = {llvm::Type::getInt8PtrTy(Contents::context)};
        llvm::FunctionType *func_type = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(Contents::context),
            arg_types,
            true);
        llvm::Function *func = llvm::Function::Create(
            func_type,
            llvm::Function::ExternalLinkage,
            "scanf",
            &*(Contents::module));
        func->setCallingConv(llvm::CallingConv::C);
        llvm_scanf = func;
    }
    std::string format;
    std::vector<llvm::Value *> scanf_args;
    if (c_scanf)
    {
        for (auto arg : args_list)
        {
            scanf_args.emplace_back(arg->GetMemory());
        }
    }
    else
    {
        scanf_args.emplace_back(nullptr);
        for (auto arg : args_list)
        {
            Our_Type::Pascal_Type *tp = arg->GetType();
            if (tp->isIntegerTy())
            {
                format += "%d";
            }
            else if (tp->isFloatingPointTy())
            {
                format += "%lf";
            }
            else if (tp->isCharTy())
            {
                format += "%c";
            }
            else if (tp->isString())
            {
                format += "%s";
            }
            else
            {
                std::cerr << "[read/readln] Unsupported type" << std::endl;
                return nullptr;
            }
            scanf_args.emplace_back(arg->GetMemory());
        }
        if (new_line)
        {
            format += "%*[^\n]";
        }
        scanf_args[0] = Contents::builder.CreateGlobalStringPtr(format, "scanf_format");
    }
    llvm::Value *ret = Contents::builder.CreateCall(llvm_scanf, scanf_args, "call_scanf");
    if (new_line)
    {
        // consume \n
        Contents::builder.CreateCall(llvm_scanf, Contents::builder.CreateGlobalStringPtr("%*c", "scanf_newline"), "call_scanf");
    }
    return ret;
}

namespace Contents
{
    int temp_variable_count = 0;

    llvm::LLVMContext context;                  //上下文变量
    llvm::IRBuilder<> builder(context);         //构造器变量
    std::unique_ptr<llvm::Module> module = std::make_unique<llvm::Module>("pascal_module", context);
    std::map<std::string, llvm::Constant *> names_2_constants; // 全局变量表
    std::vector<CodeBlock *> codeblock_list;    //符号表链表

    std::shared_ptr<Error_Information_Record> error_record;
    bool isConstant(std::string id) {
        return names_2_constants.find(id) != names_2_constants.end();
    }
    //保存生成的IR代码
    void Save(std::string path)
    {
        int fd = open(path.c_str(), O_CREAT | O_WRONLY, 0644);
        if (fd < 0)
        {
            std::cerr << "cannot generate output file " << path << ", errno: " << errno << std::endl;
        }
        if (dup2(fd, 1) < 0)
        {
            std::cerr << "cannot dup output file to stdout, errno: " << errno << std::endl;
        }
        close(fd);
        module->print(llvm::outs(), nullptr);
    }

    //获取当前CodeBlock
    CodeBlock *GetCurrentBlock(void) { return *(codeblock_list.rbegin()); }

    Our_Type::Pascal_Type *GetVarType(std::string id)
    {
        if (!GetCurrentBlock()->isValue(id) && !codeblock_list[0]->isValue(id))
        {
            std::cout << "variable not found, return nullptr" << std::endl;
            return nullptr;
        }
        for (int i = codeblock_list.size() - 1; i >= 0; i--)
        {
            if (codeblock_list[i]->isType(id, true))
            {
                return codeblock_list[i]->names_2_ourtype[id];
            }
        }
        return nullptr;
    }

    std::pair<std::vector<std::string>, std::vector<Our_Type::Pascal_Type *>> GetAllLocalVarNameType()
    {
        std::vector<std::string> name_list;
        std::vector<Our_Type::Pascal_Type *> type_list;

        if (codeblock_list.size() == 1) //如果是只有一个CodeBlock ,说明是全局
            return make_pair(name_list, type_list);

        for (auto it : GetCurrentBlock()->names_2_values)
        {
            std::string name = it.first;
            Our_Type::Pascal_Type *type = nullptr;
            for (int i = codeblock_list.size() - 1; i >= 1; i--)
            {
                // do not count global variable
                // use the nearest one as it is the currently using type
                if (codeblock_list[i]->isType(name, true))
                {
                    type = codeblock_list[i]->names_2_ourtype[name];
                    break;
                }
            }

            assert(type != nullptr);

            name_list.push_back(name);
            type_list.push_back(type);
        }
        return std::make_pair(name_list, type_list);
    }

    // 系统调用函数 : 包括readln 和 writeln
    bool isSysFunc(std::string id)
    {
        for (auto &ch : id)
            ch = tolower(ch);
        if (id == "write" || id == "writeln")
            return true;
        if (id == "read" || id == "readln")
            return true;
        if (id == "scanf" || id == "printf")
            return true;
        return false;
    }

    llvm::Value *GenSysFunc(std::string id, const std::vector<std::shared_ptr<Value_Result>> &args_list)
    {
        for (auto &ch : id)
            ch = tolower(ch);
        if (id == "write")
            return GenSysWrite(args_list, false);
        if (id == "writeln")
            return GenSysWrite(args_list, true);
        if (id == "read")
            return GenSysRead(args_list, false);
        if (id == "readln")
            return GenSysRead(args_list, true);

        if (id == "scanf")
            return GenSysRead(args_list, false, true);
        if (id == "printf")
            return GenSysWrite(args_list, false, true);
        // report error
        return nullptr;
    }
}
