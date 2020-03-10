#include <doctest/doctest.h>
#include "../graphidx/spanning/unionfind.hpp"

bool
operator==(const unsigned a, const typename UnionFind<unsigned>::Rep b)
{
    return a == b.i;
}


TEST_CASE("UnionFind: mini_test_2")
{
    UnionFind<unsigned> u (2);
    REQUIRE(u.find(1) == 1u);
    REQUIRE(u.find(0) == 0u);

    u.unite(u.find(1), u.find(0));
    REQUIRE(u.find(1) == u.find(0));
    REQUIRE(u.find(0) == u.find(1));
}


TEST_CASE("UnionFind: mini_test_3")
{
    UnionFind<unsigned> u (3);
    REQUIRE(2u == u.find(2));
    REQUIRE(1u == u.find(1));
    REQUIRE(0u == u.find(0));

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
    UnionFind<unsigned> u (4);
    REQUIRE(3u == u.find(3));
    REQUIRE(2u == u.find(2));
    REQUIRE(1u == u.find(1));
    REQUIRE(0u == u.find(0));

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
    UnionFind<unsigned> u (4);
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
    UnionFind<unsigned> u (4);
    u.unite(u.find(3), u.find(0));

    const auto parts = u.partitions();
    CHECK(parts.size() == 3);
    CHECK(std::set<unsigned>({0, 3}) == parts[0]);
    CHECK(std::set<unsigned>({1}) == parts[1]);
    CHECK(std::set<unsigned>({2}) == parts[2]);
    CHECK(parts.largest() == parts[0]);
}


TEST_CASE("UnionFind: Partitions 4-2")
{
    UnionFind<unsigned> u (4);
    u.unite(u.find(3), u.find(0));
    u.unite(u.find(3), u.find(1));

    const auto reps = u.mps();
    CHECK(reps == std::vector<unsigned>({0, 0, 2, 0}));

    const auto parts = u.partitions();
    CHECK(parts.size() == 2);
    CHECK(std::set<unsigned>({0, 1, 3}) == parts[0]);
    CHECK(std::set<unsigned>({2}) == parts[1]);
    CHECK(parts.largest() == parts[0]);
}
