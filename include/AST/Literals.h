#pragma once

#include <cstdint>
#include <string>
#include <utility>
#include <numeric>
#include <stdexcept>

#include "BaseExprs.h"

namespace AST::Literals {
    template <class ValueType, typename Derived>
    struct SimpleLiteral : ExprCRTP<Derived> {
        ValueType value;
        explicit SimpleLiteral(ValueType v) : value(std::move(v)) {}
    };

    struct IntLiteral final : SimpleLiteral<int64_t, IntLiteral> {
        using SimpleLiteral::SimpleLiteral;
    };

    struct StringLiteral final : SimpleLiteral<std::string, StringLiteral> {
        using SimpleLiteral::SimpleLiteral;
    };

    struct BoolLiteral final : SimpleLiteral<bool, BoolLiteral> {
        using SimpleLiteral::SimpleLiteral;
    };

    struct LiteralFraction final : ExprCRTP<LiteralFraction> {
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