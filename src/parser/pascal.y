%{
#include <iostream>
#include "ast/AST.hpp"
#define MAX_LITERAL_LEN 256
#define SET_LOCATION(dest) (dest)->SetLocation(yylloc.first_column,yylloc.first_line)
extern int yylex(void);
// 在此声明，消除yacc生成代码时的警告
extern int yyparse(void); 
void yyerror(const char *str);
using namespace std;
%}

%locations

%union{
    int token_type;
    char* str;

    //AST_Value.hpp
    AST_Const_Part* ast_const_part;
    AST_Const_Expression_List* ast_const_expression_list;
    AST_Const_Expression* ast_const_expression;
    AST_Const_Value* ast_const_value;
    AST_Variable_Part* ast_variable_part;
    AST_Variable_Declaration_List* ast_variable_declaration_list;
    AST_Variable_Declaration* ast_variable_declaration;

    //AST_Type.hpp
    AST_Type_Part* ast_type_part;
    AST_Type_Definition* ast_type_definition;
    AST_Type_Declaration_List* ast_type_declaration_list;
    AST_Type* ast_type;
    AST_Type_Declaration* ast_type_declaration;
    AST_Simple_Type_Declaration* ast_simple_type_declaration;
    AST_Array_Type_Declaration* ast_array_type_declaration;
    AST_Record_Type_Declaration* ast_record_type_declaration;    
    AST_Field_Declaration_List* ast_field_declaration_list;
    AST_Field_Declaration* ast_field_declaration;
    AST_Name_List* ast_name_list;
   
    //AST_Expression.hpp 
    AST_Expression* ast_expression;
    AST_Expression_List* ast_expression_list;

    //AST_Program.hpp
    AST_Program* ast_program;
    AST_Program_Head* ast_program_head;
    AST_Routine* ast_routine;
    AST_Routine_Head* ast_routine_head;
    // AST_Declaration_BaseClass* ast_declaration_baseclass;
    AST_Routine_Part* ast_routine_part;
    AST_Routine_Body* ast_routine_body;
    AST_Function_Declaration* ast_function_declaration;
    AST_Function_Head* ast_function_head;
    AST_Procedure_Declaration* ast_procedure_declaration;
    AST_Procedure_Head* ast_procedure_head;
    AST_Parameters* ast_parameters;
    AST_Parameters_Declaration_List* ast_parameters_declaration_list;
    AST_Parameters_Type_List* ast_parameters_type_list;
    AST_Variable_Parameters_List* ast_variable_parameters_list;

    //AST_Statement.hpp
    AST_Compound_Statement* ast_compound_statement;
    AST_Statement_List* ast_statement_list;
    AST_Statement* ast_statement;
    AST_Label* ast_label;
    AST_Non_Label_Statement* ast_non_label_statement;
    AST_Assign_Statement* ast_assign_statement;
    AST_Procedure_Statement* ast_procedure_statement;
    AST_If_Statement* ast_if_statement;
    AST_Else_Clause* ast_else_clause;
    AST_Case_Statement* ast_case_statement;
    AST_Case_Expression_List* ast_case_expression_list;
    AST_Case_Expression* ast_case_expression;
    AST_Repeat_Statement* ast_repeat_statement;
    AST_While_Statement* ast_while_statement;
    AST_For_Statement* ast_for_statement;
    AST_Direction* ast_direction;
    AST_Goto_Statement* ast_goto_statement;
}   

%token<token_type> KEY_BREAK KEY_EXIT
%token<token_type> TYPE_INT TYPE_INT_8 TYPE_INT_16 TYPE_INT_32 TYPE_INT_64
%token<token_type> TYPE_UNSIGNED_INT_8 TYPE_UNSIGNED_INT_16 TYPE_UNSIGNED_INT_32 TYPE_UNSIGNED_INT_64 
%token<token_type> TYPE_BOOLEAN TYPE_FLOAT TYPE_FLOAT_16 TYPE_FLOAT_32 TYPE_CHAR TYPE_STRING
%token<str> LITERAL_INT LITERAL_FLOAT LITERAL_CHAR LITERAL_ESC_CHAR LITERAL_STR LITERAL_TRUE LITERAL_FALSE IDENTIFIER
%token<token_type> SYM_ADD SYM_SUB SYM_MUL SYM_DIV SYM_EQ SYM_LT SYM_GT SYM_LBRAC SYM_RBRAC SYM_PERIOD SYM_COMMA SYM_COLON
%token<token_type> SYM_SEMICOLON SYM_AT SYM_CARET SYM_LPAREN SYM_RPAREN SYM_NE SYM_LE SYM_GE SYM_ASSIGN SYM_RANGE COMMENT
%token<token_type> KEY_AND KEY_ARRAY KEY_ASM KEY_BEGIN KEY_CASE KEY_CONST KEY_CONSTRUCTOR KEY_DESTRUCTOR KEY_DIV
%token<token_type> KEY_DO KEY_DOWNTO KEY_ELSE KEY_END KEY_FILE KEY_FOR KEY_FUNCTION KEY_GOTO KEY_IF KEY_IMPLEMENTATION KEY_IN 
%token<token_type> KEY_INHERITED KEY_INLINE KEY_INTERFACE KEY_LABEL KEY_MOD KEY_NIL KEY_NOT KEY_OBJECT KEY_OF KEY_OPERATOR KEY_OR
%token<token_type> KEY_PACKED KEY_PROCEDURE KEY_PROGRAM KEY_RECORD KEY_REINTRODUCE KEY_REPEAT KEY_SELF KEY_SET KEY_SHL KEY_SHR
%token<token_type> KEY_THEN KEY_TO KEY_TYPE KEY_UNIT KEY_UNTIL KEY_USES KEY_VAR KEY_WHILE KEY_WITH KEY_XOR
%token<token_type> SIGN

%type<ast_const_part> const_part
%type<ast_const_expression_list> const_expr_list
%type<ast_const_expression> const_expr
%type<ast_const_value> const_value
%type<ast_variable_part> var_part
%type<ast_variable_declaration_list> var_decl_list
%type<ast_variable_declaration> var_decl

%type<ast_type_part> type_part
%type<ast_type_definition> type_definition
%type<ast_type> easy_type
%type<ast_type_declaration> type_decl
%type<ast_type_declaration_list> type_decl_list
%type<ast_simple_type_declaration> simple_type_decl
%type<ast_array_type_declaration> array_type_decl
%type<ast_record_type_declaration> record_type_decl    
%type<ast_field_declaration_list> field_decl_list
%type<ast_field_declaration> field_decl
%type<ast_name_list> name_list

%type<ast_expression> expression expr term factor
%type<ast_expression_list> expression_list


%type<ast_program> program;
%type<ast_program_head> pro_head;
%type<ast_routine> routine;
%type<ast_routine_head> routine_head;
%type<ast_routine_part> routine_part;
%type<ast_routine_body> routine_body;
%type<ast_function_declaration> function_decl;
%type<ast_function_head> function_head;
%type<ast_procedure_declaration> procedure_decl;
%type<ast_procedure_head> procedure_head;
%type<ast_parameters> parameters;
%type<ast_parameters_declaration_list> para_decl_list;
%type<ast_parameters_type_list> para_type_list;
%type<ast_variable_parameters_list> var_para_list;
%type<ast_compound_statement> compound_stmt;
%type<ast_statement_list> stmt_list;
%type<ast_statement> stmt;
%type<ast_label> label;
%type<ast_non_label_statement> non_label_stmt;
%type<ast_assign_statement> assign_stmt;
%type<ast_procedure_statement> proc_stmt;
%type<ast_if_statement> if_stmt;
%type<ast_else_clause> else_clause;
%type<ast_case_statement> case_stmt;
%type<ast_case_expression_list> case_expr_list;
%type<ast_case_expression> case_expr;
%type<ast_repeat_statement> repeat_stmt;
%type<ast_while_statement> while_stmt;
%type<ast_for_statement> for_stmt;
%type<ast_direction> direction;
%type<ast_goto_statement> goto_stmt;

%%
program: 
    pro_head routine SYM_PERIOD {
        //root of the ast, a global variable;
        ast_root = new AST_Program($1,$2);
        SET_LOCATION(ast_root);
    }
;

pro_head:
    KEY_PROGRAM IDENTIFIER SYM_SEMICOLON{
        $$ = new AST_Program_Head($2);
        SET_LOCATION($$);
    }
;

routine:
    routine_head routine_body{
        // function_decl and procedure_decl
        $$ = new AST_Routine($1,$2);
        SET_LOCATION($$);
    }
;

routine_head:
    const_part type_part var_part routine_part{
        $$ = new AST_Routine_Head($1,$2,$3,$4);
        SET_LOCATION($$);
    }
;

const_part:
    KEY_CONST const_expr_list {
        $$ = new AST_Const_Part($2);
        SET_LOCATION($$);
    }
    | {
        $$ = nullptr;
    }
;

type_part:
    KEY_TYPE type_decl_list {
        $$ = new AST_Type_Part($2);
        SET_LOCATION($$);
    }
    | {
        $$ = nullptr;
    }
;

var_part:
    KEY_VAR var_decl_list {
        $$ = new AST_Variable_Part($2);
        SET_LOCATION($$);
    }
    | {
        $$ = nullptr;
    }
;

routine_part: 
    routine_part function_decl {
        AST_Declaration_BaseClass* tmp1 = new AST_Declaration_BaseClass($2);
        ($1) -> Add_Declaration(tmp1);
        $$ = $1;
        SET_LOCATION($$);
    }
    | routine_part procedure_decl {
        AST_Declaration_BaseClass* tmp2 = new AST_Declaration_BaseClass($2);
        ($1) -> Add_Declaration(tmp2);
        $$ = $1;
        SET_LOCATION($$);
    }
    | function_decl {
        AST_Declaration_BaseClass* tmp3 = new AST_Declaration_BaseClass($1);
        $$ = new AST_Routine_Part(tmp3);
        SET_LOCATION($$);
    }
    | procedure_decl {
        AST_Declaration_BaseClass* tmp4 = new AST_Declaration_BaseClass($1);
        $$ = new AST_Routine_Part(tmp4);
        SET_LOCATION($$);
    }
    | {
        $$ = nullptr;
    }
;

routine_body:
    compound_stmt {
        $$ = new AST_Routine_Body($1);
        SET_LOCATION($$);
    }
;

compound_stmt:
    KEY_BEGIN stmt_list KEY_END{
        $$ = new AST_Compound_Statement($2);
        SET_LOCATION($$);
    }
;

const_expr_list:
    const_expr_list const_expr {
        ($1)->Add_Const_Expression($2);
        $$ = $1;
        SET_LOCATION($$);
    }
    | const_expr {
        $$ = new AST_Const_Expression_List();
        ($$)->Add_Const_Expression($1);
        SET_LOCATION($$);
    }
;

const_expr:
    IDENTIFIER SYM_EQ expression SYM_SEMICOLON {
        $$ = new AST_Const_Expression($1,$3);
        SET_LOCATION($$);
    }
;

const_value:
    LITERAL_INT {
        $$ = new AST_Const_Value($1,AST_Const_Value::Value_Type::INT);
        SET_LOCATION($$);
    }
    | LITERAL_FLOAT {
        $$ = new AST_Const_Value($1,AST_Const_Value::Value_Type::FLOAT);
        SET_LOCATION($$);
    }
    | LITERAL_CHAR {
        $$ = new AST_Const_Value($1,AST_Const_Value::Value_Type::CHAR);
        SET_LOCATION($$);
    }
    | LITERAL_STR {
        $$ = new AST_Const_Value($1,AST_Const_Value::Value_Type::STRING);
        SET_LOCATION($$);
    }
    | LITERAL_FALSE {
        $$ = new AST_Const_Value($1,AST_Const_Value::Value_Type::FALSE);
        SET_LOCATION($$);
    }
    | LITERAL_TRUE {
        $$ = new AST_Const_Value($1,AST_Const_Value::Value_Type::TRUE);
        SET_LOCATION($$);
    }
;

type_decl_list:
    type_decl_list type_definition {
        ($1) -> Add_Type_Definition($2);
        $$ = $1;
        SET_LOCATION($$);
    }
    | type_definition {
        $$ = new AST_Type_Declaration_List();
        ($$) -> Add_Type_Definition($1);
        SET_LOCATION($$);
    }
;

type_definition:
    IDENTIFIER SYM_EQ type_decl SYM_SEMICOLON {
        $$ = new AST_Type_Definition($1,$3);
        SET_LOCATION($$);
    }
;

type_decl:
    simple_type_decl {
        $$ = $1;
        SET_LOCATION($$);
    }
    | array_type_decl  {
        $$ = $1;
        SET_LOCATION($$);
    }
    | record_type_decl {
        $$ = $1;
        SET_LOCATION($$);
    }
;

simple_type_decl: 
    easy_type {
        $$ = new AST_Simple_Type_Declaration($1);
        SET_LOCATION($$);
    }
    | IDENTIFIER {
        $$ = new AST_Simple_Type_Declaration($1);
        SET_LOCATION($$);
    }
    | SYM_LPAREN name_list SYM_RPAREN {
        $$ = new AST_Simple_Type_Declaration($2);
        SET_LOCATION($$);
    }
    |  const_value  SYM_RANGE  const_value {
        $$ = new AST_Simple_Type_Declaration($1,$3);
        SET_LOCATION($$);
    }
    |  IDENTIFIER  SYM_RANGE  IDENTIFIER {
        $$ = new AST_Simple_Type_Declaration($1,$3);
        SET_LOCATION($$);
    }
;

easy_type:
    TYPE_BOOLEAN {
        $$ = new AST_Type(AST_Type::Type_Name::BOOLEAN);
        SET_LOCATION($$);
    }
    | TYPE_CHAR  {
        $$ = new AST_Type(AST_Type::Type_Name::CHAR);
        SET_LOCATION($$);
    }
    | TYPE_INT {
        $$ = new AST_Type(AST_Type::Type_Name::INT);
        SET_LOCATION($$);
    }
    | TYPE_FLOAT {
        $$ = new AST_Type(AST_Type::Type_Name::FLOAT);
        SET_LOCATION($$);
    }
;

name_list:
    name_list SYM_COMMA IDENTIFIER {
        ($1) -> Add_Identifier($3);
        $$ = $1;
        SET_LOCATION($$);
    }
    | IDENTIFIER {
        $$ = new AST_Name_List();
        ($$) -> Add_Identifier($1);
        SET_LOCATION($$);
    }
;

array_type_decl:
    KEY_ARRAY SYM_LBRAC simple_type_decl SYM_RBRAC KEY_OF type_decl {
        $$ = new AST_Array_Type_Declaration($3,$6);
        SET_LOCATION($$);
    }
;

record_type_decl:
    KEY_RECORD field_decl_list KEY_END {
        $$ = new AST_Record_Type_Declaration($2);
        SET_LOCATION($$);
    }
;

field_decl_list:
    field_decl_list field_decl {
        ($1) -> Add_Field_Declaration($2);
        $$ = $1;
        SET_LOCATION($$);
    }
    | field_decl {
        $$ = new AST_Field_Declaration_List($1);
        SET_LOCATION($$);
    }
;

field_decl:
    name_list SYM_COLON type_decl SYM_SEMICOLON {
        $$ = new AST_Field_Declaration($1,$3);
        SET_LOCATION($$);
    }
;

var_decl_list:
    var_decl_list var_decl {
        ($1) -> Add_Variable_Declaration($2);
        $$ = $1;
        SET_LOCATION($$);
    }
    | var_decl {
        $$ = new AST_Variable_Declaration_List();
        ($$) -> Add_Variable_Declaration($1);
        SET_LOCATION($$);
    }
;

var_decl:
    name_list SYM_COLON type_decl SYM_SEMICOLON {
        $$ = new AST_Variable_Declaration($1,$3);
        SET_LOCATION($$);
    }
;

function_decl:
    function_head SYM_SEMICOLON routine SYM_SEMICOLON {
        $$ = new AST_Function_Declaration($1, $3);
        SET_LOCATION($$);
    }
;

function_head:
    KEY_FUNCTION IDENTIFIER parameters SYM_COLON simple_type_decl {
        $$ = new AST_Function_Head($2, $3, $5);
        SET_LOCATION($$);
    }
;

procedure_decl:
    procedure_head SYM_SEMICOLON routine SYM_SEMICOLON {
        $$ = new AST_Procedure_Declaration($1, $3);
        SET_LOCATION($$);
    }
;

procedure_head:
    KEY_PROCEDURE IDENTIFIER parameters {
        $$ = new AST_Procedure_Head($2, $3);
        SET_LOCATION($$);
    }
;

parameters:
    SYM_LPAREN para_decl_list SYM_RPAREN {
        $$ = new AST_Parameters($2);
        SET_LOCATION($$);
    }
    | {
        $$ = new AST_Parameters();
        SET_LOCATION($$);
    }
;

para_decl_list:
    para_decl_list SYM_SEMICOLON para_type_list {
        ($1) -> Add_Parameters_Type_List($3);
        $$ = $1;
        SET_LOCATION($$);
    }
    | para_type_list {
        $$ = new AST_Parameters_Declaration_List($1);
        SET_LOCATION($$);
    }
;

para_type_list:
    var_para_list SYM_COLON simple_type_decl {
        $$ = new AST_Parameters_Type_List($1,$3);
        SET_LOCATION($$);
    }
    | name_list SYM_COLON simple_type_decl {
        $$ = new AST_Parameters_Type_List($1,$3);
        SET_LOCATION($$);
    }
;

var_para_list:
    KEY_VAR name_list {
        $$ = new AST_Variable_Parameters_List($2);
        SET_LOCATION($$);
    }
;

stmt_list:
    stmt_list stmt SYM_SEMICOLON {
        ($1) -> Add_Statement($2);
        $$ = $1;
        SET_LOCATION($$);
    }
    | {
        $$ = new AST_Statement_List();
        SET_LOCATION($$);
    }
;

stmt:
    label SYM_COLON non_label_stmt {
        $$ = new AST_Statement();
        ($$) -> Add_Label_and_Non_Label_Statement($1,$3);
        SET_LOCATION($$);
    }
    | non_label_stmt {
        $$ = new AST_Statement();
        ($$) -> Add_Non_Label_Statement($1);
        SET_LOCATION($$);
    }
;

label:
    LITERAL_INT {
        $$ = new AST_Label($1);
        SET_LOCATION($$);
    }
    | IDENTIFIER {
        $$ = new AST_Label($1);
        SET_LOCATION($$);
    }
;

non_label_stmt: 
    assign_stmt {
        $$ = new AST_Non_Label_Statement($1);
        SET_LOCATION($$);
    }
    | proc_stmt {
        $$ = new AST_Non_Label_Statement($1);
        SET_LOCATION($$);
    }
    | compound_stmt {
        $$ = new AST_Non_Label_Statement($1);
        SET_LOCATION($$);
    }
    | if_stmt {
        $$ = new AST_Non_Label_Statement($1);
        SET_LOCATION($$);
    }
    | case_stmt {
        $$ = new AST_Non_Label_Statement($1);
        SET_LOCATION($$);
    }
    | repeat_stmt {
        $$ = new AST_Non_Label_Statement($1);
        SET_LOCATION($$);
    }
    | while_stmt {
        $$ = new AST_Non_Label_Statement($1);
        SET_LOCATION($$);
    }
    | for_stmt {
        $$ = new AST_Non_Label_Statement($1);
        SET_LOCATION($$);
    }
    | goto_stmt {
        $$ = new AST_Non_Label_Statement($1);
        SET_LOCATION($$);
    }
;

assign_stmt:
    IDENTIFIER SYM_ASSIGN expression {
        $$ = new AST_Assign_Statement($1, $3);
        SET_LOCATION($$);
    }
    | IDENTIFIER SYM_LBRAC expression SYM_RBRAC SYM_ASSIGN expression {
        $$ = new AST_Assign_Statement($1, $3, $6);
        SET_LOCATION($$);
    }
    | IDENTIFIER SYM_PERIOD IDENTIFIER SYM_ASSIGN expression {
        $$ = new AST_Assign_Statement($1, $3, $5);
        SET_LOCATION($$);
    }
;


proc_stmt:
    /* SYS_PROC | SYS_PROC  LP  expression_list  RP |  READ  LP  factor  RP */
    IDENTIFIER {
        $$ = new AST_Procedure_Statement($1);
        SET_LOCATION($$);
    }
    | IDENTIFIER SYM_LPAREN expression_list SYM_RPAREN {
        $$ = new AST_Procedure_Statement($1,$3);
        SET_LOCATION($$);
    }
;


if_stmt:
    KEY_IF expression KEY_THEN stmt else_clause {
        $$ = new AST_If_Statement($2,$4,$5);
        SET_LOCATION($$);
    }
;

else_clause:
    KEY_ELSE stmt {
        $$ = new AST_Else_Clause($2);
        SET_LOCATION($$);
    }
    | {
        $$ = nullptr;
    }
;

case_stmt:
    KEY_CASE expression KEY_OF case_expr_list KEY_END {
        $$ = new AST_Case_Statement($2,$4);
        SET_LOCATION($$);
    }
;

case_expr_list:
    case_expr_list case_expr {
        ($1)->Add_Case_Expression($2);
        $$ = $1;
        SET_LOCATION($$);
    }
    | case_expr {
        $$ = new AST_Case_Expression_List();
        ($$)->Add_Case_Expression($1);
        SET_LOCATION($$);
    }
;

case_expr:
    const_value SYM_COLON stmt SYM_SEMICOLON {
        $$ = new AST_Case_Expression($1,$3);
        SET_LOCATION($$);
    }
    | IDENTIFIER SYM_COLON stmt SYM_SEMICOLON {
        $$ = new AST_Case_Expression($1,$3);
        SET_LOCATION($$);
    }
;

repeat_stmt:
    KEY_REPEAT stmt_list KEY_UNTIL expression {
        $$ = new AST_Repeat_Statement($2,$4);
        SET_LOCATION($$);
    }
;

while_stmt:
    KEY_WHILE expression KEY_DO stmt {
        $$ = new AST_While_Statement($2,$4);
        SET_LOCATION($$);
    }
;

for_stmt:
    KEY_FOR IDENTIFIER SYM_ASSIGN expression direction expression KEY_DO stmt {
        $$ = new AST_For_Statement($2, $4, $5, $6, $8);
        SET_LOCATION($$);
    }
;

direction:
    KEY_TO {
        $$ = new AST_Direction();
        ($$) -> Set_To();
        SET_LOCATION($$);
    }
    | KEY_DOWNTO {
        $$ = new AST_Direction();
        ($$) -> Set_Down_To();
        SET_LOCATION($$);
    }
;

goto_stmt:
    KEY_GOTO label {
        $$ = new AST_Goto_Statement($2);
        SET_LOCATION($$);
    }
;

expression_list:
    expression_list SYM_COMMA expression{
        $$ = $1;
        $$ -> Add_Expression($3);
        SET_LOCATION($$);
    }
    | expression {
        $$ = new AST_Expression_List();
        $$ -> Add_Expression($1);
        SET_LOCATION($$);
    }
;

expression: 
    expression SYM_GE expr{
        $$ = new AST_Binary_Expression(AST_Binary_Expression::Operation::GE, $1, $3);
        SET_LOCATION($$);
    }
    | expression SYM_GT expr {
        $$ = new AST_Binary_Expression(AST_Binary_Expression::Operation::GT, $1, $3);
        SET_LOCATION($$);
    }
    | expression SYM_LE expr {
        $$ = new AST_Binary_Expression(AST_Binary_Expression::Operation::LE, $1, $3);
        SET_LOCATION($$);
    }
    | expression SYM_LT expr {
        $$ = new AST_Binary_Expression(AST_Binary_Expression::Operation::LT, $1, $3);
        SET_LOCATION($$);
    }
    | expression SYM_EQ expr {
        $$ = new AST_Binary_Expression(AST_Binary_Expression::Operation::EQUAL, $1, $3);
        SET_LOCATION($$);
    }
    | expression SYM_NE expr{
        $$ = new AST_Binary_Expression(AST_Binary_Expression::Operation::UNEQUAL, $1, $3);
        SET_LOCATION($$);
    }
    | expr{
        $$ = $1;
        SET_LOCATION($$);
    }
;

expr:
    expr SYM_ADD term {
        $$ = new AST_Binary_Expression(AST_Binary_Expression::Operation::PLUS,$1,$3);
        SET_LOCATION($$);
    }
    | expr SYM_SUB term {
        $$ = new AST_Binary_Expression(AST_Binary_Expression::Operation::MINUS,$1,$3);
        SET_LOCATION($$);
    }
    | expr KEY_OR term {
        $$ = new AST_Binary_Expression(AST_Binary_Expression::Operation::OR,$1,$3);
        SET_LOCATION($$);
    }
    | term {
        $$ = $1;
        SET_LOCATION($$);
    }
;

term:
    term  SYM_MUL factor{
        $$ = new AST_Binary_Expression(AST_Binary_Expression::Operation::MUL,$1,$3);
        SET_LOCATION($$);
    }
    | term  SYM_DIV factor{
        $$ = new AST_Binary_Expression(AST_Binary_Expression::Operation::REALDIV,$1,$3);
        SET_LOCATION($$);
    }
    | term  KEY_DIV factor {
        $$ = new AST_Binary_Expression(AST_Binary_Expression::Operation::DIV,$1,$3);
        SET_LOCATION($$);
    }
    | term  KEY_MOD factor  {
        $$ = new AST_Binary_Expression(AST_Binary_Expression::Operation::MOD,$1,$3);
        SET_LOCATION($$);
    }
    | term  KEY_AND factor{
        $$ = new AST_Binary_Expression(AST_Binary_Expression::Operation::AND,$1,$3);
        SET_LOCATION($$);
    }
    | factor {
        $$ = $1;
        SET_LOCATION($$);
    }
;

factor:
    IDENTIFIER{
        $$ = new AST_Identifier_Expression($1);
        SET_LOCATION($$);
    }
    | IDENTIFIER SYM_LPAREN expression_list SYM_RPAREN {
        $$ = new AST_Function_Call($1,$3);
        SET_LOCATION($$);
    }
    | const_value{
        $$ = new AST_Const_Value_Expression($1);
        SET_LOCATION($$);
    }
    | SYM_LPAREN expression SYM_RPAREN{
        $$ = $2;
        SET_LOCATION($$);
    }
    | KEY_NOT factor{
        $$ = new AST_Unary_Expression(AST_Unary_Expression::Operation::NOT,$2);
        SET_LOCATION($$);
    }
    | SYM_SUB factor{
        $$ = new AST_Unary_Expression(AST_Unary_Expression::Operation::SUB,$2);
        SET_LOCATION($$);
    }
    | IDENTIFIER SYM_LBRAC expression SYM_RBRAC{
        $$ = new AST_Array_Expression($1,$3);
        SET_LOCATION($$);
    }
    | IDENTIFIER SYM_PERIOD IDENTIFIER{
        $$ = new AST_Property_Expression($1,$3);
        SET_LOCATION($$);
    }
;

%%