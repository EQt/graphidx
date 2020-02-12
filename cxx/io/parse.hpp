#pragma once
#include <cstdint>
#include <istream>
#include <functional>

/**
   Call function `f(uint64_t i, bool nl)` for every number `i` in the stream `io`
   whereby `nl` tells whether it was the last number in that line.
*/
inline void
parse_uints(std::istream &io, std::function<void(uint64_t, bool)> f)
{
    uint64_t i = 0;
    bool
        first = true,
        finished = false,
        newline = false;
    char c;
    while (io.get(c)) {
        switch (c) {
        case ' ':
        case ',':
        case '\t':
            finished = true;
            break;

        case '\n':
        case '\r':
            finished = true;
            newline = true;
            break;
        case '_':
            continue;
        default:
            if ('0' <= c && c <= '9') {
                if (finished) {
                    if (!first) f(i, newline);
                    finished = false;
                    newline = false;
                    i = 0;
                }
                first = false;
                i *= 10;
                i += c - '0';
            } else {
                throw std::runtime_error(
                    std::string("Unknown character: '") + c + "'");
            }
        }
    }
    if (!first) f(i, true);
}
