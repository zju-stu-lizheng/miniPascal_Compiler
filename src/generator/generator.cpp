#include "../ast/AST.hpp"
#include <vector>
#include "../type/type.hpp"


//AST_Expression.hpp
std::shared_ptr<Custom_Result> AST_Expression_List::CodeGenerate(){
    // std::vector<std::shared_ptr<ValueResult>> ret;
}

std::shared_ptr<Custom_Result> AST_Binary_Expression::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Unary_Expression::CodeGenerate(){
    std::cout << "hello" << std::endl;
}


std::shared_ptr<Custom_Result> AST_Property_Expression::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Const_Value_Expression::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Function_Call::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Identifier_Expression::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Array_Expression::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

//AST_Program.hpp
std::shared_ptr<Custom_Result> AST_Program::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Program_Head::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Routine::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Routine_Head::CodeGenerate(){
    std::cout << "hello" << std::endl;
}


std::shared_ptr<Custom_Result> AST_Declaration_BaseClass::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Routine_Part::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Routine_Body::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Function_Declaration::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Function_Head::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Procedure_Declaration::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Procedure_Head::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Parameters::CodeGenerate(){
    std::cout << "hello" << std::endl;
}


std::shared_ptr<Custom_Result> AST_Parameters_Declaration_List::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Parameters_Type_List::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Variable_Parameters_List::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

//AST_Statement.hpp
std::shared_ptr<Custom_Result> AST_Compound_Statement::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Statement_List::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Statement::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Label::CodeGenerate(){
    std::cout << "hello" << std::endl;
}


std::shared_ptr<Custom_Result> AST_Non_Label_Statement::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Assign_Statement::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Procedure_Statement::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_If_Statement::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Else_Clause::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Case_Statement::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Case_Expression_List::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Case_Expression::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Repeat_Statement::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_While_Statement::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_For_Statement::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Direction::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Goto_Statement::CodeGenerate(){
    std::cout << "hello" << std::endl;
}


//AST_Type.hpp
std::shared_ptr<Custom_Result> AST_Type::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Simple_Type_Declaration::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Array_Type_Declaration::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Record_Type_Declaration::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Field_Declaration_List::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Field_Declaration::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Name_List::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Type_Declaration_List::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Type_Definition::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Type_Part::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

//AST_Value.hpp
std::shared_ptr<Custom_Result> AST_Const_Value::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Const_Expression_List::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Const_Expression::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Const_Part::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Variable_Part::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Variable_Declaration_List::CodeGenerate(){
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Variable_Declaration::CodeGenerate(){
    std::cout << "hello" << std::endl;
}
