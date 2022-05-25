#include "AST.hpp"

// AST_Expression
void AST_Expression_List::PrintNode(GraphViz *g)
{
    g->AddNode("expression_list", this->GetRow(),
               this->GetColumn());
    for (auto expr : expr_list)
    {
        expr->PrintNode(g);
    }
    g->Pop();
}

void AST_Binary_Expression::PrintNode(GraphViz *g)
{
    g->AddNode(std::string("binary_op_expr: ") + Get_Operation_Name(this->my_operation), this->GetRow(),
               this->GetColumn());
    left_expression->PrintNode(g);
    right_expression->PrintNode(g);
    g->Pop();
}

void AST_Unary_Expression::PrintNode(GraphViz *g)
{
    g->AddNode(std::string("unary_op_expr: ") + Get_OptionName(), this->GetRow(),
               this->GetColumn());
    expression->PrintNode(g);
    g->Pop();
}

void AST_Property_Expression::PrintNode(GraphViz *g)
{
    g->AddNode(std::string("property_expr: "), this->GetRow(),
               this->GetColumn());
    g->AddIdentifier(id);
    g->AddIdentifier(prop_id);
    g->Pop();
}

void AST_Const_Value_Expression::PrintNode(GraphViz *g)
{
    const_value->PrintNode(g);
}

void AST_Function_Call::PrintNode(GraphViz *g)
{
    g->AddNode(std::string("func_call ") , this->GetRow(),
               this->GetColumn());
    g->AddIdentifier(func_id);
    args_list->PrintNode(g);
    g->Pop();
}
void AST_Identifier_Expression::PrintNode(GraphViz *g)
{
    g->AddNode(std::string("ID_expr ") , this->GetRow(),
               this->GetColumn());
    g->AddIdentifier(id);
    g->Pop();
}

void AST_Array_Expression::PrintNode(GraphViz *g)
{
    g->AddNode(std::string("array_expr ") , this->GetRow(),
               this->GetColumn());
    g->AddIdentifier(id);
    expression->PrintNode(g);
    g->Pop();
}

// AST_program
void AST_Program::PrintNode(GraphViz *g)
{
    g->AddNode("program", GetRow(), GetColumn());
    program_head->PrintNode(g);
    routine->PrintNode(g);
    g->Pop();
}

void AST_Program_Head::PrintNode(GraphViz *g)
{
    g->AddNode("program_head", GetRow(), GetColumn());
    g->AddIdentifier(identifier);
    g->Pop();
}

void AST_Routine::PrintNode(GraphViz *g)
{
    g->AddNode("routine", GetRow(), GetColumn());
    routine_head->PrintNode(g);
    routine_body->PrintNode(g);
    g->Pop();
}

void AST_Routine_Head::PrintNode(GraphViz *g)
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

void AST_Declaration_BaseClass::PrintNode(GraphViz *g)
{
    if (is_function)
        function_declaration->PrintNode(g);
    else
        procedure_declaration->PrintNode(g);
}

void AST_Routine_Part::PrintNode(GraphViz *g)
{
    g->AddNode("routine_part", GetRow(), GetColumn());
    for (auto rp : this->declaration_list)
    {
        rp->PrintNode(g);
    }
    g->Pop();
}

void AST_Routine_Body::PrintNode(GraphViz *g)
{
    g->AddNode("routine_body", GetRow(), GetColumn());
    this->compound_statement->PrintNode(g);
    g->Pop();
}

void AST_Function_Declaration::PrintNode(GraphViz *g)
{
    g->AddNode("function_decl", this->GetRow(),
               this->GetColumn());
    if (this->function_head != nullptr)
        this->function_head->PrintNode(g);
    if (this->routine != nullptr)
        this->routine->PrintNode(g);
    g->Pop();
}

void AST_Function_Head::PrintNode(GraphViz *g)
{
    g->AddNode("function_head of " + this->identifier, this->GetRow(),
               this->GetColumn());
    if (this->parameters != nullptr)
        this->parameters->PrintNode(g);
    if (this->simple_type_declaration != nullptr)
        this->simple_type_declaration->PrintNode(g);
    g->Pop();
}

void AST_Procedure_Declaration::PrintNode(GraphViz *g)
{
    g->AddNode("procedure_decl", this->GetRow(),
               this->GetColumn());
    if (this->procedure_head != nullptr)
        this->procedure_head->PrintNode(g);
    if (this->routine != nullptr)
        this->routine->PrintNode(g);
    g->Pop();
}

void AST_Procedure_Head::PrintNode(GraphViz *g)
{
    g->AddNode("procedure_head of " + this->identifier, this->GetRow(),
               this->GetColumn());
    if (this->parameters != nullptr)
        this->parameters->PrintNode(g);
    g->Pop();
}

void AST_Parameters::PrintNode(GraphViz *g)
{
    g->AddNode("parameters", this->GetRow(),
               this->GetColumn());
    if (this->parameters_declaration_list != nullptr)
        this->parameters_declaration_list->PrintNode(g);
    g->Pop();
}

void AST_Parameters_Declaration_List::PrintNode(GraphViz *g)
{
    g->AddNode("para_decl_list", this->GetRow(),
               this->GetColumn());
    for (auto type_list : parameters_type_list_list)
    {
        type_list->PrintNode(g);
    }
    g->Pop();
}

void AST_Parameters_Type_List::PrintNode(GraphViz *g)
{
    g->AddNode("para_type_list", this->GetRow(),
               this->GetColumn());
    if (is_namelist)
    {
        name_list->PrintNode(g);
    }
    else
    {
        variable_parameters_list->PrintNode(g);
    }
    simple_type_declaration->PrintNode(g);
    g->Pop();
}

void AST_Variable_Parameters_List::PrintNode(GraphViz *g)
{
    g->AddNode("var_para_list", this->GetRow(),
               this->GetColumn());
    name_list->PrintNode(g);
    g->Pop();
}

// AST_Statement
void AST_Compound_Statement::PrintNode(GraphViz *g)
{
    g->AddNode("compound_statement", this->GetRow(),
               this->GetColumn());
    statement_list->PrintNode(g);
    g->Pop();
}
void AST_Statement_List::PrintNode(GraphViz *g)
{
    g->AddNode("stmt_list", GetRow(), GetColumn());
    for (int i = 0; (int)i < statement_list.size(); i++)
    {
        statement_list[i]->PrintNode(g);
    }
    g->Pop();
}

void AST_Statement::PrintNode(GraphViz *g)
{
    if (has_label == Has_Label::NOT_HAS)
    {
        non_label_statement->PrintNode(g);
    }
    else
    {
        g->AddNode("label_stmt " + label->_is_int ? std::to_string(label->Get_Literal_Int()) : label->identifier, GetRow(), GetColumn());
        non_label_statement->PrintNode(g);
        g->Pop();
    }
}
void AST_Non_Label_Statement::PrintNode(GraphViz *g)
{
    g->AddNode("non_label_statement", GetRow(), GetColumn());
    if (this->isAssign())
    {
        this->assgin_statement->PrintNode(g);
    }
    else if (this->isProcedure())
    {
        this->procedure_statement->PrintNode(g);
    }
    else if (this->isCompound())
    {
        this->compound_statement->PrintNode(g);
    }
    else if (this->isIf())
    {
        this->if_statement->PrintNode(g);
    }
    else if (this->isCase())
    {
        this->case_statement->PrintNode(g);
    }
    else if (this->isRepeat())
    {
        this->repeat_statement->PrintNode(g);
    }
    else if (this->isWhile())
    {
        this->while_statement->PrintNode(g);
    }
    else if (this->isFor())
    {
        this->for_statement->PrintNode(g);
    }
    else if (this->isGoto())
    {
        this->goto_statement->PrintNode(g);
    }
    else if (this->isBreak())
    {
        this->break_statement->PrintNode(g);
    }
    g->Pop();
}

void AST_Assign_Statement::PrintNode(GraphViz *g)
{
    g->AddNode("assign_stmt", GetRow(), GetColumn());
    if (isDirectAssign())
    {
        g->AddIdentifier(identifier1);
        expression1->PrintNode(g);
    }
    else if (isArrayAssign())
    {
        g->AddIdentifier(identifier1);
        expression1->PrintNode(g);
        expression2->PrintNode(g);
    }
    else if (isRecordAttrAssign())
    {
        g->AddIdentifier(identifier1);
        g->AddIdentifier(identifier2);
        expression1->PrintNode(g);
    }
    g->Pop();
}

void AST_Procedure_Statement::PrintNode(GraphViz *g)
{
    g->AddNode("proc_stmt", GetRow(), GetColumn());
    g->AddIdentifier(identifier);
    if (has_expression == Has_Expression::Yes)
    {
        expresion_list->PrintNode(g);
    }
    g->Pop();
}

void AST_If_Statement::PrintNode(GraphViz *g)
{
    g->AddNode("if_stmt", GetRow(), GetColumn());
    expression->PrintNode(g);
    statement->PrintNode(g);
    if (else_clause != nullptr)
    {
        else_clause->PrintNode(g);
    }
    g->Pop();
}

void AST_Else_Clause::PrintNode(GraphViz *g)
{
    g->AddNode("else_clause", GetRow(), GetColumn());
    statement->PrintNode(g);
    g->Pop();
}

void AST_Case_Statement::PrintNode(GraphViz *g)
{
    g->AddNode("case_stmt", GetRow(), GetColumn());
    expression->PrintNode(g);
    case_expression_list->PrintNode(g);
    g->Pop();
}
void AST_Case_Expression_List::PrintNode(GraphViz *g)
{
    g->AddNode("case_expr_list", GetRow(), GetColumn());
    for (auto expr : case_expression_list)
    {
        expr->PrintNode(g);
    }
    g->Pop();
}
void AST_Case_Expression::PrintNode(GraphViz *g)
{
    g->AddNode("case_expr", GetRow(), GetColumn());
    if (const_or_identifier == Const_or_Indentifier::CONST)
    {
        const_value->PrintNode(g);
    }
    else
    {
        g->AddIdentifier(identifier);
    }
    statement->PrintNode(g);
    g->Pop();
}

void AST_Repeat_Statement::PrintNode(GraphViz *g)
{
    g->AddNode("repeat_stmt", GetRow(), GetColumn());
    statement_list->PrintNode(g);
    expression->PrintNode(g);
    g->Pop();
}

void AST_While_Statement::PrintNode(GraphViz *g)
{
    g->AddNode("while_stmt", GetRow(), GetColumn());
    expression->PrintNode(g);
    statement->PrintNode(g);
    g->Pop();
}

void AST_For_Statement::PrintNode(GraphViz *g)
{
    g->AddNode("for_stmt:" + my_direction->GetDirection(), GetRow(), GetColumn());
    expression1->PrintNode(g);
    expression2->PrintNode(g);
    statement->PrintNode(g);
    g->Pop();
}

void AST_Goto_Statement::PrintNode(GraphViz *g)
{
    g->AddNode("goto_stmt:" + (label->isIdentifier() ? label->Get_Identifier() : std::to_string(label->Get_Literal_Int())), GetRow(), GetColumn());
    g->Pop();
}

// AST_Type
void AST_Type::PrintNode(GraphViz *g)
{
    switch (this->Get_Type_Name())
    {
    case Type_Name::INT:
        g->AddIdentifier("Integer");
        break;
    case Type_Name::FLOAT :
        g->AddIdentifier("Real");
        break;
    case Type_Name::BOOLEAN:
        g->AddIdentifier("Boolean");
        break;
    case Type_Name::CHAR:
        g->AddIdentifier("Char");
        break;
    case Type_Name::STRING:
        g->AddIdentifier("String");
        break;
    default:
        std::cout << "Unknown type" << std::endl;
        break;
    }
}
void AST_Simple_Type_Declaration::PrintNode(GraphViz *g)
{
    g->AddNode("simple_type_decl", GetRow(), GetColumn());
    if (my_type == My_Type::EASY_TYPE) {
        this->my_typename->PrintNode(g);
    }else if (my_type == My_Type::IDENTIFIER) {
        g->AddIdentifier(this->define_id);
    } else if (my_type == My_Type::VALUE_RANGE) {
        low->PrintNode(g);
        high->PrintNode(g);
    } else if (my_type == My_Type::IDENTIFIER_RANGE) {
        g->AddIdentifier(this->low_name);
        g->AddIdentifier(this->high_name);
    } else if (my_type == My_Type::ENUMERATE) {
        this->name_list->PrintNode(g);
    }
    g->Pop();
}
void AST_Array_Type_Declaration::PrintNode(GraphViz *g)
{
    g->AddNode("array_type_decl", GetRow(), GetColumn());
    simple_type_decl->PrintNode(g);
    type_decl->PrintNode(g);
    g->Pop();
}
void AST_Record_Type_Declaration::PrintNode(GraphViz *g)
{
    g->AddNode("record_decl_list", GetRow(), GetColumn());
    field_decl_list->PrintNode(g);
    g->Pop();
}

void AST_Field_Declaration_List::PrintNode(GraphViz *g)
{
    g->AddNode("field_decl_list", GetRow(), GetColumn());
    for (int i = 0; i < (int)field_decl_list.size(); i++)
    {
        field_decl_list[i]->PrintNode(g);
    }
    g->Pop();
}

void AST_Field_Declaration::PrintNode(GraphViz *g)
{
    g->AddNode("field_decl", GetRow(), GetColumn());
    name_list->PrintNode(g);
    type_decl->PrintNode(g);
    g->Pop();
}

void AST_Name_List::PrintNode(GraphViz *g)
{
    g->AddNode("name_list", GetRow(), GetColumn());
    for (auto id : identifier_list)
    {
        g->AddIdentifier(id);
    }
    g->Pop();
}

void AST_Type_Declaration_List::PrintNode(GraphViz *g)
{
    g->AddNode("type_decl_list", GetRow(), GetColumn());
    for (auto define : this->type_definition_list)
    {
        define->PrintNode(g);
    }
    g->Pop();
}

void AST_Type_Definition::PrintNode(GraphViz *g)
{
    g->AddNode("type_definition", GetRow(), GetColumn());
    g->AddIdentifier(this->identifier);
    this->type_decl->PrintNode(g);
    g->Pop();
}

void AST_Type_Part::PrintNode(GraphViz *g)
{
    g->AddNode("type_part", GetRow(), GetColumn());
    this->type_decl_list->PrintNode(g);
    g->Pop();
}

// AST_Value
void AST_Const_Value::PrintNode(GraphViz *g)
{
    //添加一个常数值
    std::string value_type_name = this->Get_Value_Type_Name(this->value_type);
    g->AddValue(value_type_name, this->content);
}
void AST_Const_Expression_List::PrintNode(GraphViz *g)
{
    g->AddNode("const_expr_list", GetRow(), GetColumn());
    for (auto expr : const_expr_list)
    {
        expr->PrintNode(g);
    }
    g->Pop();
}

void AST_Const_Expression::PrintNode(GraphViz *g)
{
    g->AddNode("const_expr", GetRow(), GetColumn());
    g->AddIdentifier(this->id);
    this->value->PrintNode(g);
    g->Pop();
}
void AST_Const_Part::PrintNode(GraphViz *g)
{
    g->AddNode("const_part", GetRow(), GetColumn());
    const_expr_list->PrintNode(g);
    g->Pop();
}
void AST_Variable_Part::PrintNode(GraphViz *g)
{
    g->AddNode("var_part", GetRow(), GetColumn());
    var_decl_list->PrintNode(g);
    g->Pop();
}
void AST_Variable_Declaration_List::PrintNode(GraphViz *g)
{
    g->AddNode("var_decl_list:", GetRow(), GetColumn());
    for (int i = 0; i < (int)var_decl_list.size(); i++)
    {
        var_decl_list[i]->PrintNode(g);
    }
    g->Pop();
}
void AST_Variable_Declaration::PrintNode(GraphViz *g)
{
    g->AddNode("var_decl:", GetRow(), GetColumn());
    name_list->PrintNode(g);
    type_decl->PrintNode(g);
    g->Pop();
}