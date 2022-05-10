%{
#include <stdio.h>
#define MAX_LITERAL_LEN 256

%}

%locations

%token TYPE_INT TYPE_INT_8 TYPE_INT_16 TYPE_INT_32 TYPE_INT_64
%token TYPE_UNSIGNED_INT_8 TYPE_UNSIGNED_INT_16 TYPE_UNSIGNED_INT_32 TYPE_UNSIGNED_INT_64 
%token TYPE_BOOLEAN TYPE_FLOAT TYPE_FLOAT_16 TYPE_FLOAT_32 TYPE_CHAR TYPE_STRING
%token LITERAL_INT LITERAL_FLOAT LITERAL_CHAR LITERAL_ESC_CHAR LITERAL_STR LITERAL_TRUE LITERAL_FALSE IDENTIFIER
%token SYM_ADD SYM_SUB SYM_MUL SYM_DIV SYM_EQ SYM_LT SYM_GT SYM_LBRAC SYM_RBRAC SYM_PERIOD SYM_COMMA SYM_COLON
%token SYM_SEMICOLON SYM_AT SYM_CARET SYM_LPAREN SYM_RPAREN SYM_NE SYM_LE SYM_GE SYM_ASSIGN SYM_RANGE COMMENT
%token KEY_AND KEY_ARRAY KEY_ASM KEY_BEGIN KEY_CASE KEY_CONST KEY_CONSTRUCTOR KEY_DESTRUCTOR KEY_DIV
%token KEY_DO KEY_DOWNTO KEY_ELSE KEY_END KEY_FILE KEY_FOR KEY_FUNCTION KEY_GOTO KEY_IF KEY_IMPLEMENTATION KEY_IN 
%token KEY_INHERITED KEY_INLINE KEY_INTERFACE KEY_LABEL KEY_MOD KEY_NIL KEY_NOT KEY_OBJECT KEY_OF KEY_OPERATOR KEY_OR
%token KEY_PACKED KEY_PROCEDURE KEY_PROGRAM KEY_RECORD KEY_REINTRODUCE KEY_REPEAT KEY_SELF KEY_SET KEY_SHL KEY_SHR
%token KEY_THEN KEY_TO KEY_TYPE KEY_UNIT KEY_UNTIL KEY_USES KEY_VAR KEY_WHILE KEY_WITH KEY_XOR
%token SIGN

%type<tok> TYPE_INT TYPE_INT_8 TYPE_INT_16 TYPE_INT_32 TYPE_INT_64
%type<tok> TYPE_UNSIGNED_INT_8 TYPE_UNSIGNED_INT_16 TYPE_UNSIGNED_INT_32 TYPE_UNSIGNED_INT_64 
%type<tok> TYPE_BOOLEAN TYPE_FLOAT TYPE_FLOAT_16 TYPE_FLOAT_32 TYPE_CHAR TYPE_STRING
%type<tok> SYM_ADD SYM_SUB SYM_MUL SYM_DIV SYM_EQ SYM_LT SYM_GT SYM_LBRAC SYM_RBRAC SYM_PERIOD SYM_COMMA SYM_COLON
%type<tok> SYM_SEMICOLON SYM_AT SYM_CARET SYM_LPAREN SYM_RPAREN SYM_NE SYM_LE SYM_GE SYM_ASSIGN SYM_RANGE COMMENT
%type<tok> KEY_AND KEY_ARRAY KEY_ASM KEY_BEGIN KEY_CASE KEY_CONST KEY_CONSTRUCTOR KEY_DESTRUCTOR KEY_DIV
%type<tok> KEY_DO KEY_DOWNTO KEY_ELSE KEY_END KEY_FILE KEY_FOR KEY_FUNCTION KEY_GOTO KEY_IF KEY_IMPLEMENTATION KEY_IN 
%type<tok> KEY_INHERITED KEY_INLINE KEY_INTERFACE KEY_LABEL KEY_MOD KEY_NIL KEY_NOT KEY_OBJECT KEY_OF KEY_OPERATOR KEY_OR
%type<tok> KEY_PACKED KEY_PROCEDURE KEY_PROGRAM KEY_RECORD KEY_REINTRODUCE KEY_REPEAT KEY_SELF KEY_SET KEY_SHL KEY_SHR
%type<tok> KEY_THEN KEY_TO KEY_TYPE KEY_UNIT KEY_UNTIL KEY_USES KEY_VAR KEY_WHILE KEY_WITH KEY_XOR
%type<tok> SIGN

%type<str> LITERAL_INT LITERAL_FLOAT LITERAL_CHAR LITERAL_ESC_CHAR LITERAL_STR LITERAL_TRUE LITERAL_FALSE IDENTIFIER

%%
program: 
    pro_head routine SYM_PERIOD {
        printf("------program------\n");
    }
;

pro_head:
    KEY_PROGRAM IDENTIFIER SYM_SEMICOLON{
        printf("----program head----\n");
    }
;

routine:
    routine_head  routine_body
;

routine_head:
    const_part type_part var_part routine_part
;

const_part:
    KEY_CONST const_expr_list | %empty 
;

type_part:
    KEY_TYPE type_decl_list 
    | %empty
;

var_part:
    KEY_VAR var_decl_list |
    %empty
;

routine_part:
    routine_part function_decl 
    | routine_part procedure_decl 
    | function_decl 
    | procedure_decl
    | %empty
;

routine_body:
    compound_stmt
;

compound_stmt:
    KEY_BEGIN stmt_list KEY_END
;

const_expr_list:
    const_expr_list IDENTIFIER SYM_EQ const_value SYM_SEMICOLON 
    | IDENTIFIER SYM_EQ const_value SYM_SEMICOLON
;

const_value:
    LITERAL_INT 
    | LITERAL_FLOAT
    | LITERAL_CHAR
    | LITERAL_STR 
    | LITERAL_FALSE
    | LITERAL_TRUE
;

type_decl_list:
    type_decl_list type_definition 
    | type_definition
;

type_definition:
    IDENTIFIER SYM_EQ type_decl SYM_SEMICOLON
;

type_decl:
    simple_type_decl 
    | array_type_decl 
    | record_type_decl
;

simple_type_decl: 
    easy_type
    | IDENTIFIER
    | SYM_LPAREN name_list SYM_RPAREN
    |  const_value  SYM_RANGE  const_value
    |  IDENTIFIER  SYM_RANGE  IDENTIFIER
;

easy_type:
    TYPE_BOOLEAN 
    | TYPE_CHAR 
    | TYPE_INT 
    | TYPE_FLOAT
;

name_list:
    name_list SYM_COMMA IDENTIFIER
    | IDENTIFIER
;

array_type_decl:
    KEY_ARRAY SYM_LBRAC simple_type_decl SYM_RBRAC KEY_OF type_decl
;

record_type_decl:
    KEY_RECORD field_decl_list KEY_END
;

field_decl_list:
    field_decl_list field_decl
    | field_decl
;

field_decl:
    name_list SYM_COLON type_decl SYM_SEMICOLON
;

var_decl_list:
    var_decl_list var_decl | var_decl
;

vec_decl:
    name_list SYM_COLON type_decl SYM_SEMICOLON
;




%%