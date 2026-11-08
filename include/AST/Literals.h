#pragma once

#include "Exprs.h"

#include <cstdint>
#include <numeric>
#include <stdexcept>
#include <string>
#include <utility>

namespace AST::Literals {
struct LiteralValue {
    virtual ~LiteralValue() = 0;
};

struct LiteralExpr final : public Expr {
    LiteralValue* literal;

	LiteralExpr() = default;
	LiteralExpr(LiteralValue* l)
		: literal(l) {}
};

struct LiteralFraction final : LiteralValue {
	int64_t numerator;
	int64_t denominator = 1;

	LiteralFraction() = default;

	LiteralFraction(int64_t num, int64_t den)
		: numerator(num), denominator(den) {
		if (denominator == 0)
			throw std::invalid_argument("LiteralFraction: zero denominator");
		if (denominator < 0) {
			numerator = -numerator;
			denominator = -denominator;
		}
		auto g = std::gcd(numerator, denominator);
		numerator /= g;
		denominator /= g;
	}
};
}