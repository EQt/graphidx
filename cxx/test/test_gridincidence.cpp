#include <doctest/doctest.h>
#include <set>

#include "../graphidx/grid.hpp"
#include "../graphidx/utils/viostream.hpp"


TEST_CASE("GridGraph: grid_2x2")
{
    GridGraph grid(2, 2);
    IncidenceIndex<int> graph = grid;

    CHECK(graph.num_nodes() == 4);
    CHECK(graph.num_edges() == 4);
}


template <typename int_ = int>
std::ostream&
operator<<(std::ostream &out, const std::tuple<int_, int_> &t)
{
    out << "[" << std::get<0>(t) << ", " << std::get<1>(t) << "]";
    return out;
}


/*  4
  0---3
 0| 5 |1
  1---4
 2|   |3
  2---5
    6
*/
TEST_CASE("GridGraph: grid_3x2")
{
    GridGraph grid(3, 2);
    IncidenceIndex<int> graph = grid;
    INFO("graph = {" << graph.index << ", " << graph.value << "}");

    CHECK(graph.num_nodes() == 6);
    CHECK(graph.num_edges() == 7);
    {
        std::vector<int> deg (6, -1);
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
