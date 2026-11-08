#include "AST/Exprs.h"
#include "AST/Literals.h"
#include "Parsing/Errors.h"
#include "Parsing/Lexer.h"
#include "Parsing/Parser.h"
#include "Parsing/Token.h"

#include <cstdio>
#include <iostream>
#include <string>
#include <variant>
#include <vector>

void printTokens(const std::vector<Token> &tokens) {
	for (auto token : tokens) {
		int64_t num = 0;
		int64_t den = 0;

		if (auto *fraction = std::get_if<AST::Literals::LiteralFraction>(&token.literal)) {
			num = fraction->numerator;
			den = fraction->denominator;
		}

		printf("Type: %d (%lld/%lld)\n", token.type, num, den);
	}
}

class ASTPrinterVisitor : ExprVisitors::ExprVisitor {
public:
	std::string Visit(AST::BinaryExpr &expr) {

    }
	virtual void Visit(AST::UnaryExpr &expr) = 0;
	virtual void Visit(AST::CallExpr &expr) = 0;

	virtual void Visit(AST::Literals::LiteralExpr &expr) = 0;
};

void process_input(const std::string &input) {
	Parsing::Lexer lexer{input};
	auto tokens = lexer.Parse();

	printTokens(tokens);

	Parsing::Parser parser{input, tokens};
	auto expr = parser.Parse();
}

int main() {
	std::string input;
	std::cout << "> ";
	std::cin >> input;

	try {
		process_input(input);
	}
	catch (Parsing::Errors::ParserException) {
	}

	return 0;
}