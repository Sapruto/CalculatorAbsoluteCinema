#include "Parsing/BinaryAst/AstPrinter.h"
#include "Parsing/Errors.h"
#include "Parsing/Lexing/Lexer.h"
#include "Parsing/Parser.h"
#include "Parsing/Lexing/Lexer.h"

#include <iostream>
#include <print>
#include <string>

void ProcessInput(const std::string &input) {
	Parsing::Lexing::Lexer lexer{input};
	auto tokens = lexer.Parse();

	Parsing::Parser parser{input, tokens};
	auto expr = parser.Parse();

	auto result = Eval(expr);

	if (result.denominator == 1) {
		std::print("{}\n", result.numerator);
	}
	else {
		std::print("{} / {}\n", result.numerator, result.denominator);
	}
}

int main() {
	std::string input;
	std::cout << "> ";
	std::cin >> input;

	try {
		ProcessInput(input);
	}
	catch (Parsing::Errors::ParserException) {
	}

	return 0;
}