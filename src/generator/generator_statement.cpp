#include "../ast/AST.hpp"
#include "../type/type.hpp"
#include "../contents/Contents.hpp"
#include "generator_error_check.hpp"

std::shared_ptr<Custom_Result> AST_Compound_Statement::CodeGenerate()
{
    std::shared_ptr<Custom_Result> stmt_list_ret = std::static_pointer_cast<Custom_Result>(statement_list->CodeGenerate());
#ifdef GEN_DEBUG
    std::cout << "statement_list ready" << std::endl;
#endif
    return stmt_list_ret;
}

std::shared_ptr<Custom_Result> AST_Statement_List::CodeGenerate()
{
    std::vector<std::shared_ptr<Custom_Result>> ret;
    int cnt = 0;
    for (auto stmt_node : this->statement_list)
    {
        auto stmt_ret = std::static_pointer_cast<Custom_Result>(stmt_node->CodeGenerate());
#ifdef GEN_DEBUG
        std::cout << "statement ready " << cnt << std::endl;
#endif
        ret.push_back(stmt_ret);
        cnt++;
    }
#ifdef GEN_DEBUG
    std::cout << "Statement list done, cnt = " << std::to_string(cnt) << std::endl;
#endif
    return std::make_shared<Custom_List_Result>(ret);
}

std::shared_ptr<Custom_Result> AST_Statement::CodeGenerate()
{
    if (has_label == Has_Label::HAS)
    {
        std::shared_ptr<Label_Type> label_ret = std::static_pointer_cast<Label_Type>(label->CodeGenerate());

        if (Check_Multiple_Label(label_ret, this->GetLocation()))
        {
            llvm::Function *function = Contents::builder.GetInsertBlock()->getParent();
            auto label_block = llvm::BasicBlock::Create(Contents::context, "label_" + label_ret->Get_label_string(), function);
            Contents::builder.CreateBr(label_block);
            Contents::builder.SetInsertPoint(label_block);
            Contents::GetCurrentBlock()->label_2_block[label_ret] = label_block;
        }
        else
        {
            return nullptr;
        }
    }

    auto ret = std::static_pointer_cast<Custom_Result>(non_label_statement->CodeGenerate());
#ifdef GEN_DEBUG
    std::cout << "non_label_statement ready" << std::endl;
#endif

#ifdef GEN_DEBUG
    std::cout << "Statement done" << std::endl;
#endif
    return ret;
}

std::shared_ptr<Custom_Result> AST_Label::CodeGenerate()
{
    std::shared_ptr<Label_Type> label_ret;
    if (isIdentifier())
    {
        label_ret = std::make_shared<Label_Type>(this->identifier);
    }
    else
    {
        label_ret = std::make_shared<Label_Type>(this->literal_int);
    }
    return label_ret;
}

std::shared_ptr<Custom_Result> AST_Non_Label_Statement::CodeGenerate()
{
#ifdef GEN_DEBUG
    std::cout << "non label statement begin " << std::endl;
#endif
    std::shared_ptr<Custom_Result> stmt_ret;
    if (this->isAssign())
    {
#ifdef GEN_DEBUG
        std::cout << "isAssign " << std::endl;
#endif
        stmt_ret = std::static_pointer_cast<Custom_Result>(this->assgin_statement->CodeGenerate());
    }
    else if (this->isProcedure())
    {
#ifdef GEN_DEBUG
        std::cout << "isProcedure " << std::endl;
#endif
        stmt_ret = std::static_pointer_cast<Custom_Result>(this->procedure_statement->CodeGenerate());
    }
    else if (this->isCompound())
    {
#ifdef GEN_DEBUG
        std::cout << "isCompound " << std::endl;
#endif
        stmt_ret = std::static_pointer_cast<Custom_Result>(this->compound_statement->CodeGenerate());
    }
    else if (this->isIf())
    {
#ifdef GEN_DEBUG
        std::cout << "isIf " << std::endl;
#endif
        stmt_ret = std::static_pointer_cast<Custom_Result>(this->if_statement->CodeGenerate());
    }
    else if (this->isCase())
    {
#ifdef GEN_DEBUG
        std::cout << "isCase " << std::endl;
#endif
        stmt_ret = std::static_pointer_cast<Custom_Result>(this->case_statement->CodeGenerate());
    }
    else if (this->isRepeat())
    {
#ifdef GEN_DEBUG
        std::cout << "isRepeat " << std::endl;
#endif
        stmt_ret = std::static_pointer_cast<Custom_Result>(this->repeat_statement->CodeGenerate());
    }
    else if (this->isWhile())
    {
#ifdef GEN_DEBUG
        std::cout << "isWhile " << std::endl;
#endif
        stmt_ret = std::static_pointer_cast<Custom_Result>(this->while_statement->CodeGenerate());
    }
    else if (this->isFor())
    {
#ifdef GEN_DEBUG
        std::cout << "isFor " << std::endl;
#endif
        stmt_ret = std::static_pointer_cast<Custom_Result>(this->for_statement->CodeGenerate());
    }
    else if (this->isGoto())
    {
#ifdef GEN_DEBUG
        std::cout << "isGoto " << std::endl;
#endif
        stmt_ret = std::static_pointer_cast<Custom_Result>(this->goto_statement->CodeGenerate());
    }
    else if (this->isBreak())
    {
#ifdef GEN_DEBUG
        std::cout << "isBreak " << std::endl;
#endif
        stmt_ret = std::static_pointer_cast<Custom_Result>(this->break_statement->CodeGenerate());
    }
    return stmt_ret;
}

std::shared_ptr<Custom_Result> AST_Assign_Statement::CodeGenerate()
{
    
    if (isDirectAssign())
    {
// Todo: type transfer
#ifdef GEN_DEBUG
        std::cout << "direct assign" << std::endl;
#endif
        llvm::Value *left_mem = Contents::GetCurrentBlock()->names_2_values[identifier1];
// Contents::codeblock_list[0]
#ifdef GEN_DEBUG
        std::cout << "get the value of right expression start" << std::endl;
#endif

        auto right = std::static_pointer_cast<Value_Result>(expression1->CodeGenerate());
#ifdef GEN_DEBUG
        std::cout << "get the value of right expression ready" << std::endl;
#endif
        Contents::builder.CreateStore(right->GetValue(), left_mem);
    }
    else if (isArrayAssign())
    {
#ifdef GEN_DEBUG
        std::cout << "array assign" << std::endl;
#endif
        // llvm::Value* left_mem = Contents::GetCurrentBlock()->names_2_values[identifier1];
        // auto expidx = std::static_pointer_cast<Value_Result>(expression1->CodeGenerate());
        auto ast_array_expression = std::make_shared<AST_Array_Expression>(this->identifier1, this->expression1);
        std::shared_ptr<Value_Result> left_array_ret = std::static_pointer_cast<Value_Result>(ast_array_expression->CodeGenerate());
        auto right = std::static_pointer_cast<Value_Result>(expression2->CodeGenerate());

        Contents::builder.CreateStore(right->GetValue(), left_array_ret->GetMemory());
        // TODO : ??????????????????
    }
    else if (isRecordAttrAssign())
    {
        //??? IDENTIFIER '.' IDENTIFIER ':=' expression
        #ifdef GEN_DEBUG
        std::cout << "record assign" << std::endl;
        #endif
        // llvm::Value* left_mem = Contents::GetCurrentBlock()->names_2_values[identifier1];
        // auto expidx = std::static_pointer_cast<Value_Result>(expression1->CodeGenerate());
        auto ast_record_expression = std::make_shared<AST_Property_Expression>(this->identifier1, this->identifier2);
        std::shared_ptr<Value_Result> left_array_ret = std::static_pointer_cast<Value_Result>(ast_record_expression->CodeGenerate());
        auto right = std::static_pointer_cast<Value_Result>(expression1->CodeGenerate());

        Contents::builder.CreateStore(right->GetValue(), left_array_ret->GetMemory());
    }
#ifdef GEN_DEBUG
    std::cout << "assign statement ready" << std::endl;
#endif
    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Procedure_Statement::CodeGenerate()
{
    //??????Function_Call??????????????????
    AST_Function_Call *ast_func = new AST_Function_Call(this->identifier, this->expresion_list);
    auto res = ast_func->CodeGenerate();
    delete ast_func;
    return res;
}

std::shared_ptr<Custom_Result> AST_If_Statement::CodeGenerate()
{
    
    llvm::Function *function = Contents::builder.GetInsertBlock()->getParent();

    llvm::BasicBlock *then_stmt_block = llvm::BasicBlock::Create(Contents::context, "if_then", function);
    llvm::BasicBlock *else_stmt_block = llvm::BasicBlock::Create(Contents::context, "if_else", function);

    llvm::BasicBlock *continue_stmt_block = llvm::BasicBlock::Create(Contents::context, "if_continue", function); // continue

    auto condition_ret = std::static_pointer_cast<Value_Result>(expression->CodeGenerate());
    // TODO: no expression / expression type not bool error check
    // contiute br
    Contents::builder.CreateCondBr(condition_ret->GetValue(), then_stmt_block, else_stmt_block);
    Contents::builder.SetInsertPoint(then_stmt_block); // then
    this->statement->CodeGenerate();                   // do then
    Contents::builder.CreateBr(continue_stmt_block);   // unconditional br label instruction
    
    // ToDO: not else
    Contents::builder.SetInsertPoint(else_stmt_block);      // else
    if(this->else_clause != nullptr){
        this->else_clause->CodeGenerate();
    }
    Contents::builder.CreateBr(continue_stmt_block);        // continue out
    Contents::builder.SetInsertPoint(continue_stmt_block);      // else

    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Else_Clause::CodeGenerate()
{
    
    return this->statement->CodeGenerate();
}

std::shared_ptr<Custom_Result> AST_Case_Statement::CodeGenerate()
{
    
    llvm::Function *function = Contents::builder.GetInsertBlock()->getParent(); // for Create parent function
    auto case_expression_vec = case_expression_list->case_expression_list;
    int case_num = case_expression_vec.size();
    std::vector<llvm::BasicBlock *> condition_block_vec;
    std::vector<llvm::BasicBlock *> handle_block_vec;

    for (int i = 0; i < case_num; i++)
    {
        condition_block_vec.push_back(llvm::BasicBlock::Create(Contents::context, "case_condition", function));
        handle_block_vec.push_back(llvm::BasicBlock::Create(Contents::context, "case_handle", function));
    }
    auto endcase_block = llvm::BasicBlock::Create(Contents::context, "case_endcase", function);

    for (int i = 0; i < case_num; i++)
    {
        // use binary expression for convenience
        // TODO: reconstruct
        Contents::builder.SetInsertPoint(condition_block_vec[i]);
        // compare
        // bool_cmp = new AST_Binary_Expression(AST_Binary_Expression::Operation::EQUAL, this->expression, case_expression_vec[i]->e)
    }
    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Case_Expression_List::CodeGenerate()
{
    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Case_Expression::CodeGenerate()
{
    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Repeat_Statement::CodeGenerate()
{
    // ???????????????BasicBlock
    llvm::Function *func = Contents::builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *conditon_block = llvm::BasicBlock::Create(Contents::context, "repeat_condition", func);
    llvm::BasicBlock *body_block = llvm::BasicBlock::Create(Contents::context, "repeat_body", func);
    llvm::BasicBlock *continue_block = llvm::BasicBlock::Create(Contents::context, "repeat_continue", func);
    
    Contents::GetCurrentBlock()->loop_return_blocks.push_back(continue_block);
    
    // ??????body??????
    Contents::builder.CreateBr(body_block);
    
    // ???body_block?????????????????????while??????
    Contents::builder.SetInsertPoint(body_block);
    this->statement_list->CodeGenerate();

    // ??????????????????condition_block ???????????????????????????
    Contents::builder.CreateBr(conditon_block);
    Contents::builder.SetInsertPoint(conditon_block);

    auto cond_res = std::static_pointer_cast<Value_Result> (this->expression->CodeGenerate());
    if (cond_res == nullptr || !isEqual(cond_res->GetType(), BOOLEAN_TYPE)){
        Record_and_Output_Error(true,"Invalid condition in repeat statement.",this->GetLocation());
        return nullptr;
    }

    Contents::builder.CreateCondBr(cond_res->GetValue(),continue_block,body_block);
    Contents::builder.SetInsertPoint(continue_block);

    Contents::GetCurrentBlock()->loop_return_blocks.pop_back();
    return nullptr;
}

// ??????while?????? : to do:??????break???????????????
// while_stmt -> `while` expression `do` stmt
std::shared_ptr<Custom_Result> AST_While_Statement::CodeGenerate()
{
    // ???????????????BasicBlock
    llvm::Function *func = Contents::builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *conditon_block = llvm::BasicBlock::Create(Contents::context, "while_condition", func);
    llvm::BasicBlock *body_block = llvm::BasicBlock::Create(Contents::context, "while_body", func);
    llvm::BasicBlock *end_block = llvm::BasicBlock::Create(Contents::context, "while_end", func);
    
    Contents::GetCurrentBlock()->loop_return_blocks.push_back(end_block);

    Contents::builder.CreateBr(conditon_block);
    Contents::builder.SetInsertPoint(conditon_block);

    auto cond_res = std::static_pointer_cast<Value_Result>(this->expression->CodeGenerate());

    if (cond_res == nullptr || !isEqual(cond_res->GetType(), BOOLEAN_TYPE)){
        Record_and_Output_Error(true,"Invalid condition in while statement.",this->GetLocation());
        return nullptr;
    }
    
    // ?????????????????????????????????
    Contents::builder.CreateCondBr(cond_res->GetValue(), body_block, end_block);
    
    // ???body_block?????????????????????while??????
    Contents::builder.SetInsertPoint(body_block);
    this->statement->CodeGenerate();

    // ??????????????????condition_block ???????????????????????????
    Contents::builder.CreateBr(conditon_block);
    Contents::builder.SetInsertPoint(end_block);

    Contents::GetCurrentBlock()->loop_return_blocks.pop_back();

    return nullptr;
}

std::shared_ptr<Custom_Result> AST_For_Statement::CodeGenerate()
{    
    llvm::Function *function = Contents::builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *for_start_block = llvm::BasicBlock::Create(Contents::context, "for_start", function);
    llvm::BasicBlock *for_handle_block = llvm::BasicBlock::Create(Contents::context, "for_handle", function);
    llvm::BasicBlock *for_condition_block = llvm::BasicBlock::Create(Contents::context, "for_condition", function);
    llvm::BasicBlock *for_end_block = llvm::BasicBlock::Create(Contents::context, "for_end", function);

    // TODO: continue
    Contents::GetCurrentBlock()->loop_return_blocks.push_back(for_end_block);

    // start
    Contents::builder.CreateBr(for_start_block);
    Contents::builder.SetInsertPoint(for_start_block);

    // definition once
    // TODO enum class step add
    auto ast_const_value = new AST_Const_Value(
        this->my_direction->isTo() ? "1" : "-1",
        AST_Const_Value::Value_Type::INT);
    auto const_value_ret = std::static_pointer_cast<Value_Result>(ast_const_value->CodeGenerate());

    // reuse ast code generator
    std::cout << "begin for assign" << std::endl;
    auto ast_assign_statement = new AST_Assign_Statement(this->identifier, this->expression1);
    ast_assign_statement->CodeGenerate(); // local varaibla

    std::cout << "begin first cmp" << std::endl;
    // compare iteration assign
    auto ast_cmp_statement = new AST_Binary_Expression(
        this->my_direction->isTo() ? AST_Binary_Expression::Operation::GT : AST_Binary_Expression::Operation::LT,
        this->expression1, this->expression2);
    auto ast_cmp_ret = std::static_pointer_cast<Value_Result>(ast_cmp_statement->CodeGenerate());

    // branch
    std::cout << "begin first condition br" << std::endl;
    Contents::builder.CreateCondBr(ast_cmp_ret->GetValue(), for_end_block, for_handle_block);

    // handle
    std::cout << "begin handle" << std::endl;
    Contents::builder.SetInsertPoint(for_handle_block);
    this->statement->CodeGenerate();

    // condition: step -> cmp ? contine(->handle) or end
    std::cout << "begin condition" << std::endl;
    Contents::builder.CreateBr(for_condition_block);
    Contents::builder.SetInsertPoint(for_condition_block);
    // step
    std::cout << "begin step" << std::endl;

    auto left_id = new AST_Identifier_Expression(this->identifier); // left value for step
    auto left_ret = std::static_pointer_cast<Value_Result>(left_id->CodeGenerate());

    std::cout << "begin step add" << std::endl;
    llvm::Value *add_ret = Contents::builder.CreateAdd(left_ret->GetValue(), const_value_ret->GetValue(), "tmpadd");

    std::cout << "begin step store" << std::endl;
    Contents::builder.CreateStore(add_ret, left_ret->GetMemory());
    // auto ast_step_statement = new AST_Binary_Expression( // has symbol
    //     AST_Binary_Expression::Operation::PLUS,
    //     left_ret, ast_const_value_expression
    // );

    // compare (loop end )
    std::cout << "begin compare" << std::endl;
    left_id = new AST_Identifier_Expression(this->identifier);
    ast_cmp_statement = new AST_Binary_Expression(
        this->my_direction->isTo() ? AST_Binary_Expression::Operation::GT : AST_Binary_Expression::Operation::LT,
        left_id, this->expression2);
    ast_cmp_ret = std::static_pointer_cast<Value_Result>(ast_cmp_statement->CodeGenerate());

    Contents::builder.CreateCondBr(ast_cmp_ret->GetValue(), for_end_block, for_handle_block);

    Contents::builder.CreateBr(for_end_block);
    Contents::builder.SetInsertPoint(for_end_block);
    Contents::GetCurrentBlock()->loop_return_blocks.pop_back();

    std::cout << "for success" << std::endl;
    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Direction::CodeGenerate()
{
    
    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Goto_Statement::CodeGenerate()
{
    
    return nullptr;
}

// ??????????????????
std::shared_ptr<Custom_Result> AST_Break_Statement::CodeGenerate()
{
    if(Contents::GetCurrentBlock()->loop_return_blocks.empty()){
        Record_and_Output_Error(true,"Cannot use break statement because of no loop.",this->GetLocation());
        return nullptr;
    }
    //?????????????????????loop
    Contents::builder.CreateBr(Contents::GetCurrentBlock()->loop_return_blocks.back());
    llvm::Function * func = Contents::builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *continue_block = llvm::BasicBlock::Create(Contents::context,"break_continue",func);
    Contents::builder.SetInsertPoint(continue_block);
    return nullptr;
}