#pragma once
#include "parse.hpp"
#include "../idx/biadjacent.hpp"

auto constexpr MAX_LINE_LENGTH = 1024;


inline std::istream&
ignore_comments(std::istream &io)
{
    int c = io.get();
    while (c == '%' || c == '\n') {
        io.ignore(MAX_LINE_LENGTH, '\n');
        c = io.get();
    }
    io.unget();
    return io;
}


inline std::istream&
parse_dimacs10_header(std::istream &io, size_t &n, size_t &m)
{
    ignore_comments(io) >> n >> m;
    if (io.get() != '\n')
        io.unget();
    return io;
}


template <typename int_ = int>
BiAdjacentIndex<int_>
parse_dimacs10_idx(std::istream &io)
{
    size_t n = 0, m = 0;
    parse_dimacs10_header(io, n, m);

    std::vector<int_> head, tail;
    head.reserve(m);
    tail.reserve(m);
    size_t vi = 0;
    parse_uints(io, [&](uint64_t u, bool last) {
                        u--;
                        if (vi != u) {
                            if (vi < u) {
                                head.push_back(vi);
                                tail.push_back(u);
                            } else {
                                head.push_back(u);
                                tail.push_back(vi);
                            }
                        }
                        if (last)
                            vi++;
                    });
    return {head, tail};
}
