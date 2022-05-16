#include "../ast/AST.hpp"
#include "../type/type.hpp"
#include "../contents/Contents.hpp"
#include "generator_error_check.hpp"
#include <iostream>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/BasicBlock.h>
#define GEN_DEBUG

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
    std::shared_ptr<Value_List_Result> value_list;
    std::vector<std::shared_ptr<Value_Result> > value_vec;
    //判断是否含有参数
    bool has_args = true;
    if(this->args_list == nullptr){
        has_args = false;
    }else{
        value_list = std::static_pointer_cast<Value_List_Result> (this->args_list->CodeGenerate());
        value_vec = value_list->GetValueList();
    }

    //获取函数名称    this->func_id;
    

    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Identifier_Expression::CodeGenerate()
{
    //判断是否在当前code_block
    if(Contents::GetCurrentBlock()->isValue(id)){
        llvm::Value *mem = Contents::GetCurrentBlock()->names_2_values[id];
        llvm::Value *value = Contents::builder.CreateLoad(mem);
        return std::make_shared<Value_Result>(Contents::GetVarType(id), value, mem);
    }
    //再判断是否在最外层code_block
    else if(Contents::codeblock_list[0]->isValue(id)){
        llvm::Value *mem = Contents::codeblock_list[0]->names_2_values[id];
        llvm::Value *value = Contents::builder.CreateLoad(mem);
        return std::make_shared<Value_Result>(Contents::codeblock_list[0]->names_2_ourtype[id], value, mem);
    }
    else{
        //可能是无参数的函数调用
        //Funcall
        return nullptr;
    }
}

std::shared_ptr<Custom_Result> AST_Array_Expression::CodeGenerate()
{
    auto index = std::static_pointer_cast<Value_Result> (expression->CodeGenerate());
    auto array = std::static_pointer_cast<Value_Result> ((new AST_Identifier_Expression(id))->CodeGenerate());
    bool isStr = array->GetType()->type_group == Pascal_Type::Type_Group::STRING;
    bool isArr = array->GetType()->type_group == Pascal_Type::Type_Group::ARRAY;
    if (array == nullptr || (!isArr && !isStr)) {
        // report error
        // std::cerr << get_location() << "Not an array nor str, cannot use index." << std::endl;
        return nullptr;
    }

    Array_Type* array_type = (Array_Type*)(array->GetType());
    if (!isEqual(index->GetType(), Our_Type::INT_TYPE) && !isEqual(index->GetType(), Our_Type::CHAR_TYPE)) 
        return nullptr;

    llvm::Value *base;  //获取数组的基址
    if (isArr) {
        base = array_type->GetLLVMLow(Contents::context);
    } else {
        base = llvm::ConstantInt::get(llvm::Type::getInt32Ty(Contents::context), 0, true);
    }

    auto offset = Contents::builder.CreateSub(index->GetValue(),base,"subtmp");
    std::vector<llvm::Value *> offset_vec = {
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(Contents::context),0),
        offset
    };

    llvm::Value *mem = Contents::builder.CreateGEP( array->GetMemory(), offset_vec, "ArrayCall");
    llvm::Value *value = Contents::builder.CreateLoad(mem);
    if (isArr) {
        return std::make_shared<Value_Result>(array_type->element_type, value, mem);
    } else {
        return std::make_shared<Value_Result>(Our_Type::CHAR_TYPE, value, mem);
    }
}

// AST_Program.hpp
std::shared_ptr<Custom_Result> AST_Program::CodeGenerate()
{
    #ifdef GEN_DEBUG
    /*Debug output*/
    std::cout << "start program"<<std::endl;
    #endif
    this->program_head->CodeGenerate();
    #ifdef GEN_DEBUG
    /*Debug output*/
    std::cout << "program_head ready"<<std::endl;
    #endif
    Contents::codeblock_list.push_back(new CodeBlock());
    #ifdef GEN_DEBUG
    /*Debug output*/
    std::cout << "new CodeBlock"<<std::endl;
    #endif
    //下面定义主函数： int main(void); 
    llvm::FunctionType * function_type  = llvm::FunctionType::get(GetLLVMType(Contents::context,INT_TYPE),false);
    llvm::Function * main_function = llvm::Function::Create(
        /*函数类型:包括返回值和函数参数*/function_type,
        /*ExternalLink表示能够模块外使用*/llvm::Function::ExternalLinkage,
        /*函数名*/"main",
        &*(Contents::module));
    llvm::BasicBlock *entry = llvm::BasicBlock::Create(Contents::context,"entry",main_function);
    Contents::builder.SetInsertPoint(entry);
    #ifdef GEN_DEBUG
    /*Debug output*/
    std::cout << "define main"<<std::endl;
    #endif
    this->routine->CodeGenerate();
    #ifdef GEN_DEBUG
    /*Debug output*/
    std::cout << "routine ready"<<std::endl;
    #endif
    //创建返回值,正常返回0
    Contents::builder.CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(Contents::context),0,true));
    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Program_Head::CodeGenerate()
{
    //do nothing
    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Routine::CodeGenerate()
{
    this->routine_head->CodeGenerate();
    #ifdef GEN_DEBUG
    /*Debug output*/
    std::cout << "routine_head ready"<<std::endl;
    #endif
    this->routine_body->CodeGenerate();
}

std::shared_ptr<Custom_Result> AST_Routine_Head::CodeGenerate()
{
    if(this->const_part) this->const_part->CodeGenerate();
    #ifdef GEN_DEBUG
    std::cout << "const_part ready"<<std::endl;
    #endif
    if(this->type_part) this->type_part->CodeGenerate();
    #ifdef GEN_DEBUG
    std::cout << "type_part ready"<<std::endl;
    #endif
    if(this->var_part) this->var_part->CodeGenerate();
    #ifdef GEN_DEBUG
    std::cout << "var_part ready"<<std::endl;
    #endif
    if(this->routine_part) this->routine_part->CodeGenerate();
    #ifdef GEN_DEBUG
    std::cout << "routine_part ready"<<std::endl;
    #endif
}

std::shared_ptr<Custom_Result> AST_Declaration_BaseClass::CodeGenerate()
{
    bool is_function = (this->declaration_type == ENUM_Declaration_Type::FUNCTION_DECLARATION);
    auto parameters = std::static_pointer_cast<Type_List_Result>(
        is_function ? this->Get_Function_Declaration()->Get_Function_Head()->Get_Parameters()->CodeGenerate()
                    : this->Get_Procedure_Declaration()->Get_Procedure_Head()->Get_Parameters()->CodeGenerate()
    );

    if(parameters == nullptr){
        Record_and_Output_Error(true,"Can not recognize the parameters for function/procedure definition.",this->GetLocation());
        return nullptr;
    }

    Pascal_Type * return_type = Our_Type::VOID_TYPE;
    std::string function_name;
    if(is_function){
        //有返回值
        function_name = this->Get_Function_Declaration()->Get_Function_Head()->Get_Identifier();
        auto return_type_result = std::static_pointer_cast<Type_Result>(this->Get_Function_Declaration()->Get_Function_Head()->Get_Simple_Type_Declaration()->CodeGenerate());
        if(return_type_result == nullptr){
            Record_and_Output_Error(true,"Can not recognize the return type for the function definition.",this->GetLocation());
            return nullptr;
        }
        return_type = return_type_result->GetType();
    }else{
        function_name = this->Get_Procedure_Declaration()->Get_Procedure_Head()->Get_Identifier();
    }
    llvm::Type *llvm_return_type = GetLLVMType(Contents::context,return_type);
    auto name_list = parameters->GetNameList();
    auto type_var_list = parameters->GetTypeList();
    std::vector<llvm::Type*> llvm_type_list;
    std::vector<Pascal_Type*> type_list;
    std::vector<bool> var_list;

    for(int i=0;i <name_list.size();i++){
        for(int j=i+1;j<name_list.size();j++){
            if(name_list[i] == name_list[j]){
                Record_and_Output_Error(true,"The parameters in the function/procedure definition are duplicated.",this->GetLocation());
                return nullptr;
            }
        }
    }

    // Adding local variables
    // we must put local variables first
    // because after we create this function, 
    // we have to add the variables to the next CodeBlock
    // in this step, we must add the function parameters later
    // so as to overwrite the older local variables


    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Routine_Part::CodeGenerate()
{
    for(AST_Declaration_BaseClass* decl : this->declaration_list){
        decl->CodeGenerate();
        #ifdef GEN_DEBUG
        std::cout << "funtion declaration ready"<<std::endl;
        #endif
    }
    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Routine_Body::CodeGenerate()
{
    #ifdef GEN_DEBUG
    std::cout << "Routine_Body ready" << std::endl;
    #endif
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
    AST_Type::Type_Name type_name = Get_Type_Name();
    if (type_name == AST_Type::Type_Name::INT)
        return std::make_shared<Type_Result>(INT_TYPE);
    else if (type_name == AST_Type::Type_Name::FLOAT)
        return std::make_shared<Type_Result>(REAL_TYPE);
    else if (type_name == AST_Type::Type_Name::BOOLEAN)
        return std::make_shared<Type_Result>(BOOLEAN_TYPE);
    else if (type_name == AST_Type::Type_Name::CHAR)
        return std::make_shared<Type_Result>(CHAR_TYPE);
    else 
        return nullptr;
}

std::shared_ptr<Custom_Result> AST_Simple_Type_Declaration::CodeGenerate()
{
    if (my_type == My_Type::EASY_TYPE) {
        return my_typename->CodeGenerate();
    } else if (my_type == My_Type::IDENTIFIER) {
        Pascal_Type *ret = nullptr;
        
        if (Contents::GetCurrentBlock()->names_2_values.count(define_id) > 0) {
            // return RecordErrorMessage("The variable " + define_id + " Can not be defined again.", get_location_pairs());
            return nullptr;
        }

        for (int i = Contents::codeblock_list.size()-1; i >= 0; i--) {
            CodeBlock *block = Contents::codeblock_list[i];
            if (block->names_2_ourtype.find(define_id) != block->names_2_ourtype.end()) {
                ret = block->names_2_ourtype[define_id];
            }
        }
        if (ret == nullptr) {
            // return RecordErrorMessage("Can not find the definition of type '" + define_id + "'.", get_location_pairs());
            return nullptr;
        }
        return std::make_shared<Type_Result>(ret);
    } else if (my_type == My_Type::VALUE_RANGE) {
        std::shared_ptr<Value_Result> low_ret = std::static_pointer_cast<Value_Result>(low->CodeGenerate());
        std::shared_ptr<Value_Result> high_ret = std::static_pointer_cast<Value_Result>(high->CodeGenerate());
        
        int low, high;
        if (llvm::ConstantInt *CI = llvm::dyn_cast<llvm::ConstantInt>(low_ret->GetValue())) {
            low = CI->getSExtValue();
        } else {
            // return RecordErrorMessage("The low number in range is incorrect.", get_location_pairs());
            return nullptr;
        }
        if (llvm::ConstantInt *CI = llvm::dyn_cast<llvm::ConstantInt>(high_ret->GetValue())) {
            high = CI->getSExtValue();
        } else {
            // return RecordErrorMessage("The high number in range is incorrect.", get_location_pairs());
            return nullptr;
        }

        // if (neg_low) low *= -1;
        // if (neg_high) high *= -1;
        
        Pascal_Type *range = new Subrange_Type(low, high);
        return std::make_shared<Type_Result>(range);
    } else if (my_type == My_Type::IDENTIFIER_RANGE) {
        std::string low_id = low_name;
        std::string high_id = high_name;

        // grab constant variable
        llvm::Constant *low, *high;
        if (Contents::names_2_constants.find(low_id) != Contents::names_2_constants.end()) {
            low = Contents::names_2_constants[low_id];
        } else {
            // return RecordErrorMessage("The low ID in range is incorrect.", get_location_pairs());
            return nullptr;
        }
        if (Contents::names_2_constants.find(high_id) != Contents::names_2_constants.end()) {
            high = Contents::names_2_constants[high_id];
        } else {
            //  return RecordErrorMessage("The high ID in range is incorrect.", get_location_pairs());
            return nullptr;
        }

        // grab int from ConstantInt*
        int low_int, high_int;
        if (llvm::ConstantInt *CI = llvm::dyn_cast<llvm::ConstantInt>(low)) {
            low_int = CI->getSExtValue();
        } else {
            // return RecordErrorMessage("The low ID in range is incorrect.", get_location_pairs());
            return nullptr;
        }
        if (llvm::ConstantInt *CI = llvm::dyn_cast<llvm::ConstantInt>(high)) {
            high_int = CI->getSExtValue();
        } else {
            // return RecordErrorMessage("The high ID in range is incorrect.", get_location_pairs());
            return nullptr;
        }
        Pascal_Type *range = new Subrange_Type(low_int, high_int);
        return std::make_shared<Type_Result>(range);

    } else if (my_type == My_Type::ENUMERATE) {
        std::shared_ptr<Name_List> list_ret;
        std::vector<std::string> name_list;
        if (list_ret = std::static_pointer_cast<Name_List>(this->name_list->CodeGenerate())) {
            name_list = list_ret->GetNameList();
        } else{
            // return RecordErrorMessage("Enum type does not has a name list.", get_location_pairs());
            return nullptr;
        }
        Enumerate_Type *new_enum = new Enumerate_Type(name_list);
        return std::make_shared<Type_Result>(new_enum);
    }
    // return RecordErrorMessage("Can not recognize the current type.", get_location_pairs());
    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Array_Type_Declaration::CodeGenerate()
{
    std::shared_ptr<Type_Result> tr;
    int low, high;
    tr = std::static_pointer_cast<Type_Result>(simple_type_decl->CodeGenerate());
    if (tr->GetType()->type_group == Pascal_Type::Type_Group::SUBRANGE) {
        Subrange_Type *range = (Subrange_Type *)tr->GetType();
        low = range->begin_2_end.first;
        high = range->begin_2_end.second;
    } else {
        // not a range
        // std::cout << node->get_location() << "index_range is not a range" << std::endl;
        return nullptr;
    }
    
    std::shared_ptr< Type_Result > type_ret;
    Pascal_Type *array_type;
    if (type_ret = std::static_pointer_cast< Type_Result >(type_decl->CodeGenerate())) {
        array_type = type_ret->GetType();
    } else {
        // not a type
        // std::cout << node->get_location() << "array_type is not a type" << std::endl;
        return nullptr;
    }
    Subrange_Type *_subrange = new Subrange_Type(low,high);
    Array_Type *this_type = new Array_Type(
        *_subrange,array_type
    ); 
    return std::make_shared<Type_Result>(this_type);
}

std::shared_ptr<Custom_Result> AST_Record_Type_Declaration::CodeGenerate()
{
    std::shared_ptr<Type_Declaration_List_Result> decls = std::static_pointer_cast<Type_Declaration_List_Result>(
        field_decl_list->CodeGenerate());

    if (decls) {
        std::vector<std::string> name_vec;
        std::vector<Pascal_Type *> type_vec;
        for(auto tdr : decls->GetTypeDeclList()) {
            Pascal_Type *type = tdr->GetType();
            for(auto attr_name : tdr->GetNameList()) {
                name_vec.push_back(attr_name);
                type_vec.push_back(type);
            }
        }
        Pascal_Type *record_type = new Record_Type(name_vec, type_vec);
        return std::make_shared<Type_Result>(record_type);
    } else {
        //report error
        // std::cout << get_location() << "fail to generate a record type." << std::endl;
        return nullptr;
    }
}

std::shared_ptr<Custom_Result> AST_Field_Declaration_List::CodeGenerate()
{
    std::shared_ptr<Custom_Result> fd_ret;
    std::shared_ptr<Type_Declaration_List_Result> ret(new Type_Declaration_List_Result());
    for (auto fd : field_decl_list) {
        fd_ret = fd->CodeGenerate();
        
        std::shared_ptr<Type_Declaration_Result> tdr;
        if (tdr = std::static_pointer_cast<Type_Declaration_Result>(fd_ret)) {
            ret->AddTypeDeclResult(tdr);
        } else {
            //report error
            // std::cout << fd->get_location() << "in a record_decl but not a type_decl" << std::endl;
        }
    }
    return ret;
}

std::shared_ptr<Custom_Result> AST_Field_Declaration::CodeGenerate()
{
    std::shared_ptr<Name_List> list_ret;
    std::vector<std::string> name_list;
    if (list_ret = std::static_pointer_cast<Name_List>(type_decl->CodeGenerate())) {
        name_list = list_ret->GetNameList();
    } else {
        //report error
        // std::cout << get_location() << " not a name list." << endl;
    }

    std::shared_ptr< Type_Result > type_ret;
    Pascal_Type *type;
    if (type_ret = std::static_pointer_cast< Type_Result >(type_decl->CodeGenerate())) {
        type = type_ret->GetType();
    } else {
        // not a type
        // std::cout << get_location() << "type_decl does not have a type" << std::endl;
        return nullptr;
    }

    return std::make_shared<Type_Declaration_Result>(list_ret->GetNameList(), type_ret->GetType());
}

std::shared_ptr<Custom_Result> AST_Name_List::CodeGenerate()
{
    return std::make_shared<Name_List>(identifier_list);
}

std::shared_ptr<Custom_Result> AST_Type_Declaration_List::CodeGenerate()
{
    for(auto td : type_definition_list){
        td->CodeGenerate();
    }
    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Type_Definition::CodeGenerate()
{
    std::shared_ptr<Type_Result> tr = std::static_pointer_cast<Type_Result>(
        type_decl->CodeGenerate());

    if (tr) {
        Pascal_Type *type = tr->GetType();
        bool defined = false;
        for (int i = Contents::codeblock_list.size()-1; i >= 0; i--) {
            CodeBlock *block = Contents::codeblock_list[i];
            if (block->names_2_ourtype.find(identifier) != block->names_2_ourtype.end()) {
                defined = true;
                break;
            }
        }
        if (defined) {
            // std::cout << get_location() << "multiple type definition." << std::endl;
            // report error
        } else {
            Contents::GetCurrentBlock()->names_2_ourtype[identifier] = type;
        }
    } else {
        // report error
        // std::cout << get_location() << "fail to generate a type." << std::endl;
    }
    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Type_Part::CodeGenerate()
{
    return type_decl_list->CodeGenerate();
}

// AST_Value.hpp
std::shared_ptr<Custom_Result> AST_Const_Value::CodeGenerate()
{
    llvm::Type * tp;
    //整数常量
    if(this->value_type == AST_Const_Value::Value_Type::INT){
        tp = llvm::Type::getInt32Ty(Contents::context);
        int v_int = atoi(this->content.c_str());
        return std::make_shared<Value_Result>(INT_TYPE,llvm::ConstantInt::get(tp,(uint64_t)v_int,true),nullptr);
    }
    //浮点常量
    else if(this->value_type == AST_Const_Value::Value_Type::FLOAT){
        tp = llvm::Type::getDoubleTy(Contents::context);
        double v_double = atof(this->content.c_str());
        return std::make_shared<Value_Result>(REAL_TYPE,llvm::ConstantFP::get(tp,v_double),nullptr);
    }
    //字符常量
    else if(this->value_type == AST_Const_Value::Value_Type::CHAR){
        tp = llvm::Type::getInt8Ty(Contents::context);
        char v_char = this->content[1]; //这里应该是第二个字符 'a'
        return std::make_shared<Value_Result>(CHAR_TYPE,llvm::ConstantInt::get(tp,v_char),nullptr);
    }
    //字面量：字符串
    else if(this->value_type == AST_Const_Value::Value_Type::STRING){
        // to make str things can store, alloc with each other
        // we have to make all string values have the same length
        // we make this 256
        // so we add suffix zero to all constant string
        std::string tmp = this->content.substr(1,this->content.length() - 2);
        int tmp_len = tmp.size();
        //如果大于255.报错
        char zero = 0;
        for(int i=0;i<255 - tmp_len;i++) tmp = tmp+zero;//填充0
        llvm::Value * mem_str = Contents::builder.CreateGlobalString(tmp);
        llvm::Value * v_str = Contents::builder.CreateLoad(mem_str);
        return std::make_shared<Value_Result> (new String_Type(),v_str,mem_str);
        // return nullptr;
    }
    //布尔常量
    else if(this->value_type == AST_Const_Value::Value_Type::FALSE){
        tp = llvm::Type::getInt1Ty(Contents::context);
        return std::make_shared<Value_Result> (BOOLEAN_TYPE,llvm::ConstantInt::get(tp,(u_int64_t)false,true),nullptr);
    }
    else if(this->value_type == AST_Const_Value::Value_Type::TRUE){
        tp = llvm::Type::getInt1Ty(Contents::context);
        return std::make_shared<Value_Result> (BOOLEAN_TYPE,llvm::ConstantInt::get(tp,(u_int64_t)true,true),nullptr);
    }
    return nullptr;
}

/*
const_expr_list->
    {const_expr}
*/
std::shared_ptr<Custom_Result> AST_Const_Expression_List::CodeGenerate()
{
    for(AST_Const_Expression * const_expr: this->const_expr_list){
        const_expr->CodeGenerate();
    }
    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Const_Expression::CodeGenerate()
{
    std::shared_ptr<Value_Result> res = std::static_pointer_cast<Value_Result>(this->value->CodeGenerate());
    llvm::GlobalVariable *constant = new llvm::GlobalVariable(
            /*Module=*/*(Contents::module),
            /*Type=*/GetLLVMType(Contents::context, res->GetType()),
            /*isConstant=*/true,
            /*Linkage=*/llvm::GlobalValue::CommonLinkage,
            /*Initializer=*/(llvm::Constant *) res->GetValue(), // has initializer, specified below
            /*Name=*/this->id );
    if (Contents::codeblock_list.back()->names_2_values.count(this->id) || Contents::names_2_constants.count(this->id)) {
        //error 
    }
    Contents::names_2_constants[this->id] = (llvm::Constant *) (res->GetValue());
    Contents::codeblock_list[0]->names_2_values[this->id] = constant;
    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Const_Part::CodeGenerate()
{
    return this->const_expr_list->CodeGenerate();
}

std::shared_ptr<Custom_Result> AST_Variable_Part::CodeGenerate()
{
    return this->var_decl_list->CodeGenerate();
}

std::shared_ptr<Custom_Result> AST_Variable_Declaration_List::CodeGenerate()
{
    for(auto var_decl : this->var_decl_list){
        var_decl->CodeGenerate();
    }
    return nullptr;
}

/**
 * @brief 
 * var_decl:
    name_list SYM_COLON type_decl SYM_SEMICOLON 
 * @return std::shared_ptr<Custom_Result> 
 */
std::shared_ptr<Custom_Result> AST_Variable_Declaration::CodeGenerate()
{
    auto name_list = std::static_pointer_cast<Name_List>(this->name_list->CodeGenerate());
    auto type_decl = std::static_pointer_cast<Type_Result>(this->type_decl->CodeGenerate());

    if(type_decl == nullptr) return nullptr;    //error
    for(auto identifier : name_list->GetNameList()){
        llvm::Type *ty = GetLLVMType(Contents::context,type_decl->GetType());
        if(Contents::codeblock_list.size() == 1){
            //是全局变量
            llvm::Constant * init_const;
            if(type_decl->GetType()->isSimple()){
                init_const = llvm::Constant::getNullValue(ty);
            }else{
                init_const = llvm::ConstantAggregateZero::get(ty);
            }
            llvm::GlobalVariable * var = new llvm::GlobalVariable(
                /*Module=*/*(Contents::module),
                /*Type=*/ty,
                /*isConstant=*/false,
                /*Linkage=*/llvm::GlobalValue::CommonLinkage,
                /*Initializer=*/init_const, // has initializer, specified below
                /*Name=*/identifier);
            if(Contents::codeblock_list.back()->names_2_values.count(identifier)){
                //error
            }
            Contents::codeblock_list.back()->names_2_values[identifier] = var;
            Contents::codeblock_list.back()->names_2_ourtype[identifier] = type_decl->GetType();
        }else{
            //是局部变量
            llvm::AllocaInst *var = Contents::builder.CreateAlloca(
                ty,
                nullptr,
                identifier
            );
            if(Contents::codeblock_list.back()->names_2_values.count(identifier)){
                //error
            }
            Contents::codeblock_list.back()->names_2_values[identifier] = var;
            Contents::codeblock_list.back()->names_2_ourtype[identifier] = type_decl->GetType();
        }
    }
}
