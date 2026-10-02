#pragma once

#include "ASTFwd.h"

namespace AST {
    class ExprVisitor {
    public:
        virtual void Visit(BinaryExpr& expr) = 0;
        virtual void Visit(UnaryExpr& expr) = 0;
        virtual void Visit(CallExpr& expr) = 0;

        virtual void Visit(Literals::IntLiteral& expr) = 0;
        virtual void Visit(Literals::StringLiteral& expr) = 0;
        virtual void Visit(Literals::BoolLiteral& expr) = 0;
        virtual void Visit(Literals::LiteralFraction& expr) = 0;

        virtual ~ExprVisitor() = default;
    };
}