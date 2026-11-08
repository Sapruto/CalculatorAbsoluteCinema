#pragma once

#include <string>
#include <memory>
#include <vector>
#include <type_traits>

#include "ExprVisitors/ExprVisitor.h"
#include "Node.h"
#include "Operators.h"

namespace AST {
    struct Expr : public Node {
        virtual void Accept(Visitors::IExprVisitor& visitor) = 0;
    };

    template<typename Derived>
    struct ExprCRTP : public Expr {
        void Accept(Visitors::IExprVisitor& visitor) override {
            static_assert(std::is_base_of_v<ExprCRTP<Derived>, Derived>,
                        "Derived must inherit from ExprCRTP<Derived>");
            return visitor.Visit(static_cast<Derived*>(this));
        }
    };

    struct BinaryExpr final : public ExprCRTP<BinaryExpr> {
        Expr* left = nullptr;
        Operators::BinOp op;
        Expr* right = nullptr;

        BinaryExpr() = default;
        BinaryExpr(Expr* l, Operators::BinOp o, Expr* r)
        : left(l), op(o), right(r) {}
    };

    struct UnaryExpr final : public ExprCRTP<UnaryExpr> {
        Operators::UnaryOp op;
        Expr* expr = nullptr;

        UnaryExpr() = default;
        UnaryExpr(Expr* e, Operators::UnaryOp o) : op(o), expr(e) {}
    };

    struct CallExpr final : public ExprCRTP<CallExpr> {
        std::string name;
        std::vector<Expr*> args;

        CallExpr() = default;
        CallExpr(const std::string& n) : name(n) {}
    };
}