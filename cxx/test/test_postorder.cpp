#include <doctest/doctest.h>
#include "../tree/postorder.hpp"
#include "../utils/perm.hpp"
#include "../utils/timer.hpp"


TEST_CASE("postorder: size")
{
    TimerQuiet _;
    const std::vector<int> parent = {0, 0, 1, 2, 3, 0, 7, 8, 3, 8};
    PostOrder pord (parent);
    REQUIRE(10 == parent.size());
    REQUIRE(parent.size()-1 == pord.size());
}


TEST_CASE("postorder: size_with_root")
{
    TimerQuiet _;
    const std::vector<int> parent = {0, 0, 1, 2, 3, 0, 7, 8, 3, 8};
    int *postord = nullptr;
    const int root = 0;
    const bool include_root = true;
    PostOrder pord (parent, postord, root, include_root);
    REQUIRE(10 == parent.size());
    REQUIRE(parent.size() == pord.size());
}


TEST_CASE("postorder: is_perm")
{
    TimerQuiet _;
    const std::vector<int> parent = {0, 0, 1, 2, 3, 0, 7, 8, 3, 8};
    int *postord = nullptr;
    const int root = 0;
    const bool include_root = true;
    PostOrder pord (parent, postord, root, include_root);
    std::vector<int> vpord (pord.begin(), pord.end());
    REQUIRE(is_perm_mut(vpord));
}


TEST_CASE("postorder: tree_mini")
{
    TimerQuiet _;
    const std::vector<int> parent {0, 0, 1, 0, 1, 2};
    const auto n = parent.size();
    const int root = 0;

    std::vector<int> postord (n, -1);
    post_order(n, parent.data(), root, postord.data());

    const std::vector<int> expected_ord { 3, 4, 5, 2, 1, 0 };
    REQUIRE(expected_ord == postord);
}
