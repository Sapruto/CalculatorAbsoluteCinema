#pragma once

#include <string>
#include <vector>
#include <type_traits>

#include "Node.h"
#include "Operators.h"

namespace AST {
	struct Expr : public Node {};

	struct BinaryExpr final : public Expr {
		Expr* left = nullptr;
		Operators::BinOp op;
		Expr* right = nullptr;

		BinaryExpr(Expr* l, Operators::BinOp o, Expr* r)
			: left(l), op(o), right(r) {}
	};

	struct UnaryExpr final : public Expr {
		Operators::UnaryOp op;
		Expr* expr = nullptr;

		UnaryExpr(Expr* e, Operators::UnaryOp o)
			: op(o), expr(e) {}
	};

	struct CallExpr final : public Expr {
		std::string name;
		std::vector<Expr*> args;

		explicit CallExpr(std::string n)
			: name(std::move(n)) {}
	};
}