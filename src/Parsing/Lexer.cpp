#include "Parsing/Lexer.h"

#include "Parsing/TokenType.h"

using namespace Parsing;
using namespace AST::Literals;

Lexer::Lexer(const std::string &_code) : code(_code), errorsLogger(_code) {}

bool Lexer::IsAlpha(char c) { return (c >= '0' && c <= '9') || c == '.'; }

void Lexer::ParseNumber() {
    bool periodParsed = false;

    int64_t numerator = 0;
    int64_t denominator = 1;

    char c;
    while (IsAlpha(c = code[current])) {
        if (c == '.') {
            if (periodParsed) {
                throw errorsLogger.Report({code, current, current}, "Second period in one number");
            }
            else {
                current++;
                periodParsed = true;
                continue;
            }
        }

        numerator *= 10;
        numerator += c - '0';

        if (periodParsed) {
            denominator *= 10;
        }

        current++;
    }

    AddToken(TokenType::LITERAL, LiteralFraction{numerator, denominator});
}

void Lexer::AddToken(TokenType type) {
    auto lexeme = code.substr(start, current - start);
    auto loc = TokenLoc{code, start, current};
    tokens.push_back(Token{type, loc});
}

void Lexer::AddToken(TokenType type, LiteralFraction literal) {
    auto lexeme = code.substr(start, current - start);
    auto loc = TokenLoc{code, start, current};
    tokens.push_back(Token{type, loc, literal});
}

std::vector<Token> Lexer::Parse() {
    while (true) {
        start = current;

        char c = code[current];

        if (c == '\0') {
            AddToken(TokenType::END_OF_FILE);
            break;
        }

        switch (c) {
        case ' ':
        case '\n':
        case '\t':
            current++;
            break;
        case '+':
            AddToken(TokenType::PLUS);
            break;
        case '-':
            AddToken(TokenType::MINUS);
            break;
        case '*':
            AddToken(TokenType::STAR);
            break;
        case '/':
            AddToken(TokenType::SLASH);
            break;
        case '(':
            AddToken(TokenType::LEFT_BRACKET);
            break;
        case ')':
            AddToken(TokenType::RIGHT_BRACKET);
            break;
        default:
            if (IsAlpha(c)) {
                ParseNumber();
                continue;
            }
            else {
                throw errorsLogger.Report({code, start, current}, "Unexpected character");
            }
        }

        current++;
    }

    return tokens;
}