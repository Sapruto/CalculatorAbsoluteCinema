#pragma once

#include "../Utils.h"
#include "Literals.h"
#include "Operators.h"
#include "Visit.h"

#include <stdexcept>
#include <string>

inline std::string Print(Parsing::BinaryAst::Expr *e) {
	using namespace Parsing::BinaryAst;

	return Visit(e, Overloaded{
						[](BinaryExpr *b) -> std::string {
							return "(" + Print(b->left) + " " + Parsing::Utils::FormatBinOp(b->op) + " " + Print(b->right) + ")";
						},
						[](UnaryExpr *u) -> std::string {
							if (u->op == Operators::UnaryOp::NEGATION)
								return "(-" + Print(u->expr) + ")";
							return "(" + Print(u->expr) + "!)";
						},
						[](CallExpr *c) -> std::string {
							std::string result = c->name + "(";
							for (size_t i = 0; i < c->args.size(); ++i) {
								if (i)
									result += ", ";
								result += Print(c->args[i]);
							}
							return result + ")";
						},
						[](LiteralExpr *l) -> std::string {
							if (l->literal->GetType() == typeid(Literals::Fraction)) {
								auto *f = static_cast<Literals::Fraction *>(l->literal);
								if (f->denominator == 1)
									return std::to_string(f->numerator);
								return std::to_string(f->numerator) + "/" + std::to_string(f->denominator);
							}
							else if (l->literal->GetType() == typeid(Literals::Identifier)) {
								auto *f = static_cast<Literals::Identifier *>(l->literal);
								return f->value;
							}
							throw std::runtime_error("Unknown literal");
						},
					});
}

inline Parsing::BinaryAst::Literals::Fraction Eval(Parsing::BinaryAst::Expr *e) {
	using namespace Parsing::BinaryAst;

	return Visit(e, Overloaded{
						[](BinaryExpr *b) -> Parsing::BinaryAst::Literals::Fraction {
							auto left = Eval(b->left);
							auto right = Eval(b->right);
							switch (b->op) {
							case Operators::BinOp::PLUS:
								return left + right;
							case Operators::BinOp::MINUS:
								return left - right;
							case Operators::BinOp::MULTIPLY:
								return left * right;
							case Operators::BinOp::DIVIDE:
								return left / right;
							}
						},
						[](UnaryExpr *u) -> Parsing::BinaryAst::Literals::Fraction {
							auto v = Eval(u->expr);
							if (u->op == Operators::UnaryOp::NEGATION)
								return -v;
							return v;
						},
						[](CallExpr *c) -> Parsing::BinaryAst::Literals::Fraction {
							throw std::runtime_error("Not implemented");
						},
						[](LiteralExpr *l) -> Parsing::BinaryAst::Literals::Fraction {
							if (l->literal->GetType() == typeid(Literals::Fraction)) {
								auto *f = static_cast<Literals::Fraction *>(l->literal);
								return *f;
							}
							else if (l->literal->GetType() == typeid(Literals::Identifier)) {
								return Literals::Fraction(0, 1);
							}
							throw std::runtime_error("Unknown literal");
						},
					});
}