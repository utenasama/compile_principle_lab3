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
