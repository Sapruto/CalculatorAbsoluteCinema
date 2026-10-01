#pragma once

#include <string>
#include <memory>
#include <vector>

#include "Literal.h"
#include "Operators.h"

namespace AST {
    using namespace Literals;
    using namespace Operators;

    class ExprVisitor {
    public:
        virtual void Visit(BinaryExpr& expr) = 0;
        virtual void Visit(UnaryExpr& expr) = 0;
        virtual void Visit(CallExpr& expr) = 0;
        virtual void Visit(LiteralExpr& expr) = 0;

        virtual ~ExprVisitor() = default;
    };

    struct Expr {
        Expr() = default;
        virtual ~Expr() = 0;

        virtual void Accept(ExprVisitor& visitor) = 0;

        virtual std::unique_ptr<Expr> Copy() = 0;
    };

    struct BinaryExpr : public Expr {
    private:
        std::unique_ptr<Expr> left;
        BinOp op;
        std::unique_ptr<Expr> right;

    public:
        const Expr* leftPtr;
        const BinOp* opPtr;
        const Expr* rightPtr;

        BinaryExpr() = default;
        BinaryExpr(Expr&& l, BinOp o, Expr&& r)
        : left(l.Copy()), op(o), right(r.Copy()),
            leftPtr(left.get()), opPtr(&op), rightPtr(right.get()) {}

        void Accept(ExprVisitor& visitor) override { visitor.Visit(*this); }

        void SetValueL(Expr& l) { left = l.Copy(); }
        void SetValueR(Expr& r) { right = r.Copy(); }
        void SetOp(BinOp op) { this->op = op; }

        std::unique_ptr<Expr> Copy() override {
            auto lCopy = left ? left->Copy() : nullptr;
            auto rCopy = right ? right->Copy() : nullptr;
            
            auto bin = std::make_unique<BinaryExpr>();
            bin->left = std::move(lCopy);
            bin->op = this->op;
            bin->right = std::move(rCopy);
            
            return bin;
        }
    };

    struct UnaryExpr : public Expr {
    private:
        UnaryOp op;
        std::unique_ptr<Expr> expr;

    public:
        const UnaryOp* opPtr;
        const Expr* exprPtr;

        UnaryExpr() = default;
        UnaryExpr(Expr&& e, UnaryOp o) : expr(e.Copy()), op(o),
            opPtr(&op), exprPtr(expr.get()) {}

        void Accept(ExprVisitor& visitor) override { visitor.Visit(*this); }

        void SetValue(Expr& e) { expr = e.Copy(); }
        void SetOp(UnaryOp op) { this->op = op; }

        std::unique_ptr<Expr> Copy() override {
            auto eCopy = expr ? expr->Copy() : nullptr;
            
            auto unary = std::make_unique<UnaryExpr>();
            unary->expr = std::move(eCopy);
            unary->op = this->op;
            
            return unary;
        }
    };

    struct CallExpr : public Expr {
    private:
        std::string name;
        std::vector<std::unique_ptr<Expr>> args;

    public:
        const std::string* namePtr;
        const std::vector<Expr*> argsPtr;

        CallExpr() = default;
        CallExpr(const std::string& n, std::vector<Expr&&> a) : name(n), namePtr(&name), argsPtr(args) {
            args.reserve(a.size());
            for (auto expr : a) {
                args.push_back(expr.Copy());
            }
        }

        void Accept(ExprVisitor& visitor) override { visitor.Visit(*this); }
    };

    struct LiteralExpr : public Expr {
    private:
        std::unique_ptr<Literal> literal;
        
    public:
        const Literal* literalPtr;

        LiteralExpr() = default;
        LiteralExpr(Literal&& l) : literal(l.Copy()), literalPtr(literal.get()) {}

        void Accept(ExprVisitor& visitor) override { visitor.Visit(*this); }

        std::unique_ptr<Expr> Copy() override {
            auto lCopy = literal ? literal->Copy() : nullptr;
            
            auto literalExpr = std::make_unique<LiteralExpr>();
            literalExpr->literal = std::move(lCopy);
            
            return literalExpr;
        }
    };
}