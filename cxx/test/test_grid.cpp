#include <doctest/doctest.h>
#include <map>
#include <set>
#include <tuple>
#include <vector>

#include "../graphidx/edges.hpp"
#include "../graphidx/grid.hpp"
#include "../graphidx/idx/biadjacent.hpp"
#include "../graphidx/idx/incidence.hpp"


TEST_CASE("GridGraph: 2x2")
{
    GridGraph grid(2, 2);
    IncidenceIndex<int> graph = grid;

    CHECK(graph.num_nodes() == 4);
    CHECK(graph.num_edges() == 4);
}


/*  4
  0---3
 0| 5 |1
  1---4
 2|   |3
  2---5
    6
*/
TEST_CASE("GridGraph: 3x2")
{
    GridGraph grid(3, 2);
    IncidenceIndex<int> graph = grid;
    INFO("graph = {" << graph.index << ", " << graph.value << "}");

    CHECK(graph.num_nodes() == 6);
    CHECK(graph.num_edges() == 7);
    {
        std::vector<int> deg(6, -1);
        graph.degrees(deg.data());
        CHECK(deg == decltype(deg)({2, 3, 2, 2, 3, 2}));
    }

    using inc_t = std::set<std::tuple<int, int>>;
    CHECK(graph[0] == inc_t({{1, 0}, {3, 4}}));
    CHECK(graph[1] == inc_t({{0, 0}, {2, 2}, {4, 5}}));
    CHECK(graph[2] == inc_t({{1, 2}, {5, 6}}));
    CHECK(graph[3] == inc_t({{0, 4}, {4, 1}}));
    CHECK(graph[4] == inc_t({{1, 5}, {3, 1}, {5, 3}}));
    CHECK(graph[5] == inc_t({{2, 6}, {4, 3}}));
}


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
        SUBCASE("capture edge ordering: is not linear")
        {
            std::vector<int> ei;
            edges<int>(graph, [&](int u, int v, int e) {
                if (u < v)
                    ei.push_back(e);
            });
            REQUIRE(ei == decltype(ei)({0, 4, 2, 5, 6, 1, 3}));
        }
        SUBCASE("compare edge dict")
        {
            std::map<int, std::tuple<int, int>> E;
            edges<int>(graph, [&](int u, int v, int e) {
                if (u < v)
                    E[e] = {u, v};
            });
            const int x[7][2] = {{0, 1}, {3, 4}, {1, 2}, {4, 5}, {0, 3}, {1, 4}, {2, 5}};
            for (int i = 0; i < 7; i++) {
                CAPTURE(i);
                CHECK(std::get<0>(E[i]) == x[i][0]);
                CHECK(std::get<1>(E[i]) == x[i][1]);
            }
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
