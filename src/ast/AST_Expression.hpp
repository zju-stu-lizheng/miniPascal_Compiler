#pragma once
#include "AST_BaseNode.hpp"
#include "AST_Value.hpp"

class AST_Expression;
class AST_Expression_List;
/* 下面的类作为AST_Expression的子类 */
class AST_Binary_Expression;
class AST_Unary_Expression;
class AST_Property_Expression;
class AST_Const_Value_Expression;
class AST_Function_Call;
class AST_Identifier_Expression;
class AST_Array_Expression;

class AST_Const_Value;

class AST_Expression : public AST_BaseNode
{
public:
    AST_Expression() = default;
};

class AST_Expression_List : public AST_Expression
{
public:
    AST_Expression_List() = default;
    void Add_Expression(AST_Expression *expr)
    {
        expr_list.push_back(expr);
    }

private:
    std::vector<AST_Expression *> expr_list;
};

/**
 * @brief : 二元表达式
 *
 */
class AST_Binary_Expression : public AST_Expression
{
public:
    enum class Operation
    {
        GE,
        GT,
        LE,
        LT,
        EQUAL,
        UNEQUAL,
        PLUS,
        MINUS,
        OR,
        MUL,
        DIV,
        MOD,
        AND
    };
    AST_Binary_Expression(Operation _my_operation, AST_Expression *_left_expression, AST_Expression *_right_expression) : my_operation(_my_operation), left_expression(_left_expression), right_expression(_right_expression){};

    static std::string Get_Operation_Name(Operation my_op)
    {
        switch (my_op)
        {
        case Operation::GE:
            return "GE";
            break;
        case Operation::GT:
            return "GT";
            break;
        case Operation::LE:
            return "LE";
            break;
        case Operation::LT:
            return "LT";
            break;
        case Operation::EQUAL:
            return "EQUAL";
            break;
        case Operation::UNEQUAL:
            return "UNEQUAL";
            break;
        case Operation::PLUS:
            return "PLUS";
            break;
        case Operation::MINUS:
            return "MINUS";
            break;
        case Operation::OR:
            return "OR";
            break;
        case Operation::MUL:
            return "MUL";
            break;
        case Operation::DIV:
            return "DIV";
            break;
        case Operation::MOD:
            return "MOD";
            break;
        case Operation::AND:
            return "AND";
            break;
        }
        return "";
    }

private:
    Operation my_operation;
    AST_Expression *left_expression, *right_expression;
};

/**
 * @brief : 一元表达式
 *
 */
class AST_Unary_Expression : public AST_Expression
{
public:
    enum class Operation
    {
        NOT,
        SUB
    };
    AST_Unary_Expression(Operation _my_operation, AST_Expression *_expression) : my_operation(_my_operation), expression(_expression){};

private:
    Operation my_operation;
    AST_Expression *expression;
};

/**
 * @brief 结构表达式 : Record的成员
 *
 */
class AST_Property_Expression : public AST_BaseNode
{
private:
    /*id:Record变量名 ; prop_id:成员变量名*/
    std::string id, prop_id;

public:
    AST_Property_Expression(std::string _id, std::string _prop_id) : id(_id), prop_id(_prop_id){};
};

/**
 * @brief : 常数表达式
 *
 */
class AST_Const_Value_Expression : public AST_BaseNode
{
private:
    AST_Const_Value *const_value;

public:
    AST_Const_Value_Expression(AST_Const_Value *_const_value) : const_value(_const_value){};
};

class AST_Function_Call
{
private:
    /*func_id:函数名 ; args_list:参数列表*/
    std::string func_id;
    AST_Expression_List *args_list;

public:
    AST_Function_Call(std::string _func_id, AST_Expression_List *_args_list) : func_id(_func_id), args_list(_args_list){};
};

class AST_Identifier_Expression : public AST_Expression
{
private:
    std::string id;

public:
    AST_Identifier_Expression(std::string _id) : id(_id){};
};

class AST_Array_Expression : public AST_Expression
{
private:
    std::string id;
    AST_Expression *expression;

public:
    AST_Array_Expression(std::string _id, AST_Expression *_expression):
        id(_id),expression(_expression){};
};