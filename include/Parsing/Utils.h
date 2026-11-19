#pragma once

#include "BinaryAst/Literals.h"
#include "BinaryAst/Operators.h"
#include "Lexing/Token.h"
#include "Lexing/TokenType.h"

#include <stdexcept>
#include <string>
#include <vector>

namespace Parsing::Utils {
	inline std::string FormatType(Lexing::TokenType type) {
		switch (type) {
		case Lexing::TokenType::PLUS:
			return "'+'";
		case Lexing::TokenType::MINUS:
			return "'-'";
		case Lexing::TokenType::STAR:
			return "'*'";
		case Lexing::TokenType::SLASH:
			return "'/'";
		case Lexing::TokenType::LEFT_BRACKET:
			return "'('";
		case Lexing::TokenType::RIGHT_BRACKET:
			return "')'";
		case Lexing::TokenType::LITERAL:
			return "number";
		case Lexing::TokenType::END_OF_FILE:
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

	inline void PrintTokens(const std::vector<Lexing::Token> &tokens) {
		for (auto token : tokens) {
			int64_t num = 0;
			int64_t den = 0;

			if (auto *fraction = std::get_if<BinaryAst::Literals::Fraction>(&token.literal)) {
				num = fraction->numerator;
				den = fraction->denominator;
			}

			printf("Type: %d (%lld/%lld)\n", token.type, num, den);
		}
	}
}