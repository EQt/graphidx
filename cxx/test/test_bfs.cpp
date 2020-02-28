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


TEST_CASE("reversed_bfs_pi: tree.mini")
{
    std::vector<int>
        parent = {0, 0, 1, 2, 3, 0, 7, 8, 3, 8};
    ChildrenIndex cidx (parent);
    CHECK(cidx.root_node() == 0);
    std::vector<int> bfs (parent.size(), -1), pi (parent.size(), -1);
    reversed_bfs_pi(bfs.data(), cidx, pi.data());
    CHECK(bfs == std::vector<int>({6, 9, 7, 8, 4, 3, 2, 5, 1, 0}));
    CHECK(pi  == std::vector<int>({2, 3, 3, 5, 5, 6, 8, 9, 9, 9}));
    // compare to ../../python/test/test_reorder.py
}
