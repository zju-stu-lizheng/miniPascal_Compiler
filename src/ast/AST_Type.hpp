#pragma once
#include "AST_BaseNode.hpp"
#include "AST_Value.hpp"
#include <vector>

class AST_BaseNode;
class AST_Const_Value;

class AST_Type_Part;
class AST_Type_Definition;
class AST_Type_Declaration_List;

class AST_Type;
class AST_Type_Declaration;
class AST_Simple_Type_Declaration;
class AST_Array_Type_Declaration;
class AST_Record_Type_Declaration;
class AST_Field_Declaration_List;
class AST_Field_Declaration;
class AST_Name_List;

// easy_type -> int / char / boolean / float / string
class AST_Type : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result>CodeGenerate() override;

public:
    enum class Type_Name
    {
        INT,
        FLOAT,
        BOOLEAN,
        CHAR,
        STRING
    };
    AST_Type(AST_Type::Type_Name _typename) : my_typename(_typename){};

    AST_Type::Type_Name Get_Type_Name() const
    {
        return this->my_typename;
    }

    AST_Type::Type_Name my_typename;
};

// type_decl -> SimpleTypeDecl / ArrayTypeDecl / RecordTypeDecl
class AST_Type_Declaration : public AST_BaseNode
{
public:
    virtual std::shared_ptr<Custom_Result> CodeGenerate()=0;
};

/*
simple_type_decl ->
    easy_type
    | IDENTIFIER
    | SYM_LPAREN name_list SYM_RPAREN
    |  const_value  SYM_RANGE  const_value
    |  IDENTIFIER  SYM_RANGE  IDENTIFIER
*/
class AST_Simple_Type_Declaration : public AST_Type_Declaration
{
public:
    std::shared_ptr<Custom_Result> CodeGenerate() override;

public:
    enum class My_Type
    {
        EASY_TYPE,
        IDENTIFIER,
        ENUMERATE,
        VALUE_RANGE,
        IDENTIFIER_RANGE
    };

    AST_Simple_Type_Declaration(AST_Type *_type) : my_typename(_type), my_type(My_Type::EASY_TYPE){};

    AST_Simple_Type_Declaration(std::string _define_id) : define_id(_define_id), my_type(My_Type::IDENTIFIER){};

    AST_Simple_Type_Declaration(AST_Name_List *_name_list) : name_list(_name_list), my_type(My_Type::ENUMERATE){};

    AST_Simple_Type_Declaration(AST_Const_Value *_low, AST_Const_Value *_high) : low(_low), high(_high), my_type(My_Type::VALUE_RANGE){};

    AST_Simple_Type_Declaration(std::string _low_name, std::string _high_name) : low_name(_low_name), high_name(_high_name), my_type(My_Type::IDENTIFIER_RANGE){};

    My_Type Get_Type() const
    {
        return this->my_type;
    }

    My_Type my_type;

    AST_Type *my_typename;
    std::string define_id;
    AST_Name_List *name_list;
    AST_Const_Value *low, *high;
    std::string low_name, high_name;
};

/*
array_type_decl->
    KEY_ARRAY SYM_LBRAC simple_type_decl SYM_RBRAC KEY_OF type_decl
*/
class AST_Array_Type_Declaration : public AST_Type_Declaration
{
public:
    std::shared_ptr<Custom_Result>CodeGenerate() override;

public:
    AST_Array_Type_Declaration(AST_Simple_Type_Declaration *_simple_type_decl, AST_Type_Declaration *_type_decl) : simple_type_decl(_simple_type_decl), type_decl(_type_decl){};

    AST_Simple_Type_Declaration *simple_type_decl;
    AST_Type_Declaration *type_decl;
};

/**
 * @brief
 * record_type_decl ->
    KEY_RECORD field_decl_list KEY_END
 */
class AST_Record_Type_Declaration : public AST_Type_Declaration
{
public:
    std::shared_ptr<Custom_Result>CodeGenerate() override;

public:
    AST_Record_Type_Declaration(AST_Field_Declaration_List *_field_decl_list) : field_decl_list(_field_decl_list){};

    AST_Field_Declaration_List *field_decl_list;
};

/**
 * @brief
 * field_decl_list -> {field_decl}
 */
class AST_Field_Declaration_List : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result>CodeGenerate() override;

public:
    AST_Field_Declaration_List(AST_Field_Declaration *_field_decl)
    {
        field_decl_list.clear();
        field_decl_list.push_back(_field_decl);
    }
    void Add_Field_Declaration(AST_Field_Declaration *_field_decl)
    {
        field_decl_list.push_back(_field_decl);
    }

    std::vector<AST_Field_Declaration *> field_decl_list;
};

/**
 * @brief
 * field_decl->
    name_list SYM_COLON type_decl SYM_SEMICOLON
 */
class AST_Field_Declaration : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result>CodeGenerate() override;

public:
    AST_Field_Declaration(AST_Name_List *_name_list, AST_Type_Declaration *_type_decl) : name_list(_name_list), type_decl(_type_decl){};

    AST_Name_List *name_list;
    AST_Type_Declaration *type_decl;
};

/**
 * name_list->
    {IDENTIFIER}
*/
class AST_Name_List : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result>CodeGenerate() override;

public:
    AST_Name_List() = default;
    void Add_Identifier(std::string id)
    {
        identifier_list.push_back(id);
    }

    std::vector<std::string> identifier_list;
};

/**
 *
 *type_decl_list->{type_definition}
 */
class AST_Type_Declaration_List : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result>CodeGenerate() override;

public:
    AST_Type_Declaration_List() = default;
    void Add_Type_Definition(AST_Type_Definition *type_definition)
    {
        type_definition_list.push_back(type_definition);
    }

    std::vector<AST_Type_Definition *> type_definition_list;
};

/**
type_definition->
    IDENTIFIER SYM_EQ type_decl SYM_SEMICOLON
*/
class AST_Type_Definition : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result>CodeGenerate() override;

public:
    AST_Type_Definition(std::string id, AST_Type_Declaration *_type_decl) : identifier(id), type_decl(_type_decl){};

    std::string identifier;
    AST_Type_Declaration *type_decl;
};

/**
type_part->
    KEY_TYPE type_decl_list | %empty
*/
class AST_Type_Part : public AST_BaseNode
{
public:
    std::shared_ptr<Custom_Result>CodeGenerate() override;

public:
    AST_Type_Part(AST_Type_Declaration_List *_type_decl_list) : type_decl_list(_type_decl_list){};

    AST_Type_Declaration_List *type_decl_list;
};
