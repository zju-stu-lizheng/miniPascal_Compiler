#pragma once
#include "AST_BaseNode.hpp"
#include <vector>

class AST_BaseNode;
class AST_Type;
class AST_TypeDecl;
class AST_SimpleTypeDecl;
class AST_ArrayTypeDecl;
class AST_RecordTypeDecl;
class AST_FieldDeclList;
class AST_FieldDecl;
class AST_NameList;

// easy_type -> int / char / boolean / float
class AST_Type: AST_BaseNode{
    public:
        enum class Type_Name{
            INT,FLOAT,BOOLEAN,CHAR
        };
        AST_Type(Type_Name _typename):
                        my_typename(_typename){};

        Type_Name Get_Type_Name() const{
            return this->my_typename;
        }
    private:
        Type_Name my_typename;
};

// type_decl -> SimpleTypeDecl / ArrayTypeDecl / RecordTypeDecl
class AST_TypeDecl: AST_BaseNode{};

/*
simple_type_decl -> 
    easy_type   (目前只支持这个)
    | IDENTIFIER
    | SYM_LPAREN name_list SYM_RPAREN
    |  const_value  SYM_RANGE  const_value
    |  IDENTIFIER  SYM_RANGE  IDENTIFIER
*/
class AST_SimpleTypeDecl: AST_TypeDecl{
    public:
        enum class My_Type{
            EASY_TYPE,IDENTIFIER,ENUMERATE,VALUE_RANGE,IDENTIFIER_RANGE
        };

        AST_SimpleTypeDecl(AST_Type *_type):
                        my_typename(_type),my_type(My_Type::EASY_TYPE){};

        // AST_SimpleTypeDecl(AST_ConstValue *_type):
        //                 my_Typename(_type),my_Type(My_Type::EASY_TYPE){};

        My_Type Get_Type() const{
            return this->my_type;
        }

        My_Type my_type;
    private:
        AST_Type* my_typename;
};

/*
array_type_decl->
    KEY_ARRAY SYM_LBRAC simple_type_decl SYM_RBRAC KEY_OF type_decl
*/
class AST_ArrayTypeDecl : AST_TypeDecl{
    public:
        AST_ArrayTypeDecl(AST_SimpleTypeDecl* _simple_type_decl,AST_TypeDecl* _type_decl):
                        simple_type_decl(_simple_type_decl),type_decl(_type_decl){};
    private:
        AST_SimpleTypeDecl* simple_type_decl;
        AST_TypeDecl* type_decl;
};

/**
 * @brief 
 * record_type_decl -> 
    KEY_RECORD field_decl_list KEY_END
 */
class AST_RecordTypeDecl : AST_TypeDecl{
    public:
        AST_RecordTypeDecl(AST_FieldDeclList* _field_decl_list):
                        field_decl_list(_field_decl_list){};
    private:
        AST_FieldDeclList* field_decl_list;
};

/**
 * @brief 
 * field_decl_list -> {field_decl}
 */
class AST_FieldDeclList : AST_TypeDecl{
    public:
        AST_FieldDeclList(){};

    private:
        std::vector<AST_FieldDecl *> field_decl_list;
};

/**
 * @brief 
 * field_decl->
    name_list SYM_COLON type_decl SYM_SEMICOLON
 */
class AST_FieldDecl : AST_TypeDecl{
    public:
        AST_FieldDecl(AST_TypeDecl* _type_decl,AST_NameList* _name_list):
                    name_list(_name_list),type_decl(_type_decl){};

    private:
        AST_NameList* name_list;
        AST_TypeDecl* type_decl;
};


class AST_NameList :AST_TypeDecl{

};