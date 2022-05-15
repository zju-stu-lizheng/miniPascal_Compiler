#include "../ast/AST.hpp"
#include "../type/type.hpp"
#include "../contents/Contents.hpp"

using namespace Our_Type;

// AST_Expression.hpp
std::shared_ptr<Custom_Result> AST_Expression_List::CodeGenerate()
{
    std::vector<std::shared_ptr<Value_Result>> ret;
    int cnt = 0;
    for (auto expression_node : expr_list)
    {
        auto value = std::static_pointer_cast<Value_Result>(expression_node->CodeGenerate());
        if (value == nullptr)
        {
            std::cerr << "meet nullptr at AST_Expression_List code generation! At parameter: " << cnt << std::endl;
        }
        ret.push_back(value);
        cnt++;
    }
    //返回一个智能指针
    return std::make_shared<Value_List_Result>(ret);
}

std::shared_ptr<Custom_Result> AST_Binary_Expression::CodeGenerate()
{
    auto l = std::static_pointer_cast<Value_Result>(left_expression->CodeGenerate());
    auto r = std::static_pointer_cast<Value_Result>(right_expression->CodeGenerate());
    if (l == nullptr || r == nullptr)
        return nullptr;

    // semantic check
    //...//

    // IR build

    bool is_real = isEqual(l->GetType(), REAL_TYPE);
    if (my_operation == Operation::REALDIV)
        is_real = true;
    auto L = l->GetValue(), R = r->GetValue();
    if (is_real)
    {
        L = Contents::builder.CreateUIToFP(L, GetLLVMType(Contents::context, REAL_TYPE));
        R = Contents::builder.CreateUIToFP(R, GetLLVMType(Contents::context, REAL_TYPE));
    }
    switch (my_operation)
    {
    case Operation::GE:
        return std::make_shared<Value_Result>(BOOLEAN_TYPE, is_real ? Contents::builder.CreateFCmpOGE(L, R, "cmpftmp")
                                                                    : Contents::builder.CreateICmpSGE(L, R, "cmptmp"));
    case Operation::GT:
        return std::make_shared<Value_Result>(BOOLEAN_TYPE, is_real ? Contents::builder.CreateFCmpOGT(L, R, "cmpftmp")
                                                                    : Contents::builder.CreateICmpSGT(L, R, "cmptmp"));
    case Operation::LE:
        return std::make_shared<Value_Result>(BOOLEAN_TYPE, is_real ? Contents::builder.CreateFCmpOLE(L, R, "cmpftmp")
                                                                    : Contents::builder.CreateICmpSLE(L, R, "cmptmp"));
    case Operation::LT:
        return std::make_shared<Value_Result>(BOOLEAN_TYPE, is_real ? Contents::builder.CreateFCmpOLT(L, R, "cmpftmp")
                                                                    : Contents::builder.CreateICmpSLT(L, R, "cmptmp"));
    case Operation::EQUAL:
        return std::make_shared<Value_Result>(BOOLEAN_TYPE, is_real ? Contents::builder.CreateFCmpOEQ(L, R, "cmpftmp")
                                                                    : Contents::builder.CreateICmpEQ(L, R, "cmptmp"));
    case Operation::UNEQUAL:
        return std::make_shared<Value_Result>(BOOLEAN_TYPE, is_real ? Contents::builder.CreateFCmpONE(L, R, "cmpftmp")
                                                                    : Contents::builder.CreateICmpNE(L, R, "cmptmp"));
    case Operation::PLUS:
        return std::make_shared<Value_Result>(BOOLEAN_TYPE, is_real ? Contents::builder.CreateFAdd(L, R, "addftmp")
                                                                    : Contents::builder.CreateAdd(L, R, "addtmp"));
    case Operation::MINUS:
        return std::make_shared<Value_Result>(BOOLEAN_TYPE, is_real ? Contents::builder.CreateFSub(L, R, "subftmp")
                                                                    : Contents::builder.CreateSub(L, R, "subtmp"));
    case Operation::MUL:
        return std::make_shared<Value_Result>(BOOLEAN_TYPE, is_real ? Contents::builder.CreateFMul(L, R, "mulftmp")
                                                                    : Contents::builder.CreateMul(L, R, "multmp"));
    case Operation::DIV:
        if (is_real)
        {
            // 报告错误
            // error_message.push_back(cur_error_message);
            // error_position.push_back(location);
            // return RecordErrorMessage("The type of two side in div must be INTEGER.", GetLocation());
        }
        return std::make_shared<Value_Result>(INT_TYPE, Contents::builder.CreateSDiv(L, R, "divtmp"));
    case Operation::MOD:
        if (is_real)
        {
            // 报告错误
            // error_message.push_back(cur_error_message);
            // error_position.push_back(location);
            // return RecordErrorMessage("The type of two side in div must be INTEGER.", GetLocation());
        }
        return std::make_shared<Value_Result>(INT_TYPE, Contents::builder.CreateSRem(L, R, "modtmp"));
    case Operation::REALDIV:
        return std::make_shared<Value_Result>(REAL_TYPE, Contents::builder.CreateFDiv(L, R, "divftmp"));
    case Operation::OR:
        return std::make_shared<Value_Result>(BOOLEAN_TYPE, Contents::builder.CreateOr(L, R, "ortmp"));
    case Operation::AND:
        return std::make_shared<Value_Result>(BOOLEAN_TYPE, Contents::builder.CreateAnd(L, R, "andtmp"));

    default:
        return nullptr;
    }
}

std::shared_ptr<Custom_Result> AST_Unary_Expression::CodeGenerate()
{
    auto t = std::static_pointer_cast<Value_Result> (expression->CodeGenerate());
    if(t == nullptr) return nullptr;
    if(my_operation == Operation::NOT){
        if(!isEqual(t->GetType(),BOOLEAN_TYPE)){
            //report error
            return nullptr;
        }
        return std::make_shared<Value_Result> (t->GetType(),Contents::builder.CreateNot(t->GetValue(),"nottmp"));
    }else if(my_operation == Operation::SUB){
        if(!isEqual(t->GetType(),INT_TYPE) && !isEqual(t->GetType(),REAL_TYPE)){
            //report error
            return nullptr;
        }
        llvm::Type *tp = t->Get_llvm_Type();
        llvm::Value *zero = llvm::ConstantInt::get(tp,(uint64_t)0,true);
        //构造负数，是通过 用零减去这个数
        if (isEqual(t->GetType(), REAL_TYPE))
            return std::make_shared<Value_Result>(t->GetType(), Contents::builder.CreateFSub(zero, t->GetValue(), "negaftmp"));
        else
            return std::make_shared<Value_Result>(t->GetType(), Contents::builder.CreateSub(zero, t->GetValue(), "negatmp"));
    }
}

std::shared_ptr<Custom_Result> AST_Property_Expression::CodeGenerate()
{
    auto val = std::static_pointer_cast<Value_Result>((new AST_Identifier_Expression(id))->CodeGenerate());
    auto _record_type = val->GetType();
    if(!_record_type->isRecord()){
        //report error
        return nullptr;
    }
    auto record_type = (Record_Type*)_record_type;
    auto name_list = record_type->name_list;
    auto type_list = record_type->type_list;
    int bias = -1;
    for(int i=0;i<name_list.size();i++){
        if(name_list[i] == prop_id){
            bias = i;
            break;
        }
    }
    if(bias == -1){
        //report error
        return nullptr;
    }
    std::vector<llvm::Value *> gep_vec = {llvm::ConstantInt::get(llvm::Type::getInt32Ty(Contents::context),0,true),
                                          (llvm::ConstantInt::get(llvm::Type::getInt32Ty(Contents::context),bias,true))};

    llvm::Value * mem = Contents::builder.CreateGEP(val->GetMemory(),gep_vec,"record_field");
    llvm::Value * ret = Contents::builder.CreateLoad(mem);
    return std::make_shared<Value_Result>(type_list[bias],ret,mem);
}

std::shared_ptr<Custom_Result> AST_Const_Value_Expression::CodeGenerate()
{
    return const_value->CodeGenerate();
}

std::shared_ptr<Custom_Result> AST_Function_Call::CodeGenerate()
{
    //先空着
    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Identifier_Expression::CodeGenerate()
{
    //判断是否在当前code_block
    // if()
    return nullptr;
    //再判断是否在最外层code_block
}

std::shared_ptr<Custom_Result> AST_Array_Expression::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

// AST_Program.hpp
std::shared_ptr<Custom_Result> AST_Program::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Program_Head::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Routine::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Routine_Head::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Declaration_BaseClass::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Routine_Part::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Routine_Body::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Function_Declaration::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Function_Head::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Procedure_Declaration::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Procedure_Head::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Parameters::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Parameters_Declaration_List::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Parameters_Type_List::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Variable_Parameters_List::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

// AST_Statement.hpp


// AST_Type.hpp
std::shared_ptr<Custom_Result> AST_Type::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Simple_Type_Declaration::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Array_Type_Declaration::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Record_Type_Declaration::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Field_Declaration_List::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Field_Declaration::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Name_List::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Type_Declaration_List::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Type_Definition::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Type_Part::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

// AST_Value.hpp
std::shared_ptr<Custom_Result> AST_Const_Value::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Const_Expression_List::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Const_Expression::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Const_Part::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Variable_Part::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Variable_Declaration_List::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Variable_Declaration::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}
