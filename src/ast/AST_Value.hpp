#pragma once
#include "AST_BaseNode.hpp"
#include "AST_Type.hpp"
#include "AST_Expression.hpp"

class AST_Expression;
class AST_Name_List;
class AST_Type_Declaration;

class AST_Const_Part;
class AST_Const_Expression_List;
class AST_Const_Expression;
class AST_Const_Value;

class AST_Variable_Part;
class AST_Variable_Declaration_List;
class AST_Variable_Declaration;

/**
 * @brief
 * const_value:
    LITERAL_INT
    | LITERAL_FLOAT
    | LITERAL_CHAR
    | LITERAL_STR
    | LITERAL_FALSE
    | LITERAL_TRUE
 */
class AST_Const_Value : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result> CodeGenerate() override;
    void PrintNode(GraphViz *g);

public:
    enum class Value_Type
    {
        INT,
        FLOAT,
        CHAR,
        STRING,
        FALSE,
        TRUE
    };
    AST_Const_Value(std::string _content, enum Value_Type _value_type) : content(_content), value_type(_value_type){};

    std::string Get_Value_Type_Name(Value_Type value_type)
    {
        std::string name;
        switch (value_type)
        {
        case AST_Const_Value::Value_Type::INT:
            name = "INT";
            break;
        case AST_Const_Value::Value_Type::FLOAT:
            name = "FLOAT";
            break;
        case AST_Const_Value::Value_Type::CHAR:
            name = "CHAR";
            break;
        case AST_Const_Value::Value_Type::STRING:
            name = "STRING";
            break;
        case AST_Const_Value::Value_Type::FALSE:
            name = "FALSE";
            break;
        case AST_Const_Value::Value_Type::TRUE:
            name = "TRUE";
            break;
        }
        return name;
    }

    AST_Const_Value::Value_Type value_type;
    std::string content;
};

/*
const_expr_list->
    {const_expr}
*/
class AST_Const_Expression_List : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result> CodeGenerate() override;
    void PrintNode(GraphViz *g);
public:
    AST_Const_Expression_List() = default;
    void Add_Const_Expression(AST_Const_Expression *const_expr)
    {
        const_expr_list.push_back(const_expr);
    }

    std::vector<AST_Const_Expression *> const_expr_list;
};

class AST_Const_Expression : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result> CodeGenerate() override;

    void PrintNode(GraphViz *g);

public:
    AST_Const_Expression(std::string _id, AST_Expression *_value) : id(_id), value(_value){};

    std::string id;
    AST_Expression *value;
};

class AST_Const_Part : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result> CodeGenerate() override;
    void PrintNode(GraphViz *g);

public:
    AST_Const_Part(AST_Const_Expression_List *_const_expr_list) : const_expr_list(_const_expr_list){};

    AST_Const_Expression_List *const_expr_list;
};

class AST_Variable_Part : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result> CodeGenerate() override;
    void PrintNode(GraphViz *g);

public:
    AST_Variable_Part(AST_Variable_Declaration_List *_var_decl_list) : var_decl_list(_var_decl_list){};

    AST_Variable_Declaration_List *var_decl_list;
};

class AST_Variable_Declaration_List : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result> CodeGenerate() override;
    void PrintNode(GraphViz *g);

public:
    AST_Variable_Declaration_List() = default;
    void Add_Variable_Declaration(AST_Variable_Declaration *var_decl)
    {
        var_decl_list.push_back(var_decl);
    }

    std::vector<AST_Variable_Declaration *> var_decl_list;
};

class AST_Variable_Declaration : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result> CodeGenerate() override;
    void PrintNode(GraphViz *g);

public:
    AST_Variable_Declaration(AST_Name_List *_name_list, AST_Type_Declaration *_type_decl) : name_list(_name_list), type_decl(_type_decl){};

    AST_Name_List *name_list;
    AST_Type_Declaration *type_decl;
};