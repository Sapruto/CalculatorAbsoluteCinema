#pragma once

#include "AST/Literals.h"
#include "AST/Operators.h"
#include "Parsing/Token.h"
#include "Parsing/TokenType.h"

#include <stdexcept>
#include <string>
#include <vector>

namespace Parsing::Utils {
	inline std::string FormatType(TokenType type) {
		switch (type) {
		case TokenType::PLUS:
			return "'+'";
		case TokenType::MINUS:
			return "'-'";
		case TokenType::STAR:
			return "'*'";
		case TokenType::SLASH:
			return "'/'";
		case TokenType::LEFT_BRACKET:
			return "'('";
		case TokenType::RIGHT_BRACKET:
			return "')'";
		case TokenType::LITERAL:
			return "number";
		case TokenType::END_OF_FILE:
			return "EOF";
		default:
			return "UNKNOWN";
		}
	}

	inline std::string FormatBinOp(Operators::BinOp op) {
		switch (op) {
		case Operators::BinOp::PLUS:
			return "+";
		case Operators::BinOp::MINUS:
			return "-";
		case Operators::BinOp::MULTIPLY:
			return "*";
		case Operators::BinOp::DIVIDE:
			return "/";
		}
		throw std::logic_error("Unexpected binop type");
	}

	inline void PrintTokens(const std::vector<Token> &tokens) {
		for (auto token : tokens) {
			int64_t num = 0;
			int64_t den = 0;

			if (auto *fraction = std::get_if<AST::Literals::Fraction>(&token.literal)) {
				num = fraction->numerator;
				den = fraction->denominator;
			}

			printf("Type: %d (%lld/%lld)\n", token.type, num, den);
		}
	}
}