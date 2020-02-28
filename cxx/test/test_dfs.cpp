#include <doctest/doctest.h>
#include "../graphidx/tree/dfs.hpp"
#include "../graphidx/std/stack.hpp"


TEST_CASE("dfs: tree.mini")
{
    const std::vector<int> parent = {0, 0, 1, 2, 3, 0, 7, 8, 3, 8};
    CHECK(dfs_discover(parent) ==
          std::vector<int>({0, 5, 1, 2, 3, 8, 9, 7, 6, 4}));
}


TEST_CASE("reversed_dfs: tree.mini")
{
    const std::vector<int> parent = {0, 0, 1, 2, 3, 0, 7, 8, 3, 8};
    CHECK(reversed_dfs_discover(parent) ==
          std::vector<int>({4, 6, 7, 9, 8, 3, 2, 1, 5, 0}));
}


TEST_CASE("reversed_dfs_pi: tree.mini")
{
    std::vector<int>
        parent = {0, 0, 1, 2, 3, 0, 7, 8, 3, 8};
    ChildrenIndex cidx (parent);
    stack<int> s;
    CHECK(cidx.root_node() == 0);
    std::vector<int>
        dfs (parent.size(), -1),
        pi (parent.size(), -1);
    reversed_dfs_discover_pi(dfs.data(), cidx, s, pi.data());
    CHECK(dfs == std::vector<int>({4, 6, 7, 9, 8, 3, 2, 1, 5, 0}));
    CHECK(pi  == std::vector<int>({3, 7, 8, 8, 3, 2, 1, 0, 0, 0}));
}
