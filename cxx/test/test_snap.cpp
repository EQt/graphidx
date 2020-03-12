#include <doctest/doctest.h>
#include <sstream>
#include "../graphidx/io/snap.hpp"


const auto GRAPH = R"(# comments
# ... to be ignored
#
# Nodes: 4 Edges: 3
# FromNodeId    ToNodeId
1       2
1       4
3       4
)";


TEST_CASE("snap: header")
{
    std::istringstream io (GRAPH);
    size_t n = 0, m = 0;
    parse_snap_header(io, n, m);
    REQUIRE(n == 4);
    REQUIRE(m == 3);
    std::string line;
    std::getline(io, line);
    REQUIRE(line == "1       2");
}


TEST_CASE("snap: biadj")
{
    std::istringstream io (GRAPH);
    auto idx = parse_snap_idx(io);
    CHECK(std::vector<int>(idx.value) == std::vector<int> {1, 3, 0, 3, 0, 2});
    CHECK(idx.index == std::vector<int> {0, 2, 3, 4, 6});
    REQUIRE(idx == BiAdjacent {{1, 3, 0, 3, 0, 2},
                               {0, 2, 3, 4, 6}});
}
