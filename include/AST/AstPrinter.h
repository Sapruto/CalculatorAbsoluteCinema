#pragma once

#include <string>

#include "Parsing/Utils.h"
#include "Visit.h"

inline std::string Print(AST::Expr* e) {
    using namespace AST;

    return Visit(e, Overloaded{
        [](BinaryExpr* b) -> std::string {
            return "(" + Print(b->left) + " " + Parsing::Utils::FormatBinOp(b->op) + " " + Print(b->right) + ")";
        },
        [](UnaryExpr* u) -> std::string {
            if (u->op == Operators::UnaryOp::NEGATION)
                return "(-" + Print(u->expr) + ")";
            return "(" + Print(u->expr) + "!)";
        },
        [](CallExpr* c) -> std::string {
            std::string result = c->name + "(";
            for (size_t i = 0; i < c->args.size(); ++i) {
                if (i) result += ", ";
                result += Print(c->args[i]);
            }
            return result + ")";
        },
        [](Literals::LiteralExpr* l) -> std::string {
            auto* f = dynamic_cast<Literals::LiteralFraction*>(l->literal);
            if (!f)
                return "<unknown literal>";
            if (f->denominator == 1)
                return std::to_string(f->numerator);
            return std::to_string(f->numerator) + "/" + std::to_string(f->denominator);
        },
    });
}