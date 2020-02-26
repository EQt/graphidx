#include <doctest/doctest.h>
#include <set>

#include "../graphidx/grid.hpp"


TEST_CASE("GridGraph: grid_3x2")
{
    GridGraph grid(3, 2);
    BiAdjacentIndex<int> graph = grid;
    CHECK(grid.num_nodes() == 6);
    CHECK(graph.num_nodes() == 6);
    CHECK(graph.num_edges() == 7);
    CHECK(std::set<int>(graph[0]) == std::set<int>({1, 3}));
    CHECK(std::set<int>(graph[4]) == std::set<int>({1, 3, 5}));
}
