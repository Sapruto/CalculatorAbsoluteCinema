#pragma once

namespace AST {
    struct Node;
    struct Expr;

    struct BinaryExpr;
    struct UnaryExpr;
    struct CallExpr;

    namespace Literals {
        struct IntLiteral;
        struct StringLiteral;
        struct BoolLiteral;
        
        struct LiteralFraction;
    }

    class ExprVisitor;
}