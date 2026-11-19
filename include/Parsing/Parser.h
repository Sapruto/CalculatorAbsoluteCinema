#pragma once

#include "AST/AstArena.h"
#include "AST/Exprs.h"
#include "AST/Literals.h"
#include "AST/Operators.h"
#include "Parsing/Errors.h"
#include "Parsing/Token.h"
#include "Parsing/TokenType.h"
#include "Parsing/Utils.h"

#include <format>
#include <vector>

namespace Parsing {
	class Parser {
	private:
		Errors::ErrorsLogger errorsLogger;
		std::vector<Token> tokens;
		AST::AstArena &arena;
		size_t start = 0;
		size_t current = 0;

		Token *Peek() {
			return &tokens[current];
		}

		Token *Advance() {
			return &tokens[current++];
		}

		bool IsAtEnd() {
			return Peek()->type == TokenType::END_OF_FILE;
		}

		bool Check(TokenType type) {
			if (IsAtEnd())
				return false;
			return Peek()->type == type;
		}

		bool Match(TokenType type) {
			if (Check(type)) {
				Advance();
				return true;
			}
			return false;
		}

		Token *Previous() {
			return &tokens[current - 1];
		}

		Token *Consume(TokenType type) {
			if (Check(type))
				return Advance();

			std::string errorMessage = std::format("Expected: {}, got: {}", Utils::FormatType(type), Utils::FormatType(Peek()->type));
			throw errorsLogger.Report(Peek()->loc, errorMessage);
		}

		AST::Expr *Factor() {
			if (Match(TokenType::LEFT_BRACKET)) {
				auto *expr = Expr();
				Consume(TokenType::RIGHT_BRACKET);
				return expr;
			}

			auto literalToken = Consume(TokenType::LITERAL);
			return arena.make<AST::LiteralExpr>(&std::get<AST::Literals::Fraction>(literalToken->literal));
		}

		AST::Expr *Term() {
			AST::Expr *node = Factor();

			while (Match(TokenType::STAR) || Match(TokenType::SLASH)) {
				auto *opToken = Previous();
				Operators::BinOp op = opToken->type == TokenType::STAR
					                      ? Operators::BinOp::MULTIPLY
					                      : Operators::BinOp::DIVIDE;
				node = arena.make<AST::BinaryExpr>(node, op, Factor());
			}

			return node;
		}

		AST::Expr *Expr() {
			AST::Expr *node = Term();

			while (Match(TokenType::PLUS) || Match(TokenType::MINUS)) {
				auto *opToken = Previous();
				Operators::BinOp op = opToken->type == TokenType::PLUS
					                      ? Operators::BinOp::PLUS
					                      : Operators::BinOp::MINUS;
				node = new AST::BinaryExpr(node, op, Term());
			}

			return node;
		}

	public:
		Parser(const std::string &_source, const std::vector<Token> &_tokens) : tokens(_tokens), errorsLogger(_source), arena(AST::AstArena::GetArena()) {
		}

		AST::Expr *Parse() {
			return Expr();
		}
	};
}