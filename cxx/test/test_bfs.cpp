#include <doctest/doctest.h>
#include "../graphidx/tree/bfs.hpp"


TEST_CASE("bfs: tree.mini")
{
    const std::vector<int> parent = {0, 0, 1, 2, 3, 0, 7, 8, 3, 8};
    CHECK(compute_bfs(parent) ==
          std::vector<int>({0, 1, 5, 2, 3, 4, 8, 7, 9, 6}));
}


TEST_CASE("reversed bfs: tree.mini")
{
    const std::vector<int> parent = {0, 0, 1, 2, 3, 0, 7, 8, 3, 8};
    CHECK(reversed_bfs(parent) ==
          std::vector<int>({6, 9, 7, 8, 4, 3, 2, 5, 1, 0}));
}
