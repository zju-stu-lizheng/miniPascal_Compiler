%code requires {
#include <iostream>
}

%{
#define MAX_LITERAL_LEN 256
extern int yylex(void);
// 在此声明，消除yacc生成代码时的警告
extern int yyparse(void); 
void yyerror(const char *str);
using namespace std;
%}

%locations

%token KEY_BREAK KEY_EXIT
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

%%
program: 
    pro_head routine SYM_PERIOD {
        cout << "hello world" << endl;
    }
;

pro_head:
    KEY_PROGRAM IDENTIFIER SYM_SEMICOLON{
    }
;

routine:
    routine_head routine_body{}
;

routine_head:
    const_part type_part var_part routine_part{}
;

const_part:
    KEY_CONST const_expr_list 
    | 
;

type_part:
    KEY_TYPE type_decl_list 
    | 
;

var_part:
    KEY_VAR var_decl_list 
    |
;

routine_part:
    routine_part function_decl 
    | routine_part procedure_decl 
    | function_decl 
    | procedure_decl
    | 
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

var_decl:
    name_list SYM_COLON type_decl SYM_SEMICOLON
;

function_decl:
    function_head SYM_SEMICOLON routine SYM_SEMICOLON 
;

function_head:
    KEY_FUNCTION IDENTIFIER parameters SYM_COLON simple_type_decl 
;

procedure_decl:
    procedure_head SYM_SEMICOLON routine SYM_SEMICOLON
;

procedure_head:
    KEY_PROCEDURE IDENTIFIER parameters
;

parameters:
    SYM_LPAREN para_decl_list SYM_RPAREN {}
    | {}
;

para_decl_list:
    para_decl_list SYM_SEMICOLON para_type_list
    | para_type_list 
;

para_type_list:
    var_para_list SYM_COLON simple_type_decl
    | val_para_list SYM_COLON simple_type_decl 
;

var_para_list:
    KEY_VAR name_list
;

val_para_list:
    name_list
;

stmt_list:
    stmt_list stmt SYM_SEMICOLON
    | 
;

stmt:
    label SYM_COLON non_label_stmt
    | non_label_stmt
;

label:
    LITERAL_INT 
    | IDENTIFIER
;

non_label_stmt: 
    assign_stmt
    | proc_stmt
    | compound_stmt
    | if_stmt
    | case_stmt
    | repeat_stmt
    | while_stmt
    | for_stmt
    | goto_stmt
;

assign_stmt:
    IDENTIFIER SYM_ASSIGN expression
    | IDENTIFIER SYM_LBRAC expression SYM_RBRAC SYM_ASSIGN expression
    | IDENTIFIER SYM_PERIOD IDENTIFIER SYM_ASSIGN expression
;


proc_stmt:
    /* SYS_PROC | SYS_PROC  LP  expression_list  RP |  READ  LP  factor  RP */
    IDENTIFIER
    | IDENTIFIER SYM_LPAREN expression_list SYM_RPAREN
;


if_stmt:
    KEY_IF expression KEY_THEN stmt else_clause
;

else_clause:
    KEY_ELSE stmt {}
    | {}
;

case_stmt:
    KEY_CASE expression KEY_OF case_expr_list KEY_END
;

case_expr_list:
    case_expr_list case_expr 
    | case_expr
;

case_expr:
    const_value SYM_COLON stmt SYM_SEMICOLON 
    | IDENTIFIER SYM_COLON stmt SYM_SEMICOLON 
;

repeat_stmt:
    KEY_REPEAT stmt_list KEY_UNTIL expression
;

while_stmt:
    KEY_WHILE expression KEY_DO stmt 
;

for_stmt:
    KEY_FOR IDENTIFIER SYM_ASSIGN expression direction expression KEY_DO stmt 
;

direction:
    KEY_TO 
    | KEY_DOWNTO 
;

goto_stmt:
    KEY_GOTO label
;

expression_list:
    expression_list SYM_COMMA expression
    | expression 
;

expression: 
    expression SYM_GE expr
    | expression SYM_GT expr 
    | expression SYM_LE expr 
    | expression SYM_LT expr 
    | expression SYM_EQ expr 
    | expression SYM_NE expr
    | expr
;

expr:
    expr SYM_ADD term 
    | expr SYM_SUB term 
    | expr KEY_OR term 
    | term
;

term:
    term  SYM_MUL factor
    | term  SYM_DIV factor
    | term  KEY_DIV factor 
    | term  KEY_MOD factor 
    | term  KEY_AND factor
    | factor
;

factor:
    IDENTIFIER
    | IDENTIFIER SYM_LPAREN expression_list SYM_RPAREN 
    | const_value
    | SYM_LPAREN expression SYM_RPAREN
    | KEY_NOT factor
    | SYM_SUB factor
    | IDENTIFIER SYM_LBRAC expression SYM_RBRAC
    | IDENTIFIER SYM_PERIOD IDENTIFIER
;

%%