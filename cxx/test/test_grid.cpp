#include <doctest/doctest.h>
#include <set>
#include <tuple>
#include <vector>

#include "../graphidx/edges.hpp"
#include "../graphidx/grid.hpp"
#include "../graphidx/idx/biadjacent.hpp"
#include "../graphidx/idx/incidence.hpp"


TEST_CASE("GridGraph: 3x2")
{
    /*
      0  3
      1  4
      2  5
    */
    const GridGraph grid(3, 2);
    SUBCASE("convert to adjacent index")
    {
        BiAdjacentIndex<int> graph = grid;
        CHECK(grid.num_nodes() == 6);
        CHECK(graph.num_nodes() == 6);
        CHECK(graph.num_edges() == 7);
        CHECK(std::set<int>(graph[0]) == std::set<int>({1, 3}));
        CHECK(std::set<int>(graph[4]) == std::set<int>({1, 3, 5}));
    }
    SUBCASE("convert to incidence index")
    {
        IncidenceIndex<int> graph = grid;
        CHECK(graph.num_nodes() == 6);
        CHECK(graph.num_edges() == 7);
        SUBCASE("compare edge set")
        {
            std::set<std::tuple<int, int>> E;
            edges<int>(graph, [&](int u, int v, int) {
                if (u < v)
                    E.insert({u, v});
            });
            REQUIRE(E.size() == graph.num_edges());
            REQUIRE(
                E ==
                decltype(E)({{0, 1}, {3, 4}, {1, 2}, {4, 5}, {0, 3}, {1, 4}, {2, 5}}));
        }
        SUBCASE("compare edge vector")
        {
            std::vector<std::tuple<int, int>> E(graph.num_edges());
            edges<int>(graph, [&](int u, int v, int e) { if (u < v) E[e] = {u, v}; });
            REQUIRE(
                E ==
                decltype(E)({{0, 1}, {2, 3}, {4, 5}, {0, 2}, {2, 4}, {1, 3}, {3, 5}}));
        }
    }
}


TEST_CASE("GridGraph: 3x7")
{
    GridGraph grid(3, 7);
    IncidenceIndex<int> graph = grid;
    REQUIRE(graph.num_nodes() == 21);
    REQUIRE(graph.num_edges() == 32);
}
