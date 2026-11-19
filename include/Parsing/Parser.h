#pragma once

#include "BinaryAst/AstArena.h"
#include "BinaryAst/Exprs.h"
#include "BinaryAst/Literals.h"
#include "BinaryAst/Operators.h"
#include "Parsing/Errors.h"
#include "Lexing/Token.h"
#include "Lexing/TokenType.h"
#include "Utils.h"

#include <format>
#include <vector>

namespace Parsing {
	class Parser {
	private:
		Errors::ErrorsLogger errorsLogger;
		std::vector<Lexing::Token> tokens;
		BinaryAst::AstArena &arena;
		size_t start = 0;
		size_t current = 0;

		Lexing::Token *Peek() {
			return &tokens[current];
		}

		Lexing::Token *Advance() {
			return &tokens[current++];
		}

		bool IsAtEnd() {
			return Peek()->type == Lexing::TokenType::END_OF_FILE;
		}

		bool Check(Lexing::TokenType type) {
			if (IsAtEnd())
				return false;
			return Peek()->type == type;
		}

		bool Match(Lexing::TokenType type) {
			if (Check(type)) {
				Advance();
				return true;
			}
			return false;
		}

		Lexing::Token *Previous() {
			return &tokens[current - 1];
		}

		Lexing::Token *Consume(Lexing::TokenType type) {
			if (Check(type))
				return Advance();

			std::string errorMessage = std::format("Expected: {}, got: {}", Utils::FormatType(type), Utils::FormatType(Peek()->type));
			throw errorsLogger.Report(Peek()->loc, errorMessage);
		}

		BinaryAst::Expr *Factor() {
			if (Match(Lexing::TokenType::LEFT_BRACKET)) {
				auto *expr = Expr();
				Consume(Lexing::TokenType::RIGHT_BRACKET);
				return expr;
			}

			auto literalToken = Consume(Lexing::TokenType::LITERAL);
			return arena.make<BinaryAst::LiteralExpr>(&std::get<BinaryAst::Literals::Fraction>(literalToken->literal));
		}

		BinaryAst::Expr *Term() {
			BinaryAst::Expr *node = Factor();

			while (Match(Lexing::TokenType::STAR) || Match(Lexing::TokenType::SLASH)) {
				auto *opToken = Previous();
				Operators::BinOp op = opToken->type == Lexing::TokenType::STAR
					                      ? Operators::BinOp::MULTIPLY
					                      : Operators::BinOp::DIVIDE;
				node = arena.make<BinaryAst::BinaryExpr>(node, op, Factor());
			}

			return node;
		}

		BinaryAst::Expr *Expr() {
			BinaryAst::Expr *node = Term();

			while (Match(Lexing::TokenType::PLUS) || Match(Lexing::TokenType::MINUS)) {
				auto *opToken = Previous();
				Operators::BinOp op = opToken->type == Lexing::TokenType::PLUS
					                      ? Operators::BinOp::PLUS
					                      : Operators::BinOp::MINUS;
				node = new BinaryAst::BinaryExpr(node, op, Term());
			}

			return node;
		}

	public:
		Parser(const std::string &_source, const std::vector<Lexing::Token> &_tokens) : tokens(_tokens), errorsLogger(_source), arena(BinaryAst::AstArena::GetArena()) {
		}

		BinaryAst::Expr *Parse() {
			return Expr();
		}
	};
}