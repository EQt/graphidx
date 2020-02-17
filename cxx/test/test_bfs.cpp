#include <doctest/doctest.h>
#include "../graphidx/tree/bfs.hpp"


TEST_CASE("bfs: tree.mini")
{
    const std::vector<int> parent = {0, 0, 1, 2, 3, 0, 7, 8, 3, 8};
    CHECK(compute_bfs(parent) ==
          std::vector<int>({0, 1, 5, 2, 3, 4, 8, 7, 9, 6}));
}
