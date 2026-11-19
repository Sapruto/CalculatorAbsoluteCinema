#pragma once

#include "ASTFwd.h"
#include "Node.h"
#include "Operators.h"

#include <string>
#include <type_traits>
#include <vector>

namespace Parsing::BinaryAst {
	enum class ExprKind { BINARY,
						  UNARY,
						  CALL,
						  LITERAL };

	struct Expr : public Node {
		const ExprKind kind;

	protected:
		explicit Expr(ExprKind k) : kind(k) {}
	};

	struct BinaryExpr final : public Expr {
		Expr *left = nullptr;
		Operators::BinOp op;
		Expr *right = nullptr;

		BinaryExpr(Expr *l, Operators::BinOp o, Expr *r)
			: Expr(ExprKind::BINARY), left(l), op(o), right(r) {}
	};

	struct UnaryExpr final : public Expr {
		Operators::UnaryOp op;
		Expr *expr = nullptr;

		UnaryExpr(Expr *e, Operators::UnaryOp o)
			: Expr(ExprKind::UNARY), op(o), expr(e) {}
	};

	struct CallExpr final : public Expr {
		std::string name;
		std::vector<Expr *> args;

		explicit CallExpr(std::string n)
			: Expr(ExprKind::CALL), name(std::move(n)) {}
	};

	struct LiteralExpr final : public Expr {
		Literals::LiteralValue *literal;

		LiteralExpr(Literals::LiteralValue *l)
			: Expr(ExprKind::LITERAL),
			  literal(l) {
		}
	};
}