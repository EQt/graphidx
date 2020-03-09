#pragma once
#include <cctype>
#include <cstdint>
#include <istream>
#include <functional>


/**
   Check that the first character is a digit and parse it as number
*/
template <typename int_ = size_t>
struct check_uint
{
    int_ &n;
    check_uint(int_ &n) : n(n) {}
};


template <typename int_ = size_t>
std::istream& operator>>(std::istream &io, check_uint<int_> c)
{
    char ch = (char) io.get();
    if (isspace(ch))
        return io >> c;
    if (!isdigit(ch))
        throw std::runtime_error(
            std::string("Expected number, but got '") + ch + "'");
    io.unget();
    return io >> c.n;
}


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
                i += decltype(i)(c - '0');
            } else {
                throw std::runtime_error(
                    std::string("Unknown character: '") + c + "'");
            }
        }
    }
    if (!first) f(i, true);
}
