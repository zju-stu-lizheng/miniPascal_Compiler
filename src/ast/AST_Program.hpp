#include "AST_BaseNode.hpp"
#include ""

class AST_Program: AST_BaseNode{
    private:
        AST_Program_Head* program_head;
        AST_Routine* routine;
    public:
        AST_Program(AST_Program_Head* _program_head, AST_Routine* _routine):
                        program_head(_program_head),routine(_routine){};

        AST_Program_Head* Get_Program_Head(){
            return this->program_head
        };

        AST_Routine* Get_Routine(){
            return this->routine
        };
};

class AST_Program_Head: AST_BaseNode{
    private:
        AST_Program* program;
        AST_Program_Name* program_name;
    public:
        AST_Program_Head(AST_Program* _program, AST_Program_Name* _program_name):
                            program(_program), program_name(_program_name){};
        
};