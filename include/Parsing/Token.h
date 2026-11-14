#pragma once

#include "AST/Literals.h"
#include "Parsing/TokenType.h"

#include <string>
#include <variant>

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

using LiteralType = std::variant<AST::Literals::LiteralFraction, std::monostate>;

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