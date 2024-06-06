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
Value* trans_unaexp(UnaExpr_ptr unaexp);
Value* trans_exparr(ExpArr_ptr exparr);
Value* trans_addexp(AddExpr_ptr addexp);
void trans_stmt(Stmt_ptr stmt, BasicBlock *entry, BasicBlock *exit);
void trans_block(Block_ptr block, BasicBlock *entry, BasicBlock *exit);
Value* trans_rel(Rel_ptr rel);
Value* trans_eq(Eq_ptr eq);
Value* trans_land(LAnd_ptr land);
Value* trans_lor(LOr_ptr lor);
Value* trans_land_shortcut(LAnd_ptr land, BasicBlock *, BasicBlock*);
Value* trans_lor_shortcut(LOr_ptr lor, BasicBlock*, BasicBlock*);