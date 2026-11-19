#pragma once

#include "Literals.h"
#include "Exprs.h"

#include <concepts>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace AST {
	template <class... Ts>
	struct Overloaded : Ts... {
		using Ts::operator()...;
	};

	template <class Func>
	decltype(auto) Visit(Expr *e, Func &&func) {
		switch (e->kind) {
		case ExprKind::BINARY:
			return std::forward<Func>(func)(static_cast<BinaryExpr *>(e));
		case ExprKind::UNARY:
			return std::forward<Func>(func)(static_cast<UnaryExpr *>(e));
		case ExprKind::CALL:
			return std::forward<Func>(func)(static_cast<CallExpr *>(e));
		case ExprKind::LITERAL:
			return std::forward<Func>(func)(static_cast<Literals::LiteralExpr *>(e));
		}
		throw std::logic_error("Visit: unknown ExprKind");
	}
}