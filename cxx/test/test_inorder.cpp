#include <doctest/doctest.h>
#include <vector>
#include "../graphidx/tree/inorder.hpp"


TEST_CASE("inorder: t0")
{
    REQUIRE(std::vector<int>({}) == binary_inorder(0));
}


TEST_CASE("inorder: t1")
{
    REQUIRE(std::vector<int>({0}) == binary_inorder(1));
}


TEST_CASE("inorder: t2")
{
    REQUIRE(std::vector<int>({1, 0, 2}) == binary_inorder(2));
}


TEST_CASE("inorder: t3")
{
    REQUIRE(std::vector<int>({3, 1, 4, 0, 5, 2, 6}) == binary_inorder(3));
}


TEST_CASE("inorder: t4")
{
    REQUIRE(std::vector<int>({7, 3, 8, 1, 9, 4, 10, 0, 11, 5, 12, 2, 13, 6, 14}) == binary_inorder(4));
}
