#include "../ast/AST.hpp"
#include "../type/type.hpp"
#include "../contents/Contents.hpp"
#include "generator_error_check.hpp"

std::shared_ptr<Custom_Result> AST_Compound_Statement::CodeGenerate(){
    std::shared_ptr<Custom_Result> stmt_list_ret = std::static_pointer_cast<Custom_Result>(statement_list->CodeGenerate());
    // Check_Result_NULLPtr(stmt_list_ret,"AST_Compound_Statement", this->GetLocation());
    return stmt_list_ret;
}

std::shared_ptr<Custom_Result> AST_Statement_List::CodeGenerate(){
    // std::cout << "hello" << std::endl;
    std::vector<std::shared_ptr<Custom_Result>> ret;
    int cnt = 0;
    for( auto stmt_node : statement_list){
        auto stmt_ret = std::static_pointer_cast<Custom_Result>(stmt_node->CodeGenerate());
        // Check_Result_NULLPtr(stmt_ret,"AST_Statement_List", this->GetLocation(), cnt);
        ret.push_back(stmt_ret);
        cnt ++;
    }
    return std::make_shared<Custom_List_Result>(ret);
}

std::shared_ptr<Custom_Result> AST_Statement::CodeGenerate(){
    // std::cout << "hello" << std::endl;
    if(has_label == Has_Label::HAS){
        std::shared_ptr<Label_Type> label_ret = std::static_pointer_cast<Label_Type>(label->CodeGenerate());
        
        if(Check_Multiple_Label(label_ret, this->GetLocation())){
            llvm::Function *function = Contents::builder.GetInsertBlock()->getParent();
            auto label_block = llvm::BasicBlock::Create(Contents::context, "label_" + label_ret->Get_label_string(), function);
            Contents::builder.CreateBr(label_block);
            Contents::builder.SetInsertPoint(label_block);
            Contents::GetCurrentBlock()->label_2_block[label_ret] = label_block;
        }else{
            return nullptr;
        }
        // check label number -> cannot goto multiple places
    }

    auto ret =  std::static_pointer_cast<Custom_Result>(non_label_statement->CodeGenerate());

    return ret;
}


std::shared_ptr<Custom_Result> AST_Label::CodeGenerate(){
    // std::cout << "hello" << std::endl;
    std::shared_ptr<Label_Type> label_ret;
    if(isIdentifier()){
        label_ret = std::make_shared<Label_Type>(this->identifier);
    }else{
        label_ret = std::make_shared<Label_Type>(this->literal_int);
    }
    return label_ret;
}

std::shared_ptr<Custom_Result> AST_Non_Label_Statement::CodeGenerate(){
    // std::cout << "hello" << std::endl;
    std::shared_ptr<Custom_Result> stmt_ret;
    if(this->isAssign()){
        stmt_ret = std::static_pointer_cast<Custom_Result>(this->assgin_statement->CodeGenerate());
    }else if (this->isProcedure()){
        stmt_ret = std::static_pointer_cast<Custom_Result>(this->procedure_statement->CodeGenerate());
    }else if (this->isCompound()){
        stmt_ret = std::static_pointer_cast<Custom_Result>(this->compound_statement->CodeGenerate());
    }else if (this->isIf()){
        stmt_ret = std::static_pointer_cast<Custom_Result>(this->if_statement->CodeGenerate());
    }else if (this->isCase()){
        stmt_ret = std::static_pointer_cast<Custom_Result>(this->case_statement->CodeGenerate());
    }else if (this->isRepeat()){
        stmt_ret = std::static_pointer_cast<Custom_Result>(this->repeat_statement->CodeGenerate());
    }else if (this->isWhile()){
        stmt_ret = std::static_pointer_cast<Custom_Result>(this->while_statement->CodeGenerate());
    }else if (this->isFor()){
        stmt_ret = std::static_pointer_cast<Custom_Result>(this->for_statement->CodeGenerate());
    }else if (this->isGoto()){
        stmt_ret = std::static_pointer_cast<Custom_Result>(this->goto_statement->CodeGenerate());
    }
    return stmt_ret;
}

std::shared_ptr<Custom_Result> AST_Assign_Statement::CodeGenerate(){
    // std::cout << "hello" << std::endl;
    if(isDirectAssign()){
        // Todo: type transfer
        llvm::Value* left_mem = Contents::GetCurrentBlock()->names_2_values[identifier1];
        auto right = std::static_pointer_cast<Value_Result>(expression1->CodeGenerate());
        Contents::builder.CreateStore(right->GetValue(), left_mem);
        #ifdef GEN_DEBUG
        std::cout << "assign statement ready" << std::endl;
        #endif
    }else if(isArrayAssign()){

    }else if(isRecordAttrAssign()){

    }
    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Procedure_Statement::CodeGenerate(){
    // std::cout << "hello" << std::endl;

}


std::shared_ptr<Custom_Result> AST_If_Statement::CodeGenerate(){
    // std::cout << "hello" << std::endl;
    llvm::Function *function = Contents::builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *then_stmt_block = llvm::BasicBlock::Create(Contents::context, "if_then", function);
    llvm::BasicBlock *else_stmt_block = llvm::BasicBlock::Create(Contents::context, "if_else", function);
    llvm::BasicBlock *continue_stmt_block = llvm::BasicBlock::Create(Contents::context, "if_continue", function); //continue

    auto condition_ret = std::static_pointer_cast<Value_Result>(expression->CodeGenerate());
    //TODO: no expression / expression type not bool error check
    //contiute br
    Contents::builder.CreateCondBr(condition_ret->GetValue(), then_stmt_block, else_stmt_block);
    Contents::builder.SetInsertPoint(then_stmt_block); // then
    this->statement->CodeGenerate(); // do then
    Contents::builder.CreateBr(continue_stmt_block); // unconditional br label instruction
    Contents::builder.SetInsertPoint(else_stmt_block); // else
    //ToDO: not else
    this->else_clause->CodeGenerate();
    Contents::builder.CreateBr(continue_stmt_block); //continue out

    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Else_Clause::CodeGenerate(){
    // std::cout << "hello" << std::endl;
    return this->statement->CodeGenerate();
}

/*
std::shared_ptr<VisitorResult> Generator::VisitASTCaseStmt(ASTCaseStmt *node) {
    llvm::Function *func = this->builder.GetInsertBlock()->getParent();
    auto case_expr_list = node->getCaseExprList()->getCaseExprList();
    std::vector<llvm::BasicBlock *> cond_vec;
    std::vector<llvm::BasicBlock *> body_vec;
    int len = case_expr_list.size();
    for (int i=0; i < len; i++) {
        cond_vec.push_back(llvm::BasicBlock::Create(this->context, "case_branch", func));
        body_vec.push_back(llvm::BasicBlock::Create(this->context, "case_body", func));
    }
    auto end_block = llvm::BasicBlock::Create(this->context, "case_end", func);
    this->builder.CreateBr(len == 0 ? end_block : cond_vec[0]);
    for (int i=0; i < len; i++) {
        auto case_expr = case_expr_list[i];
        this->builder.SetInsertPoint(cond_vec[i]);
        auto ast_cmp = new ASTBinaryExpr(ASTBinaryExpr::Oper::EQUAL, node->getExpr(), case_expr->getExpr());
        auto match_res = std::static_pointer_cast<ValueResult>(ast_cmp->Accept(this));
        delete ast_cmp;
        this->builder.CreateCondBr(match_res->getValue(), body_vec[i], i == len - 1 ? end_block : cond_vec[i+1]);
        this->builder.SetInsertPoint(body_vec[i]);
        case_expr->getStmt()->Accept(this);
    }

    return nullptr;
}
*/
std::shared_ptr<Custom_Result> AST_Case_Statement::CodeGenerate(){
    // std::cout << "hello" << std::endl;
    llvm::Function* function = Contents::builder.GetInsertBlock()->getParent(); // for Create parent function
    auto case_expression_vec = case_expression_list->case_expression_list;
    int case_num = case_expression_vec.size();
    std::vector<llvm::BasicBlock *> condition_block_vec;
    std::vector<llvm::BasicBlock *> handle_block_vec;

    for(int i=0; i<case_num; i++){
        condition_block_vec.push_back(llvm::BasicBlock::Create(Contents::context, "case_condition", function));
        handle_block_vec.push_back(llvm::BasicBlock::Create(Contents::context, "case_handle", function));
    }
    auto endcase_block = llvm::BasicBlock::Create(Contents::context, "case_endcase", function);

    for(int i=0; i<case_num; i++){
        //use binary expression for convenience
        //TODO: reconstruct
        Contents::builder.SetInsertPoint(condition_block_vec[i]);
        // compare
        // bool_cmp = new AST_Binary_Expression(AST_Binary_Expression::Operation::EQUAL, this->expression, case_expression_vec[i]->e)
    }
    return nullptr;
}

std::shared_ptr<Custom_Result> AST_Case_Expression_List::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Case_Expression::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Repeat_Statement::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_While_Statement::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_For_Statement::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Direction::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}

std::shared_ptr<Custom_Result> AST_Goto_Statement::CodeGenerate()
{
    std::cout << "hello" << std::endl;
}
