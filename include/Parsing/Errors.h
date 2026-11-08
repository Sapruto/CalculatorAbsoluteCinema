#pragma once

#include <string>
#include "Parsing/Token.h"

namespace Parsing::Errors {
    class ParserException : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    class ErrorsLogger {
    private:
        std::string source;

    public:
        ErrorsLogger(const std::string& _source);

        ParserException Report(TokenLoc loc, const std::string& message);
    };
}