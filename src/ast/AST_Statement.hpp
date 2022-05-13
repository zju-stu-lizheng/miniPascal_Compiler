#pragma once
#include "AST_BaseNode.hpp"
#include "AST_Expression.hpp"
#include "AST_Value.hpp"

class AST_Compound_Statement;
class AST_Statement_List;
class AST_Statement;
class AST_Label;
class AST_Non_Label_Statement;
class AST_Assign_Statement;
class AST_Procedure_Statement;

class AST_If_Statement;
class AST_Case_Statement;
class AST_Repeat_Statement;
class AST_While_Statement;
class AST_For_Statement;
class AST_Goto_Statement;
class AST_Else_Clause;

class AST_Case_Expression_List;
class AST_Case_Expression;
class AST_Direction;

/*
compound_stmt:
    KEY_BEGIN stmt_list KEY_END
;
*/
class AST_Compound_Statement{
    private:
        AST_Statement_List* statement_list;
    public:
        AST_Compound_Statement(AST_Statement_List* _statement_list):
                                statement_list(_statement_list){};
        AST_Statement_List* Get_Statement_List() const{
            return this->statement_list;
        }
};

/*
stmt_list:
    stmt_list stmt SYM_SEMICOLON
    | 
;
*/
class AST_Statement_List{
    private:
        std::vector<AST_Statement*> statement_list;
    public:
        AST_Statement_List() = default;
        void Add_Statement(AST_Statement* _statement){
            this->statement_list.push_back(_statement);
        }
};

/*
stmt:
    label SYM_COLON non_label_stmt
    | non_label_stmt
;
*/
class AST_Statement{
    private:
        enum class Has_Label{
            NOT_HAS,
            HAS
        };
        AST_Label* label;
        AST_Non_Label_Statement* non_label_statement;
        Has_Label has_label;
    public:
        AST_Statement() = default;
        void Add_Label_and_Non_Label_Statement(AST_Label* _label, AST_Non_Label_Statement* _non_label_statement){
            this->label = _label;
            this->non_label_statement = _non_label_statement;
            this->has_label = Has_Label::HAS;
        }
        void Add_Non_Label_Statement(AST_Non_Label_Statement* _non_label_statement){
            this->non_label_statement = _non_label_statement;
            this->has_label = Has_Label::NOT_HAS;
        }
        AST_Label* Get_Label() const{
            return this->label;
        }
        AST_Non_Label_Statement* Get_Non_Label_Statement() const{
            return this->non_label_statement;
        }
        Has_Label Get_Has_Label() const{
            return this->has_label;
        }
};

/*
label:
    LITERAL_INT 
    | IDENTIFIER
;
*/
class AST_Label{
    private:
        enum class Int_or_Identifier{
            LITERAL_INT,
            IDENTIFIER
        };
        int literal_int;
        std::string identifier;
        Int_or_Identifier int_or_identifier;
    public:
        AST_Label(int _literal_int):literal_int(_literal_int){
            this->int_or_identifier = Int_or_Identifier::LITERAL_INT;
        }
        AST_Label(std::string _identifier):identifier(_identifier){
            this->int_or_identifier = Int_or_Identifier::IDENTIFIER;
        }
        
        int Get_Literal_Int() const{
            return this->literal_int;
        }
        std::string Get_Identifier() const{
            return this->identifier;
        }
        Int_or_Identifier Get_Int_or_Identifier() const{
            return this->int_or_identifier;
        }
};

/*
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
*/
class AST_Non_Label_Statement{
    private:
        enum class Statement_Type{
            ASSIGN,
            PROCEDURE,
            COMPOUND,
            IF,
            CASE,
            REPEAT,
            WHILE,
            FOR,
            GOTO
        };
        Statement_Type statement_type;

        AST_Assign_Statement* assgin_statement;
        AST_Procedure_Statement* procedure_statement;
        AST_Compound_Statement* compound_statement;
        AST_If_Statement* if_statement;
        AST_Case_Statement* case_statement;
        AST_Repeat_Statement* repeat_statement;
        AST_While_Statement* while_statement;
        AST_For_Statement* for_statement;
        AST_Goto_Statement* goto_statement;
    public:
        AST_Non_Label_Statement(AST_Assign_Statement* _assgin_statement):assgin_statement(_assgin_statement){
            this->statement_type = Statement_Type::ASSIGN;
        }
        AST_Non_Label_Statement(AST_Procedure_Statement* _procedure_statement):procedure_statement(_procedure_statement){
            this->statement_type = Statement_Type::PROCEDURE;
        }
        AST_Non_Label_Statement(AST_Compound_Statement* _compound_statement):compound_statement(_compound_statement){
            this->statement_type = Statement_Type::COMPOUND;
        }
        AST_Non_Label_Statement(AST_If_Statement* _if_statement):if_statement(_if_statement){
            this->statement_type = Statement_Type::IF;
        }
        AST_Non_Label_Statement(AST_Case_Statement* _case_statement):case_statement(_case_statement){
            this->statement_type = Statement_Type::CASE;
        }
        AST_Non_Label_Statement(AST_Repeat_Statement* _repeat_statement):repeat_statement(_repeat_statement){
            this->statement_type = Statement_Type::REPEAT;
        }
        AST_Non_Label_Statement(AST_While_Statement* _while_statement):while_statement(_while_statement){
            this->statement_type = Statement_Type::WHILE;
        }
        AST_Non_Label_Statement(AST_For_Statement* _for_statement):for_statement(_for_statement){
            this->statement_type = Statement_Type::FOR;
        }
        AST_Non_Label_Statement(AST_Goto_Statement* _goto_statement):goto_statement(_goto_statement){
            this->statement_type = Statement_Type::GOTO;
        }
        Statement_Type Get_Statement_Type() const{
            return statement_type;
        }
};

/*
assign_stmt:
    IDENTIFIER SYM_ASSIGN expression
    | IDENTIFIER SYM_LBRAC expression SYM_RBRAC SYM_ASSIGN expression
    | IDENTIFIER SYM_PERIOD IDENTIFIER SYM_ASSIGN expression
;
*/

class AST_Assign_Statement{
    private:
        enum class Assign_Type{
            I_1_E_1,
            I_1_E_2,
            I_2_E_1
        };

        Assign_Type assign_type;

        std::string identifier1;
        std::string identifier2;
        AST_Expression* expression1;
        AST_Expression* expression2;
        
    public:
        AST_Assign_Statement(std::string _identifier1, AST_Expression* _expression1):
                            identifier1(_identifier1), expression1(_expression1), assign_type(Assign_Type::I_1_E_1){}
        AST_Assign_Statement(std::string _identifier1, AST_Expression* _expression1, AST_Expression* _expression2):
                            identifier1(_identifier1), expression1(_expression1), expression2(_expression2), assign_type(Assign_Type::I_1_E_2){}  
        AST_Assign_Statement(std::string _identifier1, std::string _identifier2, AST_Expression* _expression1):
                            identifier1(_identifier1), identifier2(_identifier2), expression1(_expression1), assign_type(Assign_Type::I_2_E_1){}  
        Assign_Type Get_Assign_Type() const{
            return assign_type;
        }           
};


/*
proc_stmt:
    // SYS_PROC | SYS_PROC  LP  expression_list  RP |  READ  LP  factor  RP 
    IDENTIFIER
    | IDENTIFIER SYM_LPAREN expression_list SYM_RPAREN
;
*/
class AST_Procedure_Statement{
    private:
        enum class Has_Expression{
            Not,
            Yes
        };
        Has_Expression has_expression;

        std::string identifier;
        AST_Expression_List* expresion_list;
    public:
        AST_Procedure_Statement(std::string _identifier):
                                identifier(_identifier),has_expression(Has_Expression::Not){}
        AST_Procedure_Statement(std::string _identifier, AST_Expression_List* _expresion_list):
                                identifier(_identifier),expresion_list(_expresion_list), has_expression(Has_Expression::Yes){}                        
        Has_Expression Get_Has_Expression(){
            return has_expression;
        }
};

/*
if_stmt:
    KEY_IF expression KEY_THEN stmt else_clause
;
*/
class AST_If_Statement{
    public:
        AST_Expression* expression;
        AST_Statement* statement;
        AST_Else_Clause* else_clause;
    
        AST_If_Statement(AST_Expression* _expression, AST_Statement* _statement, AST_Else_Clause* _else_clause):
                            expression(_expression), statement(_statement), else_clause(_else_clause){}
};

/*
else_clause:
    KEY_ELSE stmt {}
    | {}
;
*/
class AST_Else_Clause{
    public:
        AST_Statement* statement;
        AST_Else_Clause() = default;
        AST_Else_Clause(AST_Statement* _statement):statement(_statement){}
};

/*
case_stmt:
    KEY_CASE expression KEY_OF case_expr_list KEY_END
;
*/
class AST_Case_Statement{
    public:
        AST_Expression* expression;
        AST_Case_Expression_List* case_expression_list;
        AST_Case_Statement(AST_Expression* _expression, AST_Case_Expression_List* _case_expression_list):
                            expression(_expression), case_expression_list(_case_expression_list){}
};

/*
case_expr_list:
    case_expr_list case_expr 
    | case_expr
;
*/
class AST_Case_Expression_List{
    public:
        std::vector<AST_Case_Expression*> case_expression_list;
        
        AST_Case_Expression_List() = default;
        void Add_Case_Expression(AST_Case_Expression* _case_expression){
            case_expression_list.push_back(_case_expression);
        }
};

/*
case_expr:
    const_value SYM_COLON stmt SYM_SEMICOLON 
    | IDENTIFIER SYM_COLON stmt SYM_SEMICOLON 
;
*/
class AST_Case_Expression{
    public:
        enum class Const_or_Indentifier{
            CONST,
            IDENTIFIER
        };
        Const_or_Indentifier const_or_identifier;
        AST_Const_Value* const_value;
        AST_Statement* statement;
        std::string identifier;

        AST_Case_Expression(AST_Const_Value* _const_value, AST_Statement* _statement):
                                const_value(_const_value), statement(_statement), const_or_identifier(Const_or_Indentifier::CONST){}
        AST_Case_Expression(std::string _identifier, AST_Statement* _statement):
                                identifier(_identifier), statement(_statement), const_or_identifier(Const_or_Indentifier::IDENTIFIER){}                     
};

/*
repeat_stmt:
    KEY_REPEAT stmt_list KEY_UNTIL expression
;
*/
class AST_Repeat_Statement{
    public:
        AST_Statement_List* statement_list;
        AST_Expression* expression;

        AST_Repeat_Statement(AST_Statement_List* _statement_list, AST_Expression* _expression):
                            statement_list(_statement_list), expression(_expression){}
};

/*
repeat_stmt:
    KEY_REPEAT stmt_list KEY_UNTIL expression
;
*/
class AST_While_Statement{
    public:
        AST_Expression* expression;
        AST_Statement* statement;

        AST_While_Statement(AST_Expression* _expression, AST_Statement* _statement):
                            expression(_expression), statement(_statement){}        

};

/*
for_stmt:
    KEY_FOR IDENTIFIER SYM_ASSIGN expression direction expression KEY_DO stmt 
;
*/
class AST_For_Statement{
    public:
        std::string identifier;
        AST_Expression* expression1;
        AST_Direction* direction;
        AST_Expression* expression2;
        AST_Statement* statement;

        AST_For_Statement(std::string _identifier, AST_Expression* _expression1, AST_Direction* _direction, AST_Expression* _expression2, AST_Statement* _statement):
            identifier(_identifier), expression1(_expression1), direction(_direction), expression2(_expression2), statement(_statement){}
};

/*
direction:
    KEY_TO 
    | KEY_DOWNTO 
;
*/
class AST_Direction{
    public:
        enum class To_or_DownTo{
            To,
            DownTo
        };
        To_or_DownTo to_or_downto;
        AST_Direction() = default;
        void Set_To(){
            to_or_downto = To_or_DownTo::To;
        }
        void Set_Down_To(){
            to_or_downto = To_or_DownTo::DownTo;
        }
};

/*
goto_stmt:
    KEY_GOTO label
;
*/

class AST_Goto_Statement{
    public:
        AST_Label* label;
        AST_Goto_Statement(AST_Label* _label):label(_label){}
};


