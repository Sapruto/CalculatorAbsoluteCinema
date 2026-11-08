#pragma once

#include "AST/Exprs.h"
#include "ExprVisitors/ExprVisitor.h"

#include <unordered_map>

namespace Visitors {
    class EqualExecutor : public IExprVisitor {
    private:
        bool ok = true;

    public:
        void Visit(AST::BinaryExpr* expr) override {
            
        }

        void Visit(AST::UnaryExpr* expr) override {
            
        }

        void Visit(AST::CallExpr* expr) override {
            
        }

        void Visit(AST::Literals::LiteralExpr* expr) override {
            
        }

        bool GetResult() { return ok; }
    };
}