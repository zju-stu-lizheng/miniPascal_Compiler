#ifndef __AST_HPP__
#define __AST_HPP__
#include "AST_BaseNode.hpp"
#include "AST_Expression.hpp"
#include "AST_Program.hpp"
#include "AST_Type.hpp"
#include "AST_Value.hpp"
#include "AST_Statement.hpp"
//生成代码的debug信息
#define GEN_DEBUG

extern AST_Program* ast_root;
#endif