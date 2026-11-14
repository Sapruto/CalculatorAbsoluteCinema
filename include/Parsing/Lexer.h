#pragma once

#include <string>
#include <vector>
#include "Parsing/Token.h"
#include "Parsing/Errors.h"
#include "AST/Literals.h"

namespace Parsing {
	class Lexer {
	private:
		std::string code;
		std::vector<Token> tokens;
		Errors::ErrorsLogger errorsLogger;
		size_t start = 0;
		size_t current = 0;

		static bool IsAlpha(char c);
		void ParseNumber();
		void AddToken(TokenType type);
		void AddToken(TokenType type, AST::Literals::LiteralFraction literal);

	public:
		Lexer(const std::string &_code);
		std::vector<Token> Parse();
	};
}