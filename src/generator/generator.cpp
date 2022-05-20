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
#include <llvm/IR/Instruction.h>

using namespace Our_Type;

// AST_Expression.hpp
std::shared_ptr<Custom_Result> AST_Expression_List::CodeGenerate()
{
    std::vector<std::shared_ptr<Value_Result> > ret;
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
            // return RecordErrorMessage("The type of two side in div must be INTEGER.", GetLocationString());
        }
        return std::make_shared<Value_Result>(INT_TYPE, Contents::builder.CreateSDiv(L, R, "divtmp"));
    case Operation::MOD:
        if (is_real)
        {
            // 报告错误
            // error_message.push_back(cur_error_message);
            // error_position.push_back(location);
            // return RecordErrorMessage("The type of two side in div must be INTEGER.", GetLocationString());
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
            Record_and_Output_Error(true,"Operation::NOT 作用的 operand 必须是布尔类型!",this->GetLocation());
            return nullptr;
        }
        return std::make_shared<Value_Result> (t->GetType(),Contents::builder.CreateNot(t->GetValue(),"nottmp"));
    }else if(my_operation == Operation::SUB){
        if(!isEqual(t->GetType(),INT_TYPE) && !isEqual(t->GetType(),REAL_TYPE)){
            Record_and_Output_Error(true,"Operation::SUB 作用的 operand 必须是数值类型!",this->GetLocation());
            return nullptr;
        }
        llvm::Type *tp = t->Get_llvm_Type();
        llvm::Value *zero = llvm::ConstantInt::get(tp,(uint64_t)0,true);
        //构造负数，是通过 用零减去这个数
        if (isEqual(t->GetType(), REAL_TYPE))
            return std::make_shared<Value_Result>(t->GetType(), Contents::builder.CreateFSub(zero, t->GetValue(), "negaftmp"));
        else
            return std::make_shared<Value_Result>(t->GetType(), Contents::builder.CreateSub(zero, t->GetValue(), "negatmp"));
    }else if(my_operation == Operation::ADD){
        if(!isEqual(t->GetType(),INT_TYPE) && !isEqual(t->GetType(),REAL_TYPE)){
            Record_and_Output_Error(true,"Operation::ADD 作用的 operand 必须是数值类型!",this->GetLocation());
            return nullptr;
        }
        return std::make_shared<Value_Result>(t->GetType(), t->GetValue());
    }
    Record_and_Output_Error(true,"未定义的操作符!",this->GetLocation());
    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Property_Expression::CodeGenerate()
{
    // auto val = std::static_pointer_cast<Value_Result>((new AST_Identifier_Expression(id))->CodeGenerate());
    // 这里直接从变量表里面找
    auto _record_type = Contents::GetVarType(this->id);
    auto val =  (Contents::GetCurrentBlock()->isValue(this->id))?
                    std::make_shared<Value_Result>(_record_type,nullptr,Contents::GetCurrentBlock()->names_2_values[this->id]):
                    std::make_shared<Value_Result>(_record_type,nullptr,Contents::codeblock_list[0]->names_2_values[this->id]);
    //判断是否在当前code_block
    //再判断是否在最外层code_block
    
    if(!_record_type->isRecord()){
        //report error
        return nullptr;
    }
    auto record_type = (Record_Type*)_record_type;
    auto name_list = record_type->name_list;
    auto type_list = record_type->type_list;
    int bias = -1;
    for(int i=0;i<name_list.size();i++){
        if(name_list[i] == this->prop_id){
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

    llvm::Type * my_type = Our_Type::GetLLVMType(Contents::context,type_list[bias]);
    llvm::Value * mem = Contents::builder.CreateGEP(/*type = my_type,*/val->GetMemory(),gep_vec,"record_field");
    #ifdef GEN_DEBUG
    std::cout << "AST_Property_Expression CreateLoad" <<std::endl;
    #endif
    llvm::Value * ret = Contents::builder.CreateLoad(/*type = */my_type,mem,"load record type");
    return std::make_shared<Value_Result>(type_list[bias],ret,mem);
}

std::shared_ptr<Custom_Result> AST_Const_Value_Expression::CodeGenerate()
{
    return const_value->CodeGenerate();
}

std::shared_ptr<Custom_Result> AST_Function_Call::CodeGenerate()
{
    #ifdef GEN_DEBUG
    std::cout << "func_call start" <<std::endl;
    #endif
    std::shared_ptr<Value_List_Result> value_list;
    std::vector<std::shared_ptr<Value_Result> > value_vec;
    //判断是否含有参数
    bool has_args = true;
    if(this->args_list == nullptr){
        has_args = false;
    }else{
        #ifdef GEN_DEBUG
        std::cout << "get args_list start" <<std::endl;
        #endif
        value_list = std::static_pointer_cast<Value_List_Result> (this->args_list->CodeGenerate());
        #ifdef GEN_DEBUG
        std::cout << "get args_list ready" <<std::endl;
        #endif
        value_vec = value_list->GetValueList();
    }

    //获取函数名称    this->func_id;
    using namespace std;
	for (int i = Contents::codeblock_list.size() - 1; i>= 0; i--){
        #ifdef GEN_DEBUG
        std::cout << "enter CodeBlock" <<std::endl;
        #endif
        FuncSign *funcsign = (Contents::codeblock_list[i])->Find_FuncSign(this->func_id);
        if(funcsign == nullptr) {
            #ifdef GEN_DEBUG
            std::cout << "continue" <<std::endl;
            #endif
            
            continue;
        }else{
            #ifdef GEN_DEBUG
            std::cout << "find funcSign " <<std::endl;
            #endif
        }
        // Note the function/procedure can not be overridden in pascal, so the function is matched iff the name is matched.
        // NameList().size include all local variables that require to be passed
        // we should compare NameList.size() - n_local
        // which is the actual arg size
        if(funcsign->GetNameList().size() - funcsign->GetLocalVariablesNum() != value_vec.size()){
            Record_and_Output_Error(true,"Can't find function" + this->func_id + ": you have "+std::to_string(value_vec.size()) + "parameters, but the defined one has " 
            +std::to_string(funcsign->GetNameList().size() - funcsign->GetLocalVariablesNum()) + "parameters.",this->GetLocation());
            #ifdef GEN_DEBUG
            std::cout << "Can't find function" + this->func_id + ": you have "+std::to_string(value_vec.size()) + "parameters, but the defined one has " 
            +std::to_string(funcsign->GetNameList().size() - funcsign->GetLocalVariablesNum()) + "parameters." <<std::endl;
            #endif
            return nullptr;
        }
        auto name_list = funcsign->GetNameList();
        auto type_list = funcsign->GetTypeList();
        auto var_list = funcsign->GetVarList();
        auto return_type = funcsign->GetReturnType();

        llvm::Function *callee = (Contents::codeblock_list[i])->Find_Function(this->func_id);
        if(callee == nullptr) {
            #ifdef GEN_DEBUG
            std::cout << "continue" <<std::endl;
            #endif
            
            continue;
        }else{
            #ifdef GEN_DEBUG
            std::cout << "find function " <<std::endl;
            #endif
        }
        std::vector<llvm::Value*> parameters;

        // 添加局部变量
        // in generator_program.cpp, we define all locals at the head of the para list
        int cur;
        int n_local = funcsign->GetLocalVariablesNum();
        for(cur = 0; cur < n_local; cur++) {
            std::string local_name = name_list[cur];
            if (Contents::GetCurrentBlock()->names_2_values.find(local_name) == Contents::GetCurrentBlock()->names_2_values.end()) {
                #ifdef GEN_DEBUG
                std::cout << this->GetLocationString() << "local variable " << local_name << " need to be passed, but not found." << std::endl;
                #endif
                
                parameters.push_back(nullptr);
            } else {
                parameters.push_back(Contents::GetCurrentBlock()->names_2_values[local_name]);
            }
        }
        #ifdef GEN_DEBUG
        std::cout << "添加完局部变量 " <<std::endl;
        #endif

        // 函数传参
        for (auto value: value_vec){
            #ifdef GEN_DEBUG
            std::cout << "函数传参 " << cur <<std::endl;
            #endif
            if (!isEqual(value->GetType(), type_list[cur])){
                Record_and_Output_Error(true,"Type does not match on function " + this->func_id + " calling.",this->GetLocation());
                return nullptr;
            }
            #ifdef GEN_DEBUG
            std::cout << "类型匹配 " << cur <<std::endl;
            #endif
            if (value->GetMemory() != nullptr) {
                parameters.push_back(value->GetMemory());
            } else {
                Contents::temp_variable_count++;    //不重复编码
                // here we encounter a literally const value as a parameter
                // we add a local variable to the IRBuilder
                // but do not reflect it in Current_CodeBlock->named_values
                // thus we do not add abnormal local variables when we declare another function/procedure
                llvm::AllocaInst *mem = Contents::builder.CreateAlloca(
                    GetLLVMType(Contents::context, type_list[cur]), 
                    nullptr, 
                    "0_" + std::to_string(Contents::temp_variable_count)
                );
                Contents::builder.CreateStore(value->GetValue(), mem);
                parameters.push_back(mem);
            }
            #ifdef GEN_DEBUG
            std::cout << "传参结束 " << cur <<std::endl;
            #endif
            cur++;
        } 
        auto ret = Contents::builder.CreateCall(callee, parameters);

        if (funcsign->GetReturnType()->type_group == Our_Type::Pascal_Type::Type_Group::STRING) {
            // to return a str type for writeln to print
            // we have to use its pointer
            // to achieve this, we add a never used variable here
            Contents::temp_variable_count++;
            #ifdef GEN_DEBUG
            std::cout << ((String_Type *)funcsign->GetReturnType())->len << std::endl;
            #endif
            
            llvm::AllocaInst *mem = Contents::builder.CreateAlloca(
                GetLLVMType(Contents::context, funcsign->GetReturnType()),
                nullptr,
                "0_" + this->func_id + std::to_string(Contents::temp_variable_count)
            );
            Contents::builder.CreateStore(ret, mem);
            llvm::Type * my_type =Our_Type::GetLLVMType(Contents::context,funcsign->GetReturnType());
            #ifdef GEN_DEBUG
            std::cout << "GetReturnType CreateLoad" <<std::endl;
            #endif
            llvm::Value *value = Contents::builder.CreateLoad(/*type=*/my_type,mem,"load return value");
            return std::make_shared<Value_Result>(funcsign->GetReturnType(), value, mem); //, ret->getPointerOperand()); //, "call_"+ node->getFuncId()
        } else {
            #ifdef GEN_DEBUG
            std::cout << "function call ready" <<std::endl;
            #endif
            return std::make_shared<Value_Result>(funcsign->GetReturnType(), ret); 
        }
	}
    using namespace Our_Type;

    // To do list : 系统调用
    // Currently, sys_function will use no local variables that has cascade relation
    // So we do not need to deal with the locals and do it simply
    if (Contents::isSysFunc(this->func_id)) {
        return std::make_shared<Value_Result>(VOID_TYPE, Contents::GenSysFunc(this->func_id, value_vec));
    }
    Record_and_Output_Error(true,"Function " + this->func_id + " not found.",this->GetLocation());
    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Identifier_Expression::CodeGenerate()
{
    //判断是否在当前code_block
    if(Contents::GetCurrentBlock()->isValue(this->id)){
        llvm::Type * my_type =Our_Type::GetLLVMType(Contents::context,Contents::GetVarType(this->id));
        llvm::Value *mem = Contents::GetCurrentBlock()->names_2_values[this->id];
        #ifdef GEN_DEBUG
        std::cout << "AST_Identifier_Expression CreateLoad" <<std::endl;
        #endif
        llvm::Value *value = Contents::builder.CreateLoad(/*type=*/my_type,mem,"load identifier value");
        return std::make_shared<Value_Result>(Contents::GetVarType(this->id), value, mem);
    }
    //再判断是否在最外层code_block
    else if(Contents::codeblock_list[0]->isValue(this->id)){
        llvm::Type * my_type =Our_Type::GetLLVMType(Contents::context,Contents::codeblock_list[0]->names_2_ourtype[this->id]);
        llvm::Value *mem = Contents::codeblock_list[0]->names_2_values[this->id];
        #ifdef GEN_DEBUG
        std::cout << "AST_Identifier_Expression CreateLoad" <<std::endl;
        #endif
        llvm::Value *value = Contents::builder.CreateLoad(/*type=*/my_type,mem,"load identifier value");
        return std::make_shared<Value_Result>(Contents::codeblock_list[0]->names_2_ourtype[this->id], value, mem);
    }
    else{
        //可能是无参数的函数调用
        #ifdef GEN_DEBUG
        std::cout << "start calling no arg func : " << this->id << std::endl;
        #endif
        //Funcall
        AST_Function_Call *func_call = new AST_Function_Call(this->id, nullptr);
        auto ret = func_call->CodeGenerate();
        #ifdef GEN_DEBUG
        std::cout << "finish calling no arg func : " << this->id << " , return " << (ret == nullptr ? "is" : "is not") << " nullptr" << std::endl;
        #endif
        if (ret != nullptr) return ret;
        Record_and_Output_Error(true,this->id + " is neither a variable nor a no-arg function. Cannot get named value: ",this->GetLocation());
        return nullptr;
    }
}

std::shared_ptr<Custom_Result> AST_Array_Expression::CodeGenerate()
{
    auto index = std::static_pointer_cast<Value_Result> (expression->CodeGenerate());
    // 这里直接从变量表里面找
    Pascal_Type* _array_type  = Contents::GetVarType(this->id);
    auto array =  (Contents::GetCurrentBlock()->isValue(this->id))?
                    std::make_shared<Value_Result>(_array_type,nullptr,Contents::GetCurrentBlock()->names_2_values[this->id]):
                    std::make_shared<Value_Result>(_array_type,nullptr,Contents::codeblock_list[0]->names_2_values[this->id]);
    //判断是否在当前code_block
    //再判断是否在最外层code_block

    bool isStr = array->GetType()->type_group == Pascal_Type::Type_Group::STRING;
    bool isArr = array->GetType()->type_group == Pascal_Type::Type_Group::ARRAY;
    if (array == nullptr || (!isArr && !isStr)) {
        // report error
        // std::cerr << get_location() << "Not an array nor str, cannot use index." << std::endl;
        std::cout << "array exp fail" << std::endl;
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

    //考虑不是从0开始编号
    auto offset = Contents::builder.CreateSub(index->GetValue(),base,"subtmp");
    std::vector<llvm::Value *> offset_vec = {
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(Contents::context),0),
        offset
    };

    if (isArr) {
        llvm::Type *my_type = Our_Type::GetLLVMType(Contents::context,array_type->element_type);
        llvm::Value *tmp_mem = Contents::builder.CreateGEP(/*type=my_type,*/array->GetMemory(), offset_vec, "ArrayCall");
        #ifdef GEN_DEBUG
        std::cout << "AST_Array_Expression CreateLoad" <<std::endl;
        #endif
        llvm::Value *value = Contents::builder.CreateLoad(/*type=*/my_type,tmp_mem,"load array value");  //直接从name2_to_value中取
        return std::make_shared<Value_Result>(array_type->element_type, value, tmp_mem);
    } else {
        llvm::Type *my_type = Our_Type::GetLLVMType(Contents::context,Our_Type::CHAR_TYPE);
        llvm::Value *tmp_mem = Contents::builder.CreateGEP(/*type=my_type,*/array->GetMemory(), offset_vec, "ArrayCall");
        #ifdef GEN_DEBUG
        std::cout << "AST_Array_Expression CreateLoad" <<std::endl;
        #endif
        llvm::Value *value = Contents::builder.CreateLoad(/*type=*/my_type,tmp_mem,"load string value");
        return std::make_shared<Value_Result>(Our_Type::CHAR_TYPE, value, tmp_mem);
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
    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Routine_Head::CodeGenerate()
{
    if(this->const_part) this->const_part->CodeGenerate();
    #ifdef GEN_DEBUG
    std::cout << "const_part ready"<<std::endl;
    std::cout << "type_part start"<<std::endl;
    #endif
    if(this->type_part) this->type_part->CodeGenerate();
    #ifdef GEN_DEBUG
    std::cout << "type_part ready"<<std::endl;
    std::cout << "var_part start"<<std::endl;
    #endif
    if(this->var_part) this->var_part->CodeGenerate();
    #ifdef GEN_DEBUG
    std::cout << "var_part ready"<<std::endl;
    #endif
    if(this->routine_part) this->routine_part->CodeGenerate();
    #ifdef GEN_DEBUG
    std::cout << "routine_part ready"<<std::endl;
    #endif
    return nullptr;
}

//这里处理函数/过程定义
std::shared_ptr<Custom_Result> AST_Declaration_BaseClass::CodeGenerate()
{
    #ifdef GEN_DEBUG
    std::cout << "function start"<<std::endl;
    #endif
    bool is_function = (this->declaration_type == ENUM_Declaration_Type::FUNCTION_DECLARATION);
    auto parameters = std::static_pointer_cast<Type_List_Result>(
        is_function ? this->Get_Function_Declaration()->Get_Function_Head()->Get_Parameters()->CodeGenerate()
                    : this->Get_Procedure_Declaration()->Get_Procedure_Head()->Get_Parameters()->CodeGenerate()
    );

    #ifdef GEN_DEBUG
    std::cout << "is_function :" << is_function <<std::endl;
    #endif

    if(parameters == nullptr){
        #ifdef GEN_DEBUG
        std::cout << "Can not recognize the parameters for function/procedure definition." <<std::endl;
        #endif
        Record_and_Output_Error(true,"Can not recognize the parameters for function/procedure definition.",this->GetLocation());
        return nullptr;
    }

    #ifdef GEN_DEBUG
    std::cout << "recognize the parameters" <<std::endl;
    #endif

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
    std::vector<std::shared_ptr<Type_Result>> type_var_list = parameters->GetTypeList();
    std::vector<llvm::Type*> llvm_type_list;
    std::vector<Pascal_Type*> type_list;
    std::vector<bool> var_list;

    //检查是否有重名变量
    for(int i=0;i <name_list.size();i++){
        for(int j=i+1;j<name_list.size();j++){
            if(name_list[i] == name_list[j]){
                Record_and_Output_Error(true,"The parameters in the function/procedure definition are duplicated.",this->GetLocation());
                return nullptr;
            }
        }
    }

    #ifdef GEN_DEBUG
    std::cout << "Adding local variables" <<std::endl;
    #endif

    // Adding local variables
    // we must put local variables first
    // because after we create this function, 
    // we have to add the variables to the next CodeBlock
    // in this step, we must add the function parameters later
    // so as to overwrite the older local variables
    auto local_vars = Contents::GetAllLocalVarNameType();
    std::vector<std::string> local_name_list = local_vars.first;
    std::vector<Pascal_Type*> local_type_list = local_vars.second;

    for(int i=0;i<local_name_list.size();i++){
        name_list.push_back(local_name_list[i]);
        type_list.push_back(local_type_list[i]);
        var_list.push_back(true);
        llvm_type_list.push_back(llvm::PointerType::getUnqual(GetLLVMType(Contents::context,local_type_list[i])));
    }

    #ifdef GEN_DEBUG
    std::cout << "adding function parameters" <<std::endl;
    #endif

    //adding function parameters
    for(std::shared_ptr<Type_Result> type : type_var_list){
        type_list.push_back(type->GetType());
        var_list.push_back(type->GetIsVal());
        llvm_type_list.push_back(llvm::PointerType::getUnqual(GetLLVMType(Contents::context,type->GetType())));
    }

    FuncSign *funcsign = new FuncSign((int)local_name_list.size(),name_list,type_list,var_list,return_type);
    llvm::FunctionType *functiontype = llvm::FunctionType::get(
        /*返回类型*/llvm_return_type,
        /*参数类型列表*/llvm_type_list,
        /*isVar*/false
    );
    llvm::Function *function = llvm::Function::Create(functiontype,llvm::GlobalVariable::ExternalLinkage,function_name,Contents::module.get());

    Contents::GetCurrentBlock()->Set_Function(function_name,function,funcsign);

    llvm::BasicBlock* oldBlock = Contents::builder.GetInsertBlock();
    llvm::BasicBlock* basicBlock = llvm::BasicBlock::Create(Contents::context,"entry",function,nullptr);
    Contents::builder.SetInsertPoint(basicBlock);


    #ifdef GEN_DEBUG
    std::cout << "MODIFY PARAMETERS PASSING" <<std::endl;
    #endif

    //MODIFY PARAMETERS PASSING
    Contents::codeblock_list.push_back(new CodeBlock());
    Contents::GetCurrentBlock()->block_name = function_name;
    Contents::GetCurrentBlock()->is_function = is_function;
    int j = 0;
    llvm::Function::arg_iterator arg_id;
    for(arg_id = function->arg_begin();arg_id != function->arg_end();arg_id++,j++){
        if(var_list[j]){
            Contents::GetCurrentBlock()->names_2_values[name_list[j]] = (llvm::Value *) arg_id;
            if(j >= local_name_list.size()){
                Contents::GetCurrentBlock()->names_2_ourtype[name_list[j]] = type_list[j];
            }
            std::cout << "Inserted var param " << name_list[j] << std::endl;
        }else{
            llvm::Type * my_type = Our_Type::GetLLVMType(Contents::context,type_list[j]);
            llvm::Value *value = Contents::builder.CreateLoad(/*type=*/my_type,(llvm::Value*)arg_id,"load var param");
            llvm::AllocaInst *mem = Contents::builder.CreateAlloca(
                GetLLVMType(Contents::context,type_list[j]),
                nullptr,
                name_list[j]
            );
            Contents::builder.CreateStore(value,mem);
            Contents::GetCurrentBlock()->names_2_values[name_list[j]] = mem;
            if(j >= local_name_list.size())
                Contents::GetCurrentBlock()->names_2_ourtype[name_list[j]] = type_list[j];
            std::cout << "Inserted val param " << name_list[j] << std::endl;
        }
    }

    
    if(is_function){
        //add function to named_value for itself
        llvm::AllocaInst *mem = Contents::builder.CreateAlloca(
                GetLLVMType(Contents::context,return_type),
                nullptr,
                function_name
        );
        Contents::GetCurrentBlock()->names_2_values[function_name] = mem;
        Contents::GetCurrentBlock()->names_2_ourtype[function_name] = return_type;
        std::cout << "Inserted val param " << function_name << std::endl;

        //add return mechanism
        this->Get_Function_Declaration()->Get_routine()->CodeGenerate();
        if(Contents::codeblock_list.size() == 1){
            Contents::builder.CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(Contents::context),0,true));
        }else {
            llvm::Type *my_type = Our_Type::GetLLVMType(Contents::context,return_type);
            llvm::Value * ret = Contents::builder.CreateLoad(/*type=*/my_type,Contents::GetCurrentBlock()->names_2_values[function_name],"load ret param");
            Contents::builder.CreateRet(ret);
        }
    }else{
        this->Get_Procedure_Declaration()->Get_Routine()->CodeGenerate();
        Contents::builder.CreateRetVoid();
    }

    Contents::builder.SetInsertPoint(oldBlock);
    Contents::codeblock_list.pop_back();
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
    std::cout << "Routine_Body start" << std::endl;
    #endif
    return this->Get_Compound_Statement()->CodeGenerate();
}

std::shared_ptr<Custom_Result> AST_Function_Declaration::CodeGenerate()
{
    //实现在AST_Declaration_BaseClass
    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Function_Head::CodeGenerate()
{
    //do nothing
    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Procedure_Declaration::CodeGenerate()
{
    //实现在AST_Declaration_BaseClass
    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Procedure_Head::CodeGenerate()
{
    //do nothing
    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Parameters::CodeGenerate()
{
    //直接进入para_decl_list进行代码生成
    auto result = this->Get_Parameters_Declaration_List()->CodeGenerate();
    #ifdef GEN_DEBUG
    std::cout << "para_decl_list ready"  <<std::endl;
    #endif
    return result;
}

std::shared_ptr<Custom_Result> AST_Parameters_Declaration_List::CodeGenerate()
{
    std::vector<std::string> name_list;
    std::vector<std::shared_ptr<Type_Result> > type_list;
    for(auto son : this->Get_Parameter_Type_List_List()){
        //将parameter_type_list逐一添加
        auto temp_list = std::static_pointer_cast<Type_List_Result>(son->CodeGenerate());
        name_list.insert(name_list.end(),temp_list->GetNameList().begin(),temp_list->GetNameList().end());
        type_list.insert(type_list.end(),temp_list->GetTypeList().begin(),temp_list->GetTypeList().end());
        #ifdef GEN_DEBUG
        std::cout << temp_list->GetNameList()[0]<< " " << temp_list->GetTypeList()[0]->GetType() <<std::endl;
        #endif
    }
    return std::make_shared<Type_List_Result>(type_list,name_list);
}

std::shared_ptr<Custom_Result> AST_Parameters_Type_List::CodeGenerate()
{
    std::shared_ptr<Custom_Result> list;
    if(this->isVar()){
        //是Variable
        list = this->Get_Variable_Parameters_List()->CodeGenerate();
    }else{
        //是name_list
        list = this->Get_Name_List()->CodeGenerate();
    }

    auto name_list = std::static_pointer_cast<Name_List>(list)->GetNameList();
    auto type_value = std::static_pointer_cast<Type_Result>(this->Get_Simple_Type_Declaration()->CodeGenerate());
    if(this->isVar()){
        type_value->SetIsVal(true);
    }
    std::vector<std::shared_ptr<Type_Result> > type_list(name_list.size(),type_value);
    return std::make_shared<Type_List_Result>(type_list,name_list);
}

std::shared_ptr<Custom_Result> AST_Variable_Parameters_List::CodeGenerate()
{
    return this->Get_Name_List()->CodeGenerate();
}

// AST_Statement.hpp


// AST_Type.hpp
std::shared_ptr<Custom_Result> AST_Type::CodeGenerate()
{
    AST_Type::Type_Name type_name = Get_Type_Name();
    if (type_name == AST_Type::Type_Name::INT)
        return std::make_shared<Type_Result>(Our_Type::INT_TYPE);
    else if (type_name == AST_Type::Type_Name::FLOAT)
        return std::make_shared<Type_Result>(Our_Type::REAL_TYPE);
    else if (type_name == AST_Type::Type_Name::BOOLEAN)
        return std::make_shared<Type_Result>(Our_Type::BOOLEAN_TYPE);
    else if (type_name == AST_Type::Type_Name::CHAR)
        return std::make_shared<Type_Result>(Our_Type::CHAR_TYPE);
    else if (type_name == AST_Type::Type_Name::STRING)
        return std::make_shared<Type_Result>(new Our_Type::String_Type());
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
    #ifdef GEN_DEBUG
    std::cout << "field_decl_list start" <<std::endl;
    #endif
    std::shared_ptr<Type_Declaration_List_Result> decls = std::static_pointer_cast<Type_Declaration_List_Result>(
        field_decl_list->CodeGenerate());
    
    #ifdef GEN_DEBUG
    std::cout << "field_decl_list ready" <<std::endl;
    #endif

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
        #ifdef GEN_DEBUG
        std::cout << "field_decl start" <<std::endl;
        #endif
        fd_ret = fd->CodeGenerate();
        #ifdef GEN_DEBUG
        std::cout << "field_decl ready" <<std::endl;
        #endif
        
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
    #ifdef GEN_DEBUG
    std::cout << "name_list start" <<std::endl;
    #endif
    if (list_ret = std::static_pointer_cast<Name_List>(this->name_list->CodeGenerate())) {
        name_list = list_ret->GetNameList();
    } else {
        //report error
        #ifdef GEN_DEBUG
        std::cout << GetLocationString() << " not a name list." <<std::endl;
        #endif
        return nullptr;
    }
    #ifdef GEN_DEBUG
    std::cout << GetLocationString() << "name_list ready" <<std::endl;
    #endif

    std::shared_ptr< Type_Result > type_ret;
    Pascal_Type *type;
    if (type_ret = std::static_pointer_cast< Type_Result >(type_decl->CodeGenerate())) {
        type = type_ret->GetType();
    } else {
        // not a type
        #ifdef GEN_DEBUG
        std::cout << GetLocationString() << "type_decl does not have a type" <<std::endl;
        #endif
        return nullptr;
    }
    #ifdef GEN_DEBUG
    std::cout << GetLocationString() << "type_decl ready" <<std::endl;
    #endif

    return std::make_shared<Type_Declaration_Result>(list_ret->GetNameList(), type_ret->GetType());
}

std::shared_ptr<Custom_Result> AST_Name_List::CodeGenerate()
{
    return std::make_shared<Name_List>(identifier_list);
}

std::shared_ptr<Custom_Result> AST_Type_Declaration_List::CodeGenerate()
{
    #ifdef GEN_DEBUG
    std::cout << "AST_Type_Declaration_List start" <<std::endl;
    #endif
    for(auto td : type_definition_list){
        td->CodeGenerate();
    }
    #ifdef GEN_DEBUG
    std::cout << "AST_Type_Declaration_List ready" <<std::endl;
    #endif
    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Type_Definition::CodeGenerate()
{
    //判断是 SimpleTypeDecl / ArrayTypeDecl / RecordTypeDecl
    // this->type_decl->

    #ifdef GEN_DEBUG
    std::cout <<  "AST_Type_Definition start" <<std::endl;
    #endif

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
            #ifdef GEN_DEBUG
            std::cout << GetLocationString() << " multiple type definition." <<std::endl;
            #endif
        } else {
            Contents::GetCurrentBlock()->names_2_ourtype[identifier] = type;
        }
    } else {
        // report error
        #ifdef GEN_DEBUG
        std::cout << GetLocationString() << " fail to generate a type." <<std::endl;
        #endif
    }
    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Type_Part::CodeGenerate()
{
    std::cout << "type_decl_list"<<std::endl;
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
        if(this->content == "'\\n'"){
            #ifdef GEN_DEBUG
            std::cout << "读入换行符" <<std::endl;
            #endif
            char v_char = '\n'; //换行符
            return std::make_shared<Value_Result>(CHAR_TYPE,llvm::ConstantInt::get(tp,v_char),nullptr);
        }else{
            char v_char = this->content[1]; //这里应该是第二个字符 'a'
            return std::make_shared<Value_Result>(CHAR_TYPE,llvm::ConstantInt::get(tp,v_char),nullptr);
        }
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
        llvm::Type * my_type = Our_Type::GetLLVMType(Contents::context,new String_Type());
        llvm::Value * mem_str = Contents::builder.CreateGlobalString(tmp);
        llvm::Value * v_str = Contents::builder.CreateLoad(/*type=*/my_type,mem_str,"load const string");
        return std::make_shared<Value_Result> (new String_Type(),v_str,mem_str);
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
            /*Linkage=*/llvm::GlobalValue::PrivateLinkage,
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
    #ifdef GEN_DEBUG
    std::cout << "var_decl_list start" <<std::endl;
    #endif
    return this->var_decl_list->CodeGenerate();
}

std::shared_ptr<Custom_Result> AST_Variable_Declaration_List::CodeGenerate()
{
    for(auto var_decl : this->var_decl_list){
        #ifdef GEN_DEBUG
        std::cout << "var_decl start" <<std::endl;
        #endif
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
    #ifdef GEN_DEBUG
    std::cout << "name_list start" <<std::endl;
    #endif
    auto name_list = std::static_pointer_cast<Name_List>(this->name_list->CodeGenerate());
    #ifdef GEN_DEBUG
    std::cout << "name_list ready" <<std::endl;
    #endif
    auto type_decl = std::static_pointer_cast<Type_Result>(this->type_decl->CodeGenerate());
    #ifdef GEN_DEBUG
    std::cout << "type_decl ready" <<std::endl;
    #endif

    if(type_decl == nullptr){
        #ifdef GEN_DEBUG
        std::cout << "type_decl is null" <<std::endl;
        #endif
        return nullptr;    //error
    } 
    for(auto identifier : name_list->GetNameList()){
        #ifdef GEN_DEBUG
        type_decl->PrintType();
        #endif
        llvm::Type *ty = GetLLVMType(Contents::context,type_decl->GetType());
        if(Contents::codeblock_list.size() == 1){
            //是全局变量
            llvm::Constant * init_const;
            if(type_decl->GetType()->isSimple()){
                #ifdef GEN_DEBUG
                std::cout << "is simple type" <<std::endl;
                #endif
                init_const = llvm::Constant::getNullValue(ty);
            }else{
                #ifdef GEN_DEBUG
                std::cout << "is not simple type" <<std::endl;
                #endif
                init_const = llvm::ConstantAggregateZero::get(ty);
            }
            #ifdef GEN_DEBUG
            std::cout << "start get global variable" <<std::endl;
            #endif
            llvm::GlobalVariable * var = new llvm::GlobalVariable(
                /*Module=*/*(Contents::module),
                /*Type=*/ty,
                /*isConstant=*/false,
                /*Linkage=*/llvm::GlobalValue::CommonLinkage,
                /*Initializer=*/init_const, // has initializer, specified below
                /*Name=*/identifier);
            if(Contents::codeblock_list.back()->names_2_values.count(identifier)){
                #ifdef GEN_DEBUG
                std::cout << "变量重复定义" <<std::endl;
                #endif
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
    return nullptr;
}