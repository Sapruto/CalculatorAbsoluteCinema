#pragma once

#include "Exprs.h"
#include "Types.h"

#include <numeric>
#include <stdexcept>
#include <type_traits>
#include <typeindex>
#include <typeinfo>

namespace Parsing::BinaryAst::Literals {
	struct LiteralValue {
		virtual ~LiteralValue() = default;

		virtual std::type_index GetType() const = 0;
	};

	struct Fraction final : public LiteralValue {
		Types::LiteralInt numerator = 0;
		Types::LiteralInt denominator = 1;

		void Normalize() {
			if (denominator == 0)
				throw std::invalid_argument("Fraction: zero denominator");
			if (denominator < 0) {
				numerator = -numerator;
				denominator = -denominator;
			}
			auto g = std::gcd(numerator, denominator);
			numerator /= g;
			denominator /= g;
		}

		Fraction() = default;
		Fraction(Types::LiteralInt num, Types::LiteralInt den)
			: numerator(num), denominator(den) {
			Normalize();
		}

		Fraction &operator+=(const Fraction &other) {
			auto lcm = std::lcm(denominator, other.denominator);
			numerator = numerator * (lcm / denominator) + other.numerator * (lcm / other.denominator);
			denominator = lcm;
			Normalize();
			return *this;
		}

		Fraction &operator-=(const Fraction &other) {
			auto lcm = std::lcm(denominator, other.denominator);
			numerator = numerator * (lcm / denominator) - other.numerator * (lcm / other.denominator);
			denominator = lcm;
			Normalize();
			return *this;
		}

		Fraction &operator*=(const Fraction &other) {
			numerator *= other.numerator;
			denominator *= other.denominator;
			Normalize();
			return *this;
		}

		Fraction &operator/=(const Fraction &other) {
			if (other.numerator == 0) {
				throw std::invalid_argument("Division by zero");
			}
			numerator *= other.denominator;
			denominator *= other.numerator;
			Normalize();
			return *this;
		}

		Fraction operator+(const Fraction &other) const {
			auto lcm = std::lcm(denominator, other.denominator);
			auto newNumerator = numerator * (lcm / denominator) + other.numerator * (lcm / other.denominator);
			return Fraction(newNumerator, lcm);
		}

		Fraction operator-(const Fraction &other) const {
			auto lcm = std::lcm(denominator, other.denominator);
			auto newNumerator = numerator * (lcm / denominator) - other.numerator * (lcm / other.denominator);
			return Fraction(newNumerator, lcm);
		}

		Fraction operator*(const Fraction &other) const {
			return Fraction(numerator * other.numerator, denominator * other.denominator);
		}

		Fraction operator/(const Fraction &other) const {
			if (other.numerator == 0) {
				throw std::invalid_argument("Division by zero");
			}
			return Fraction(numerator * other.denominator, denominator * other.numerator);
		}

		Fraction operator-() const {
			return Fraction(-numerator, denominator);
		}

		std::type_index GetType() const override { return typeid(Fraction); }
	};

	struct Identifier final : public LiteralValue {
		std::string value;

		Identifier() = default;
		Identifier(const std::string& _value) : value(_value) {}

		std::type_index GetType() const override { return typeid(Identifier); }
	};
}