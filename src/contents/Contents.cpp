#include "Contents.hpp"

namespace Contents
{
    int num_of_global_variables =0;
    llvm::LLVMContext context;
    llvm::IRBuilder<> builder(context);
    std::unique_ptr<llvm::Module> module = std::make_unique<llvm::Module>("pascal_module", context);
    std::map<std::string, llvm::Constant* > names_2_constants; // global constants
    std::vector<CodeBlock* > codeblock_list;
    std::vector<std::string> error_message;
    std::vector<std::pair<int, int> > error_position;
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
}