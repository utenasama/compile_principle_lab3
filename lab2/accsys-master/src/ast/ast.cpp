#include "ast/ast.h"

#include <fmt/core.h>
#include <cassert>

static std::string op_str(OpType op_type) {
    switch (op_type) {
#define OpcodeDefine(x, s)     \
        case x: return s;
#include "common/common.def"
        default:
            return "<unknown>";
        }
}

static std::string ret_str(RetType ret_type) {
    switch (ret_type) {
#define RetTypeDefine(x, s)     \
        case x: return s;
#include "common/common.def"
        default:
            return "<unknown>";
        }
}

// void print_expr(Expr_ptr exp, std::string prefix, std::string ident) {
//     assert(exp != nullptr);
//     fmt::print(prefix);
//     if (auto *bin_op = exp->as<TreeBinaryExpr *>()) {
//         fmt::print("BinOp \"{}\"\n", op_str(bin_op->op));
//         print_expr(bin_op->lhs, ident + "├─ ", ident + "│  ");
//         print_expr(bin_op->rhs, ident + "└─ ", ident + "   ");
//     }
//     if (auto *un_op = exp->as<TreeUnaryExpr *>()) {
//         fmt::print("UnOp \"{}\"\n", op_str(un_op->op));
//         print_expr(un_op->operand, ident + "└─ ", ident + "   ");
//     }
//     if (auto* lit = exp->as < TreeIntegerLiteral *>()) {
//         fmt::print("Int {}\n", lit->value);
//     }
// }

// //打印[][]
// //这里要先声明一下，不然print_compunit_valdec中无法调用
// void print_compunit_fundec(CompUnitFunDec_ptr compunit_fundec, std::string prefix, std::string sonprefix);
// void print_unaexp(UnaExpr_ptr unaexp, std::string prefix, std::string sonprefix);
// void print_exparr(ExpArr_ptr exparr, std::string prefix, std::string sonprefix);
// void print_addexp(AddExpr_ptr addexp, std::string prefix, std::string sonprefix);
// void print_stmt(Stmt_ptr stmt, std::string prefix, std::string sonprefix);
// void print_block(Block_ptr block, std::string prefix, std::string sonprefix);
// void print_rel(Rel_ptr rel, std::string prefix, std::string sonprefix);
// void print_eq(Eq_ptr eq, std::string prefix, std::string sonprefix);
// void print_land(LAnd_ptr land, std::string prefix, std::string sonprefix);
// void print_lor(LOr_ptr lor, std::string prefix, std::string sonprefix);

// void print_funrparam(FunRParam_ptr funrparam, std::string prefix, std::string sonprefix)
// {
//     assert(funrparam != nullptr);
//     fmt::print(prefix);
//     fmt::print("RParam:\n");
//     print_addexp(funrparam->FirstParam, sonprefix + "└─ ", sonprefix + "   ");
//     // if(funrparam->RestParam != nullptr)
//     //     print_funrparam(funrparam->RestParam, prefix, sonprefix);
// }

// void print_pmn_unaexpr(PMNUnaExpr_ptr pmn_unaexp, std::string prefix, std::string sonprefix)
// {
//     assert(pmn_unaexp != nullptr);
//     fmt::print(prefix);
//     fmt::print("{}\n", op_str(pmn_unaexp->OP));
//     print_unaexp(pmn_unaexp->Operand, sonprefix + "└─ ", sonprefix + "   ");
// }

// void print_func_unaexpr(FunUnaExpr_ptr func_unaexpr, std::string prefix, std::string sonprefix)
// {
//     assert(func_unaexpr != nullptr);
//     fmt::print(prefix);
//     fmt::print("FunId:{}\n", func_unaexpr->FunID);
//     if(func_unaexpr->FunRParam != nullptr)
//     {
//         auto *funrparam = func_unaexpr->FunRParam;
//         while(funrparam->NextFunRParam != nullptr)
//         {
//             print_funrparam(funrparam, sonprefix + "├─ ", sonprefix + "│  ");
//             funrparam = funrparam->NextFunRParam;
//         }
//         print_funrparam(funrparam, sonprefix + "└─ ", sonprefix + "   ");
//     }
// }

// void print_integer(Integer_ptr integer, std::string prefix, std::string sonprefix)
// {
//     assert(integer != nullptr);
//     fmt::print(prefix);
//     fmt::print("{}\n", integer->Val);
// }

// void print_lval(LVal_ptr lval, std::string prefix, std::string sonprefix)
// {
//     assert(lval != nullptr);
//     fmt::print(prefix);
//     fmt::print("LVal:\"{}\"\n", lval->ID);
//     if(lval->ExpArr != nullptr)
//     {
//         auto *exparr = lval->ExpArr;
//         while(exparr->NextExpArr != nullptr)
//         {
//             print_exparr(exparr, sonprefix + "├─ ", sonprefix + "│  ");
//             exparr = exparr->NextExpArr;
//         }
//         print_exparr(exparr, sonprefix + "└─ ", sonprefix + "   ");
//     }
// }

// void print_prim_unaexpr(PrimExpr_ptr primexp, std::string prefix, std::string sonprefix)
// {
//     assert(primexp != nullptr);
//     if(auto *lpexprp = primexp->as<LpExprRp_ptr>())
//     {   
//         fmt::print(prefix);
//         fmt::print("Exp\n");
//         print_addexp(lpexprp->Operand, sonprefix + "└─ ", sonprefix + "   ");
//     }
//     else if(auto *integer = primexp->as<Integer_ptr>())
//         print_integer(integer, prefix, sonprefix);
//     else if(auto *lval = primexp->as<LVal_ptr>())
//     {   
//         print_lval(lval, prefix, sonprefix);
//     }else{
//         printf("Error in print_prim_unaexpr!!!!\n");
//     }
// }

// void print_unaexp(UnaExpr_ptr unaexp, std::string prefix, std::string sonprefix)
// {
//     assert(unaexp != nullptr);
//     if(auto *pmn_unaexpr = unaexp->as<PMNUnaExpr_ptr>())
//         print_pmn_unaexpr(pmn_unaexpr, prefix, sonprefix);
//     else if(auto *func_unaexpr = unaexp->as<FunUnaExpr_ptr>())
//         print_func_unaexpr(func_unaexpr, prefix, sonprefix);
//     else{
//         auto *primexp = static_cast<PrimExpr_ptr>(unaexp);
//         print_prim_unaexpr(primexp, prefix, sonprefix);
//     }
// }

// void print_mulexp(MulExpr_ptr mulexp, std::string prefix, std::string sonprefix)
// {
//     assert(mulexp != nullptr);
//     if(mulexp->OP != OP_None)
//     {
//         fmt::print(prefix);
//         fmt::print("{}\n", op_str(mulexp->OP));
//         print_mulexp(mulexp->Operand, sonprefix + "├─ ", sonprefix + "│  ");
//         print_unaexp(mulexp->UnaExpr, sonprefix + "└─ ", sonprefix + "   ");
//     }else
//         print_unaexp(mulexp->UnaExpr, prefix, sonprefix);
// }

// void print_addexp(AddExpr_ptr addexp, std::string prefix, std::string sonprefix)
// {
//     assert(addexp != nullptr);
//     if(addexp->OP != OP_None)
//     {
//         fmt::print(prefix);
//         fmt::print("{}\n", op_str(addexp->OP));
//         print_addexp(addexp->Operand, sonprefix + "├─ ", sonprefix + "│  ");
//         print_mulexp(addexp->MulExpr, sonprefix + "└─ ", sonprefix + "   ");
//     }else
//         print_mulexp(addexp->MulExpr, prefix, sonprefix);
// }

// void print_exparr(ExpArr_ptr exparr, std::string prefix, std::string sonprefix)
// {
//     assert(exparr != nullptr);
//     fmt::print(prefix);
//     fmt::print("ExpArr[]\n");

//     print_addexp(exparr->Expr, sonprefix + "└─ ", sonprefix + "   ");
//     // if(exparr->NextExpArr != nullptr)
//     //     print_exparr(exparr->NextExpArr, prefix, sonprefix);
// }


// //打印初始值
// void print_initval(AddExpr_ptr initval, std::string prefix, std::string sonprefix)
// {
//     assert(initval != nullptr);
//     fmt::print(prefix);
//     fmt::print("=\n");

//     print_addexp(initval, sonprefix + "└─ ", sonprefix + "   ");
// }

// //具体打印变量信息
// void print_valdec(ValDec_ptr valdec, std::string prefix, std::string sonprefix)
// {
//     assert(valdec != nullptr);
//     fmt::print(prefix);
//     fmt::print("Val:\"int {}\"\n", valdec->ID);

//     if(valdec->ExpArr != nullptr)
//     {
//         auto *exparr = valdec->ExpArr;
//         while(exparr->NextExpArr != nullptr)
//         {
//             print_exparr(exparr, sonprefix + "├─ ", sonprefix + "│  ");
//             exparr = exparr->NextExpArr;
//         }
//         print_exparr(exparr, sonprefix + "└─ ", sonprefix + "   ");
//     }
//     if(valdec->InitVal != nullptr)
//         print_initval(valdec->InitVal, sonprefix + "└─ ", sonprefix + "   ");
//     // if(valdec->NextValDec != nullptr)
//     //     print_valdec(valdec->NextValDec, sonprefix + "└─ ", sonprefix + "   ");
// }


// void print_funfparam(FunFParam_ptr funfparam, std::string prefix, std::string sonprefix)
// {
//     assert(funfparam != nullptr);
//     if(funfparam->IsArr)
//     {
//         fmt::print(prefix);
//         fmt::print("fparam\"int {}[]\":\n", funfparam->ID);
//         if(funfparam->ExpArr != nullptr)
//         {
//             auto *exparr = funfparam->ExpArr;
//             while(exparr->NextExpArr != nullptr)
//             {
//                 print_exparr(exparr, sonprefix + "├─ ", sonprefix + "│  ");
//                 exparr = exparr->NextExpArr;
//             }
//             print_exparr(exparr, sonprefix + "└─ ", sonprefix + "   ");
//         }
//     }else{
//         fmt::print(prefix);
//         fmt::print("fparam\"int {}\":\n", funfparam->ID);
//     }
//     // if(funfparam->FunFParam != nullptr)
//     //     print_funfparam(funfparam->FunFParam, prefix, sonprefix);
// }


// //打印block中的valdec语句
// void print_valdecitem(ValDecItem_ptr valdecitem, std::string prefix, std::string sonprefix)
// {
//     assert(valdecitem != nullptr);
//     fmt::print(prefix);
//     fmt::print("ValDecItem:\n");

//     auto *valdec = valdecitem->ValDec;
//     while(valdec->NextValDec != nullptr)
//     {
//         print_valdec(valdec, sonprefix + "├─ ", sonprefix + "│  ");
//         valdec = valdec->NextValDec;
//     }
//     print_valdec(valdec, sonprefix + "└─ ", sonprefix + "   ");
// }

// //打印block中的statement
// void print_stmtitem(StmtItem_ptr stmtitem, std::string prefix, std::string sonprefix)
// {
//     assert(stmtitem != nullptr);
//     print_stmt(stmtitem->Stmt, prefix, sonprefix);
// }


// void print_lvalstmt(LValStmt_ptr lvalstmt, std::string prefix, std::string sonprefix)
// {
//     assert(lvalstmt != nullptr);
//     fmt::print(prefix);
//     fmt::print("LValAssignStmt:\n");
//     print_lval(lvalstmt->LVal, sonprefix + "├─ ", sonprefix + "│  ");
//     print_addexp(lvalstmt->Expr, sonprefix + "└─ ", sonprefix + "   ");
// }

// void print_retstmt(RetStmt_ptr retstmt, std::string prefix, std::string sonprefix)
// {
//     assert(retstmt != nullptr);
//     fmt::print(prefix);
//     fmt::print("RetStmt:\n");

//     if(retstmt->Expr != nullptr)
//         print_addexp(retstmt->Expr, sonprefix + "└─ ", sonprefix + "   ");
// }

// void print_expstmt(ExpStmt_ptr expstmt, std::string prefix, std::string sonprefix)
// {
//     assert(expstmt != nullptr);
//     fmt::print(prefix);
//     fmt::print("ExpStmt:\n");

//     if(expstmt->Expr != nullptr)
//         print_addexp(expstmt->Expr, sonprefix + "└─ ", sonprefix + "   ");
// }

// void print_breakstmt(BreakStmt_ptr breakstmt, std::string prefix, std::string sonprefix)
// {
//     assert(breakstmt != nullptr);
//     fmt::print(prefix);
//     fmt::print("BreakStmt\n");
// }

// void print_contistmt(ContiStmt_ptr contistmt, std::string prefix, std::string sonprefix)
// {
//     assert(contistmt != nullptr);
//     fmt::print(prefix);
//     fmt::print("ContiStmt\n");
// }

// void print_blockinstmt(BlockInStmt_ptr blockinstmt, std::string prefix, std::string sonprefix)
// {
//     assert(blockinstmt != nullptr);
//     print_block(blockinstmt->Block, prefix, sonprefix);
// }


// //         print_expr(bin_op->lhs, ident + "├─ ", ident + "│  ");
// //         print_expr(bin_op->rhs, ident + "└─ ", ident + "   ");

// void print_lor(LOr_ptr lor, std::string prefix, std::string sonprefix)
// {
//     assert(lor != nullptr);
//     if(lor->Operand != nullptr)
//     {
//         fmt::print(prefix);
//         fmt::print("Or\n");
//         print_land(lor->LAnd, sonprefix + "├─ ", sonprefix + "│  ");
//         print_lor(lor->Operand, sonprefix + "└─ ", sonprefix + "   ");
//     }else
//         print_land(lor->LAnd, prefix, sonprefix);
// }


// void print_land(LAnd_ptr land, std::string prefix, std::string sonprefix)
// {
//     assert(land != nullptr);
//     if(land->Operand != nullptr)
//     {
//         fmt::print(prefix);
//         fmt::print("And\n");
//         print_eq(land->Eq, sonprefix + "├─ ", sonprefix + "│  ");
//         print_land(land->Operand, sonprefix + "└─ ", sonprefix + "   ");
//     }else
//         print_eq(land->Eq, prefix, sonprefix);
// }


// void print_eq(Eq_ptr eq, std::string prefix, std::string sonprefix)
// {
//     assert(eq != nullptr);
//     if(eq->Operand != nullptr)
//     {
//         fmt::print(prefix);
//         fmt::print("{}\n", op_str(eq->OP));
//         print_eq(eq->Operand, sonprefix + "├─ ", sonprefix + "│  ");
//         print_rel(eq->Rel, sonprefix + "└─ ", sonprefix + "   ");
//     }else
//         print_rel(eq->Rel, prefix, sonprefix);
// }

// void print_rel(Rel_ptr rel, std::string prefix, std::string sonprefix)
// {
//     assert(rel != nullptr);
//     if(rel->Operand != nullptr)
//     {
//         fmt::print(prefix);
//         fmt::print("{}\n", op_str(rel->OP));
//         print_rel(rel->Operand, sonprefix + "├─ ", sonprefix + "│  ");
//         print_addexp(rel->Expr, sonprefix + "└─ ", sonprefix + "   ");
//     }else
//         print_addexp(rel->Expr, prefix, sonprefix);
// }

// void print_whilestmt(WhileStmt_ptr whilestmt, std::string prefix, std::string sonprefix)
// {
//     assert(whilestmt != nullptr);
//     fmt::print(prefix);
//     fmt::print("WhileStmt\n");

//     print_lor(whilestmt->Cond, sonprefix + "├─ ", sonprefix + "│  ");

//     print_stmt(whilestmt->WhileBody, sonprefix + "└─ ", sonprefix + "   ");
// }

// void print_ifstmt(IfStmt_ptr ifstmt, std::string prefix, std::string sonprefix)
// {
//     assert(ifstmt != nullptr);
//     fmt::print(prefix);
//     fmt::print("IfStmt\n");

//     print_lor(ifstmt->Cond, sonprefix + "├─ ", sonprefix + "│  ");


//     if(ifstmt->ElseBody != nullptr)
//     {
//         print_stmt(ifstmt->IfBody, sonprefix + "├─(IF Body) ", sonprefix + "│  ");
//         print_stmt(ifstmt->ElseBody, sonprefix + "└─(Else Body) ", sonprefix + "   ");
//     }else
//         print_stmt(ifstmt->IfBody, sonprefix + "└─(IF Body) ", sonprefix + "   ");
// }

// void print_emptystmt(EmptyStmt_ptr emptystmt, std::string prefix, std::string sonprefix)
// {
//     assert(emptystmt != nullptr);
//     fmt::print(prefix);
//     fmt::print("EmptyStmt\n");
// }


// void print_stmt(Stmt_ptr stmt, std::string prefix, std::string sonprefix)
// {
//     assert(stmt != nullptr);
//     if(auto *lvalstmt = stmt->as<LValStmt_ptr>())
//         print_lvalstmt(lvalstmt, prefix ,sonprefix);
//     else if(auto *retstmt = stmt->as<RetStmt_ptr>())
//         print_retstmt(retstmt, prefix ,sonprefix);
//     else if(auto *expstmt = stmt->as<ExpStmt_ptr>())
//         print_expstmt(expstmt, prefix ,sonprefix);
//     else if(auto *breakstmt = stmt->as<BreakStmt_ptr>())
//         print_breakstmt(breakstmt, prefix ,sonprefix);
//     else if(auto *contistmt = stmt->as<ContiStmt_ptr>())
//         print_contistmt(contistmt, prefix ,sonprefix);
//     else if(auto *blockinstmt = stmt->as<BlockInStmt_ptr>())
//         print_blockinstmt(blockinstmt, prefix ,sonprefix);
//     else if(auto *ifstmt = stmt->as<IfStmt_ptr>())
//         print_ifstmt(ifstmt, prefix ,sonprefix);
//     else if(auto *whilestmt = stmt->as<WhileStmt_ptr>())
//         print_whilestmt(whilestmt, prefix ,sonprefix);
//     else if(auto *emptystmt = stmt->as<EmptyStmt_ptr>())
//         print_emptystmt(emptystmt, prefix ,sonprefix);
//     else
//         fmt::print("error in function print_stmt!\n");
// }

// void print_blockitem(BlockItem_ptr blockitem, std::string prefix, std::string sonprefix)
// {
//     assert(blockitem != nullptr);
//     if(auto *valdecitem = blockitem->as<ValDecItem_ptr>())
//         print_valdecitem(valdecitem, prefix, sonprefix);
//     else if(auto *stmtitem = blockitem->as<StmtItem_ptr>())
//         print_stmtitem(stmtitem, prefix, sonprefix);
// }

// void print_block(Block_ptr block, std::string prefix, std::string sonprefix)
// {
//     assert(block != nullptr);
//     fmt::print(prefix);
//     fmt::print("Block\n");
//     if(block->BlockItemHead != nullptr)
//     {
//         auto *blockitem = block->BlockItemHead;
//         while(blockitem->NextBlockItem != nullptr)
//         {
//             print_blockitem(blockitem, sonprefix + "├─ ", sonprefix + "│  ");
//             blockitem = blockitem->NextBlockItem;
//         }
//         print_blockitem(blockitem, sonprefix + "└─ ", sonprefix + "   ");
//     }
// }

// //具体打印函数信息
// void print_fundec(FunDef_ptr fundef, std::string prefix, std::string sonprefix)
// {
//     assert(fundef != nullptr);
//     fmt::print(prefix);
//     fmt::print("Func:\"{} {}\"\n", ret_str(fundef->RType), fundef->FunID);
//     if(fundef->FunFParam != nullptr)
//     {
//         auto *funfparam = fundef->FunFParam;
//         while(funfparam->NextFunFParam != nullptr)
//         {
//             print_funfparam(funfparam, sonprefix + "├─ ", sonprefix + "│  ");
//             funfparam = funfparam->NextFunFParam;
//         }
//         print_funfparam(funfparam, sonprefix + "├─ ", sonprefix + "│  ");  
//         //这里比较特殊，因为语法树下面一定有block，所以这里最后一个fparam也要打印├─
//     }
//     print_block(fundef->Block, sonprefix + "└─ ", sonprefix + "   ");
// }


// //打印变量声明
// void print_compunit_valdec(CompUnitValDec_ptr compunit_valdec, std::string prefix, std::string sonprefix)
// {
//     assert(compunit_valdec != nullptr);
//     fmt::print(prefix);
//     fmt::print("ValDec\n");

//     //具体打印变量信息
//     auto *valdec = compunit_valdec->ValDec;
//     while(valdec->NextValDec != nullptr)
//     {
//         print_valdec(valdec, sonprefix + "├─ ", sonprefix + "│  ");
//         valdec = valdec->NextValDec;
//     }
//     print_valdec(valdec, sonprefix + "└─ ", sonprefix + "   ");
// }


// //打印函数声明
// void print_compunit_fundec(CompUnitFunDec_ptr compunit_fundec, std::string prefix, std::string sonprefix)
// {
//     assert(compunit_fundec != nullptr);
//     fmt::print(prefix);
//     fmt::print("FunDec\n");

//     //具体打印函数信息
//     print_fundec(compunit_fundec->FunDef, sonprefix + "└─ ", sonprefix + "   ");
// }


// //打印CompUnit
// void print_compunit(CompUnit_ptr compunit, std::string prefix, std::string sonprefix)
// {
//     assert(compunit != nullptr);
//     fmt::print(prefix);
//     fmt::print("CompUnit\n");

//     //根据compunit中语句的具体类型(函数声明 变量声明)进一步打印
//     while(compunit->NextCompUnit != nullptr)
//     {
//         if(auto *compunit_valdec = compunit->as<CompUnitValDec_ptr>())
//             print_compunit_valdec(compunit_valdec, sonprefix + "├─ ", sonprefix + "│  ");
//         else if(auto *compunit_fundec = compunit->as<CompUnitFunDec_ptr>())
//             print_compunit_fundec(compunit_fundec, sonprefix + "├─ ", sonprefix + "│  ");
//         else
//             fmt::print("Error in function print_compunit\n");

//         compunit = compunit->NextCompUnit;
//     }

//     if(auto *compunit_valdec = compunit->as<CompUnitValDec_ptr>())
//         print_compunit_valdec(compunit_valdec, sonprefix + "└─ ", sonprefix + "   ");
//     else if(auto *compunit_fundec = compunit->as<CompUnitFunDec_ptr>())
//         print_compunit_fundec(compunit_fundec, sonprefix + "└─ ", sonprefix + "   ");
//     else
//         fmt::print("Error in function print_compunit\n");
// }

// //打印root
// void print_root(Root_ptr root, std::string prefix, std::string sonprefix)
// {
//     assert(root != nullptr);
//     fmt::print(prefix);
//     fmt::print("Root\n");
//     if(root->CompUnitHead != nullptr)
//         print_compunit(root->CompUnitHead, sonprefix + "└─ ", sonprefix + "   ");
// }