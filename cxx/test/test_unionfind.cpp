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


TEST_CASE("UnionFind: Partitions 4-3")
{
    UnionFind<int> u (4);
    u.unite(u.find(3), u.find(0));

    const auto parts = u.partitions();
    CHECK(parts.size() == 3);
    CHECK(std::set<int>({0, 3}) == parts[0]);
    CHECK(std::set<int>({1}) == parts[1]);
    CHECK(std::set<int>({2}) == parts[2]);
    CHECK(parts.largest() == parts[0]);
}


TEST_CASE("UnionFind: Partitions 4-2")
{
    UnionFind<int> u (4);
    u.unite(u.find(3), u.find(0));
    u.unite(u.find(3), u.find(1));

    const auto reps = u.mps();
    CHECK(reps == std::vector<int>({0, 0, 2, 0}));

    const auto parts = u.partitions();
    CHECK(parts.size() == 2);
    CHECK(std::set<int>({0, 1, 3}) == parts[0]);
    CHECK(std::set<int>({2}) == parts[1]);
    CHECK(parts.largest() == parts[0]);
}
