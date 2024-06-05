#pragma once
#include <cstdint>
#include <type_traits>
#include <string>
#include <vector>
#include "ast.h"

struct VarType;
using VarType_ptr = VarType *;
struct FuncType;
using FuncType_ptr = FuncType *;

struct VarType
{
    std::string ValID;
    int Dimensions;
    std::vector<int> DimensionSizes;
    VarType(std::string valid, int dimensions, std::vector<int> dim_vec) : ValID(valid), Dimensions(dimensions), DimensionSizes(dim_vec) {}
};

struct FuncType
{
    std::string FuncID;
    RetType RType;
    std::vector<VarType_ptr> FParams;
    FuncType(std::string funcid, RetType rtype, std::vector<VarType_ptr> fparams) : FuncID(funcid), RType(rtype), FParams(fparams) {}
};

struct ResType
{
    RetType RType;
    int Dimensions;
    std::vector<int> DimensionSizes;
    int Value;   
    bool Is_Var; 

    ResType(RetType rettype, int dimensions, std::vector<int> dim_vec, int value = 1, bool is_var = false) : RType(rettype), Dimensions(dimensions), DimensionSizes(dim_vec), Value(value), Is_Var(is_var) {}

    void set_value(int val)
    {
        this->Value = val;
    }

    bool operator==(const ResType& right)
    {
        if (RType != right.RType)
            return false;
        if (RType == Ret_Void) return true;
        if (!Is_Var && !right.Is_Var) return true;
        if (Dimensions != right.Dimensions) return false;
        for (int i = 0 ; i < Dimensions ; i++)
            if (DimensionSizes[i] != right.DimensionSizes[i] && DimensionSizes[i] != -1 && right.DimensionSizes[i] != -1) return false;
        return true;
    }

    bool operator!=(const ResType& right)
    {
        return !(*this == right);
    }

    int get_value() { return this->Value; }
};

void check_funrparam(FunRParam_ptr funrparam, std::vector<VarType_ptr> funfparam);

ResType check_pmn_unaexpr(PMNUnaExpr_ptr pmn_unaexp);

ResType check_func_unaexpr(FunUnaExpr_ptr func_unaexpr);

ResType check_integer(Integer_ptr integer);

ResType check_lval(LVal_ptr lval);

ResType check_prim_unaexpr(PrimExpr_ptr primexp);

ResType check_unaexp(UnaExpr_ptr unaexp);

ResType check_mulexp(MulExpr_ptr mulexp);

ResType check_addexp(AddExpr_ptr addexp);

void check_exparr(ExpArr_ptr exparrm, int &dimension, std::vector<int> &dim);

ResType check_initval(AddExpr_ptr initval);

void check_valdec(ValDec_ptr valdec);

VarType_ptr check_funfparam(FunFParam_ptr funfparam);

void check_valdecitem(ValDecItem_ptr valdecitem);

void check_stmtitem(StmtItem_ptr stmtitem);

void check_lvalstmt(LValStmt_ptr lvalstmt);

void check_retstmt(RetStmt_ptr retstmt);

void check_expstmt(ExpStmt_ptr expstmt);

void check_breakstmt(BreakStmt_ptr breakstmt);

void check_contistmt(ContiStmt_ptr contistmt);

void check_blockinstmt(BlockInStmt_ptr blockinstmt);

ResType check_lor(LOr_ptr lor);

ResType check_land(LAnd_ptr land);

ResType check_eq(Eq_ptr eq);

ResType check_rel(Rel_ptr rel);

void check_whilestmt(WhileStmt_ptr whilestmt);

void check_ifstmt(IfStmt_ptr ifstmt);

void check_emptystmt(EmptyStmt_ptr emptystmt);

void check_stmt(Stmt_ptr stmt);

void check_blockitem(BlockItem_ptr blockitem);

void check_block(Block_ptr block);

void check_fundec(FunDef_ptr fundef);

void check_compunit_valdec(CompUnitValDec_ptr compunit_valdec);

void check_compunit_fundec(CompUnitFunDec_ptr compunit_fundec);

void check_compunit(CompUnit_ptr compunit);

void check_root(Root_ptr root);