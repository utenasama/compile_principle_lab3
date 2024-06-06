#pragma once
#include "inst/translate.h"

extern bool error;
std::vector<std::map<std::string, VarType_ptr>> symbol_table_var_; 
std::vector<std::map<std::string, FuncType_ptr>> symbol_table_func_;
//生成module
auto Module_main = std::make_unique<Module>();
Type *IntegerType = Type::getIntegerTy();
Type *UnitType = Type::getUnitTy();
PointerType *PtrIntType = PointerType::get(IntegerType);
FunctionType *FT_main = FunctionType::get(IntegerType, {});
Function *F_main = Function::Create(FT_main, false, "main", Module_main.get());
BasicBlock *Entry_main = BasicBlock::Create(F_main);
BasicBlock *current_basic_block;

//用于记录if while的数量，方便block命名
int if_count = 0;
int while_count = 0;
int block_count = 0;
//用于记录if while中的lor/land操作，方便shortcut block命名
int lor_count = 0;
int land_count = 0;
bool cur_bb_has_term = false;

void push_symbol_table_()  //加入一个新的符号表
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
    if (symbol_table_var_.begin() == symbol_table_var_.end())
    {
        error = true;
        fmt::print("Error in add_var_to_table, no scopes\n");
        return;
    }

    auto scope = symbol_table_var_.end() - 1; // 最后一个scope
    //找到了重复的变量名
    if (scope->find(variableptr->ValID) != scope->end())
    {
        error = true;
        fmt::print("Error! Redefination of VarType \"{}\"\n", variableptr->ValID);
        return;
    }else{
        scope->insert(std::pair<std::string, VarType_ptr>(variableptr->ValID, variableptr));
    }
}

void add_func_to_table_(FuncType_ptr funcptr)
{
    if (symbol_table_func_.begin() == symbol_table_func_.end())
    {
        error = true;
        fmt::print("Error in add_func_to_table, no scopes\n");
        return;
    }
    // 函数名不可重复
    auto iter = symbol_table_func_.end() - 1;
    for (auto iter = symbol_table_func_.end() - 1; iter >= symbol_table_func_.begin(); iter--)
    {
        if (iter->find(funcptr->FuncID) != iter->end())
        {
            error = true;
            fmt::print("Error! Redefination of FuncType \"{}\"\n", funcptr->FuncID);
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

Value* trans_funrparam(FunRParam_ptr funrparam)
{
    return trans_lor(funrparam->FirstParam);
}

Value* trans_pmn_unaexpr(PMNUnaExpr_ptr pmn_unaexp)
{

    switch(pmn_unaexp->OP)
    {
        case OP_Lnot:
        {
            Value* ret_value = trans_unaexp(pmn_unaexp->Operand);
            return BinaryInst::CreateEq(ret_value, ConstantInt::Create(0), IntegerType, current_basic_block);
            break;
        }
        case OP_Neg:
        {
            Value* ret_value = trans_unaexp(pmn_unaexp->Operand);
            return BinaryInst::CreateSub(ConstantInt::Create(0), ret_value, IntegerType, current_basic_block);
            break;
        }
        case OP_Pos:
        {
            return trans_unaexp(pmn_unaexp->Operand);
            break;
        }
    }
}
//TODO:
Value* trans_func_unaexpr(FunUnaExpr_ptr func_unaexpr)
{
    std::vector<Value*> args;
    //先检查函数是否定义，再检查参数
    for(std::vector<std::map<std::string, FuncType_ptr>>::iterator iter = symbol_table_func_.end()-1; 
        iter >= symbol_table_func_.begin(); iter--)
    {
        auto map_iter = iter->find(func_unaexpr->FunID);
        if(map_iter != iter->end())
        {   //如果找到了这个函数, 检查参数
            auto *funrparam = func_unaexpr->FunRParam;
            auto *funcptr = map_iter->second;
            for(auto *funfparam : funcptr->FParams) //依次翻译实参
            {
                args.push_back(trans_funrparam(funrparam));
                funrparam = funrparam->NextFunRParam;
            }

            //生成一条Call语句
            CallInst *Call = CallInst::Create(funcptr->F, args, current_basic_block);
            return Call;
        }

        //没有找到
        if(iter == symbol_table_func_.begin())
        {
            error = true;
            fmt::print("Error in trans_func_unaexpr, \"{}\" not defined\n", func_unaexpr->FunID);
            return nullptr;
        }
    }
    fmt::print("Error in trans_func_unaexpr, should not reach here\n");
    return nullptr;
}

Value* trans_integer(Integer_ptr integer)
{
    return ConstantInt::Create(integer->Val);
}
//TODO:
Value* trans_lval(LVal_ptr lval)
{
    //检查变量是否已经定义，以及维数是否正确
    int dimensions = 0;
    std::vector<Value*> Indices;
    if(lval->ExpArr != nullptr)
    {
        auto *exparr = lval->ExpArr;
        while(exparr != nullptr)
        {
            Value* dim = trans_exparr(exparr);
            dimensions += 1;

            Indices.push_back(dim);
            exparr = exparr->NextExpArr;
        }
    }
    
    for(std::vector<std::map<std::string, VarType_ptr>>::iterator iter = symbol_table_var_.end()-1; 
        iter >= symbol_table_var_.begin(); iter--)
    {
        auto map_iter = iter->find(lval->ID);
        if(map_iter != iter->end())
        {   //如果找到了这个变量名
            auto *valptr = map_iter->second;

            //对于没有给定的维数，使用0，比如int a[2][3], a[1]的地址就是a[1][0]的地址
            bool need_load = true;
            while(dimensions < valptr->Dimensions)
            {
                need_load = false;
                Indices.push_back(ConstantInt::Create(0));
                dimensions++;
            }
            std::vector<std::optional<std::size_t>> Bounds = valptr->Bounds;

            if(dimensions != 0){
                OffsetInst *Offset;

                if(valptr->Val_Ptr == nullptr)  //Value是nullptr，说明这是一个形参，需要用getarg获得实参
                    Offset = OffsetInst::Create(IntegerType, current_basic_block->getParent()->getArg(valptr->Param_No), Indices, valptr->Bounds, current_basic_block);
                else
                    Offset = OffsetInst::Create(IntegerType, valptr->Val_Ptr, Indices, valptr->Bounds,current_basic_block);
                
                if(!need_load)
                    return Offset;
                else
                    return LoadInst::Create(Offset, current_basic_block);
            }
            else{
                return LoadInst::Create(valptr->Val_Ptr, current_basic_block);
            }
        }

        //没有找到
        if(iter == symbol_table_var_.begin())
        {
            error = true;
            fmt::print("Error in trans_lval, \"{}\" not defined\n", lval->ID);
            return nullptr;
        }
    }
    fmt::print("Error in trans_lval, should not reach here\n");
    return nullptr;
}
//TODO
Value* trans_lval_noload(LVal_ptr lval)
{
    //检查变量是否已经定义，以及维数是否正确
    int dimensions = 0;
    std::vector<Value*> Indices;
    if(lval->ExpArr != nullptr)
    {
        auto *exparr = lval->ExpArr;
        while(exparr != nullptr)
        {
            Value* dim = trans_exparr(exparr);
            dimensions += 1;

            Indices.push_back(dim);
            exparr = exparr->NextExpArr;
        }
    }
    
    for(std::vector<std::map<std::string, VarType_ptr>>::iterator iter = symbol_table_var_.end()-1; 
        iter >= symbol_table_var_.begin(); iter--)
    {
        auto map_iter = iter->find(lval->ID);
        if(map_iter != iter->end())
        {   //如果找到了这个变量名
            auto *valptr = map_iter->second;


            while(dimensions < valptr->Dimensions)
            {
                Indices.push_back(ConstantInt::Create(0));
                dimensions++;
            }
            std::vector<std::optional<std::size_t>> Bounds = valptr->Bounds;

            if(dimensions != 0){
                OffsetInst *Offset;
                if(valptr->Val_Ptr == nullptr)  
                    Offset = OffsetInst::Create(IntegerType, current_basic_block->getParent()->getArg(valptr->Param_No), Indices, valptr->Bounds, current_basic_block);
                else
                    Offset = OffsetInst::Create(IntegerType, valptr->Val_Ptr, Indices, valptr->Bounds,current_basic_block);
                
                return Offset;
            }
            else{
                return valptr->Val_Ptr;
            }
        }


        if(iter == symbol_table_var_.begin())
        {
            error = true;
            fmt::print("Error in trans_lval, \"{}\" not defined\n", lval->ID);
            return nullptr;
        }
    }
    fmt::print("Error in trans_lval, should not reach here\n");
    return nullptr;
}

Value* trans_prim_unaexpr(PrimExpr_ptr primexp)
{
    if(auto *lpexprp = primexp->as<LpExprRp_ptr>())
        return trans_lor(lpexprp->Operand);
    else if(auto *integer = primexp->as<Integer_ptr>())
        return trans_integer(integer);
    else if(auto *lval = primexp->as<LVal_ptr>())
        return trans_lval(lval);   
}

Value* trans_unaexp(UnaExpr_ptr unaexp)
{
    if(auto *pmn_unaexpr = unaexp->as<PMNUnaExpr_ptr>())
        return trans_pmn_unaexpr(pmn_unaexpr);
    else if(auto *func_unaexpr = unaexp->as<FunUnaExpr_ptr>())
        return trans_func_unaexpr(func_unaexpr);
    else return trans_prim_unaexpr(static_cast<PrimExpr_ptr>(unaexp));

}

Value* trans_mulexp(MulExpr_ptr mulexp)
{
    switch(mulexp->OP) {
        case OP_None:
        {
            return trans_unaexp(mulexp->UnaExpr);
        }

        case OP_Mul:
        {
            return BinaryInst::CreateMul(
                trans_mulexp(mulexp->Operand), 
                trans_unaexp(mulexp->UnaExpr), 
                IntegerType, 
                current_basic_block
            );
        }
        case OP_Div:
        {
            return BinaryInst::CreateDiv(
                trans_mulexp(mulexp->Operand), 
                trans_unaexp(mulexp->UnaExpr),
                IntegerType,
                current_basic_block
            );
        }
        case OP_Mod:
        {
            return BinaryInst::CreateMod(
                trans_mulexp(mulexp->Operand), 
                trans_unaexp(mulexp->UnaExpr), 
                IntegerType, 
                current_basic_block
            );
        }
    }
}

Value* trans_addexp(AddExpr_ptr addexp)
{
    switch(addexp->OP) {
        case OP_None:
        {
            return trans_mulexp(addexp->MulExpr);
        }
        case OP_Add:
        {
            return BinaryInst::CreateAdd(
                trans_addexp(addexp->Operand), 
                trans_mulexp(addexp->MulExpr), 
                IntegerType, 
                current_basic_block
            );
        }
        case OP_Sub:
        {
            return BinaryInst::CreateSub(
                trans_addexp(addexp->Operand), 
                trans_mulexp(addexp->MulExpr), 
                IntegerType, 
                current_basic_block
            );
        }
    }
}

Value* trans_exparr(ExpArr_ptr exparr)
{
    return trans_lor(exparr->Expr);
}


//打印初始值
Value* trans_initval(LOr_ptr initval)
{
    return trans_lor(initval);
}

//具体翻译变量声明
//TODO:
void trans_valdec(ValDec_ptr valdec)
{
    int dimensions = 0;
    int element_len = 1;
    std::vector<int> dim_vec;
    if(valdec->ExpArr != nullptr)
    {
        auto *exparr = valdec->ExpArr;
        while(exparr != nullptr)
        {
            auto *unaexp = exparr->Expr->LAnd->Eq->Rel->Expr->MulExpr->UnaExpr;
            auto *primexp = static_cast<PrimExpr_ptr>(unaexp);
            auto *integer = primexp->as<Integer_ptr>();
            int dim = integer->Val;
            dimensions += 1;
            dim_vec.push_back(dim);
            exparr = exparr->NextExpArr;
            element_len *= dim;
        }
    }

    //变量alloca指令
    AllocaInst *ValAddr = AllocaInst::Create(IntegerType, element_len, current_basic_block);

    if(valdec->InitVal != nullptr)
    {
        if(valdec->ExpArr != nullptr)  //lab为了简化，不支持数组初始化
        {
            error = true;
            fmt::print("error in initialization: array can not be initialized!\n");
        }
        Value *init_val = trans_initval(valdec->InitVal);
        StoreInst *ValInit = StoreInst::Create(init_val, ValAddr, current_basic_block);
    }

    auto *variable = new VarType(valdec->ID, dimensions, dim_vec, ValAddr);
    add_var_to_table_(variable);
}

//具体翻译变量声明
//TODO
void trans_valdec_global(ValDec_ptr valdec)
{

    int dimensions = 0;
    int element_len = 1;
    std::vector<int> dim_vec;
    if(valdec->ExpArr != nullptr)
    {
        auto *exparr = valdec->ExpArr;
        while(exparr != nullptr)
        {
            auto *unaexp = exparr->Expr->LAnd->Eq->Rel->Expr->MulExpr->UnaExpr;
            auto *primexp = static_cast<PrimExpr_ptr>(unaexp);
            auto *integer = primexp->as<Integer_ptr>();
            int dim = integer->Val;
            dimensions += 1;
            dim_vec.push_back(dim);
            exparr = exparr->NextExpArr;
            element_len *= dim;
        }
    }

    //变量alloca指令

    auto ValAddr = GlobalVariable::Create(IntegerType, element_len, false, valdec->ID, Module_main.get());  
    if(valdec->InitVal != nullptr)
    {
        if(valdec->ExpArr != nullptr)  //lab为了简化，不支持数组初始化
        {
            error = true;
            fmt::print("error in initialization: array can not be initialized!\n");
        }
        Value *init_val = trans_initval(valdec->InitVal);
        //所有的全局变量赋值语句，都放到main中
        StoreInst *ValInit = StoreInst::Create(init_val, ValAddr, Entry_main);
    }

    auto *variable = new VarType(valdec->ID, dimensions, dim_vec, ValAddr);
    add_var_to_table_(variable);
}


VarType_ptr trans_funfparam(FunFParam_ptr funfparam)
{
    int dimensionCount = 0;
    std::vector<int> dimensionSizes;

    auto extractDimensionSize = [](ExpArr_ptr expArr) {
        auto *unaryExpr = expArr->Expr->LAnd->Eq->Rel->Expr->MulExpr->UnaExpr;
        auto *primaryExpr = static_cast<PrimExpr_ptr>(unaryExpr);
        auto *integerExpr = primaryExpr->as<Integer_ptr>();
        return integerExpr->Val;
    };

    // 如果形式参数是一个数组，需要检查维度
    if(funfparam->IsArr)
    {
        dimensionCount++;    // 如果形式参数是数组，第一维是空的，且在语法分析时不会被视为一个 ExpArr
        dimensionSizes.push_back(0);
        if(funfparam->ExpArr != nullptr)
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


void trans_valdecitem(ValDecItem_ptr valdecitem)
{
    for(auto *valueDeclaration = valdecitem->ValDec; 
        valueDeclaration != nullptr; 
        valueDeclaration = valueDeclaration->NextValDec)
    {
        trans_valdec(valueDeclaration);
    }
}

void trans_stmtitem(StmtItem_ptr stmtitem, BasicBlock *entry, BasicBlock *exit)
{
    trans_stmt(stmtitem->Stmt, entry, exit);
}

void trans_lvalstmt(LValStmt_ptr lvalstmt)
{
   StoreInst *ResStore = StoreInst::Create(
                            trans_lor(lvalstmt->Expr), 
                            trans_lval_noload(lvalstmt->LVal), 
                            current_basic_block
                        );
}

void trans_retstmt(RetStmt_ptr retstmt)
{

    Value* returnValue;
    if(retstmt->Expr != nullptr)
    {
        returnValue = trans_lor(retstmt->Expr);
    }else
    {
        returnValue = ConstantUnit::Create();
    }

    RetInst *returnInstruction = RetInst::Create(returnValue, current_basic_block);
    cur_bb_has_term = true;
}

void trans_expstmt(ExpStmt_ptr expstmt)
{
    if(expstmt->Expr != nullptr)
        trans_lor(expstmt->Expr);
}

void trans_breakstmt(BreakStmt_ptr breakstmt, BasicBlock *exit)
{
    if(!cur_bb_has_term){
        JumpInst *JFE = JumpInst::Create(exit, current_basic_block);
        cur_bb_has_term = true;
    }
}

void trans_contistmt(ContiStmt_ptr contistmt, BasicBlock *entry)
{
    if(!cur_bb_has_term){
        JumpInst *JFE = JumpInst::Create(entry, current_basic_block);
        cur_bb_has_term = true;
    }
}

void trans_blockinstmt(BlockInStmt_ptr blockinstmt, BasicBlock *entry, BasicBlock *exit)
{
    push_symbol_table_();
    trans_block(blockinstmt->Block, entry, exit);
    pop_symbol_table_();
}



Value* trans_lor(LOr_ptr lor)
{
    if(lor->Operand != nullptr)
    {
        return BinaryInst::CreateOr(
            trans_land(lor->LAnd), 
            trans_lor(lor->Operand), 
            IntegerType, 
            current_basic_block
        );
    }else{
        return trans_land(lor->LAnd);
    }
}


Value* trans_land(LAnd_ptr land)
{
    if(land->Operand != nullptr)
    {
        return BinaryInst::CreateAnd(
            trans_eq(land->Eq), 
            trans_land(land->Operand), 
            IntegerType, 
            current_basic_block
        );
    }else{
        return trans_eq(land->Eq);
    }
}


//shortcut版本 if while
Value* trans_lor_shortcut(LOr_ptr lor, BasicBlock *true_bb, BasicBlock *false_bb)
{
    if(lor->Operand != nullptr)
    {
        BasicBlock *lor_con1_false_bb = BasicBlock::Create(current_basic_block->getParent());
        Value* res_val1 = trans_land_shortcut(lor->LAnd, true_bb, lor_con1_false_bb);
        current_basic_block = lor_con1_false_bb;
        // lor_count++;
        // block_count++;
        // cur_bb_has_term = false;
        return trans_lor_shortcut(lor->Operand, true_bb, false_bb);
    }else{
        return trans_land_shortcut(lor->LAnd, true_bb, false_bb);
    }
}


Value* trans_land_shortcut(LAnd_ptr land, BasicBlock *true_bb, BasicBlock *false_bb)
{
    if(land->Operand != nullptr)
    {
        BasicBlock *land_con1_true_bb = BasicBlock::Create(current_basic_block->getParent());
        Value* res_val1 = trans_eq(land->Eq);
        BranchInst *Br = BranchInst::Create(land_con1_true_bb, false_bb, res_val1, current_basic_block);

        current_basic_block = land_con1_true_bb;
        // land_count++;

        // cur_bb_has_term = false;
        // block_count++;

        return trans_land_shortcut(land->Operand, true_bb, false_bb);
    }else{
        if(land->Eq->Operand == nullptr && land->Eq->Rel->Operand == nullptr &&
            land->Eq->Rel->Expr->Operand == nullptr && land->Eq->Rel->Expr->MulExpr->Operand == nullptr)
        {
            if(auto *lpexprp = land->Eq->Rel->Expr->MulExpr->UnaExpr->as<LpExprRp_ptr>())
                return trans_lor_shortcut(lpexprp->Operand, true_bb, false_bb);
        }

        Value* res_value = trans_eq(land->Eq);
        BranchInst *Br = BranchInst::Create(true_bb, false_bb, res_value, current_basic_block);
        return res_value;
    }
}



Value* trans_eq(Eq_ptr eq)
{
    if(eq->Operand != nullptr)
    {
        switch(eq->OP)
        {
            case OP_Eq:
                return BinaryInst::CreateEq(
                    trans_eq(eq->Operand), 
                    trans_rel(eq->Rel), 
                    IntegerType, 
                    current_basic_block
                );
                break;
            case OP_Ne:
                return BinaryInst::CreateNe(
                    trans_eq(eq->Operand), 
                    trans_rel(eq->Rel), 
                    IntegerType, 
                    current_basic_block
                );
                break;
        }
    }else
        return trans_rel(eq->Rel);
}

Value* trans_rel(Rel_ptr rel)
{
    if(rel->Operand != nullptr)
    {
        switch(rel->OP)
        {
            case OP_Lt:
                return BinaryInst::CreateLt(
                    trans_rel(rel->Operand), 
                    trans_addexp(rel->Expr), 
                    IntegerType, 
                    current_basic_block
                );
                break;
            case OP_Gt:
                return BinaryInst::CreateGt(
                    trans_rel(rel->Operand), 
                    trans_addexp(rel->Expr), 
                    IntegerType, 
                    current_basic_block
                );
                break;
            case OP_Le:
                return BinaryInst::CreateLe(
                    trans_rel(rel->Operand), 
                    trans_addexp(rel->Expr), 
                    IntegerType, 
                    current_basic_block
                );
                break;
            case OP_Ge:
                return BinaryInst::CreateGe(
                    trans_rel(rel->Operand), 
                    trans_addexp(rel->Expr), 
                    IntegerType, 
                    current_basic_block
                );
                break;
            default:
                error = true;
                fmt::print("Error in trans_rel, operand should be Lt / Gt / Le / Ge!!\n");
                return nullptr;
        }
    }else{
        return trans_addexp(rel->Expr);
    }
}
//TODO
void trans_whilestmt(WhileStmt_ptr whilestmt)
{

    BasicBlock *Body = BasicBlock::Create(current_basic_block->getParent());
    BasicBlock *Entry = BasicBlock::Create(current_basic_block->getParent());
    BasicBlock *Exit = BasicBlock::Create(current_basic_block->getParent());

    //插一条jump到当前block 跳转到entry
    if(!cur_bb_has_term){
        JumpInst *JTE = JumpInst::Create(Entry, current_basic_block);
        cur_bb_has_term = true;
    }

    //下面开始翻译
    current_basic_block = Entry;
    Value* res_value = trans_lor_shortcut(whilestmt->Cond, Body, Exit);  //如果不等于0，就是true

    current_basic_block = Body;
    cur_bb_has_term = false;

    trans_stmt(whilestmt->WhileBody, Entry, Exit);
    if(!cur_bb_has_term)
    {
        JumpInst *JTE2 = JumpInst::Create(Entry, current_basic_block);
        cur_bb_has_term = true;
    }

    current_basic_block = Exit;
    cur_bb_has_term = false;

}
//TODO
void trans_ifstmt(IfStmt_ptr ifstmt, BasicBlock *entry, BasicBlock *exit)
{
    
    BasicBlock *True = BasicBlock::Create(current_basic_block->getParent());
    BasicBlock *False = nullptr;
    if(ifstmt->ElseBody != nullptr){
        False = BasicBlock::Create(current_basic_block->getParent());
    }
    BasicBlock *Exit_If = BasicBlock::Create(current_basic_block->getParent());

    //下面开始翻译
    if(ifstmt->ElseBody != nullptr)
        Value* res_value = trans_lor_shortcut(ifstmt->Cond, True, False);
    else
        Value* res_value = trans_lor_shortcut(ifstmt->Cond, True, Exit_If);
    if(ifstmt->ElseBody != nullptr)
    {   
        current_basic_block = True;
        cur_bb_has_term = false;
        trans_stmt(ifstmt->IfBody, entry, exit);
        if(!cur_bb_has_term){
            JumpInst::Create(Exit_If, current_basic_block);
            cur_bb_has_term = true;
        }
        current_basic_block = False;
        cur_bb_has_term = false;
        trans_stmt(ifstmt->ElseBody, entry, exit);
    }else{
        current_basic_block = True;
        cur_bb_has_term = false;
        trans_stmt(ifstmt->IfBody, entry, exit);
    }
    if(!cur_bb_has_term){
        JumpInst::Create(Exit_If, current_basic_block);
        cur_bb_has_term = true;
    }
    current_basic_block = Exit_If;
    cur_bb_has_term = false;
}


void trans_stmt(Stmt_ptr stmt, BasicBlock *entry, BasicBlock *exit)
{
    if(auto *expstmt = stmt->as<ExpStmt_ptr>())
        trans_expstmt(expstmt);
    else if(auto *contistmt = stmt->as<ContiStmt_ptr>())
        trans_contistmt(contistmt, entry);
    else if(auto *blockinstmt = stmt->as<BlockInStmt_ptr>())
        trans_blockinstmt(blockinstmt, entry, exit);
    else if(auto *ifstmt = stmt->as<IfStmt_ptr>())
        trans_ifstmt(ifstmt, entry, exit);
    else if(auto *whilestmt = stmt->as<WhileStmt_ptr>())
        trans_whilestmt(whilestmt);
    else if(auto *lvalstmt = stmt->as<LValStmt_ptr>())
        trans_lvalstmt(lvalstmt);
    else if(auto *retstmt = stmt->as<RetStmt_ptr>())
        trans_retstmt(retstmt);
    else if(auto *breakstmt = stmt->as<BreakStmt_ptr>())
        trans_breakstmt(breakstmt, exit);
}

void trans_blockitem(BlockItem_ptr blockitem, BasicBlock *entry, BasicBlock *exit)
{
    if(auto *valdecitem = blockitem->as<ValDecItem_ptr>())
        trans_valdecitem(valdecitem);
    else if(auto *stmtitem = blockitem->as<StmtItem_ptr>())
        trans_stmtitem(stmtitem, entry, exit);
}

void trans_block(Block_ptr block, BasicBlock *entry, BasicBlock *exit)
{  
    for(auto *blockitem = block->BlockItemHead; blockitem != nullptr; blockitem = blockitem->NextBlockItem)
    {
        trans_blockitem(blockitem, entry, exit);
    }
}

//TODO
void trans_fundec(FunDef_ptr fundef)
{
    std::vector<VarType_ptr> params;
    std::vector<Type *> Params_lab3;
    if(fundef->FunFParam != nullptr)
    {
        auto *funfparam = fundef->FunFParam;
        while(funfparam != nullptr)
        {
            //先记录参数信息
            auto *param = trans_funfparam(funfparam);
            if(param != nullptr)
                params.push_back(param);
            if(param->Dimensions != 0)    //记录形参type
                Params_lab3.push_back(PtrIntType);
            else
                Params_lab3.push_back(IntegerType);
            funfparam = funfparam->NextFunFParam;
        }
    }

    //设置返回类型Type
    Type *ret_type;
    if(fundef->RType == Ret_Int)
        ret_type = IntegerType;
    else
        ret_type = UnitType;

    //生成函数以及对应block
    BasicBlock *Entry;
    Function *F;
    if(fundef->FunID != "main"){
        FunctionType *FT = FunctionType::get(ret_type, Params_lab3);
        F = Function::Create(FT, false, fundef->FunID, Module_main.get());
        Entry = BasicBlock::Create(F);
    }else{
        F = F_main;
        Entry = Entry_main;
    }

    auto *function = new FuncType(fundef->FunID, fundef->RType, params, F);
    add_func_to_table_(function);

    //新加入一个scope，也就是函数的作用域
    push_symbol_table_();
    current_basic_block = Entry;
    cur_bb_has_term = false;
    block_count++;
    //函数的参数属于自己的那个作用域，顺便为所有形参加上名字
    int count = 0;
    for(auto *ele : params)
    {
        Value *val_ptr = nullptr;
        if(ele->Dimensions == 0)
        {
            AllocaInst *Val_Addr = AllocaInst::Create(IntegerType, 1, current_basic_block);

            StoreInst *NArgStore = StoreInst::Create(current_basic_block->getParent()->getArg(count), Val_Addr, current_basic_block);
            val_ptr = Val_Addr;           
        }
        auto *param = new VarType(ele->ValID, ele->Dimensions, ele->DimensionSizes,val_ptr, count); //这里改成拷贝构造函数可能更好
        add_var_to_table_(param);

        count++;
    }
    trans_block(fundef->Block, nullptr, nullptr);
    pop_symbol_table_();
}



void trans_compunit_valdec(CompUnitValDec_ptr compunit_valdec)
{
    for(auto *valdec = compunit_valdec->ValDec; 
        valdec != nullptr; 
        valdec = valdec->NextValDec)
    {
        trans_valdec_global(valdec);
    }
}


void trans_compunit_fundec(CompUnitFunDec_ptr compunit_fundec)
{
    trans_fundec(compunit_fundec->FunDef);
}



void trans_compunit(CompUnit_ptr compunit)
{

    //lab3要先对全局变量翻译，然后翻译函数
    std::vector<CompUnitFunDec_ptr> functiondec_vec;

    for(auto *curr_compunit = compunit; curr_compunit != nullptr; curr_compunit = curr_compunit->NextCompUnit)
    {
        if(auto *compunit_valdec = curr_compunit->as<CompUnitValDec_ptr>())
        {
            trans_compunit_valdec(compunit_valdec);
        }
        else if(auto *compunit_fundec = curr_compunit->as<CompUnitFunDec_ptr>())
        {
            functiondec_vec.emplace_back(compunit_fundec);
        }
        else
        {
            fmt::print("Error in function trans_compunit\n");
        }
    }
    //函数翻译
    for(auto compunit_fundec : functiondec_vec)
    {
        trans_compunit_fundec(compunit_fundec);
    }
}


void trans_root(Root_ptr root, std::ostream & out)
{
    push_symbol_table_();
    //加入运行时函数到最外层作用域之中
    auto scope = symbol_table_func_.begin();
    //putint
    FunctionType *FT_putint = FunctionType::get(UnitType, {IntegerType});
    Function *F_putint = Function::Create(FT_putint, true, "putint", Module_main.get());
    std::vector<VarType_ptr> params_putint;
    auto param_putint = new VarType("value", 0, {}); //这里因为不会编译putint的函数定义，所以形参叫什么都无所谓
    params_putint.push_back(param_putint);
    scope->insert(std::pair<std::string, FuncType_ptr>("putint", 
                        new FuncType("putint", Ret_Void, params_putint, F_putint)));

    //getint
    FunctionType *FT_getint = FunctionType::get(IntegerType, {});
    Function *F_getint = Function::Create(FT_getint, true, "getint", Module_main.get());
    scope->insert(std::pair<std::string, FuncType_ptr>("getint", 
                        new FuncType("getint", Ret_Int, std::vector<VarType_ptr>(), F_getint)));

    //putch
    FunctionType *FT_putch = FunctionType::get(UnitType, {IntegerType});
    Function *F_putch = Function::Create(FT_putch, true, "putch", Module_main.get());
    std::vector<VarType_ptr> params_putch;
    auto param_putch = new VarType("value", 0, {}); //这里因为不会编译putint的函数定义，所以形参叫什么都无所谓
    params_putch.push_back(param_putch);
    scope->insert(std::pair<std::string, FuncType_ptr>("putch", 
                        new FuncType("putch", Ret_Void, params_putch, F_putch)));
    
    //getch
    FunctionType *FT_getch = FunctionType::get(IntegerType, {});
    Function *F_getch = Function::Create(FT_getch, true, "getch", Module_main.get());
    scope->insert(std::pair<std::string, FuncType_ptr>("getch", 
                        new FuncType("getch", Ret_Int, std::vector<VarType_ptr>(), F_getch)));
    
    //starttime
    FunctionType *FT_starttime = FunctionType::get(UnitType, {});
    Function *F_starttime = Function::Create(FT_starttime, true, "starttime", Module_main.get());
    scope->insert(std::pair<std::string, FuncType_ptr>("starttime", 
                        new FuncType("starttime", Ret_Void, std::vector<VarType_ptr>(), F_starttime)));

    //stoptime
    FunctionType *FT_stoptime = FunctionType::get(UnitType, {});
    Function *F_stoptime = Function::Create(FT_stoptime, true, "stoptime", Module_main.get());
    scope->insert(std::pair<std::string, FuncType_ptr>("stoptime", 
                        new FuncType("stoptime", Ret_Void, std::vector<VarType_ptr>(), F_stoptime)));

    //getarray
    FunctionType *FT_getarray = FunctionType::get(IntegerType, {PtrIntType});
    Function *F_getarray = Function::Create(FT_getarray, true, "getarray", Module_main.get());
    std::vector<VarType_ptr> params_getarray;
    auto param_getarray = new VarType("value", 1, std::vector({0})); //这里因为不会编译putint的函数定义，所以形参叫什么都无所谓
    params_getarray.push_back(param_getarray);
    scope->insert(std::pair<std::string, FuncType_ptr>("getarray", 
                        new FuncType("getarray", Ret_Int, params_getarray, F_getarray)));

    //putarray
    FunctionType *FT_putarray = FunctionType::get(UnitType, {IntegerType, PtrIntType});
    Function *F_putarray = Function::Create(FT_putarray, true, "putarray", Module_main.get());
    std::vector<VarType_ptr> params_putarray;
    auto param1_putarray = new VarType("value", 0, {});
    auto param2_putarray = new VarType("value", 1, std::vector({0})); //这里因为不会编译putint的函数定义，所以形参叫什么都无所谓
    params_putarray.push_back(param1_putarray);
    params_putarray.push_back(param2_putarray);
    scope->insert(std::pair<std::string, FuncType_ptr>("putarray", 
                        new FuncType("putarray", Ret_Void, params_putarray, F_putarray)));

    if(root->CompUnitHead != nullptr)
        trans_compunit(root->CompUnitHead);
    Module_main->print(out, false);
}
