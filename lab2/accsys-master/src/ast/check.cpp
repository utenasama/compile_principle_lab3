#include "ast/ast.h"
#include "ast/check.h"

#include <fmt/core.h>
#include <cassert>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

static std::string op_str(OpType op_type)
{
    switch (op_type)
    {
#define OpcodeDefine(x, s) \
    case x:                \
        return s;
#include "common/common.def"
    default:
        return "<unknown>";
    }
}

static std::string ret_str(RetType ret_type)
{
    switch (ret_type)
    {
#define RetTypeDefine(x, s) \
    case x:                 \
        return s;
#include "common/common.def"
    default:
        return "<unknown>";
    }
}

extern bool error;

// 符号表
std::vector<std::map<std::string, VarType_ptr>> symbol_table_var;
std::vector<std::map<std::string, FuncType_ptr>> symbol_table_func;
std::vector<ResType> func_call_ret;

void push_symbol_table() // 加入一个新的符号表
{
    symbol_table_var.push_back(std::map<std::string, VarType_ptr>());
    symbol_table_func.push_back(std::map<std::string, FuncType_ptr>());
    // puts("1");
}

void pop_symbol_table()
{
    auto table_var = symbol_table_var.back();
    symbol_table_var.pop_back();

    auto table_func = symbol_table_func.back();
    symbol_table_func.pop_back();
    // puts("2");
}

void add_var_to_table(VarType_ptr variableptr)
{
    if (symbol_table_var.begin() == symbol_table_var.end())
    {
        error = true;
        fmt::print("Error in add_var_to_table, no scopes\n");
        return;
    }

    auto scope = symbol_table_var.end() - 1; // 最后一个scope
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

void add_func_to_table(FuncType_ptr funcptr)
{
    if (symbol_table_func.begin() == symbol_table_func.end())
    {
        error = true;
        fmt::print("Error in add_func_to_table, no scopes\n");
        return;
    }
    // 函数名不可重复
    auto iter = symbol_table_func.end() - 1;
    for (auto iter = symbol_table_func.end() - 1; iter >= symbol_table_func.begin(); iter--)
    {
        if (iter->find(funcptr->FuncID) != iter->end())
        {
            error = true;
            fmt::print("Error! Redefination of FuncType \"{}\"\n", funcptr->FuncID);
            return;
        }
    }
    // 未找到重复的函数定义，可以插入
    if (iter == symbol_table_func.begin())
    {
        auto scope = symbol_table_func.rbegin(); // 最后一个scope
        scope->insert(std::pair<std::string, FuncType_ptr>(funcptr->FuncID, funcptr));
    }
}


// TODO:

void check_funrparam(FunRParam_ptr funrparam, std::vector<VarType_ptr> funfparam)
{
    // std::cout << funfparam.back()->ValID << std::endl;
    if (funrparam->FirstParam != nullptr) {
        ResType ret = check_addexp(funrparam->FirstParam);
        if (ret.RType != Ret_Int || ret.Dimensions != funfparam.back()->Dimensions) {
            error = true;
            fmt::print("Error! Type of function parameters doesn't match\n");
        }
        for (int i = 0 ; i < ret.Dimensions - 1 ; i++)
            if (ret.DimensionSizes[i] != funfparam.back()->DimensionSizes[i]) {
                error = true;
                fmt::print("Error! Type of function parameters doesn't match\n");
                break;
            }
        funfparam.pop_back();
    }
    if (funrparam->NextFunRParam != nullptr)
        check_funrparam(funrparam->NextFunRParam, funfparam);
}
    
ResType check_pmn_unaexpr(PMNUnaExpr_ptr pmn_unaexp)
{
    switch (pmn_unaexp->OP)
    {
        case OpType::OP_Neg: {
            ResType ret = check_unaexp(pmn_unaexp->Operand);
            if (ret.Dimensions >= 1) {
                error = true;
                fmt::print("Error in expression calculation, type mismatch\n");
            }
            ret.Value = -ret.Value;
            return ret;
            break;
        }
        case OpType::OP_Pos: {
            ResType ret = check_unaexp(pmn_unaexp->Operand);
            if (ret.Dimensions >= 1) {
                error = true;
                fmt::print("Error in expression calculation, type mismatch\n");
            }
            return ret;
            break;
        }
        case OpType::OP_Lnot: {
            ResType ret = check_unaexp(pmn_unaexp->Operand);
            if (ret.Dimensions >= 1) {
                error = true;
                fmt::print("Error in expression calculation, type mismatch\n");
            }
            ret.Value = !ret.Value;
            return ret;
            break;
        }
    }
}

ResType check_func_unaexpr(FunUnaExpr_ptr func_unaexpr)
{
    bool flag = false;
    RetType ret = RetType::Ret_Error;
    for (auto p : symbol_table_func)
        if (p.count(func_unaexpr->FunID)) {
            flag = true;
            std::cout << func_unaexpr->FunID << std::endl;
            if (func_unaexpr->FunRParam != nullptr)
                check_funrparam(func_unaexpr->FunRParam, p[func_unaexpr->FunID]->FParams);
            ret = p[func_unaexpr->FunID]->RType;
            break;
        }
    if (!flag) {
        error = true;
        fmt::print("Error in expression calculation, no such function\n");
    }
    std::vector<int> temp;
    return ResType(ret, 0, temp, -1);
}

ResType check_integer(Integer_ptr integer)
{
    std::vector<int> temp;
    return ResType(Ret_Int, 0, temp, integer->Val);
}

ResType check_lval(LVal_ptr lval)
{
    bool flag = false;
    VarType_ptr var;
    // std::cout << lval->ID << std::endl;
    for (auto p : symbol_table_var)
        if (p.count(lval->ID)) {
            flag = true;
            var = p[lval->ID];
            break;
        }
    if (flag == false) {
        error = true;
        fmt::print("Error! VarType can not be found \"{}\"\n", lval->ID);
    }
    int dimension = var->Dimensions;
    std::vector<int> ret_dim = var->DimensionSizes;
    for (auto p = lval->ExpArr ; p ; p = p->NextExpArr) {
        ResType ret = check_addexp(p->Expr);
        if (ret.RType != RetType::Ret_Int || ret.Dimensions > 0) {
            error = true;
            fmt::print("Error in array definition, type mismatch\n");
        }
        dimension--;
        ret_dim.pop_back();
    }
    if (dimension < 0) {
        error = true;
        fmt::print("Error! VarType dimensions don't match \"{}\"\n", lval->ID);
    }
    // std::cout << dimension << 'x' << std::endl;
    return ResType(Ret_Int, dimension, ret_dim, -1 ,true);
}

ResType check_prim_unaexpr(PrimExpr_ptr primexp)
{
    if (primexp->is<Node_LVal>())
        return check_lval(primexp->as<LVal_ptr>());
    else if (primexp->is<Node_LpExprRp>())
        return check_addexp(primexp->as<LpExprRp_ptr>()->Operand);
    else if (primexp->is<Node_Integer>())
        return check_integer(primexp->as<Integer_ptr>());
}

ResType check_unaexp(UnaExpr_ptr unaexp)
{
    if (unaexp->is<Node_PMNUnaExpr>())
        return check_pmn_unaexpr(unaexp->as<PMNUnaExpr_ptr>());
    else if (unaexp->is<Node_FuncUnaExpr>())
        return check_func_unaexpr(unaexp->as<FunUnaExpr_ptr>());
    else return check_prim_unaexpr(static_cast<PrimExpr_ptr>(unaexp));
}

ResType check_mulexp(MulExpr_ptr mulexp)
{
    switch (mulexp->OP)
    {
        case OpType::OP_Mul: {
            ResType ret = check_unaexp(mulexp->UnaExpr);
            if (mulexp->Operand != nullptr) {
                ResType temp = check_mulexp(mulexp->Operand);
                if (temp != ret) {
                    error = true;
                    fmt::print("Error in expression calculation, type mismatch\n");
                }
                ret.Value = ret.Value * temp.Value;
            }
            return ret;
            break;
        }
        case OpType::OP_Div: {
            ResType ret = check_unaexp(mulexp->UnaExpr);
            if (mulexp->Operand != nullptr) {
                ResType temp = check_mulexp(mulexp->Operand);
                if (temp != ret) {
                    error = true;
                    fmt::print("Error in expression calculation, type mismatch\n");
                }
                if (ret.Value == 0) {
                    error = true;
                    fmt::print("Error in expression calculation, divided by zero\n");
                }
                ret.Value = ret.Value == -1 ? -1 : temp.Value / ret.Value;
            }
            return ret;
            break;
        }
        case OpType::OP_Mod: {
            ResType ret = check_unaexp(mulexp->UnaExpr);
            if (mulexp->Operand != nullptr) {
                ResType temp = check_mulexp(mulexp->Operand);
                if (temp != ret) {
                    error = true;
                    fmt::print("Error in expression calculation, type mismatch\n");
                }
                ret.Value = temp.Value % ret.Value;
            }
            return ret;
            break;
        }
        default: return check_unaexp(mulexp->UnaExpr); break;
    }
}

ResType check_addexp(AddExpr_ptr addexp)
{
    switch (addexp->OP)
    {
        case OpType::OP_Add: {
            ResType ret = check_mulexp(addexp->MulExpr);
            if (addexp->Operand != nullptr) {
                ResType temp = check_addexp(addexp->Operand);
                if (temp != ret) {
                    error = true;
                    fmt::print("Error in expression calculation, type mismatch\n");
                }
                ret.Value += temp.Value;
            }
            return ret;
            break;
        }
        case OpType::OP_Sub: {
            ResType ret = check_mulexp(addexp->MulExpr);
            if (addexp->Operand != nullptr) {
                ResType temp = check_addexp(addexp->Operand);
                if (temp != ret) {
                    error = true;
                    fmt::print("Error in expression calculation, type mismatch\n");
                }
                ret.Value = temp.Value - ret.Value;
            }
            return ret;
            break;
        }
        default: return check_mulexp(addexp->MulExpr); break;
    }
}

void check_exparr(ExpArr_ptr exparrm, int &dimension, std::vector<int> &dim)
{
    if (exparrm->NextExpArr != nullptr)
        check_exparr(exparrm->NextExpArr, dimension, dim);
    dimension += 1;
    ResType ret = check_addexp(exparrm->Expr);
    if (ret.Value <= 0) {
        error = true;
        fmt::print("Error in array definition, the length of dimension is less than 0\n");
    }
    dim.push_back(ret.Value);
    if (ret.RType != RetType::Ret_Int || ret.Dimensions > 0) {
        error = true;
        fmt::print("Error in array definition, type mismatch\n");
    }
}

ResType check_initval(AddExpr_ptr initval)
{
    return check_addexp(initval);
}

void check_valdec(ValDec_ptr valdec)
{
    int dimension = 0;
    std::vector<int> temp;
    if (valdec->ExpArr != nullptr)
        check_exparr(valdec->ExpArr, dimension, temp);
    if (valdec->InitVal) {
        ResType ret = check_initval(valdec->InitVal);
        if (ret.RType != RetType::Ret_Int) {
            error = true;
            fmt::print("Error! VarType Type mismatch \n");
            return ;
        }
    }
    auto *new_var = new VarType(valdec->ID, dimension, temp);
    add_var_to_table(new_var);
    if (valdec->NextValDec != nullptr)
        check_valdec(valdec->NextValDec);
    return ;
}

VarType_ptr check_funfparam(FunFParam_ptr funfparam)
{
    int dimension = funfparam->IsArr;
    std::vector<int> temp;
    if (funfparam->ExpArr != nullptr)
        check_exparr(funfparam->ExpArr, dimension, temp);
    if (funfparam->IsArr == true)
        temp.push_back(-1);
    auto *new_param = new VarType(funfparam->ID, dimension, temp);
    return new_param;
}

void check_valdecitem(ValDecItem_ptr valdecitem)
{
    check_valdec(valdecitem->ValDec);
}

void check_stmtitem(StmtItem_ptr stmtitem)
{
    check_stmt(stmtitem->Stmt);
}

void check_lvalstmt(LValStmt_ptr lvalstmt)
{
    ResType left = check_lval(lvalstmt->LVal);
    ResType right = check_addexp(lvalstmt->Expr);
    // std::cout << left.Dimensions << "xx" << std::endl;
    if (left != right || left.RType == Ret_Void || left.Dimensions >=1 || right.Dimensions >= 1) {
        error = true;
        fmt::print("Error! Left value Type mismatch \n");
        return ;
    }
}

void check_retstmt(RetStmt_ptr retstmt)
{
    if (retstmt->Expr != nullptr) {
        ResType ret = check_addexp(retstmt->Expr);
        if (ret != func_call_ret.back()) {
            error = true;
            fmt::print("Error! FuncType return Type mismatch \n");
            return ;
        }
    } else if (func_call_ret.back().RType != Ret_Void) {
        error = true;
        fmt::print("Error! FuncType return must have value \n");
    }
}

void check_expstmt(ExpStmt_ptr expstmt) {
    check_addexp(expstmt->Expr);
}

void check_breakstmt(BreakStmt_ptr breakstmt) {
    return;
}

void check_contistmt(ContiStmt_ptr contistmt) {
    return;
}

void check_blockinstmt(BlockInStmt_ptr blockinstmt)
{
    push_symbol_table();
    check_block(blockinstmt->Block);
    pop_symbol_table();
}

ResType check_lor(LOr_ptr lor)
{
    ResType ret = check_land(lor->LAnd);
    if (lor->Operand != nullptr) {
        ResType op = check_lor(lor->Operand);
        if (ret != op) {
            error = true;
            fmt::print("Error! logic or calculation Type mismatch \n");
        }
    }
    return ret;
}

ResType check_land(LAnd_ptr land)
{
    ResType ret = check_eq(land->Eq);
    if (land->Operand != nullptr) {
        ResType op = check_land(land->Operand);
        if (ret != op) {
            error = true;
            fmt::print("Error! logic or calculation Type mismatch \n");
        }
    }
    return ret;
}

ResType check_eq(Eq_ptr eq)
{
    ResType ret = check_rel(eq->Rel);
    if (eq->Operand != nullptr) {
        ResType op = check_eq(eq->Operand);
        if (ret != op) {
            error = true;
            fmt::print("Error! logic or calculation Type mismatch \n");
        }
    }
    return ret;
}

ResType check_rel(Rel_ptr rel)
{
    ResType ret = check_addexp(rel->Expr);
    if (rel->Operand != nullptr) {
        ResType op = check_rel(rel->Operand);
        if (ret != op) {
            error = true;
            fmt::print("Error! logic or calculation Type mismatch \n");
        }
    }
    return ret;
}

void check_whilestmt(WhileStmt_ptr whilestmt)
{
    check_lor(whilestmt->Cond);
    check_stmt(whilestmt->WhileBody);
}

void check_ifstmt(IfStmt_ptr ifstmt)
{
    check_lor(ifstmt->Cond);
    check_stmt(ifstmt->IfBody);
    if (ifstmt->ElseBody)
        check_stmt(ifstmt->ElseBody);
}

void check_emptystmt(EmptyStmt_ptr emptystmt);

void check_stmt(Stmt_ptr stmt)
{
    if (stmt->is<LValStmt_ptr>())
        check_lvalstmt(stmt->as<LValStmt_ptr>());
    if (stmt->is<RetStmt_ptr>())
        check_retstmt(stmt->as<RetStmt_ptr>());
    if (stmt->is<ExpStmt_ptr>())
        check_expstmt(stmt->as<ExpStmt_ptr>());
    if (stmt->is<BreakStmt_ptr>())
        check_breakstmt(stmt->as<BreakStmt_ptr>());
    if (stmt->is<ContiStmt_ptr>())
        check_contistmt(stmt->as<ContiStmt_ptr>());
    if (stmt->is<BlockInStmt_ptr>())
        check_blockinstmt(stmt->as<BlockInStmt_ptr>());
    if (stmt->is<IfStmt_ptr>())
        check_ifstmt(stmt->as<IfStmt_ptr>());
    if (stmt->is<WhileStmt_ptr>())
        check_whilestmt(stmt->as<WhileStmt_ptr>());
}

void check_blockitem(BlockItem_ptr blockitem)
{
    if (blockitem->is<ValDecItem_ptr>())
        check_valdecitem(blockitem->as<ValDecItem_ptr>());
    if (blockitem->is<StmtItem_ptr>())
        check_stmtitem(blockitem->as<StmtItem_ptr>());
    if (blockitem->NextBlockItem != nullptr)
        check_blockitem(blockitem->NextBlockItem);
}

void check_block(Block_ptr block)
{
    check_blockitem(block->BlockItemHead);
}

void check_fundec(FunDef_ptr fundef)
{
    std::cout << fundef->FunID << std::endl;
    std::vector<VarType_ptr> func_var;
    for (auto *p = fundef->FunFParam; p ; p = p->NextFunFParam)
        func_var.push_back(check_funfparam(p));
    reverse(func_var.begin(), func_var.end()); //最后的参数放在最前面
    FuncType_ptr new_fun = new FuncType(fundef->FunID, fundef->RType, func_var);
    add_func_to_table(new_fun);
    push_symbol_table();
    for (auto p : func_var)
        add_var_to_table(p);
    std::vector<int> temp;
    func_call_ret.push_back(ResType(fundef->RType, 0, temp));
    check_block(fundef->Block);
    func_call_ret.pop_back();
    pop_symbol_table();
}

void check_compunit_valdec(CompUnitValDec_ptr compunit_valdec)
{
    check_valdec(compunit_valdec->ValDec);
}

void check_compunit_fundec(CompUnitFunDec_ptr compunit_fundec)
{
    check_fundec(compunit_fundec->FunDef);
}

void check_compunit(CompUnit_ptr compunit)
{
    if (compunit->is<CompUnitValDec_ptr>())
        check_compunit_valdec(compunit->as<CompUnitValDec_ptr>());
    if (compunit->is<CompUnitFunDec_ptr>())
        check_compunit_fundec(compunit->as<CompUnitFunDec_ptr>());
    if (compunit->NextCompUnit != nullptr)
        check_compunit(compunit->NextCompUnit);
}

void check_root(Root_ptr root)
{
    push_symbol_table();

    std::vector<VarType_ptr> temp;
    std::vector<int> dim;
    FuncType_ptr fp = new FuncType("getint", Ret_Int, temp);
    add_func_to_table(fp);
    fp = new FuncType("getch", Ret_Int, temp);
    add_func_to_table(fp);
    VarType_ptr vp0 = new VarType("_", 1, dim);
    temp.push_back(vp0);
    fp = new FuncType("getarray", Ret_Int, temp);
    temp.pop_back();
    add_func_to_table(fp);
    VarType_ptr vp1 = new VarType("__", 0, dim);
    temp.push_back(vp1);
    fp = new FuncType("putint", Ret_Void, temp);
    add_func_to_table(fp);
    fp = new FuncType("putch", Ret_Void, temp);
    add_func_to_table(fp);
    temp.push_back(vp0);
    fp = new FuncType("putarray", Ret_Void, temp);
    add_func_to_table(fp);

    check_compunit(root->CompUnitHead);
    pop_symbol_table();
    return ;
}