#include "Contents.hpp"
#include <cstdio>

#include <iostream>
#include <vector>
#include <map>

namespace Contents
{
    int temp_variable_count = 0;
    llvm::LLVMContext context;
    llvm::IRBuilder<> builder(context);
    std::unique_ptr<llvm::Module> module = std::make_unique<llvm::Module>("pascal_module", context);
    std::map<std::string, llvm::Constant *> names_2_constants; // global constants
    std::vector<CodeBlock *> codeblock_list;
    // std::vector<std::string> error_message;
    // std::vector<std::pair<int, int> > error_position;
    std::shared_ptr<Error_Information_Record> error_record;
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
}
