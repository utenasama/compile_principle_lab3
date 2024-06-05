#pragma once
#include "ir/ir.h"
#include "ir/type.h"
#include "ir/ir.def"
#include "utils/list.h"
#include "utils/casting.h"
#include <iostream>
#include "ast/check.h"
#include <fmt/core.h>
#include <cassert>
#include <map>
#include <vector>
#include <list>
#include <memory>

void trans_root(Root_ptr root, std::ostream& out);

extern bool error;
std::vector<std::map<std::string, VarType_ptr>> scopes_variable_lab3; 
std::vector<std::map<std::string, FuncType_ptr>> scopes_function_lab3;
//生成module
auto M = std::make_unique<Module>();
Type *IntegerType = Type::getIntegerTy();
Type *UnitType = Type::getUnitTy();
PointerType *PtrIntType = PointerType::get(IntegerType);
FunctionType *FT_main = FunctionType::get(IntegerType, {});
Function *F_main = Function::Create(FT_main, false, "main", M.get());
BasicBlock *Entry_main = BasicBlock::Create(F_main);
//ConstantInt *One = ConstantInt::Create(1);
ConstantInt *Zero = ConstantInt::Create(0);
//ConstantInt *Minus_One = ConstantInt::Create(-1);
BasicBlock *current_bb;

//用于记录if while的数量，方便block命名
int if_count = 0;
int while_count = 0;
int block_count = 0;
//用于记录if while中的lor/land操作，方便shortcut block命名
int lor_count = 0;
int land_count = 0;
bool cur_bb_has_term = false;

Value* trans_unaexp(UnaExpr_ptr unaexp);
Value* trans_exparr(ExpArr_ptr exparr);
Value* trans_addexp(AddExpr_ptr addexp);
void trans_stmt(Stmt_ptr stmt, BasicBlock *entry, BasicBlock *exit);
void trans_block(Block_ptr block, BasicBlock *entry, BasicBlock *exit);
Value* trans_rel(Rel_ptr rel);
Value* trans_eq(Eq_ptr eq);
Value* trans_land(LAnd_ptr land);
Value* trans_lor(LOr_ptr lor);
Value* trans_land_sc(LAnd_ptr land, BasicBlock *, BasicBlock*);
Value* trans_lor_sc(LOr_ptr lor, BasicBlock*, BasicBlock*);


void push_scope_lab3()  //加入一个新的作用域
{
    scopes_variable_lab3.push_back(std::map<std::string, VarType_ptr>());
    scopes_function_lab3.push_back(std::map<std::string, FuncType_ptr>());
}

void pop_scope_lab3()
{
    //记得清理new的元素
    auto scope_var = scopes_variable_lab3.back();
    for(auto &ele : scope_var)
    {
        delete ele.second;
        ele.second = nullptr;
    }
    scopes_variable_lab3.pop_back();

    auto scope_func = scopes_function_lab3.back();
    for(auto &ele : scope_func)
    {   
        //先清理funcptr里面的fparams(这是一个vector<VarType_ptr>)
        for(auto &var_ele : ele.second->FParams)
        {
            delete var_ele;
            var_ele = nullptr;
        }
        delete ele.second;
        ele.second = nullptr;
    }
    scopes_function_lab3.pop_back();
}

void add_variable_to_table_lab3(VarType_ptr variableptr)
{
    if(scopes_variable_lab3.begin() == scopes_variable_lab3.end())
    {
        error = true;
        fmt::print("Error in add_variable_to_table, no scopes\n");
        return;
    }

    auto scope = scopes_variable_lab3.rbegin(); //最后一个scope
    if(scope->find(variableptr->ValID) != scope->end())
    {
        error = true;
        fmt::print("Error! Redefination of VarType \"{}\"\n", variableptr->ValID);
        return;
    }
    scope->insert(std::pair<std::string, VarType_ptr>(variableptr->ValID, variableptr));
}

void add_function_to_table_lab3(FuncType_ptr funcptr)
{
    if(scopes_function_lab3.begin() == scopes_function_lab3.end())
    {
        error = true;
        fmt::print("Error in add_function_to_table, no scopes\n");
        return;
    }

    for(std::vector<std::map<std::string, FuncType_ptr>>::iterator iter = scopes_function_lab3.end()-1; 
        iter >= scopes_function_lab3.begin(); iter--)
    {
        if(iter->find(funcptr->FuncID) != iter->end())
        {
            error = true;
            fmt::print("Error! Redefination of FuncType \"{}\"\n", funcptr->FuncID);
            return;
        }

        //没有找到重复的函数定义，可以插入
        if(iter == scopes_function_lab3.begin())
        {
            auto scope = scopes_function_lab3.rbegin(); //最后一个scope
            scope->insert(std::pair<std::string, FuncType_ptr>(funcptr->FuncID, funcptr));
        }
    }

}

Value* trans_funrparam(FunRParam_ptr funrparam)
{
    assert(funrparam != nullptr);
    Value* res_value = trans_lor(funrparam->FirstParam);
    return res_value;
}

Value* trans_pmn_unaexpr(PMNUnaExpr_ptr pmn_unaexp)
{
    assert(pmn_unaexp != nullptr);
    Value* res_value = trans_unaexp(pmn_unaexp->Operand);

    //用0-val代替neg
    switch(pmn_unaexp->OP)
    {
        case OP_Lnot:
        {
            return BinaryInst::CreateEq(res_value, Zero, IntegerType, current_bb);
        }
        case OP_Neg:
        {
            return BinaryInst::CreateSub(Zero, res_value, IntegerType, current_bb);
        }
        case OP_Pos:
        {
            return res_value;
        }
        default:
        {
            fmt::print("Error in trans_pmn_unaexpr, OP should be Neg / Pos / Lnot!\n");
            error = 1;
            return nullptr;
        }
    }
}

Value* trans_func_unaexpr(FunUnaExpr_ptr func_unaexpr)
{
    assert(func_unaexpr != nullptr);
    std::vector<Value*> args;
    //先检查函数是否定义，再检查参数
    for(std::vector<std::map<std::string, FuncType_ptr>>::iterator iter = scopes_function_lab3.end()-1; 
        iter >= scopes_function_lab3.begin(); iter--)
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
            CallInst *Call = CallInst::Create(funcptr->F, args, current_bb);
            return Call;
        }

        //没有找到
        if(iter == scopes_function_lab3.begin())
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
    assert(integer != nullptr);
    return ConstantInt::Create(integer->Val);
}

Value* trans_lval(LVal_ptr lval)
{
    assert(lval != nullptr);
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
    
    for(std::vector<std::map<std::string, VarType_ptr>>::iterator iter = scopes_variable_lab3.end()-1; 
        iter >= scopes_variable_lab3.begin(); iter--)
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
                Indices.push_back(Zero);
                dimensions++;
            }
            std::vector<std::optional<std::size_t>> Bounds = valptr->Bounds;

            if(dimensions != 0){
                OffsetInst *Offset;

                if(valptr->Val_Ptr == nullptr)  //Value是nullptr，说明这是一个形参，需要用getarg获得实参
                    Offset = OffsetInst::Create(IntegerType, current_bb->getParent()->getArg(valptr->Param_No), Indices, valptr->Bounds, current_bb);
                else
                    Offset = OffsetInst::Create(IntegerType, valptr->Val_Ptr, Indices, valptr->Bounds,current_bb);
                
                if(!need_load)
                    return Offset;
                else
                    return LoadInst::Create(Offset, current_bb);
            }
            else{
                return LoadInst::Create(valptr->Val_Ptr, current_bb);
            }
        }

        //没有找到
        if(iter == scopes_variable_lab3.begin())
        {
            error = true;
            fmt::print("Error in trans_lval, \"{}\" not defined\n", lval->ID);
            return nullptr;
        }
    }
    fmt::print("Error in trans_lval, should not reach here\n");
    return nullptr;
}

Value* trans_lval_noload(LVal_ptr lval)
{
    assert(lval != nullptr);
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
    
    for(std::vector<std::map<std::string, VarType_ptr>>::iterator iter = scopes_variable_lab3.end()-1; 
        iter >= scopes_variable_lab3.begin(); iter--)
    {
        auto map_iter = iter->find(lval->ID);
        if(map_iter != iter->end())
        {   //如果找到了这个变量名
            auto *valptr = map_iter->second;

            //对于没有给定的维数，使用0，比如int a[2][3], a[1]的地址就是a[1][0]的地址
            while(dimensions < valptr->Dimensions)
            {
                Indices.push_back(Zero);
                dimensions++;
            }
            std::vector<std::optional<std::size_t>> Bounds = valptr->Bounds;

            if(dimensions != 0){
                OffsetInst *Offset;
                if(valptr->Val_Ptr == nullptr)  //Value是nullptr，说明这是一个形参，需要用getarg获得实参
                    Offset = OffsetInst::Create(IntegerType, current_bb->getParent()->getArg(valptr->Param_No), Indices, valptr->Bounds, current_bb);
                else
                    Offset = OffsetInst::Create(IntegerType, valptr->Val_Ptr, Indices, valptr->Bounds,current_bb);
                
                return Offset;
            }
            else{
                return valptr->Val_Ptr;
            }
        }

        //没有找到
        if(iter == scopes_variable_lab3.begin())
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
    assert(primexp != nullptr);
    if(auto *lpexprp = primexp->as<LpExprRp_ptr>())
    {   
        return trans_lor(lpexprp->Operand);
    }
    else if(auto *integer = primexp->as<Integer_ptr>())
        return trans_integer(integer);
    else if(auto *lval = primexp->as<LVal_ptr>())
    {   
        Value *val_addr = trans_lval(lval);
        return val_addr;   
    }
    else{
        fmt::print("Error in trans_prim_unaexpr!!!!\n");
        error = true;
        return nullptr;
    }
}

Value* trans_unaexp(UnaExpr_ptr unaexp)
{
    assert(unaexp != nullptr);
    if(auto *pmn_unaexpr = unaexp->as<PMNUnaExpr_ptr>()){
        return trans_pmn_unaexpr(pmn_unaexpr);
    }
    else if(auto *func_unaexpr = unaexp->as<FunUnaExpr_ptr>())
        return trans_func_unaexpr(func_unaexpr);
    else{
        auto *primexp = static_cast<PrimExpr_ptr>(unaexp);
        return trans_prim_unaexpr(primexp);
    }
}

Value* trans_mulexp(MulExpr_ptr mulexp)
{
    assert(mulexp != nullptr);
    if(mulexp->OP != OP_None)
    {
        Value* res_val1 = trans_mulexp(mulexp->Operand);
        Value* res_val2 = trans_unaexp(mulexp->UnaExpr);

        if(mulexp->OP == OP_Mul){
            BinaryInst *Mul = BinaryInst::CreateMul(res_val1, res_val2, IntegerType, current_bb);
            return Mul;
        }
        else if(mulexp->OP == OP_Div){
            BinaryInst *Div = BinaryInst::CreateDiv(res_val1, res_val2, IntegerType, current_bb);
            return Div;
        }
        else if(mulexp->OP == OP_Mod){
            BinaryInst *Mod = BinaryInst::CreateMod(res_val1, res_val2, IntegerType, current_bb);
            return Mod;
        }
        else{
            error = true;
            fmt::print("Error in trans_mulexp, operand should be Mul / Div!!\n");
            return nullptr;
        }
    }else
        return trans_unaexp(mulexp->UnaExpr);
}

Value* trans_addexp(AddExpr_ptr addexp)
{
    assert(addexp != nullptr);
    if(addexp->OP != OP_None)
    {
        Value* res_val1 = trans_addexp(addexp->Operand);
        Value* res_val2 = trans_mulexp(addexp->MulExpr);
        
        if(addexp->OP == OP_Add){
            BinaryInst *Add = BinaryInst::CreateAdd(res_val1, res_val2, IntegerType, current_bb);
            return Add;
        }
        else if(addexp->OP == OP_Sub){
            BinaryInst *Sub = BinaryInst::CreateSub(res_val1, res_val2, IntegerType, current_bb);
            return Sub;
        }
        else{
            error = true;
            fmt::print("Error in trans_addexp, operand should be Add / Sub!!\n");
            return nullptr;
        }
    }else
        return trans_mulexp(addexp->MulExpr);
}

Value* trans_exparr(ExpArr_ptr exparr)
{
    assert(exparr != nullptr);

    return trans_lor(exparr->Expr);
}


//打印初始值
Value* trans_initval(LOr_ptr initval)
{
    assert(initval != nullptr);

    return trans_lor(initval);
}

//具体翻译变量声明
void trans_valdec(ValDec_ptr valdec)
{
    assert(valdec != nullptr);

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
    AllocaInst *ValAddr = AllocaInst::Create(IntegerType, element_len, current_bb);

    if(valdec->InitVal != nullptr)
    {
        if(valdec->ExpArr != nullptr)  //lab为了简化，不支持数组初始化
        {
            error = true;
            fmt::print("error in initialization: array can not be initialized!\n");
        }
        Value *init_val = trans_initval(valdec->InitVal);
        StoreInst *ValInit = StoreInst::Create(init_val, ValAddr, current_bb);
    }

    auto *variable = new VarType(valdec->ID, dimensions, dim_vec, ValAddr);
    add_variable_to_table_lab3(variable);
}

//具体翻译变量声明
void trans_valdec_global(ValDec_ptr valdec)
{
    assert(valdec != nullptr);

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

    auto ValAddr = GlobalVariable::Create(IntegerType, element_len, false, valdec->ID, M.get());  
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
    add_variable_to_table_lab3(variable);
}


VarType_ptr trans_funfparam_lab3(FunFParam_ptr funfparam)
{
    assert(funfparam != nullptr);
    int dimensions = 0;

    //如果形参是一个数组，需要check维度
    std::vector<int> dim_vec;
    if(funfparam->IsArr)
    {
        dimensions += 1;    //形参如果是array，第一维是空的，而且语法分析的时候也不会视为一个ExpArr
        dim_vec.push_back(0);
        if(funfparam->ExpArr != nullptr)
        {
            auto *exparr = funfparam->ExpArr;
            while(exparr != nullptr)
            {
                auto *unaexp = exparr->Expr->LAnd->Eq->Rel->Expr->MulExpr->UnaExpr;
                auto *primexp = static_cast<PrimExpr_ptr>(unaexp);
                auto *integer = primexp->as<Integer_ptr>();
                int dim = integer->Val;
                dimensions += 1;
                dim_vec.push_back(dim);
                exparr = exparr->NextExpArr; 
                //函数形参不需要alloca，所以不用算总size
            }
        }
    }

    return new VarType(funfparam->ID, dimensions, dim_vec);
}


//打印block中的valdec语句
void trans_valdecitem(ValDecItem_ptr valdecitem)
{
    assert(valdecitem != nullptr);

    auto *valdec = valdecitem->ValDec;
    while(valdec != nullptr)
    {
        trans_valdec(valdec);
        valdec = valdec->NextValDec;
    }
}

//打印block中的statement
void trans_stmtitem(StmtItem_ptr stmtitem, BasicBlock *entry, BasicBlock *exit)
{
    assert(stmtitem != nullptr);
    trans_stmt(stmtitem->Stmt, entry, exit);
}


//block内的变量赋值语句
void trans_lvalstmt(LValStmt_ptr lvalstmt)
{
    assert(lvalstmt != nullptr);
    Value* res_value1 = trans_lval_noload(lvalstmt->LVal);
    Value* res_value2 = trans_lor(lvalstmt->Expr);

   StoreInst *ResStore = StoreInst::Create(res_value2, res_value1, current_bb);
}

void trans_retstmt(RetStmt_ptr retstmt)
{
    assert(retstmt != nullptr);

    if(retstmt->Expr != nullptr)
    {
        Value* res_value = trans_lor(retstmt->Expr);
        RetInst *Ret = RetInst::Create(res_value,current_bb);
        cur_bb_has_term = true;
    }else{
        Value *V = ConstantUnit::Create();
        RetInst *Ret = RetInst::Create(V,current_bb);
        cur_bb_has_term = true;
    }
}

void trans_expstmt(ExpStmt_ptr expstmt)
{
    assert(expstmt != nullptr);

    if(expstmt->Expr != nullptr)
        trans_lor(expstmt->Expr);
}

void trans_breakstmt(BreakStmt_ptr breakstmt, BasicBlock *exit)
{
    assert(breakstmt != nullptr);
    if(exit == nullptr)
    {
        printf("error in break!\n");
        return;
    }
    if(!cur_bb_has_term){
        JumpInst *JFE = JumpInst::Create(exit, current_bb);
        cur_bb_has_term = true;
    }
}

void trans_contistmt(ContiStmt_ptr contistmt, BasicBlock *entry)
{
    assert(contistmt != nullptr);
    if(entry == nullptr)
    {
        printf("error in continue !\n");
        return;
    }
    if(!cur_bb_has_term){
        JumpInst *JFE = JumpInst::Create(entry, current_bb);
        cur_bb_has_term = true;
    }
}

void trans_blockinstmt(BlockInStmt_ptr blockinstmt, BasicBlock *entry, BasicBlock *exit)
{
    assert(blockinstmt != nullptr);
    push_scope_lab3();
    trans_block(blockinstmt->Block, entry, exit);
    pop_scope_lab3();

}



Value* trans_lor(LOr_ptr lor)
{
    assert(lor != nullptr);
    if(lor->Operand != nullptr)
    {
        Value* res_val1 = trans_land(lor->LAnd);
        Value* res_val2 = trans_lor(lor->Operand);
        BinaryInst *Lor = BinaryInst::CreateOr(res_val1, res_val2, IntegerType, current_bb);
        return Lor;
    }else{
        return trans_land(lor->LAnd);
    }
}


Value* trans_land(LAnd_ptr land)
{
    assert(land != nullptr);
    if(land->Operand != nullptr)
    {
        Value* res_val1 = trans_eq(land->Eq);
        Value* res_val2 = trans_land(land->Operand);
        BinaryInst *Land = BinaryInst::CreateAnd(res_val1, res_val2, IntegerType, current_bb);
        return Land;
    }else{
        return trans_eq(land->Eq);
    }
}


//短路shortcut版本，用于if while
Value* trans_lor_sc(LOr_ptr lor, BasicBlock *true_bb, BasicBlock *false_bb)
{
    assert(lor != nullptr);
    if(lor->Operand != nullptr)
    {
        BasicBlock *lor_con1_false_bb = BasicBlock::Create(current_bb->getParent());
        Value* res_val1 = trans_land_sc(lor->LAnd, true_bb, lor_con1_false_bb);
        //左边是false，就进入到lor语句的右部分block
        current_bb = lor_con1_false_bb;
        lor_count++;
        cur_bb_has_term = false;
        block_count++;
        Value* res_val2 = trans_lor_sc(lor->Operand, true_bb, false_bb);
        return res_val2;
    }else{
        return trans_land_sc(lor->LAnd, true_bb, false_bb);
    }
}


Value* trans_land_sc(LAnd_ptr land, BasicBlock *true_bb, BasicBlock *false_bb)
{
    assert(land != nullptr);
    if(land->Operand != nullptr)
    {
        BasicBlock *land_con1_true_bb = BasicBlock::Create(current_bb->getParent());
        Value* res_val1 = trans_eq(land->Eq);
        BranchInst *Br = BranchInst::Create(land_con1_true_bb, false_bb, res_val1, current_bb);

        //左边是true，就进入到land语句的右部分block
        current_bb = land_con1_true_bb;
        land_count++;

        cur_bb_has_term = false;
        block_count++;

        Value* res_val2 = trans_land_sc(land->Operand, true_bb, false_bb);
        //BinaryInst *Land = BinaryInst::CreateAnd(res_val1, res_val2, IntegerType, current_bb);
        return res_val2;
    }else{
        //如果这个land表达式没有operand，还有一种特殊情况，就是带有()的表达式，比如if((a>1 || b<1))，这种括号表达式在if/while内也要shortcut
        //懒得改代码，直接遍历指针，判断是不是一个括号表达式
        if(land->Eq->Operand == nullptr && land->Eq->Rel->Operand == nullptr &&
            land->Eq->Rel->Expr->Operand == nullptr && land->Eq->Rel->Expr->MulExpr->Operand == nullptr)
        {
            auto *unaexp = land->Eq->Rel->Expr->MulExpr->UnaExpr;
            if(auto *lpexprp = unaexp->as<LpExprRp_ptr>())
            {
                return trans_lor_sc(lpexprp->Operand, true_bb, false_bb);
            }
        }

        Value* res_value = trans_eq(land->Eq);
        BranchInst *Br = BranchInst::Create(true_bb, false_bb, res_value, current_bb);
        return res_value;
    }
}



Value* trans_eq(Eq_ptr eq)
{
    assert(eq != nullptr);
    if(eq->Operand != nullptr)
    {
        Value* res_val1 = trans_eq(eq->Operand);
        Value* res_val2 = trans_rel(eq->Rel);
     
        if(eq->OP == OP_Eq)
            return BinaryInst::CreateEq(res_val1, res_val2, IntegerType, current_bb);
        else if(eq->OP == OP_Ne)
            return BinaryInst::CreateNe(res_val1, res_val2, IntegerType, current_bb);
        else{
            error = true;
            fmt::print("Error in trans_eq, operand should be Eq / Ne!!\n");
            return nullptr;
        }
    }else
        return trans_rel(eq->Rel);
}

Value* trans_rel(Rel_ptr rel)
{
    assert(rel != nullptr);
    if(rel->Operand != nullptr)
    {
        Value* res_val1 = trans_rel(rel->Operand);
        Value* res_val2 = trans_addexp(rel->Expr);

        if(rel->OP == OP_Lt)
            return BinaryInst::CreateLt(res_val1, res_val2, IntegerType, current_bb);
        else if(rel->OP == OP_Gt)
            return BinaryInst::CreateGt(res_val1, res_val2, IntegerType, current_bb);
        else if(rel->OP == OP_Le)
            return BinaryInst::CreateLe(res_val1, res_val2, IntegerType, current_bb);
        else if(rel->OP == OP_Ge)
            return BinaryInst::CreateGe(res_val1, res_val2, IntegerType, current_bb);
        else{
            error = true;
            fmt::print("Error in trans_rel, operand should be Lt / Gt / Le / Ge!!\n");
            return nullptr;
        }
    }else{
        return trans_addexp(rel->Expr);
    }
}

void trans_whilestmt(WhileStmt_ptr whilestmt)
{
    assert(whilestmt != nullptr);

    while_count++;
    lor_count = 0;
    land_count = 0;

    BasicBlock *Body = BasicBlock::Create(current_bb->getParent());
    BasicBlock *Entry = BasicBlock::Create(current_bb->getParent());
    BasicBlock *Exit = BasicBlock::Create(current_bb->getParent());

    //先插入一条jump到当前block，跳转到entry
    if(!cur_bb_has_term){
        JumpInst *JTE = JumpInst::Create(Entry, current_bb);
        cur_bb_has_term = true;
    }

    //下面开始翻译
    current_bb = Entry;
    cur_bb_has_term = false;
    block_count++;

    Value* res_value = trans_lor_sc(whilestmt->Cond, Body, Exit);  //如果不等于0，就是true

    current_bb = Body;
    cur_bb_has_term = false;
    block_count++;
    trans_stmt(whilestmt->WhileBody, Entry, Exit);
    if(!cur_bb_has_term)
    {
        JumpInst *JTE2 = JumpInst::Create(Entry, current_bb);
        cur_bb_has_term = true;
    }

    current_bb = Exit;
    cur_bb_has_term = false;
    block_count++;
}

void trans_ifstmt(IfStmt_ptr ifstmt, BasicBlock *entry, BasicBlock *exit)
{
    assert(ifstmt != nullptr);
    
    if_count++;
    lor_count = 0;
    land_count = 0;
    
    BasicBlock *True = BasicBlock::Create(current_bb->getParent());
    BasicBlock *False = nullptr;
    if(ifstmt->ElseBody != nullptr){
        False = BasicBlock::Create(current_bb->getParent());
    }
    BasicBlock *Exit_If = BasicBlock::Create(current_bb->getParent());

    //下面开始翻译
    if(ifstmt->ElseBody != nullptr)
        Value* res_value = trans_lor_sc(ifstmt->Cond, True, False);
    else
        Value* res_value = trans_lor_sc(ifstmt->Cond, True, Exit_If);
    if(ifstmt->ElseBody != nullptr)
    {   
        current_bb = True;
        cur_bb_has_term = false;
        block_count++;
        trans_stmt(ifstmt->IfBody, entry, exit);
        if(!cur_bb_has_term){
            JumpInst::Create(Exit_If, current_bb);
            cur_bb_has_term = true;
        }
        current_bb = False;
        cur_bb_has_term = false;
        block_count++;
        trans_stmt(ifstmt->ElseBody, entry, exit);
        if(!cur_bb_has_term){
            JumpInst::Create(Exit_If, current_bb);
            cur_bb_has_term = true;
        }
    }else{
        current_bb = True;
        cur_bb_has_term = false;
        block_count++;
        trans_stmt(ifstmt->IfBody, entry, exit);
        if(!cur_bb_has_term){
            JumpInst::Create(Exit_If, current_bb);
            cur_bb_has_term = true;
        }
    }
    current_bb = Exit_If;
    cur_bb_has_term = false;
    block_count++;
}

void trans_emptystmt(EmptyStmt_ptr emptystmt)
{
    assert(emptystmt != nullptr);
}

void trans_stmt(Stmt_ptr stmt, BasicBlock *entry, BasicBlock *exit)
{
    assert(stmt != nullptr);
    if(auto *lvalstmt = stmt->as<LValStmt_ptr>())
        trans_lvalstmt(lvalstmt);
    else if(auto *retstmt = stmt->as<RetStmt_ptr>())
        trans_retstmt(retstmt);
    else if(auto *expstmt = stmt->as<ExpStmt_ptr>())
        trans_expstmt(expstmt);
    else if(auto *breakstmt = stmt->as<BreakStmt_ptr>())
        trans_breakstmt(breakstmt, exit);
    else if(auto *contistmt = stmt->as<ContiStmt_ptr>())
        trans_contistmt(contistmt, entry);
    else if(auto *blockinstmt = stmt->as<BlockInStmt_ptr>())
        trans_blockinstmt(blockinstmt, entry, exit);
    else if(auto *ifstmt = stmt->as<IfStmt_ptr>())
        trans_ifstmt(ifstmt, entry, exit);
    else if(auto *whilestmt = stmt->as<WhileStmt_ptr>())
        trans_whilestmt(whilestmt);
    else if(auto *emptystmt = stmt->as<EmptyStmt_ptr>())
        trans_emptystmt(emptystmt);
    else{
        fmt::print("error in function trans_stmt!\n");
        error = true;
    }
}

void trans_blockitem(BlockItem_ptr blockitem, BasicBlock *entry, BasicBlock *exit)
{
    assert(blockitem != nullptr);
    if(auto *valdecitem = blockitem->as<ValDecItem_ptr>())
        trans_valdecitem(valdecitem);
    else if(auto *stmtitem = blockitem->as<StmtItem_ptr>())
        trans_stmtitem(stmtitem, entry, exit);
}

void trans_block(Block_ptr block, BasicBlock *entry, BasicBlock *exit)
{
    assert(block != nullptr);
    if(block->BlockItemHead != nullptr)
    {   
        auto *blockitem = block->BlockItemHead;
        while(blockitem != nullptr)
        {
            trans_blockitem(blockitem, entry, exit);
            blockitem = blockitem->NextBlockItem;
        }
    }
}

//具体打印函数信息
void trans_fundec_lab3(FunDef_ptr fundef)
{
    assert(fundef != nullptr);
    std::vector<VarType_ptr> params;
    std::vector<Type *> Params_lab3;
    if(fundef->FunFParam != nullptr)
    {
        auto *funfparam = fundef->FunFParam;
        while(funfparam != nullptr)
        {
            //先记录参数信息
            auto *param = trans_funfparam_lab3(funfparam);
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
        F = Function::Create(FT, false, fundef->FunID, M.get());
        Entry = BasicBlock::Create(F);
    }else{
        F = F_main;
        Entry = Entry_main;
    }

    auto *function = new FuncType(fundef->FunID, fundef->RType, params, F);
    add_function_to_table_lab3(function);

    //新加入一个scope，也就是函数的作用域
    push_scope_lab3();
    current_bb = Entry;
    cur_bb_has_term = false;
    block_count++;
    //函数的参数属于自己的那个作用域，顺便为所有形参加上名字
    int count = 0;
    for(auto *ele : params)
    {
        Value *val_ptr = nullptr;
        if(ele->Dimensions == 0)
        {
            AllocaInst *Val_Addr = AllocaInst::Create(IntegerType, 1, current_bb);

            StoreInst *NArgStore = StoreInst::Create(current_bb->getParent()->getArg(count), Val_Addr, current_bb);
            val_ptr = Val_Addr;           
        }
        auto *param = new VarType(ele->ValID, ele->Dimensions, ele->DimensionSizes,val_ptr, count); //这里改成拷贝构造函数可能更好
        add_variable_to_table_lab3(param);

        count++;
    }
    //TODO:
    trans_block(fundef->Block, nullptr, nullptr);
    pop_scope_lab3();
}


//翻译变量声明
void trans_compunit_valdec(CompUnitValDec_ptr compunit_valdec)
{
    assert(compunit_valdec != nullptr);

    auto *valdec = compunit_valdec->ValDec;
    //逐个翻译
    while(valdec != nullptr)
    {
        trans_valdec_global(valdec);
        valdec = valdec->NextValDec;
    }
}


//打印函数声明
void trans_compunit_fundec(CompUnitFunDec_ptr compunit_fundec)
{
    assert(compunit_fundec != nullptr);

    //具体打印函数信息
    trans_fundec_lab3(compunit_fundec->FunDef);
}



void trans_compunit(CompUnit_ptr compunit)
{
    assert(compunit != nullptr);

    //lab2 根据compunit中语句的具体类型(函数声明 变量声明)进一步打印
    //lab3和lab2的区别，需要先进行全局变量的翻译，再进行函数的翻译
    std::vector<CompUnitFunDec_ptr> functiondec_vec;
    //这里会主动设置main的basicblock
    while(compunit != nullptr)
    {
        if(auto *compunit_valdec = compunit->as<CompUnitValDec_ptr>())
            trans_compunit_valdec(compunit_valdec);
        else if(auto *compunit_fundec = compunit->as<CompUnitFunDec_ptr>())
            functiondec_vec.push_back(compunit_fundec);
        else
            fmt::print("Error in function trans_compunit\n");

        compunit = compunit->NextCompUnit;
    }

    //然后翻译函数
    for(auto compunit_fundec : functiondec_vec)
        trans_compunit_fundec(compunit_fundec);
}



//打印root
void trans_root(Root_ptr root, std::ostream & out)
{
    assert(root != nullptr);
    push_scope_lab3();

    //加入运行时函数到最外层作用域之中
    auto scope = scopes_function_lab3.begin();
    //putint
    FunctionType *FT_putint = FunctionType::get(UnitType, {IntegerType});
    Function *F_putint = Function::Create(FT_putint, true, "putint", M.get());
    std::vector<VarType_ptr> params_putint;
    auto param_putint = new VarType("value", 0, {}); //这里因为不会编译putint的函数定义，所以形参叫什么都无所谓
    params_putint.push_back(param_putint);
    scope->insert(std::pair<std::string, FuncType_ptr>("putint", 
                        new FuncType("putint", Ret_Void, params_putint, F_putint)));

    //getint
    FunctionType *FT_getint = FunctionType::get(IntegerType, {});
    Function *F_getint = Function::Create(FT_getint, true, "getint", M.get());
    scope->insert(std::pair<std::string, FuncType_ptr>("getint", 
                        new FuncType("getint", Ret_Int, std::vector<VarType_ptr>(), F_getint)));

    //putch
    FunctionType *FT_putch = FunctionType::get(UnitType, {IntegerType});
    Function *F_putch = Function::Create(FT_putch, true, "putch", M.get());
    std::vector<VarType_ptr> params_putch;
    auto param_putch = new VarType("value", 0, {}); //这里因为不会编译putint的函数定义，所以形参叫什么都无所谓
    params_putch.push_back(param_putch);
    scope->insert(std::pair<std::string, FuncType_ptr>("putch", 
                        new FuncType("putch", Ret_Void, params_putch, F_putch)));
    
    //getch
    FunctionType *FT_getch = FunctionType::get(IntegerType, {});
    Function *F_getch = Function::Create(FT_getch, true, "getch", M.get());
    scope->insert(std::pair<std::string, FuncType_ptr>("getch", 
                        new FuncType("getch", Ret_Int, std::vector<VarType_ptr>(), F_getch)));
    
    //starttime
    FunctionType *FT_starttime = FunctionType::get(UnitType, {});
    Function *F_starttime = Function::Create(FT_starttime, true, "starttime", M.get());
    scope->insert(std::pair<std::string, FuncType_ptr>("starttime", 
                        new FuncType("starttime", Ret_Void, std::vector<VarType_ptr>(), F_starttime)));

    //stoptime
    FunctionType *FT_stoptime = FunctionType::get(UnitType, {});
    Function *F_stoptime = Function::Create(FT_stoptime, true, "stoptime", M.get());
    scope->insert(std::pair<std::string, FuncType_ptr>("stoptime", 
                        new FuncType("stoptime", Ret_Void, std::vector<VarType_ptr>(), F_stoptime)));

    //getarray
    FunctionType *FT_getarray = FunctionType::get(IntegerType, {PtrIntType});
    Function *F_getarray = Function::Create(FT_getarray, true, "getarray", M.get());
    std::vector<VarType_ptr> params_getarray;
    auto param_getarray = new VarType("value", 1, std::vector({0})); //这里因为不会编译putint的函数定义，所以形参叫什么都无所谓
    params_getarray.push_back(param_getarray);
    scope->insert(std::pair<std::string, FuncType_ptr>("getarray", 
                        new FuncType("getarray", Ret_Int, params_getarray, F_getarray)));

    //putarray
    FunctionType *FT_putarray = FunctionType::get(UnitType, {IntegerType, PtrIntType});
    Function *F_putarray = Function::Create(FT_putarray, true, "putarray", M.get());
    std::vector<VarType_ptr> params_putarray;
    auto param1_putarray = new VarType("value", 0, {});
    auto param2_putarray = new VarType("value", 1, std::vector({0})); //这里因为不会编译putint的函数定义，所以形参叫什么都无所谓
    params_putarray.push_back(param1_putarray);
    params_putarray.push_back(param2_putarray);
    scope->insert(std::pair<std::string, FuncType_ptr>("putarray", 
                        new FuncType("putarray", Ret_Void, params_putarray, F_putarray)));

    if(root->CompUnitHead != nullptr)
        trans_compunit(root->CompUnitHead);
    M->print(out, false);
}
