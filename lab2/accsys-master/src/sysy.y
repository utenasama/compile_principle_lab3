%define parse.error verbose

%{
#include <ast/ast.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <errno.h>


extern Root_ptr root;
extern int line_count;
extern int yylineno;
extern char *yytext;
extern int yylex();
extern int yyparse();
extern bool error;
void yyerror(const char *s);
int syntax_error = 0;
%}


/// types
%union {
      int int_Val;
      char* str_Val;
      Root_ptr root_ptr;
      CompUnit_ptr compunit_ptr;
      ValDec_ptr valdec_ptr;
      PrimExpr_ptr primexpr_ptr;
      Block_ptr block_ptr;
      BlockItem_ptr blockitem_ptr;
      FunRParam_ptr funrparam_ptr;
      FunDef_ptr fundef_ptr;
      FunFParam_ptr funfparam_ptr;
      LVal_ptr lval_ptr;
      ExpArr_ptr exparr_ptr;
      Stmt_ptr stmt_ptr;
      AddExpr_ptr addexp_ptr;
      MulExpr_ptr mulexp_ptr;
      UnaExpr_ptr unaexpr_ptr;
      
      LOr_ptr lor_ptr;
      LAnd_ptr land_ptr;
      Eq_ptr eq_ptr;
      Rel_ptr rel_ptr; 
}

%type <root_ptr> Root
%type <compunit_ptr> CompUnit CompUnitSub
%type <valdec_ptr> VarDecl VarDef
%type <fundef_ptr> FuncDef
%type <funfparam_ptr> FuncFParam
%type <primexpr_ptr> PrimaryExp
%type <funrparam_ptr> FuncRParams
%type <block_ptr> Block
%type <blockitem_ptr> BlockItem
%type <stmt_ptr> Stmt M_Stmt U_Stmt
%type <lor_ptr> Cond LOrExp LOrExp_Sub Exp InitVal
%type <land_ptr> LAndExp LAndExp_Sub
%type <eq_ptr> EqExp EqExp_Sub
%type <rel_ptr> RelExp RelExp_Sub
%type <addexp_ptr> AddExp AddExp_Sub
%type <mulexp_ptr> MulExp MulExp_Sub
%type <unaexpr_ptr> UnaryExp
%type <lval_ptr> LVal
%type <exparr_ptr> ExpArray  


%token <str_Val> ID
%token <int_Val> INT_CONST
%token ADD SUB MUL DIV MOD LT LE GT GE L_AND L_OR L_EQUAL L_NOT ASSIGN NE    
%token INT VOID RETURN IF ELSE WHILE BREAK CONTINUE 
%token LP RP LB RB LC RC COMMA SEMICOLON

%left L_OR L_EQUAL L_NOT
%left LT LE GT GE
%left ADD SUB
%left MUL DIV MOD

%nonassoc ELSE


%%
Root: CompUnit { root = new TreeRoot($1); };

/* CompUnit: CompUnitSub VarDecl { $$ = new Node_CompUnitValDec($2, $1); }
            | CompUnitSub FuncDef { $$ = new Node_CompUnitFunDec($2, $1); }
CompUnitSub: CompUnit { $$ = $1;}
            | { $$ = nullptr; } */

CompUnit: VarDecl { $$ = new Node_CompUnitValDec($1, nullptr); }
        | FuncDef { $$ = new Node_CompUnitFunDec($1, nullptr); }
        | VarDecl CompUnit { $$ = new Node_CompUnitValDec($1, $2); }
        | FuncDef CompUnit { $$ = new Node_CompUnitFunDec($1, $2); };


VarDecl: INT VarDef SEMICOLON { $$ = $2; };

VarDef: ID ExpArray { $$ = new Node_ValDec($1, $2, nullptr, nullptr); }
            | ID ExpArray ASSIGN InitVal { $$ = new Node_ValDec($1, $2, $4, nullptr); }
            | ID ExpArray ASSIGN InitVal COMMA VarDef { $$ = new Node_ValDec($1, $2, $4, $6); };
            | ID ExpArray COMMA VarDef { $$ = new Node_ValDec($1, $2, nullptr, $4); }


InitVal: Exp { $$ = $1; };

Cond: LOrExp { $$ = $1; };

LOrExp: LAndExp LOrExp_Sub { $$ = new Node_LOr($2, $1); }
LOrExp_Sub: L_OR LAndExp LOrExp_Sub { $$ = new Node_LOr($3, $2); }
                  | { $$ = nullptr; }

/* LOrExp: LAndExp { $$ = new Node_LOr(nullptr, $1); }
            | LOrExp L_OR LAndExp { $$ = new Node_LOr($1, $3); }; */


LAndExp: EqExp LAndExp_Sub { $$ = new Node_LAnd($2, $1); }
LAndExp_Sub: L_AND EqExp LAndExp_Sub { $$ = new Node_LAnd($3, $2); }
            | { $$ = nullptr; }

/* LAndExp: EqExp { $$ = new Node_LAnd(nullptr, $1); }
            | LAndExp L_AND EqExp { $$ = new Node_LAnd($1, $3); }; */


/* EqExp: RelExp EqExp_Sub { $$ = new Node_Eq($2, OP_None, $1); }
EqExp_Sub : L_EQUAL RelExp EqExp_Sub { $$ = new Node_Eq($3, OP_Eq, $2); }
            | NE RelExp EqExp_Sub { $$ = new Node_Eq($3, OP_Ne, $2); }
            | { $$ = nullptr; } */

EqExp: RelExp { $$ = new Node_Eq(nullptr, OP_None, $1); }
            | EqExp L_EQUAL RelExp { $$ = new Node_Eq($1, OP_Eq, $3); }
            | EqExp NE RelExp { $$ = new Node_Eq($1, OP_Ne, $3); };

/* RelExp: AddExp RelExp_Sub { $$ = new Node_Rel($2, OP_None, $1); }
RelExp_Sub: LT AddExp RelExp_Sub { $$ = new Node_Rel($3, OP_Lt, $2); }
            | LE AddExp RelExp_Sub { $$ = new Node_Rel($3, OP_Le, $2); }
            | GT AddExp RelExp_Sub { $$ = new Node_Rel($3, OP_Gt, $2); }
            | GE AddExp RelExp_Sub { $$ = new Node_Rel($3, OP_Ge, $2); }
            | { $$ = nullptr; } */

RelExp:  RelExp LT AddExp { $$ = new Node_Rel($1, OP_Lt, $3); }
            | RelExp LE AddExp { $$ = new Node_Rel($1, OP_Le, $3); }
            | RelExp GT AddExp { $$ = new Node_Rel($1, OP_Gt, $3); }
            | RelExp GE AddExp { $$ = new Node_Rel($1, OP_Ge, $3); };
            | AddExp { $$ = new Node_Rel(nullptr, OP_None, $1); }
            
Stmt: M_Stmt { $$ = $1; } | U_Stmt { $$ = $1; }
      

M_Stmt: IF LP Cond RP M_Stmt ELSE M_Stmt { $$ = new Node_IfStmt($3, $5, $7); }
            | BREAK SEMICOLON { $$ = new Node_BreakStmt(); }
            | CONTINUE SEMICOLON { $$ = new Node_ContiStmt(); }
            | RETURN Exp SEMICOLON { $$ = new Node_RetStmt($2); }
            | RETURN SEMICOLON { $$ = new Node_RetStmt(nullptr); }
            | LVal ASSIGN Exp SEMICOLON { $$ = new Node_LValStmt($1, $3); } 
            | Exp SEMICOLON { $$ = new Node_ExpStmt($1); }
            | Block { $$ = new Node_BlockInStmt($1); };
            | SEMICOLON { $$ = new Node_EmptyStmt();  }
            | WHILE LP Cond RP M_Stmt { $$ = new Node_WhileStmt($3, $5); }
            

U_Stmt: IF LP Cond RP Stmt { $$ = new Node_IfStmt($3, $5, nullptr); }
            | IF LP Cond RP M_Stmt ELSE U_Stmt { $$ = new Node_IfStmt($3, $5, $7); }
            | WHILE LP Cond RP U_Stmt { $$ = new Node_WhileStmt($3, $5); }


Exp: LOrExp { $$ = $1; };


AddExp: MulExp { $$ = new Node_AddExpr(nullptr, OP_None, $1); }
            | AddExp ADD MulExp { $$ = new Node_AddExpr($1, OP_Add, $3); }
            | AddExp SUB MulExp { $$ = new Node_AddExpr($1, OP_Sub, $3); }

/* AddExp: MulExp AddExp_Sub { $$ = new Node_AddExpr($2, OP_None, $1); }

AddExp_Sub: ADD MulExp AddExp_Sub { $$ = new Node_AddExpr($3, OP_Add, $2); }
            | SUB MulExp AddExp_Sub { $$ = new Node_AddExpr($3, OP_Sub, $2); }
            | { $$ = nullptr; } */


MulExp: UnaryExp { $$ = new Node_MulExpr(nullptr, OP_None, $1); }
            | MulExp MUL UnaryExp { $$ = new Node_MulExpr($1, OP_Mul, $3); }
            | MulExp DIV UnaryExp { $$ = new Node_MulExpr($1, OP_Div, $3); }
            | MulExp MOD UnaryExp { $$ = new Node_MulExpr($1, OP_Mod, $3); }

/* MulExp: UnaryExp MulExp_Sub { $$ = new Node_MulExpr($2, OP_None, $1); }
MulExp_Sub: MUL UnaryExp MulExp_Sub { $$ = new Node_MulExpr($3, OP_Mul, $2); }
            | DIV UnaryExp MulExp_Sub { $$ = new Node_MulExpr($3, OP_Div, $2); }
            | MOD UnaryExp MulExp_Sub { $$ = new Node_MulExpr($3, OP_Mod, $2); }
            | { $$ = nullptr; } */

FuncDef: INT ID LP RP Block { $$ = new Node_FunDef(Ret_Int, $2, nullptr, $5); }
            | VOID ID LP RP Block { $$ = new Node_FunDef(Ret_Void, $2, nullptr, $5); }
            | VOID ID LP FuncFParam RP Block { $$ = new Node_FunDef(Ret_Void, $2, $4, $6); };
            | INT ID LP FuncFParam RP Block { $$ = new Node_FunDef(Ret_Int, $2, $4, $6); }

FuncFParam: INT ID { $$ = new Node_FunFParam($2, false, nullptr, nullptr); }
            | INT ID LB RB ExpArray { $$ = new Node_FunFParam($2, true, $5, nullptr); }
            | INT ID LB RB ExpArray COMMA FuncFParam { $$ = new Node_FunFParam($2, true, $5, $7); };
            | INT ID COMMA FuncFParam { $$ = new Node_FunFParam($2, false, nullptr, $4); }

Block: LC BlockItem RC { $$ = new Node_Block($2); };
BlockItem: { $$ = nullptr; }
            | VarDecl BlockItem { $$ = new Node_BlockValDecItem($1, $2); };
            | Stmt BlockItem { $$ = new Node_BlockStmtItem($1, $2); };

UnaryExp: PrimaryExp { $$ = $1; }
            | ID LP RP { $$ = new Node_FuncUnaExpr($1, nullptr); }
            | ID LP FuncRParams RP { $$ = new Node_FuncUnaExpr($1, $3); }
            | ADD UnaryExp { $$ = new Node_PMNUnaExpr(OP_Pos, $2); }
            | SUB UnaryExp { $$ = new Node_PMNUnaExpr(OP_Neg, $2); }
            | L_NOT UnaryExp { $$ = new Node_PMNUnaExpr(OP_Lnot, $2); };

FuncRParams: Exp { $$ = new Node_FunRParam($1, nullptr); }
            | Exp COMMA FuncRParams { $$ = new Node_FunRParam($1, $3); };

PrimaryExp: LP Exp RP { $$ = new Node_LpExprRp($2); }
            | LVal { $$ = $1; }
            | INT_CONST { $$ = new Node_Integer($1); };

LVal: ID ExpArray { $$ = new Node_LVal($1, $2); }; 


ExpArray: { $$ = nullptr; }
            | LB Exp RB ExpArray { $$ = new Node_ExpArr($2, $4); };
%%


#include<stdarg.h>
void yyerror(const char *s) {
    printf("line: %d  error: %s\n", yylineno, s);
    error = 1;
}

