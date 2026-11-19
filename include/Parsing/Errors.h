#pragma once

#include <stdexcept>
#include <string>
#include "Lexing/Token.h"

namespace Parsing::Errors {
	class ParserException : public std::runtime_error {
		using std::runtime_error::runtime_error;
	};

	class ErrorsLogger {
	private:
		std::string source;

	public:
		ErrorsLogger(const std::string &_source);

		ParserException Report(Lexing::TokenLoc loc, const std::string &message);
	};
}