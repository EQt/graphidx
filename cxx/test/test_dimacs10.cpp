#include <doctest/doctest.h>
#include <sstream>
#include "../io/dimacs10.hpp"


const auto GRAPH = R"(% some comments
%  ... to be ignored
% integer node numbers start at one
% number of nodes, number of edges
4 3
2 4
2
4
)";


TEST_CASE("dimacs10: ignore_comments")
{
    std::istringstream io (GRAPH);
    std::string line;
    ignore_comments(io);
    std::getline(io, line);
    REQUIRE(line == "4 3");
}


TEST_CASE("dimacs10: header")
{
    std::istringstream io (GRAPH);
    size_t n = 0, m = 0;
    parse_dimacs10_header(io, n, m);
    REQUIRE(n == 4);
    REQUIRE(m == 3);
    std::string line;
    std::getline(io, line);
    REQUIRE(line == "2 4");
}


TEST_CASE("dimacs10: biadj")
{
    std::istringstream io (GRAPH);
    auto idx = parse_dimacs10_idx(io);
    CHECK(std::vector<int>(idx.value) == std::vector<int> {1, 3, 0, 3, 0, 2});
    CHECK(idx.index == std::vector<int> {0, 2, 3, 4, 6});
    REQUIRE(idx == BiAdjacent {{1, 3, 0, 3, 0, 2},
                               {0, 2, 3, 4, 6}});
}
