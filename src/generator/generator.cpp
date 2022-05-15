#include "../ast/AST.hpp"
#include "../type/type.hpp"
#include "../contents/Contents.hpp"

using namespace Our_Type;

//AST_Expression.hpp
std::shared_ptr<Custom_Result> AST_Expression_List::CodeGenerate(){
    std::vector<std::shared_ptr<Value_Result> > ret;
    int cnt = 0;
    for(auto expression_node : expr_list){
        auto value = std::static_pointer_cast<Value_Result>(expression_node->CodeGenerate());
        if(value == nullptr){
            std::cerr << "meet nullptr at AST_Expression_List code generation! At parameter: " << cnt << std::endl;
        }
        ret.push_back(value);
        cnt++;
    }
    //返回一个智能指针
    return std::make_shared<Value_List_Result>(ret);
}

std::shared_ptr<Custom_Result> AST_Binary_Expression::CodeGenerate(){
    auto l = std::static_pointer_cast<Value_Result>(left_expression->CodeGenerate());
    auto r = std::static_pointer_cast<Value_Result>(right_expression->CodeGenerate());
    if(l==nullptr || r == nullptr) return nullptr;

    //semantic check
    //...//

    //IR build

    bool is_real = isEqual(l->GetType(),REAL_TYPE);
    if(my_operation == Operation::REALDIV) is_real = true;
    auto L = l->GetValue(), R = r->GetValue();
    if (is_real){
        L = Contents::builder.CreateUIToFP(L, GetLLVMType(Contents::context, REAL_TYPE));
        R = Contents::builder.CreateUIToFP(R, GetLLVMType(Contents::context, REAL_TYPE));
    }
    switch (my_operation)
    {
    case Operation::GE :
        return std::make_shared<Value_Result>(BOOLEAN_TYPE,is_real ? Contents::builder.CreateFCmpOGE(L,R,"cmpftmp")
                                                                   : Contents::builder.CreateICmpSGE(L,R,"cmptmp"));
    default:
        break;
    }
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
