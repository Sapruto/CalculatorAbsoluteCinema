#include "AST/AstPrinter.h"
#include "Parsing/Errors.h"
#include "Parsing/Lexer.h"
#include "Parsing/Parser.h"
#include "include/Parsing/Lexer.h"

#include <iostream>
#include <string>

void ProcessInput(const std::string &input) {
	Parsing::Lexer lexer{input};
	auto tokens = lexer.Parse();

	Parsing::Parser parser{input, tokens};
	auto expr = parser.Parse();

	std::cout << Print(expr) << std::endl;
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