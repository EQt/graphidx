#include <doctest/doctest.h>
#include <set>
#include <utility>

#include "../graphidx/utils/viostream.hpp"
#include "../graphidx/tree/prufer.hpp"


TEST_CASE("prufer: networkx_example_parent")
{
    const std::vector<int> pruf {3, 3, 3, 4};
    const size_t n = pruf.size() + 2;
    std::vector<int> parent (n, -1);
    prufer2parent(n, pruf.data(), parent.data());

    const std::vector<int> parent_x {3, 3, 3, 4, 5, 5};
    REQUIRE(parent_x == parent);
}


TEST_CASE("prufer: networkx_example_edges")
{
    const std::vector<int> pruf {3, 3, 3, 4};
    const size_t n = pruf.size() + 2;

    std::vector<int>
        head (n-1, -1),
        tail (n-0, -1);

    prufer2edges(n, pruf.data(), head.data(), tail.data());
    std::set<std::set<int>> edges;
    for (size_t i = 0; i < n-1; i++)
        edges.insert({head[i], tail[i]});
        
    const std::set<std::set<int>>
        expected {{0, 3}, {1, 3}, {2, 3}, {3, 4}, {4, 5}};

    REQUIRE(expected == edges);
}


TEST_CASE("prufer: paper")
{
    const std::vector<int> c {2, 4, 0, 1, 3, 3};
    const size_t n = c.size() + 2;
    std::vector<int>
        head (n-1, -1),
        tail (n-0, -1);

    prufer2edges(n, c.data(), head.data(), tail.data());
    std::set<std::set<int>> edges;
    for (size_t i = 0; i < n-1; i++)
        edges.insert({head[i], tail[i]});

    const std::set<std::set<int>>
        expected {{0,1}, {0,4}, {1,3}, {4,2}, {3,6}, {3,7}, {2,5}};

    REQUIRE(expected == edges);
}
