#include "Parsing/Errors.h"

using namespace Parsing::Errors;

ErrorsLogger::ErrorsLogger(const std::string &_source) : source(_source) {}

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <string>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <io.h>
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#else
#include <unistd.h>
#endif

ParserException ErrorsLogger::Report(TokenLoc loc, const std::string &message) {
    static const bool useColor = [] {
        if (std::getenv("NO_COLOR"))
            return false;
#ifdef _WIN32
        if (!_isatty(_fileno(stdout)))
            return false;
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD mode = 0;
        return GetConsoleMode(h, &mode) &&
               SetConsoleMode(h, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#else
        return isatty(fileno(stdout)) != 0;
#endif
    }();

    const char *red = useColor ? "\x1b[1;31m" : "";
    const char *cyan = useColor ? "\x1b[36m" : "";
    const char *gray = useColor ? "\x1b[90m" : "";
    const char *yellow = useColor ? "\x1b[1;33m" : "";
    const char *reset = useColor ? "\x1b[0m" : "";

    const size_t start = std::min<size_t>(loc.start, source.size());

    size_t lineBegin = 0;
    if (start > 0) {
        const size_t prevNl = source.rfind('\n', start - 1);
        if (prevNl != std::string::npos)
            lineBegin = prevNl + 1;
    }

    size_t lineEnd = source.find('\n', start);
    if (lineEnd == std::string::npos)
        lineEnd = source.size();

    const size_t lineNo = std::count(source.begin(), source.begin() + start, '\n') + 1;
    const size_t col = start - lineBegin;

    std::string line = source.substr(lineBegin, lineEnd - lineBegin);
    if (!line.empty() && line.back() == '\r')
        line.pop_back();

    // отступ под лексему: табы сохраняем, чтобы подчёркивание не съезжало
    std::string pad;
    for (size_t i = 0; i < col && i < line.size(); ++i)
        pad += (line[i] == '\t') ? '\t' : ' ';

    const size_t available = line.size() > col ? line.size() - col : 1;
    const size_t len = std::max<size_t>(1, std::min(loc.lexeme.size(), available));

    const std::string num = std::to_string(lineNo);
    const std::string gutter(num.size(), ' ');

    printf("\n%s  --> line %zu, column %zu%s\n", cyan, lineNo, col + 1, reset);
    printf("%s %s |%s\n", gray, gutter.c_str(), reset);
    printf("%s %s |%s %s\n", gray, num.c_str(), reset, line.c_str());
    printf("%s %s |%s %s%s%s%s\n", gray, gutter.c_str(), reset,
           pad.c_str(), red, std::string(len, '^').c_str(), reset);
    printf("%sSyntaxError%s: %s%s%s\n\n", red, reset, yellow, message.c_str(), reset);

    return ParserException(message);
}