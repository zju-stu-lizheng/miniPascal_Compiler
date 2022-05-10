#include "AST_BaseNode.hpp"
// #include ""

class AST_Program: AST_BaseNode{
    private:
        AST_Program_Head* program_head;
        AST_Routine* routine;
    public:
        AST_Program(AST_Program_Head* _program_head, AST_Routine* _routine):
                        program_head(_program_head),routine(_routine){};

        AST_Program_Head* Get_Program_Head() const{
            return this->program_head;
        }

        AST_Routine* Get_Routine() const{
            return this->routine;
        }
};

class AST_Program_Head: AST_BaseNode{
    private:
        std::string identifier;
    public:
        AST_Program_Head(std::string _identifier): identifier(_identifier){};

        std::string Get_identifier() const{
            return identifier;
        }

};

class AST_Routine: AST_BaseNode{
    private:
        AST_Routine_Head* routine_head;
        AST_Routine_Body* routine_body;
    public:
        AST_Routine(AST_Routine_Head* _routine_head, AST_Routine_Body* _routine_body):
                        routine_head(_routine_head), routine_body(_routine_body){};
        
        AST_Routine_Head* Get_Routine_Head() const{
            return this->routine_head;
        }

        AST_Routine_Body* Get_Routine_Body() const{
            return this->routine_body;
        }
};

class AST_Routine_Head: AST_BaseNode{
    private:
        AST_Const_Part* const_part;
        AST_Type_Part* type_part;
        AST_Var_Part* var_part;
        AST_Routine_Part* routine_part;
    public:
        AST_Routine_Head(AST_Const_Part* _const_part, AST_Type_Part* _type_part, AST_Var_Part* _var_part, AST_Routine_Part* _routine_part):
                        const_part(_const_part), type_part(_type_part), var_part(_var_part), routine_part(_routine_part){};
        AST_Const_Part* Get_Const_Part() const{
            return this->const_part;
        }
        AST_Type_Part* Get_Type_Part() const{
            return this->type_part;
        }
        AST_Var_Part* Get_Var_Part() const{
            return this->var_part;
        }
        AST_Routine_Part* Get_Routine_Part() const{
            return this->routine_part;
        }
};

class AST_Routine_Body: AST_BaseNode{
    private:
        AST_Compound_Statement* compound_statement;
    public:
        AST_Routine_Body(AST_Compound_Statement* _compound_statement):
                    compound_statement(_compound_statement){};
        AST_Compound_Statement* Get_Compound_Statement() const{
            return this->compound_statement;
        }
};

class AST_Function_Declaration: AST_BaseNode{
    private:
        AST_Function_Head* function_head;
        AST_Routine* routine;
    public:
        AST_Function_Declaration(AST_Function_Head* _function_head, AST_Routine* _routine):
                                    function_head(_function_head), routine(_routine){};
        AST_Function_Head* Get_Function_Head() const{
            return this->function_head;
        }
        AST_Routine* Get_routine() const{
            return this->routine;
        }
};

class AST_Function_Head: AST_BaseNode{
    private:
        std::string identifier;
        AST_Parameters* parameters;
        AST_Simple_Type_Declaration* simple_type_declaration;
    public:
        AST_Function_Head(std::string _identifier, AST_Parameters* _parameters, AST_Simple_Type_Declaration* _simple_type_declaration):
                            identifier(_identifier), parameters(_parameters), simple_type_declaration(_simple_type_declaration){};
        std::string Get_identifier() const{
            return this->identifier;
        }
        AST_Parameters* Get_Parameters() const{
            return this->parameters;
        }
        AST_Simple_Type_Declaration* Get_Simple_Type_Declaration() const{
            return this->simple_type_declaration;
        }
}

class AST_Procedure_Declaration: AST_BaseNode{
    private:
        
}