#include <memory>

#include "AST.h"
#include "Literal.h"
#include "Operators.h"

using namespace AST;
using namespace Literals;

struct LiteralNumber : public Literal {
    int i = 0;

    LiteralNumber() = default;
    LiteralNumber(int i) { this->i = i; }

    std::unique_ptr<Literal> Copy() override {
        auto num = std::make_unique<LiteralNumber>();
        num->i = i;
        return num;
    }
};

class EvaluationVisitor : public ExprVisitor {
public:
    void Visit(BinaryExpr& expr) override
    {
        std::cout << "BinaryExpr\n";

        expr.left->accept(*this);
        expr.right->accept(*this);
    }

    void Visit(UnaryExpr& expr) override
    {
        std::cout << "UnaryExpr\n";

        expr.expr->accept(*this);
    }

    void Visit(CallExpr& expr) override
    {
        std::cout << "CallExpr\n";

        expr.argument->accept(*this);
    }

    void Visit(LiteralExpr& expr) override
    {
        std::cout << "LiteralExpr\n";
    }
};

void Evaluate(Expr& expr) {
    expr.Accept(*(new EvaluationVisitor()));
}

int main() {
    auto expr = BinaryExpr(
        LiteralExpr(LiteralNumber(1)),
        BinOp::PLUS,
        LiteralExpr(LiteralNumber(2))
    );

    return 0;
}