#pragma once

#include "../BinaryAst/Literals.h"
#include "TokenType.h"

#include <string>
#include <variant>

namespace Parsing::Lexing {
	struct TokenLoc {
		size_t start;
		size_t stop;
		std::string lexeme;

		TokenLoc(const std::string &code, size_t _start, size_t _stop)
			: start(_start),
			stop(_stop) {
			lexeme = code.substr(start, stop - start);
		}
	};

	using LiteralType = std::variant<BinaryAst::Literals::Fraction, std::monostate>;

	struct Token {
		TokenType type;
		TokenLoc loc;
		LiteralType literal;

		Token(TokenType _type, TokenLoc _loc, LiteralType _literal = {})
			: type(_type),
			loc(_loc),
			literal(_literal) {
		}
	};
}