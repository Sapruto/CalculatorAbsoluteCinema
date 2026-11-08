#pragma once

#include "AST/ASTFwd.h"
#include <cstdint>

namespace Visitors {
    class IExprVisitor {
    public:
        virtual void Visit(AST::BinaryExpr* expr) = 0;
        virtual void Visit(AST::UnaryExpr* expr) = 0;
        virtual void Visit(AST::CallExpr* expr) = 0;
        virtual void Visit(AST::Literals::LiteralExpr* expr) = 0;
    };
}