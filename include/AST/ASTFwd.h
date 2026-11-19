#pragma once

namespace AST {
	struct Node;
	struct Expr;

	struct BinaryExpr;
	struct UnaryExpr;
	struct CallExpr;
	struct LiteralExpr;

	namespace Literals {
		struct LiteralValue;
		struct Fraction;
	}
}