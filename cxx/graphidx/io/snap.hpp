#pragma once
#include <regex>
#include <stdexcept>
#include <string>

#include "parse.hpp"
#include "../idx/biadjacent.hpp"


inline std::istream&
parse_snap_header(std::istream &io, size_t &n, size_t &m)
{
    auto re = std::regex("# Nodes: (\\d+) Edges: (\\d+)");
    std::string line;
    std::streampos pos;
    do {
        pos = io.tellg();
        std::getline(io, line);
        std::smatch cm;
        if (std::regex_match(line, cm, re)) {
            n = size_t(std::stoll(cm[1].str()));
            m = size_t(std::stoll(cm[2].str()));
        }
    } while (line == "" || line[0] == '#');
    io.seekg(pos);
    return io;
}


template <typename int_ = int>
size_t
parse_snap_edges(
    std::istream &io,
    std::vector<int_> &head,
    std::vector<int_> &tail)
{
    size_t n = 0, m = 0;
    parse_snap_header(io, n, m);
    if (m == 0)
        throw std::runtime_error(
            std::string("number of edges not found: pos=") +
            std::to_string(io.tellg()));
    if (n == 0)
        throw std::runtime_error(
            std::string("number of edges not found: pos=") +
            std::to_string(io.tellg()));
    head.reserve(m);
    tail.reserve(m);

    bool odd = false;
    parse_uints(
        io,
        [&](uint64_t u, bool last) {
            u--;
            if (odd)
                tail.push_back(int_(u));
            else
                head.push_back(int_(u));
            if (odd != last)
                throw std::runtime_error("more than two number in one line");
            odd = !odd;
        });
    return n;
}


template <typename int_ = int>
BiAdjacentIndex<int_>
parse_snap_idx(std::istream &io)
{
    std::vector<int_> head, tail;
    parse_snap_edges(io, head, tail);
    return {head, tail};
}
