#include <doctest/doctest.h>
#include "../graphidx/tree/dfs.hpp"


TEST_CASE("dfs: tree.mini")
{
    const std::vector<int> parent = {0, 0, 1, 2, 3, 0, 7, 8, 3, 8};
    CHECK(dfs_discover(parent) ==
          std::vector<int>({0, 5, 1, 2, 3, 8, 9, 7, 6, 4}));
}
