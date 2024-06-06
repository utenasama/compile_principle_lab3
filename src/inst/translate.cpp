#pragma once
#include "inst/translate.h"

std::vector<std::map<std::string, VarType_ptr>> symbol_table_var_;
std::vector<std::map<std::string, FuncType_ptr>> symbol_table_func_;

// 生成module
auto Module_main = std::make_unique<Module>();

Function *Function_main = Function::Create(
    FunctionType::get(Type::getIntegerTy(), {}),
    false,
    "main",
    Module_main.get());
BasicBlock *Entry_main = BasicBlock::Create(Function_main);
BasicBlock *current_basic_block;

// current basic block has terminator?
bool hasTerminator = false;
extern bool error;

void push_symbol_table_() // 加入一个新的符号表
{
    symbol_table_var_.push_back(std::map<std::string, VarType_ptr>());
    symbol_table_func_.push_back(std::map<std::string, FuncType_ptr>());
    // puts("1");
}

void pop_symbol_table_()
{
    auto table_var = symbol_table_var_.back();
    symbol_table_var_.pop_back();

    auto table_func = symbol_table_func_.back();
    symbol_table_func_.pop_back();
    // puts("2");
}

void add_var_to_table_(VarType_ptr variableptr)
{

    auto scope = symbol_table_var_.end() - 1; // 最后一个scope
    // 找到了重复的变量名
    if (scope->find(variableptr->ValID) != scope->end())
    {
        error = true;
        return;
    }
    else
    {
        scope->insert(std::pair<std::string, VarType_ptr>(variableptr->ValID, variableptr));
    }
}

void add_func_to_table_(FuncType_ptr funcptr)
{

    // 函数名不可重复
    auto iter = symbol_table_func_.end() - 1;
    for (auto iter = symbol_table_func_.end() - 1; iter >= symbol_table_func_.begin(); iter--)
    {
        if (iter->find(funcptr->FuncID) != iter->end())
        {
            error = true;
            return;
        }
    }
    // 未找到重复的函数定义
    if (iter == symbol_table_func_.begin())
    {
        auto scope = symbol_table_func_.rbegin(); // 最后一个scope
        scope->insert(std::pair<std::string, FuncType_ptr>(funcptr->FuncID, funcptr));
    }
}

Value *trans_pmn_unaexpr(PMNUnaExpr_ptr pmn_unaexp)
{

    switch (pmn_unaexp->OP)
    {
    case OP_Lnot:
    {
        Value *ret_value = trans_unaexp(pmn_unaexp->Operand);
        return BinaryInst::CreateEq(ret_value, ConstantInt::Create(0), Type::getIntegerTy(), current_basic_block);
        break;
    }
    case OP_Neg:
    {
        Value *ret_value = trans_unaexp(pmn_unaexp->Operand);
        return BinaryInst::CreateSub(ConstantInt::Create(0), ret_value, Type::getIntegerTy(), current_basic_block);
        break;
    }
    case OP_Pos:
    {
        return trans_unaexp(pmn_unaexp->Operand);
        break;
    }
    }
}

Value *trans_func_unaexpr(FunUnaExpr_ptr func_unaexpr)
{
    for (const auto &table : symbol_table_func_)
    {
        auto map_iter = table.find(func_unaexpr->FunID);
        if (map_iter != table.end())
        {
            auto *funrparam = func_unaexpr->FunRParam;
            auto *funcptr = map_iter->second;
            std::vector<Value *> args;

            for (auto *funfparam : funcptr->FParams)
            {
                args.push_back(trans_lor(funrparam->FirstParam));
                funrparam = funrparam->NextFunRParam;
            }

            CallInst *Call = CallInst::Create(funcptr->F, args, current_basic_block);
            return Call;
        }
    }

    error = true;

    return nullptr;
}

Value *trans_lval(LVal_ptr lval)
{

    int dimensions = 0;
    std::vector<Value *> Indices;

    for (auto *exparr = lval->ExpArr; exparr != nullptr; exparr = exparr->NextExpArr)
    {
        Value *dim = trans_lor(exparr->Expr);
        dimensions += 1;
        Indices.push_back(dim);
    }

    for (const auto &symbol_table : symbol_table_var_)
    {
        auto map_iter = symbol_table.find(lval->ID);
        if (map_iter != symbol_table.end())
        { 
            auto *valptr = map_iter->second;

            bool need_load = true;
            while (dimensions < valptr->Dimensions)
            {
                need_load = false;
                Indices.push_back(ConstantInt::Create(0));
                dimensions++;
            }
            auto Bounds = valptr->Bounds;

            if (dimensions != 0)
            {
                Value *offsetVal = valptr->Val_Ptr ? valptr->Val_Ptr : current_basic_block->getParent()->getArg(valptr->Param_No);
                OffsetInst *Offset = OffsetInst::Create(Type::getIntegerTy(), offsetVal, Indices, valptr->Bounds, current_basic_block);
                return need_load ? static_cast<Value *>(LoadInst::Create(Offset, current_basic_block)) : static_cast<Value *>(Offset);
            }
            else
            {
                return LoadInst::Create(valptr->Val_Ptr, current_basic_block);
            }
        }
    }
    error = true;
}

Value *trans_lval_noload(LVal_ptr lval)
{

    int dimensions = 0;
    std::vector<Value *> Indices;

    for (auto *exparr = lval->ExpArr; exparr != nullptr; exparr = exparr->NextExpArr)
    {
        Value *dim = trans_lor(exparr->Expr);
        dimensions += 1;
        Indices.push_back(dim);
    }

    for (const auto &symbol_table : symbol_table_var_)
    {
        auto map_iter = symbol_table.find(lval->ID);
        if (map_iter != symbol_table.end())
        { 
            auto *valptr = map_iter->second;

            while (dimensions < valptr->Dimensions)
            {
                Indices.push_back(ConstantInt::Create(0));
                dimensions++;
            }
            std::vector<std::optional<std::size_t>> Bounds = valptr->Bounds;

            if (dimensions != 0)
            {
                Value *offsetVal = valptr->Val_Ptr ? valptr->Val_Ptr : current_basic_block->getParent()->getArg(valptr->Param_No);
                return OffsetInst::Create(Type::getIntegerTy(), offsetVal, Indices, valptr->Bounds, current_basic_block);
            }
            else
            {
                return valptr->Val_Ptr;
            }
        }
    }
    error = true;
}

Value *trans_prim_unaexpr(PrimExpr_ptr primexp)
{
    if (auto *lpexprp = primexp->as<LpExprRp_ptr>())
        return trans_lor(lpexprp->Operand);
    else if (auto *integer = primexp->as<Integer_ptr>())
        return ConstantInt::Create(integer->Val);
    else if (auto *lval = primexp->as<LVal_ptr>())
        return trans_lval(lval);
}

Value *trans_unaexp(UnaExpr_ptr unaexp)
{
    if (auto *pmn_unaexpr = unaexp->as<PMNUnaExpr_ptr>())
        return trans_pmn_unaexpr(pmn_unaexpr);
    else if (auto *func_unaexpr = unaexp->as<FunUnaExpr_ptr>())
        return trans_func_unaexpr(func_unaexpr);
    else
        return trans_prim_unaexpr(static_cast<PrimExpr_ptr>(unaexp));
}

Value *trans_mulexp(MulExpr_ptr mulexp)
{
    switch (mulexp->OP)
    {
    case OP_None:
    {
        return trans_unaexp(mulexp->UnaExpr);
    }

    case OP_Mul:
    {
        return BinaryInst::CreateMul(
            trans_mulexp(mulexp->Operand),
            trans_unaexp(mulexp->UnaExpr),
            Type::getIntegerTy(),
            current_basic_block);
    }
    case OP_Div:
    {
        return BinaryInst::CreateDiv(
            trans_mulexp(mulexp->Operand),
            trans_unaexp(mulexp->UnaExpr),
            Type::getIntegerTy(),
            current_basic_block);
    }
    case OP_Mod:
    {
        return BinaryInst::CreateMod(
            trans_mulexp(mulexp->Operand),
            trans_unaexp(mulexp->UnaExpr),
            Type::getIntegerTy(),
            current_basic_block);
    }
    }
}

Value *trans_addexp(AddExpr_ptr addexp)
{
    switch (addexp->OP)
    {
    case OP_None:
    {
        return trans_mulexp(addexp->MulExpr);
    }
    case OP_Add:
    {
        return BinaryInst::CreateAdd(
            trans_addexp(addexp->Operand),
            trans_mulexp(addexp->MulExpr),
            Type::getIntegerTy(),
            current_basic_block);
    }
    case OP_Sub:
    {
        return BinaryInst::CreateSub(
            trans_addexp(addexp->Operand),
            trans_mulexp(addexp->MulExpr),
            Type::getIntegerTy(),
            current_basic_block);
    }
    }
}


Value *trans_initval(LOr_ptr initval)
{
    return trans_lor(initval);
}


void trans_valdec(ValDec_ptr valdec)
{
    int dimensions = 0;
    int array_size_total = 1;
    std::vector<int> dimensionsizes;

    for (auto *exparr = valdec->ExpArr; exparr != nullptr; exparr = exparr->NextExpArr)
    {
        auto *primexp = static_cast<PrimExpr_ptr>(exparr->Expr->LAnd->Eq->Rel->Expr->MulExpr->UnaExpr);
        auto *integer = primexp->as<Integer_ptr>();
        dimensions += 1;
        dimensionsizes.push_back(integer->Val);
        array_size_total *= integer->Val;
    }

    // alloca指令
    AllocaInst *val_addr = AllocaInst::Create(Type::getIntegerTy(), array_size_total, current_basic_block);

    if (valdec->InitVal != nullptr)
    {
        if (valdec->ExpArr != nullptr)
            error = true;
        Value *init_val = trans_initval(valdec->InitVal);
        StoreInst *ValInit = StoreInst::Create(init_val, val_addr, current_basic_block);
    }

    auto *variable = new VarType(valdec->ID, dimensions, dimensionsizes, val_addr);
    add_var_to_table_(variable);
}


void trans_valdec_global(ValDec_ptr valdec)
{
    int dimensions = 0;
    int array_size_total = 1;
    std::vector<int> dimensionsizes;

    for (auto *exparr = valdec->ExpArr; exparr != nullptr; exparr = exparr->NextExpArr)
    {
        auto *primexp = static_cast<PrimExpr_ptr>(exparr->Expr->LAnd->Eq->Rel->Expr->MulExpr->UnaExpr);
        auto *integer = primexp->as<Integer_ptr>();
        dimensions += 1;
        dimensionsizes.push_back(integer->Val);
        array_size_total *= integer->Val;
    }

    // alloca指令
    auto val_addr = GlobalVariable::Create(Type::getIntegerTy(), array_size_total, false, valdec->ID, Module_main.get());
    if (valdec->InitVal != nullptr)
    {
        if (valdec->ExpArr != nullptr)
            error = true;
        Value *init_val = trans_initval(valdec->InitVal);
        StoreInst *ValInit = StoreInst::Create(init_val, val_addr, Entry_main); // 所有的全局变量赋值语句，都放到main中
    }

    auto *variable = new VarType(valdec->ID, dimensions, dimensionsizes, val_addr);
    add_var_to_table_(variable);
}

VarType_ptr trans_funfparam(FunFParam_ptr funfparam)
{
    int dimensionCount = 0;
    std::vector<int> dimensionSizes;

    auto extractDimensionSize = [](ExpArr_ptr expArr)
    {
        auto *unaryExpr = expArr->Expr->LAnd->Eq->Rel->Expr->MulExpr->UnaExpr;
        auto *primaryExpr = static_cast<PrimExpr_ptr>(expArr->Expr->LAnd->Eq->Rel->Expr->MulExpr->UnaExpr);
        auto *integerExpr = primaryExpr->as<Integer_ptr>();
        return integerExpr->Val;
    };

    // 如果形式参数是一个数组，需要检查维度
    if (funfparam->IsArr)
    {
        dimensionCount++; // 如果形式参数是数组，第一维是空的，且在语法分析时不会被视为一个 ExpArr
        dimensionSizes.push_back(0);
        if (funfparam->ExpArr != nullptr)
        {
            for (auto *expArr = funfparam->ExpArr; expArr != nullptr; expArr = expArr->NextExpArr)
            {
                int dimensionSize = extractDimensionSize(expArr);
                dimensionCount++;
                dimensionSizes.push_back(dimensionSize);
                // 函数形式参数不需要分配存储空间，所以不需要计算总大小
            }
        }
    }
    return new VarType(funfparam->ID, dimensionCount, dimensionSizes);
}

void trans_retstmt(RetStmt_ptr retstmt)
{

    Value *returnValue;
    if (retstmt->Expr != nullptr)
    {
        returnValue = trans_lor(retstmt->Expr);
    }
    else
    {
        returnValue = ConstantUnit::Create();
    }

    RetInst *returnInstruction = RetInst::Create(returnValue, current_basic_block);
    hasTerminator = true;
}

Value *trans_lor(LOr_ptr lor)
{
    if (lor->Operand != nullptr)
    {
        return BinaryInst::CreateOr(
            trans_land(lor->LAnd),
            trans_lor(lor->Operand),
            Type::getIntegerTy(),
            current_basic_block);
    }
    else
    {
        return trans_land(lor->LAnd);
    }
}

Value *trans_land(LAnd_ptr land)
{
    if (land->Operand != nullptr)
    {
        return BinaryInst::CreateAnd(
            trans_eq(land->Eq),
            trans_land(land->Operand),
            Type::getIntegerTy(),
            current_basic_block);
    }
    else
    {
        return trans_eq(land->Eq);
    }
}

// shortcut版本 if while
Value *trans_lor_shortcut(LOr_ptr lor, BasicBlock *true_bb, BasicBlock *false_bb)
{
    if (lor->Operand != nullptr)
    {
        BasicBlock *lor_con1_false_bb = BasicBlock::Create(current_basic_block->getParent());
        Value *res_val1 = trans_land_shortcut(lor->LAnd, true_bb, lor_con1_false_bb);
        current_basic_block = lor_con1_false_bb;

        return trans_lor_shortcut(lor->Operand, true_bb, false_bb);
    }
    else
    {
        return trans_land_shortcut(lor->LAnd, true_bb, false_bb);
    }
}

Value *trans_land_shortcut(LAnd_ptr land, BasicBlock *true_bb, BasicBlock *false_bb)
{
    if (land->Operand != nullptr)
    {
        BasicBlock *land_con1_true_bb = BasicBlock::Create(current_basic_block->getParent());
        Value *res_val1 = trans_eq(land->Eq);
        BranchInst *Br = BranchInst::Create(land_con1_true_bb, false_bb, res_val1, current_basic_block);

        current_basic_block = land_con1_true_bb;

        return trans_land_shortcut(land->Operand, true_bb, false_bb);
    }
    else
    {
        if (land->Eq->Operand == nullptr && land->Eq->Rel->Operand == nullptr &&
            land->Eq->Rel->Expr->Operand == nullptr && land->Eq->Rel->Expr->MulExpr->Operand == nullptr)
        {
            if (auto *lpexprp = land->Eq->Rel->Expr->MulExpr->UnaExpr->as<LpExprRp_ptr>())
                return trans_lor_shortcut(lpexprp->Operand, true_bb, false_bb);
        }

        Value *res_value = trans_eq(land->Eq);
        BranchInst *Br = BranchInst::Create(true_bb, false_bb, res_value, current_basic_block);
        return res_value;
    }
}

Value *trans_eq(Eq_ptr eq)
{
    if (eq->Operand != nullptr)
    {
        switch (eq->OP)
        {
        case OP_Eq:
            return BinaryInst::CreateEq(
                trans_eq(eq->Operand),
                trans_rel(eq->Rel),
                Type::getIntegerTy(),
                current_basic_block);
            break;
        case OP_Ne:
            return BinaryInst::CreateNe(
                trans_eq(eq->Operand),
                trans_rel(eq->Rel),
                Type::getIntegerTy(),
                current_basic_block);
            break;
        }
    }
    else
        return trans_rel(eq->Rel);
}

Value *trans_rel(Rel_ptr rel)
{
    if (rel->Operand != nullptr)
    {
        switch (rel->OP)
        {
        case OP_Lt:
            return BinaryInst::CreateLt(
                trans_rel(rel->Operand),
                trans_addexp(rel->Expr),
                Type::getIntegerTy(),
                current_basic_block);
            break;
        case OP_Gt:
            return BinaryInst::CreateGt(
                trans_rel(rel->Operand),
                trans_addexp(rel->Expr),
                Type::getIntegerTy(),
                current_basic_block);
            break;
        case OP_Le:
            return BinaryInst::CreateLe(
                trans_rel(rel->Operand),
                trans_addexp(rel->Expr),
                Type::getIntegerTy(),
                current_basic_block);
            break;
        case OP_Ge:
            return BinaryInst::CreateGe(
                trans_rel(rel->Operand),
                trans_addexp(rel->Expr),
                Type::getIntegerTy(),
                current_basic_block);
            break;
        }
    }
    else
    {
        return trans_addexp(rel->Expr);
    }
}

void trans_whilestmt(WhileStmt_ptr whilestmt)
{
    // 创建三个基本块：Body, Entry, Exit
    Function *parentFunction = current_basic_block->getParent();
    BasicBlock *EntryBlock = BasicBlock::Create(parentFunction);
    BasicBlock *BodyBlock = BasicBlock::Create(parentFunction);
    BasicBlock *ExitBlock = BasicBlock::Create(parentFunction);

    // 如果当前块没有终止指令，则插入跳转到 EntryBlock 的指令
    if (!hasTerminator)
    {
        JumpInst::Create(EntryBlock, current_basic_block);
        hasTerminator = true;
    }

    // 设置当前块为 EntryBlock，并翻译条件表达式
    current_basic_block = EntryBlock;
    Value *cond_value = trans_lor_shortcut(whilestmt->Cond, BodyBlock, ExitBlock);

    // 设置当前块为 BodyBlock，并翻译循环体
    current_basic_block = BodyBlock;
    hasTerminator = false;
    trans_stmt(whilestmt->WhileBody, EntryBlock, ExitBlock);

    // 如果当前块没有终止指令，则插入跳转到 EntryBlock 的指令
    if (!hasTerminator)
    {
        JumpInst::Create(EntryBlock, current_basic_block);
        hasTerminator = true;
    }

    // 设置当前块为 ExitBlock，表示循环结束部分
    current_basic_block = ExitBlock;
    hasTerminator = false;
}


void trans_ifstmt(IfStmt_ptr ifstmt, BasicBlock *entry, BasicBlock *exit)
{
    BasicBlock *True = BasicBlock::Create(current_basic_block->getParent());
    BasicBlock *False = ifstmt->ElseBody ? BasicBlock::Create(current_basic_block->getParent()) : nullptr;
    BasicBlock *Exit_If = BasicBlock::Create(current_basic_block->getParent());

    // 开始翻译
    Value *res_value = trans_lor_shortcut(ifstmt->Cond, True, ifstmt->ElseBody ? False : Exit_If);

    trans_stmt_block(True, ifstmt->IfBody, Exit_If, entry, exit);

    if (ifstmt->ElseBody)
    {
        trans_stmt_block(False, ifstmt->ElseBody, Exit_If, entry, exit);
    }

    current_basic_block = Exit_If;
    hasTerminator = false;
}

void trans_stmt_block(BasicBlock *block, Stmt_ptr stmt, BasicBlock *exit, BasicBlock *entry, BasicBlock *exit_stmt)
{
    current_basic_block = block;
    hasTerminator = false;
    trans_stmt(stmt, entry, exit_stmt);
    if (!hasTerminator)
    {
        JumpInst::Create(exit, current_basic_block);
        hasTerminator = true;
    }
}

void trans_stmt(Stmt_ptr stmt, BasicBlock *entry, BasicBlock *exit)
{
    if (auto *expstmt = stmt->as<ExpStmt_ptr>())
    {
        if (expstmt->Expr != nullptr)
            trans_lor(expstmt->Expr);
    }
    else if (auto *contistmt = stmt->as<ContiStmt_ptr>()) {
        if (!hasTerminator)
        {
            JumpInst *JFE = JumpInst::Create(entry, current_basic_block);
            hasTerminator = true;
        }
    }
    else if (auto *blockinstmt = stmt->as<BlockInStmt_ptr>()) {
        push_symbol_table_();
        trans_block(blockinstmt->Block, entry, exit);
        pop_symbol_table_();
    }
    else if (auto *lvalstmt = stmt->as<LValStmt_ptr>())
    {
        StoreInst *ResStore = StoreInst::Create(trans_lor(lvalstmt->Expr), trans_lval_noload(lvalstmt->LVal), current_basic_block);
    }
    else if (auto *breakstmt = stmt->as<BreakStmt_ptr>())
    {
        if (!hasTerminator)
        {
            JumpInst *JFE = JumpInst::Create(exit, current_basic_block);
            hasTerminator = true;
        }
    }
    else if (auto *ifstmt = stmt->as<IfStmt_ptr>())
        trans_ifstmt(ifstmt, entry, exit);
    else if (auto *whilestmt = stmt->as<WhileStmt_ptr>())
        trans_whilestmt(whilestmt);
    else if (auto *retstmt = stmt->as<RetStmt_ptr>())
        trans_retstmt(retstmt);
}

void trans_block(Block_ptr block, BasicBlock *entry, BasicBlock *exit)
{
    for (auto *blockitem = block->BlockItemHead; blockitem != nullptr; blockitem = blockitem->NextBlockItem)
    {
        if (auto *valdecitem = blockitem->as<ValDecItem_ptr>())
        {
            for (auto *valueDeclaration = valdecitem->ValDec;
                 valueDeclaration != nullptr;
                 valueDeclaration = valueDeclaration->NextValDec)
            {
                trans_valdec(valueDeclaration);
            }
        }
        else if (auto *stmtitem = blockitem->as<StmtItem_ptr>())
        {
            trans_stmt(stmtitem->Stmt, entry, exit);
        }
    }
}

void trans_fundec(FunDef_ptr fundef)
{
    std::vector<VarType_ptr> params;
    std::vector<Type *> Params_lab3;
    trans_params(fundef, params, Params_lab3);

    // 设置返回类型
    Type *ret_type = (fundef->RType == Ret_Int) ? Type::getIntegerTy() : Type::getUnitTy();

    BasicBlock *Entry;
    Function *F;
    if (fundef->FunID != "main")
    {
        FunctionType *FT = FunctionType::get(ret_type, Params_lab3);
        F = Function::Create(FT, false, fundef->FunID, Module_main.get());
        Entry = BasicBlock::Create(F);
    }
    else
    {
        F = Function_main;
        Entry = Entry_main;
    }

    auto *function = new FuncType(fundef->FunID, fundef->RType, params, F);
    add_func_to_table_(function);

    push_symbol_table_();
    current_basic_block = Entry;
    hasTerminator = false;

    int count = 0;
    for (auto *ele : params)
    {
        handle_param(ele, count);
        count++;
    }
    trans_block(fundef->Block, nullptr, nullptr);
    pop_symbol_table_();
}

void trans_params(FunDef_ptr fundef, std::vector<VarType_ptr>& params, std::vector<Type *>& Params_)
{
    if (fundef->FunFParam != nullptr)
    {
        auto *funfparam = fundef->FunFParam;
        while (funfparam != nullptr)
        {
            // 记录参数信息
            auto *param = trans_funfparam(funfparam);
            if (param != nullptr)
                params.push_back(param);
            if (param->Dimensions != 0) // 记录形参type
                Params_.push_back(PointerType::get(Type::getIntegerTy()));
            else
                Params_.push_back(Type::getIntegerTy());
            funfparam = funfparam->NextFunFParam;
        }
    }
}

void handle_param(VarType_ptr ele, int count)
{
    Value *val_ptr = nullptr;
    if (ele->Dimensions == 0)
    {
        AllocaInst *Val_Addr = AllocaInst::Create(Type::getIntegerTy(), 1, current_basic_block);

        StoreInst *NArgStore = StoreInst::Create(current_basic_block->getParent()->getArg(count), Val_Addr, current_basic_block);
        val_ptr = Val_Addr;
    }
    auto *param = new VarType(ele->ValID, ele->Dimensions, ele->DimensionSizes, val_ptr, count); 
    add_var_to_table_(param);
}

void trans_compunit(CompUnit_ptr compunit)
{

    // lab3要先对全局变量翻译，然后翻译函数
    std::vector<CompUnitFunDec_ptr> functiondec_vec;

    for (auto *curr_compunit = compunit; curr_compunit != nullptr; curr_compunit = curr_compunit->NextCompUnit)
    {
        if (auto *compunit_valdec = curr_compunit->as<CompUnitValDec_ptr>())
        {
            for (auto *valdec = compunit_valdec->ValDec;
                 valdec != nullptr;
                 valdec = valdec->NextValDec)
            {
                trans_valdec_global(valdec);
            }
        }
        else if (auto *compunit_fundec = curr_compunit->as<CompUnitFunDec_ptr>())
        {
            functiondec_vec.emplace_back(compunit_fundec);
        }
    }
    // 函数翻译
    for (auto compunit_fundec : functiondec_vec)
    {
        trans_fundec(compunit_fundec->FunDef);
    }
}

void trans_root(Root_ptr root, std::ostream &out)
{
    push_symbol_table_();
    
    // 加入运行时函数到最外层作用域之中
    auto scope = symbol_table_func_.begin();

    // getint
    FunctionType *FT_getint = FunctionType::get(Type::getIntegerTy(), {});
    Function *F_getint = Function::Create(FT_getint, true, "getint", Module_main.get());
    auto fp = new FuncType("getint", Ret_Int, std::vector<VarType_ptr>(), F_getint);
    scope->insert(std::pair<std::string, FuncType_ptr>("getint",fp));
    // getch
    FunctionType *FT_getch = FunctionType::get(Type::getIntegerTy(), {});
    Function *F_getch = Function::Create(FT_getch, true, "getch", Module_main.get());
    fp = new FuncType("getch", Ret_Int, std::vector<VarType_ptr>(), F_getch);
    scope->insert(std::pair<std::string, FuncType_ptr>("getch",fp));
    
    // getarray
    FunctionType *FT_getarray = FunctionType::get(Type::getIntegerTy(), {PointerType::get(Type::getIntegerTy())});
    Function *F_getarray = Function::Create(FT_getarray, true, "getarray", Module_main.get());
    std::vector<VarType_ptr> params_getarray;
    auto param_getarray = new VarType("_", 1, std::vector({0}));
    fp = new FuncType("getarray", Ret_Int, params_getarray, F_getarray);
    scope->insert(std::pair<std::string, FuncType_ptr>("getarray",fp));
                                                       
    // putint
    FunctionType *FT_putint = FunctionType::get(Type::getUnitTy(), {Type::getIntegerTy()});
    Function *F_putint = Function::Create(FT_putint, true, "putint", Module_main.get());
    std::vector<VarType_ptr> params_putint;
    auto param_putint = new VarType("__", 0, {});
    params_putint.push_back(param_putint);
    fp = new FuncType("putint", Ret_Void, params_putint, F_putint);
    scope->insert(std::pair<std::string, FuncType_ptr>("putint",fp));

    // putch
    FunctionType *FT_putch = FunctionType::get(Type::getUnitTy(), {Type::getIntegerTy()});
    Function *F_putch = Function::Create(FT_putch, true, "putch", Module_main.get());
    std::vector<VarType_ptr> params_putch;
    auto param_putch = new VarType("_", 0, {}); // 这里因为不会编译putint的函数定义，所以形参叫什么都无所谓
    params_putch.push_back(param_putch);
    fp = new FuncType("putch", Ret_Void, params_putch, F_putch);
    scope->insert(std::pair<std::string, FuncType_ptr>("putch",fp));

    // putarray
    FunctionType *FT_putarray = FunctionType::get(Type::getUnitTy(), {Type::getIntegerTy(), PointerType::get(Type::getIntegerTy())});
    Function *F_putarray = Function::Create(FT_putarray, true, "putarray", Module_main.get());
    std::vector<VarType_ptr> params_putarray;
    auto param1_putarray = new VarType("_", 0, {});
    auto param2_putarray = new VarType("_", 1, std::vector({0}));
    params_putarray.push_back(param1_putarray);
    params_putarray.push_back(param2_putarray);
    fp = new FuncType("putarray", Ret_Void, params_putarray, F_putarray);
    scope->insert(std::pair<std::string, FuncType_ptr>("putarray",fp));

    trans_compunit(root->CompUnitHead);
    Module_main->print(out, false);
}