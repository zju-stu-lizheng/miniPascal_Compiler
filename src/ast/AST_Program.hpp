#pragma once
#include "AST_BaseNode.hpp"
#include "AST_Type.hpp"
#include "AST_Expression.hpp"

class AST_Variable_Part;
class AST_Type_Part;
class AST_Const_Part;

class AST_Compound_Statement;
class AST_Program_Head;
class AST_Routine;
class AST_Routine_Body;
class AST_Routine_Head;

class AST_Routine_Part;
class AST_Parameters_Declaration_List;
class AST_Parameters;
class AST_Function_Declaration;
class AST_Procedure_Declaration;
class AST_Procedure_Head;
class AST_Parameters_Type_List;
class AST_Variable_Parameters_List;
class AST_Function_Head;

/*
program:
    pro_head routine SYM_PERIOD
;
*/
class AST_Program : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result> CodeGenerate() override;
    void PrintNode(GraphViz *g)
    {
        g->AddNode("program", GetRow(), GetColumn());
        program_head->PrintNode(g);
        routine->PrintNode(g);
        g->Pop();
    }

private:
    AST_Program_Head *program_head;
    AST_Routine *routine;

public:
    AST_Program(AST_Program_Head *_program_head, AST_Routine *_routine) : program_head(_program_head), routine(_routine){};

    AST_Program_Head *Get_Program_Head() const
    {
        return this->program_head;
    }

    AST_Routine *Get_Routine() const
    {
        return this->routine;
    }
};

/*
pro_head:
    KEY_PROGRAM IDENTIFIER SYM_SEMICOLON{
    }
;
*/
class AST_Program_Head : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result> CodeGenerate() override;
    void PrintNode(GraphViz *g)
    {
        g->AddNode("program_head", GetRow(), GetColumn());
        g->AddIdentifier(identifier);
        g->Pop();
    }

private:
    std::string identifier;

public:
    AST_Program_Head(std::string _identifier) : identifier(_identifier){};

    std::string Get_Identifier() const
    {
        return identifier;
    }
};

/*
routine:
    routine_head routine_body{}
;
*/

class AST_Routine : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result> CodeGenerate() override;
    void PrintNode(GraphViz *g)
    {
        g->AddNode("routine", GetRow(), GetColumn());
        routine_head->PrintNode(g);
        routine_body->PrintNode(g);
        g->Pop();
    }

private:
    AST_Routine_Head *routine_head;
    AST_Routine_Body *routine_body;

public:
    AST_Routine(AST_Routine_Head *_routine_head, AST_Routine_Body *_routine_body) : routine_head(_routine_head), routine_body(_routine_body){};

    AST_Routine_Head *Get_Routine_Head() const
    {
        return this->routine_head;
    }

    AST_Routine_Body *Get_Routine_Body() const
    {
        return this->routine_body;
    }
};

/*
routine_head:
    const_part type_part var_part routine_part{}
;
*/
class AST_Routine_Head : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result> CodeGenerate() override;
    void PrintNode(GraphViz *g)
    {
        g->AddNode("routine_head", GetRow(), GetColumn());
        if (const_part != nullptr)
            const_part->PrintNode(g);
        if (type_part != nullptr)
            type_part->PrintNode(g);
        if (var_part != nullptr)
            var_part->PrintNode(g);
        if (routine_part != nullptr)
            routine_part->PrintNode(g);
        g->Pop();
    }

private:
    AST_Const_Part *const_part;
    AST_Type_Part *type_part;
    AST_Variable_Part *var_part;
    AST_Routine_Part *routine_part;

public:
    AST_Routine_Head(AST_Const_Part *_const_part, AST_Type_Part *_type_part, AST_Variable_Part *_var_part, AST_Routine_Part *_routine_part) : const_part(_const_part), type_part(_type_part), var_part(_var_part), routine_part(_routine_part){};
    AST_Const_Part *Get_Const_Part() const
    {
        return this->const_part;
    }
    AST_Type_Part *Get_Type_Part() const
    {
        return this->type_part;
    }
    AST_Variable_Part *Get_Variable_Part() const
    {
        return this->var_part;
    }
    AST_Routine_Part *Get_Routine_Part() const
    {
        return this->routine_part;
    }
};

/// for routine part list
class AST_Declaration_BaseClass : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result> CodeGenerate() override;
    void PrintNode(GraphViz *g)
    {
        if (is_function)
            function_declaration->PrintNode(g);
        else
            procedure_declaration->PrintNode(g);
    }

private:
    enum class ENUM_Declaration_Type
    {
        FUNCTION_DECLARATION,
        PROCEDURE_DECLARATION
    };
    AST_Function_Declaration *function_declaration;
    AST_Procedure_Declaration *procedure_declaration;
    ENUM_Declaration_Type declaration_type;
    bool is_function;

public:
    AST_Declaration_BaseClass(AST_Function_Declaration *_function_declaration) : function_declaration(_function_declaration)
    {
        is_function = true;
        this->declaration_type = ENUM_Declaration_Type::FUNCTION_DECLARATION;
    }
    AST_Declaration_BaseClass(AST_Procedure_Declaration *_procedure_declaration) : procedure_declaration(_procedure_declaration)
    {
        is_function = false;
        this->declaration_type = ENUM_Declaration_Type::PROCEDURE_DECLARATION;
    }

    AST_Function_Declaration *Get_Function_Declaration() const
    {
        return this->function_declaration;
    }
    AST_Procedure_Declaration *Get_Procedure_Declaration() const
    {
        return this->procedure_declaration;
    }
    ENUM_Declaration_Type Get_Declaration_Type() const
    {
        return this->declaration_type;
    }
};

/*
routine_part:  {function_decl | procedure_decl}
    routine_part function_decl
    | routine_part procedure_decl
    | function_decl
    | procedure_decl
    |
;
*/
class AST_Routine_Part : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result> CodeGenerate() override;
    void PrintNode(GraphViz *g)
    {
        g->AddNode("routine_part", GetRow(), GetColumn());
        for (auto rp : this->declaration_list)
        {
            rp->PrintNode(g);
        }
        g->Pop();
    }

private:
    std::vector<AST_Declaration_BaseClass *> declaration_list;

public:
    void Add_Declaration(AST_Declaration_BaseClass *_declaration)
    {
        this->declaration_list.push_back(_declaration);
    }
    AST_Routine_Part(AST_Declaration_BaseClass *_declaration)
    {
        this->declaration_list.clear();
        Add_Declaration(_declaration);
    }
    std::vector<AST_Declaration_BaseClass *> Get_Declaration_List() const
    {
        return declaration_list;
    }
};

/*
routine_body:
    compound_stmt
;
*/

class AST_Routine_Body : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result> CodeGenerate() override;
    void PrintNode(GraphViz *g)
    {
        g->AddNode("routine_body", GetRow(), GetColumn());
        this->compound_statement->PrintNode(g);
        g->Pop();
    }

private:
    AST_Compound_Statement *compound_statement;

public:
    AST_Routine_Body(AST_Compound_Statement *_compound_statement) : compound_statement(_compound_statement){};
    AST_Compound_Statement *Get_Compound_Statement() const
    {
        return this->compound_statement;
    }
};

/*
function_decl:
    function_head SYM_SEMICOLON routine SYM_SEMICOLON
;
*/
class AST_Function_Declaration : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result> CodeGenerate() override;
    void PrintNode(GraphViz *g)
    {
        g->AddNode("function_decl", this->GetRow(),
                   this->GetColumn());
        if (this->function_head != nullptr)
            this->function_head->PrintNode(g);
        if (this->routine != nullptr)
            this->routine->PrintNode(g);
        g->Pop();
    }

private:
    AST_Function_Head *function_head;
    AST_Routine *routine;

public:
    AST_Function_Declaration(AST_Function_Head *_function_head, AST_Routine *_routine) : function_head(_function_head), routine(_routine){};
    AST_Function_Head *Get_Function_Head() const
    {
        return this->function_head;
    }
    AST_Routine *Get_routine() const
    {
        return this->routine;
    }
};

/*
function_head:
    KEY_FUNCTION IDENTIFIER parameters SYM_COLON simple_type_decl
;
*/
class AST_Function_Head : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result> CodeGenerate() override;
    void PrintNode(GraphViz *g)
    {
        g->AddNode("function_head of " + this->identifier, this->GetRow(),
                   this->GetColumn());
        if (this->parameters != nullptr)
            this->parameters->PrintNode(g);
        if (this->simple_type_declaration != nullptr)
            this->simple_type_declaration->PrintNode(g);
        g->Pop();
    }

private:
    std::string identifier;
    AST_Parameters *parameters;
    AST_Simple_Type_Declaration *simple_type_declaration;

public:
    AST_Function_Head(std::string _identifier, AST_Parameters *_parameters, AST_Simple_Type_Declaration *_simple_type_declaration) : identifier(_identifier), parameters(_parameters), simple_type_declaration(_simple_type_declaration){};
    std::string Get_Identifier() const
    {
        return this->identifier;
    }
    AST_Parameters *Get_Parameters() const
    {
        return this->parameters;
    }
    AST_Simple_Type_Declaration *Get_Simple_Type_Declaration() const
    {
        return this->simple_type_declaration;
    }
};

/*
procedure_decl:
    procedure_head SYM_SEMICOLON routine SYM_SEMICOLON
;
*/
class AST_Procedure_Declaration : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result> CodeGenerate() override;
    void PrintNode(GraphViz *g)
    {
        g->AddNode("procedure_decl", this->GetRow(),
                   this->GetColumn());
        if (this->procedure_head != nullptr)
            this->procedure_head->PrintNode(g);
        if (this->routine != nullptr)
            this->routine->PrintNode(g);
        g->Pop();
    }

private:
    AST_Procedure_Head *procedure_head;
    AST_Routine *routine;

public:
    AST_Procedure_Declaration(AST_Procedure_Head *_procedure_head, AST_Routine *_routine) : procedure_head(_procedure_head), routine(_routine){};
    AST_Procedure_Head *Get_Procedure_Head() const
    {
        return this->procedure_head;
    }
    AST_Routine *Get_Routine() const
    {
        return this->routine;
    }
};

/*
procedure_head:
    KEY_PROCEDURE IDENTIFIER parameters
;
*/
class AST_Procedure_Head : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result> CodeGenerate() override;
    void PrintNode(GraphViz *g)
    {
        g->AddNode("procedure_head of " + this->identifier, this->GetRow(),
                   this->GetColumn());
        if (this->parameters != nullptr)
            this->parameters->PrintNode(g);
        g->Pop();
    }

private:
    std::string identifier;
    AST_Parameters *parameters;

public:
    AST_Procedure_Head(std::string _identifier, AST_Parameters *_parameters) : identifier(_identifier), parameters(_parameters){};
    std::string Get_Identifier() const
    {
        return this->identifier;
    }
    AST_Parameters *Get_Parameters() const
    {
        return this->parameters;
    }
};

/*
parameters:
    SYM_LPAREN para_decl_list SYM_RPAREN 
    | 
;
*/
class AST_Parameters : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result> CodeGenerate() override;
    void PrintNode(GraphViz *g)
    {
        g->AddNode("parameters", this->GetRow(),
                   this->GetColumn());
        if (this->parameters_declaration_list != nullptr)
            this->parameters_declaration_list->PrintNode(g);
        g->Pop();
    }
private:
    AST_Parameters_Declaration_List *parameters_declaration_list;

public:
    AST_Parameters() = default;
    AST_Parameters(AST_Parameters_Declaration_List *_parameters_declaration_list) : parameters_declaration_list(_parameters_declaration_list){};
    AST_Parameters_Declaration_List *Get_Parameters_Declaration_List() const
    {
        return this->parameters_declaration_list;
    }
};

/*
para_decl_list:
    para_decl_list SYM_SEMICOLON para_type_list
    | para_type_list
;
*/
class AST_Parameters_Declaration_List : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result> CodeGenerate() override;
    void PrintNode(GraphViz *g)
    {
        g->AddNode("para_decl_list", this->GetRow(),
                   this->GetColumn());
        for(auto type_list : parameters_type_list_list){
            type_list ->PrintNode(g);
        }
        g->Pop();
    }
private:
    std::vector<AST_Parameters_Type_List *> parameters_type_list_list;

public:
    void Add_Parameters_Type_List(AST_Parameters_Type_List *_parameters_type_list)
    {
        this->parameters_type_list_list.push_back(_parameters_type_list);
    }
    AST_Parameters_Declaration_List(AST_Parameters_Type_List *_parameters_type_list)
    {
        this->parameters_type_list_list.clear();
        Add_Parameters_Type_List(_parameters_type_list);
    }
    AST_Parameters_Declaration_List()
    {
        this->parameters_type_list_list.clear();
    }
    std::vector<AST_Parameters_Type_List *> Get_Parameter_Type_List_List() const
    {
        return this->parameters_type_list_list;
    }
};

/*
para_type_list:
    var_para_list SYM_COLON simple_type_decl
    | name_list SYM_COLON simple_type_decl
;
*/
class AST_Parameters_Type_List : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result> CodeGenerate() override;
    void PrintNode(GraphViz *g)
    {
        g->AddNode("para_type_list", this->GetRow(),
                   this->GetColumn());
        if(is_namelist){
            name_list->PrintNode(g);
        }else{
            variable_parameters_list->PrintNode(g);
        }
        simple_type_declaration->PrintNode(g);
        g->Pop();
    }
private:
    enum class List_Type
    {
        VARIABLE_PARAMETERS_LIST,
        NAME_LIST
    };
    AST_Variable_Parameters_List *variable_parameters_list;
    AST_Name_List *name_list;
    List_Type list_type;
    AST_Simple_Type_Declaration *simple_type_declaration;

public:
    bool is_namelist;
    AST_Parameters_Type_List(AST_Variable_Parameters_List *_variable_parameters_list, AST_Simple_Type_Declaration *_simple_type_declaration) : variable_parameters_list(_variable_parameters_list), simple_type_declaration(_simple_type_declaration), list_type(List_Type::VARIABLE_PARAMETERS_LIST){
        is_namelist = false;
    };
    AST_Parameters_Type_List(AST_Name_List *_name_list, AST_Simple_Type_Declaration *_simple_type_declaration) : name_list(_name_list), simple_type_declaration(_simple_type_declaration), list_type(List_Type::NAME_LIST){
        is_namelist = true
    };
    AST_Variable_Parameters_List *Get_Variable_Parameters_List() const
    {
        return this->variable_parameters_list;
    }
    AST_Name_List *Get_Name_List() const
    {
        return this->name_list;
    }
    AST_Simple_Type_Declaration *Get_Simple_Type_Declaration() const
    {
        return this->simple_type_declaration;
    }
    List_Type Get_List_Type() const
    {
        return this->list_type;
    }
    bool isVar()
    {
        return this->list_type == List_Type::VARIABLE_PARAMETERS_LIST;
    }
};

/*
var_para_list:
    KEY_VAR name_list
;
*/
class AST_Variable_Parameters_List : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result> CodeGenerate() override;
    void PrintNode(GraphViz *g)
    {
        g->AddNode("var_para_list", this->GetRow(),
                   this->GetColumn());
        name_list->PrintNode(g);
        g->Pop();
    }
private:
    AST_Name_List *name_list;

public:
    AST_Variable_Parameters_List(AST_Name_List *_name_list) : name_list(_name_list){};
    AST_Name_List *Get_Name_List() const
    {
        return this->name_list;
    }
};
