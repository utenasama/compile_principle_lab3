#pragma once
#include <cstdint>
#include <type_traits>
#include <string>

enum OpType
{
#define OpcodeDefine(x, s) x,
#include "common/common.def"
};

enum NodeType
{
#define TreeNodeDefine(x) x,
#include "common/common.def"
};

// 返回值类型
enum RetType
{
#define RetTypeDefine(x, s) x,
#include "common/common.def"
};
//

struct Node;
using Node_ptr = Node *;
//struct TreeType;


// AST节点定义
struct TreeRoot;
using Root_ptr = TreeRoot *;
struct Node_CompUnit;
using CompUnit_ptr = Node_CompUnit *;    
struct Node_CompUnitValDec; // 变量声明模块
using CompUnitValDec_ptr = Node_CompUnitValDec *;   
struct Node_ValDec;         // 变量声明    
using ValDec_ptr = Node_ValDec *;   

struct Node_CompUnitFunDec; // 函数声明模块
using CompUnitFunDec_ptr = Node_CompUnitFunDec *;
struct Node_FunDef;         // 函数声明
using FunDef_ptr = Node_FunDef *;
struct Node_FuncUnaExpr;    // 函数调用表达式
using FunUnaExpr_ptr = Node_FuncUnaExpr *;
struct Node_FunRParam;      // 函数调用参数
using FunRParam_ptr = Node_FunRParam *;
struct Node_FunFParam;      // 函数定义参数
using FunFParam_ptr = Node_FunFParam *;

struct Node_ExpArr;     // 表达式数组
using ExpArr_ptr = Node_ExpArr *;  
struct Node_AddExpr;    // 加法表达式
using AddExpr_ptr = Node_AddExpr *;
struct Node_MulExpr;    // 乘法表达式
using MulExpr_ptr = Node_MulExpr *;
struct Node_UnaExpr;        // 一元表达式
using UnaExpr_ptr = Node_UnaExpr *;
struct Node_PMNUnaExpr;     // 正负号表达式
using PMNUnaExpr_ptr = Node_PMNUnaExpr *;

struct Node_PrimExpr;       // 基本表达式
using PrimExpr_ptr = Node_PrimExpr *;
struct Node_LpExprRp;       // 括号表达式
using LpExprRp_ptr = Node_LpExprRp *;
struct Node_Integer;        // 整数
using Integer_ptr = Node_Integer *;
struct Node_LVal;           // 左值
using LVal_ptr = Node_LVal *;

struct Node_Block;          // 代码块
using Block_ptr = Node_Block *;
struct Node_BlockItem;      // 代码块内的一条语句
using BlockItem_ptr = Node_BlockItem *;
struct Node_BlockValDecItem;    // 代码块内的变量声明
using ValDecItem_ptr = Node_BlockValDecItem *;
struct Node_BlockStmtItem;      // 代码块内的语句
using StmtItem_ptr = Node_BlockStmtItem *;
struct Node_Stmt;               // 语句
using Stmt_ptr = Node_Stmt *;
struct Node_LValStmt;           // 赋值语句
using LValStmt_ptr = Node_LValStmt *;
struct Node_RetStmt;            // 返回语句
using RetStmt_ptr = Node_RetStmt *;
struct Node_ExpStmt;            // 表达式语句
using ExpStmt_ptr = Node_ExpStmt *;
struct Node_BreakStmt;          // break语句
using BreakStmt_ptr = Node_BreakStmt *;
struct Node_ContiStmt;          // continue语句
using ContiStmt_ptr = Node_ContiStmt *;
struct Node_BlockInStmt;        // 代码块内的语句
using BlockInStmt_ptr = Node_BlockInStmt *;
struct Node_IfStmt;             // if语句
using IfStmt_ptr = Node_IfStmt *;
struct Node_WhileStmt;          // while语句
using WhileStmt_ptr = Node_WhileStmt *;
struct Node_LOr;                // 逻辑或
using LOr_ptr = Node_LOr *;
struct Node_LAnd;               // 逻辑与
using LAnd_ptr = Node_LAnd *;
struct Node_Eq;                 // 等于
using Eq_ptr = Node_Eq *;
struct Node_Rel;                // 关系
using Rel_ptr = Node_Rel *;
struct Node_EmptyStmt;          // 空语句
using EmptyStmt_ptr = Node_EmptyStmt *;
//

struct Node
{
    NodeType node_type;
    Node(NodeType type) : node_type(type) {}
    template <typename T>
    bool is()
    {
        return node_type == std::remove_pointer_t<T>::this_type;
    }
    template <typename T>
    T as()
    {
        if (is<T>())
            return static_cast<T>(this);
        return nullptr;
    }
    template <typename T>
    T as_unchecked() { return static_cast<T>(this); }
};

// AST节点定义
struct TreeRoot : public Node
{
    constexpr static NodeType this_type = ND_TreeRoot;
    CompUnit_ptr CompUnitHead;
    TreeRoot(CompUnit_ptr compunit_head) : Node(this_type), CompUnitHead(compunit_head) {}
};

struct Node_CompUnit : public Node
{
    CompUnit_ptr NextCompUnit;
    Node_CompUnit(CompUnit_ptr compunit_next, NodeType type) : Node(type), NextCompUnit(compunit_next) {}
};

struct Node_CompUnitValDec : public Node_CompUnit
{
    constexpr static NodeType this_type = ND_CompUnitValDec;
    ValDec_ptr ValDec;
    
    Node_CompUnitValDec(ValDec_ptr valdec_ptr, CompUnit_ptr compunit_next) : Node_CompUnit(compunit_next, this_type), ValDec(valdec_ptr) {}
};

struct Node_CompUnitFunDec : public Node_CompUnit
{
    constexpr static NodeType this_type = ND_CompUnitFunDec;
    FunDef_ptr FunDef;
    
    Node_CompUnitFunDec(FunDef_ptr fundef_ptr, CompUnit_ptr compunit_next) : Node_CompUnit(compunit_next, this_type), FunDef(fundef_ptr) {}
};

struct Node_ValDec : public Node
{
    constexpr static NodeType this_type = ND_ValDec;
    std::string ID;
    ExpArr_ptr ExpArr;
    AddExpr_ptr InitVal;
    ValDec_ptr NextValDec; 
    Node_ValDec(std::string id, ExpArr_ptr exparr, AddExpr_ptr initval, ValDec_ptr valdec_next) : 
        Node(this_type), ID(id), ExpArr(exparr), InitVal(initval), NextValDec(valdec_next) {}
};

struct Node_AddExpr : public Node
{
    constexpr static NodeType this_type = ND_AddExpr;
    AddExpr_ptr Operand;
    OpType OP;
    MulExpr_ptr MulExpr;
    Node_AddExpr(AddExpr_ptr operand, OpType op, MulExpr_ptr mulexpr) : Node(this_type), Operand(operand), OP(op), MulExpr(mulexpr) {}
};

struct Node_MulExpr : public Node
{
    constexpr static NodeType this_type = ND_MulExpr;
    MulExpr_ptr Operand;
    OpType OP;
    UnaExpr_ptr UnaExpr;
    Node_MulExpr(MulExpr_ptr operand, OpType op, UnaExpr_ptr unaexpr) : Node(this_type), Operand(operand), OP(op), UnaExpr(unaexpr) {}
};

struct Node_UnaExpr : public Node
{
    Node_UnaExpr(NodeType type) : Node(type) {}
};

struct Node_FuncUnaExpr : public Node_UnaExpr
{
    std::string FunID;
    FunRParam_ptr FunRParam;
    constexpr static NodeType this_type = ND_FunUnaExpr;
    Node_FuncUnaExpr(std::string funid, FunRParam_ptr funrparam) : Node_UnaExpr(this_type), FunID(funid), FunRParam(funrparam) {}
};

struct Node_FunRParam : public Node
{
    AddExpr_ptr FirstParam;
    FunRParam_ptr NextFunRParam;
    constexpr static NodeType this_type = ND_FunRParam;
    Node_FunRParam(AddExpr_ptr firstparam, FunRParam_ptr nextfunrparam) : Node(this_type), FirstParam(firstparam), NextFunRParam(nextfunrparam) {}
};

struct Node_PMNUnaExpr : public Node_UnaExpr
{
    OpType OP;
    UnaExpr_ptr Operand;
    constexpr static NodeType this_type = ND_PMNUnaExpr;
    Node_PMNUnaExpr(OpType op, UnaExpr_ptr operand) : Node_UnaExpr(this_type), OP(op), Operand(operand) {}
};

struct Node_PrimExpr : public Node_UnaExpr
{
    Node_PrimExpr(NodeType type) : Node_UnaExpr(type) {}
};

struct Node_LpExprRp : public Node_PrimExpr
{
    AddExpr_ptr Operand;
    constexpr static NodeType this_type = ND_LpExprRp;
    Node_LpExprRp(AddExpr_ptr operand) : Node_PrimExpr(this_type), Operand(operand) {}
};

struct Node_Integer : public Node_PrimExpr
{
    int64_t Val;
    constexpr static NodeType this_type = ND_Integer;
    Node_Integer(int64_t val) : Node_PrimExpr(this_type), Val(val) {}
};

struct Node_LVal : public Node_PrimExpr
{
    constexpr static NodeType this_type = ND_LVal;
    std::string ID;
    ExpArr_ptr ExpArr;
    Node_LVal(std::string id, ExpArr_ptr exparr) : Node_PrimExpr(this_type), ID(id), ExpArr(exparr) {}
};

struct Node_FunDef : public Node
{
    constexpr static NodeType this_type = ND_FunDef;
    RetType RType;
    std::string FunID;
    FunFParam_ptr FunFParam;
    Block_ptr Block;
    Node_FunDef(RetType rtype, std::string funid, FunFParam_ptr funfparam, Block_ptr block) : Node(this_type), RType(rtype), FunID(funid), FunFParam(funfparam), Block(block) {}
};

struct Node_FunFParam : public Node
{
    constexpr static NodeType this_type = ND_FunFParam;
    std::string ID;
    bool IsArr;
    ExpArr_ptr ExpArr;
    FunFParam_ptr NextFunFParam;
    Node_FunFParam(std::string id, bool isarr, ExpArr_ptr exparr, FunFParam_ptr funfparam_next) : 
        Node(this_type), ID(id), IsArr(isarr), ExpArr(exparr), NextFunFParam(funfparam_next) {}
};

struct Node_ExpArr : public Node
{
    constexpr static NodeType this_type = ND_ExpArr;
    AddExpr_ptr Expr;
    ExpArr_ptr NextExpArr;
    Node_ExpArr(AddExpr_ptr expr, ExpArr_ptr exparr_next) : Node(this_type), Expr(expr), NextExpArr(exparr_next) {}
};

struct Node_Block : public Node
{
    constexpr static NodeType this_type = ND_Block;
    BlockItem_ptr BlockItemHead;
    Node_Block(BlockItem_ptr blockitem_head) : Node(this_type), BlockItemHead(blockitem_head) {}
};

struct Node_BlockItem : public Node
{
    BlockItem_ptr NextBlockItem;
    Node_BlockItem(BlockItem_ptr nextblockitem, NodeType type) : Node(type), NextBlockItem(nextblockitem) {}
};

struct Node_BlockValDecItem : public Node_BlockItem
{
    constexpr static NodeType this_type = ND_BlockValDecItem;
    ValDec_ptr ValDec;
    BlockItem_ptr NextBlockItem;
    Node_BlockValDecItem(ValDec_ptr valdec, BlockItem_ptr nextblockitem) : Node_BlockItem(nextblockitem, this_type), ValDec(valdec) {}
};

struct Node_BlockStmtItem : public Node_BlockItem
{
    Stmt_ptr Stmt;
    BlockItem_ptr NextBlockItem;
    constexpr static NodeType this_type = ND_BlockStmtItem;
    Node_BlockStmtItem(Stmt_ptr stmt, BlockItem_ptr nextblockitem) : Node_BlockItem(nextblockitem, this_type), Stmt(stmt) {}
};

struct Node_Stmt : public Node
{
    Node_Stmt(NodeType type) : Node(type) {}
};

struct Node_LValStmt : public Node_Stmt 
{
    constexpr static NodeType this_type = ND_LValStmt;
    LVal_ptr LVal;
    AddExpr_ptr Expr;
    Node_LValStmt(LVal_ptr lval, AddExpr_ptr expr) : Node_Stmt(this_type), LVal(lval), Expr(expr) {} 
};

struct Node_RetStmt : public Node_Stmt
{
    constexpr static NodeType this_type = ND_RetStmt;
    AddExpr_ptr Expr;
    Node_RetStmt(AddExpr_ptr expr) : Node_Stmt(this_type), Expr(expr) {}
};

struct Node_ExpStmt : public Node_Stmt
{
    constexpr static NodeType this_type = ND_ExpStmt;
    AddExpr_ptr Expr;
    Node_ExpStmt(AddExpr_ptr expr) : Node_Stmt(this_type), Expr(expr) {}
};

struct Node_BreakStmt : public Node_Stmt
{
    constexpr static NodeType this_type = ND_BreakStmt;
    Node_BreakStmt() : Node_Stmt(this_type) {}
};

struct Node_ContiStmt : public Node_Stmt
{
    constexpr static NodeType this_type = ND_ContiStmt;
    Node_ContiStmt() : Node_Stmt(this_type) {}
};

struct Node_BlockInStmt : public Node_Stmt
{
    constexpr static NodeType this_type = ND_BlockInStmt;
    Block_ptr Block;
    Node_BlockInStmt(Block_ptr block) : Node_Stmt(this_type), Block(block) {}
};

struct Node_IfStmt : public Node_Stmt
{
    constexpr static NodeType this_type = ND_IfStmt;
    LOr_ptr Cond;
    Stmt_ptr IfBody;
    Stmt_ptr ElseBody;
    Node_IfStmt(LOr_ptr cond, Stmt_ptr ifbody, Stmt_ptr elsebody) : Node_Stmt(this_type), Cond(cond), IfBody(ifbody), ElseBody(elsebody) {}
};

struct Node_WhileStmt : public Node_Stmt
{
    constexpr static NodeType this_type = ND_WhileStmt;
    LOr_ptr Cond;
    Stmt_ptr WhileBody;
    Node_WhileStmt(LOr_ptr cond, Stmt_ptr whilebody) : Node_Stmt(this_type), Cond(cond), WhileBody(whilebody) {}
};

struct Node_LOr : public Node
{
    constexpr static NodeType this_type = ND_LOr;
    LOr_ptr Operand;
    LAnd_ptr LAnd;
    Node_LOr(LOr_ptr operand, LAnd_ptr land) : Node(this_type), Operand(operand), LAnd(land) {}
};

struct Node_LAnd : public Node
{
    constexpr static NodeType this_type = ND_LAnd;
    LAnd_ptr Operand;
    Eq_ptr Eq;
    Node_LAnd(LAnd_ptr operand, Eq_ptr eq) : Node(this_type), Operand(operand), Eq(eq) {}
};

struct Node_Eq : public Node
{
    constexpr static NodeType this_type = ND_Eq;
    Eq_ptr Operand;
    OpType OP;
    Rel_ptr Rel;
    Node_Eq(Eq_ptr operand, OpType op, Rel_ptr rel) : Node(this_type), Operand(operand), OP(op), Rel(rel) {}
    // Node_Eq(Rel_ptr rel, OpType op, Eq_ptr operand) : Rel(rel), Operand(operand), OP(op), Node(this_type) {}
};

struct Node_Rel : public Node
{
    constexpr static NodeType this_type = ND_Rel;
    Rel_ptr Operand;
    OpType OP;
    AddExpr_ptr Expr;
    Node_Rel(Rel_ptr operand, OpType op, AddExpr_ptr expr) : Node(this_type), Operand(operand), OP(op), Expr(expr) {}
};

struct Node_EmptyStmt: public Node_Stmt{
    constexpr static NodeType this_type = ND_EmptyStmt;
    Node_EmptyStmt() : Node_Stmt(this_type) {}
};

/// A possible helper function dipatch based on the type of `Node_Expr`
// void print_expr(AddExpr_ptr exp, std::string prefix = "", std::string ident = "");
void print_root(Root_ptr root, std::string prefix, std::string sonprefix);