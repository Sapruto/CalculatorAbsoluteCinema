#pragma once

#include "Exprs.h"
#include "Types.h"

#include <numeric>
#include <stdexcept>

namespace AST::Literals {
	struct LiteralValue {
		virtual ~LiteralValue() = default;
	};

	struct LiteralExpr final : public Expr {
		LiteralValue *literal;

		LiteralExpr(LiteralValue *l)
			: Expr(ExprKind::LITERAL),
			  literal(l) {
		}
	};

	struct LiteralFraction final : LiteralValue {
		Types::LiteralInt numerator = 0;
		Types::LiteralInt denominator = 1;

		void Normalize() {
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

		LiteralFraction() = default;
		LiteralFraction(Types::LiteralInt num, Types::LiteralInt den)
			: numerator(num), denominator(den) {
			Normalize();
		}

		LiteralFraction &operator+=(const LiteralFraction &other) {
			auto lcm = std::lcm(denominator, other.denominator);
			numerator = numerator * (lcm / denominator) + other.numerator * (lcm / other.denominator);
			denominator = lcm;
			Normalize();
			return *this;
		}

		LiteralFraction &operator-=(const LiteralFraction &other) {
			auto lcm = std::lcm(denominator, other.denominator);
			numerator = numerator * (lcm / denominator) - other.numerator * (lcm / other.denominator);
			denominator = lcm;
			Normalize();
			return *this;
		}

		LiteralFraction &operator*=(const LiteralFraction &other) {
			numerator *= other.numerator;
			denominator *= other.denominator;
			Normalize();
			return *this;
		}

		LiteralFraction &operator/=(const LiteralFraction &other) {
			if (other.numerator == 0) {
				throw std::invalid_argument("Division by zero");
			}
			numerator *= other.denominator;
			denominator *= other.numerator;
			Normalize();
			return *this;
		}

		LiteralFraction operator+(const LiteralFraction &other) const {
			auto lcm = std::lcm(denominator, other.denominator);
			auto newNumerator = numerator * (lcm / denominator) + other.numerator * (lcm / other.denominator);
			return LiteralFraction(newNumerator, lcm);
		}

		LiteralFraction operator-(const LiteralFraction &other) const {
			auto lcm = std::lcm(denominator, other.denominator);
			auto newNumerator = numerator * (lcm / denominator) - other.numerator * (lcm / other.denominator);
			return LiteralFraction(newNumerator, lcm);
		}

		LiteralFraction operator*(const LiteralFraction &other) const {
			return LiteralFraction(numerator * other.numerator, denominator * other.denominator);
		}

		LiteralFraction operator/(const LiteralFraction &other) const {
			if (other.numerator == 0) {
				throw std::invalid_argument("Division by zero");
			}
			return LiteralFraction(numerator * other.denominator, denominator * other.numerator);
		}
	};
}