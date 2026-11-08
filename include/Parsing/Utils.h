#pragma once

#include "Parsing/TokenType.h"

#include <string>

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
}