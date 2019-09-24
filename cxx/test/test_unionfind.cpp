#include <doctest/doctest.h>
#include "../spanning/unionfind.hpp"

bool
operator==(const int a, const UnionFind<int>::Rep b)
{
    return a == b.i;
}


TEST_CASE("UnionFind: mini_test_2")
{
    UnionFind<int> u (2);
    REQUIRE(1 == u.find(1));
    REQUIRE(0 == u.find(0));

    u.unite(u.find(1), u.find(0));
    REQUIRE(u.find(1) == u.find(0));
    REQUIRE(u.find(0) == u.find(1));
}


TEST_CASE("UnionFind: mini_test_3")
{
    UnionFind<int> u (3);
    REQUIRE(2 == u.find(2));
    REQUIRE(1 == u.find(1));
    REQUIRE(0 == u.find(0));

    u.unite(u.find(2), u.find(0));
    CHECK(u.find(2) == u.find(0));
    CHECK(u.find(0) == u.find(2));

    CHECK(u.find(1) != u.find(2));
    CHECK(u.find(0) != u.find(1));

    u.unite(u.find(1), u.find(0));
    CHECK(u.find(1) == u.find(2));
    CHECK(u.find(0) == u.find(1));
    CHECK(u.find(1) == u.find(0));
}


TEST_CASE("UnionFind: mini_test_4")
{
    UnionFind<int> u (4);
    REQUIRE(3 == u.find(3));
    REQUIRE(2 == u.find(2));
    REQUIRE(1 == u.find(1));
    REQUIRE(0 == u.find(0));

    u.unite(u.find(3), u.find(0));
    CHECK(u.find(0) == u.find(3));
    CHECK(u.find(0) == u.find(3));
    CHECK(u.find(0) == u.find(0));
    CHECK(u.find(3) == u.find(0));

    CHECK(u.find(2) != u.find(3));
    CHECK(u.find(3) != u.find(2));
    CHECK(u.find(0) != u.find(2));
    CHECK(u.find(0) != u.find(2));

    u.unite(u.find(3), u.find(2));
    CHECK(u.find(2) == u.find(3));
    CHECK(u.find(3) == u.find(2));
    CHECK(u.find(0) == u.find(2));
    CHECK(u.find(0) == u.find(2));
    CHECK(u.find(2) == u.find(0));
}


TEST_CASE("UnionFind: mini_test_4a")
{
    UnionFind<int> u (4);
    u.unite(u.find(3), u.find(0));

    CHECK(u.find(3) != u.find(2));

    u.unite(u.find(2), u.find(0));

    CHECK(u.find(3) == u.find(2));
    CHECK(u.find(1) != u.find(2));
    CHECK(u.find(1) != u.find(3));

    u.unite(u.find(0), u.find(1));

    CHECK(u.find(1) == u.find(2));
    CHECK(u.find(1) == u.find(3));
    CHECK(u.find(0) == u.find(2));
    CHECK(u.find(0) == u.find(3));
}
