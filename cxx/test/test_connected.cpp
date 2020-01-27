#include <doctest/doctest.h>
#include <vector>
#include "../idx/biadjacent.hpp"
#include "../spanning/connected.hpp"


TEST_CASE("Connected: 4-3")
{
    const std::vector<int>
        head ({0, 1}),
        tail ({1, 3});
    BiAdjacent idx (head, tail);
    auto cc = connected_components(idx);

    CHECK(cc.size() == 2);
    CHECK(std::set<int>({0, 1, 3}) == cc[0]);
    CHECK(std::set<int>({2}) == cc[1]);
}


TEST_CASE("Connected: 4-2")
{
    const int n = 4;
    const std::vector<int>
        head ({0}),
        tail ({1});
    BiAdjacent idx (head, tail, n);
    auto cc = connected_components(idx);

    CHECK(cc.size() == 3);
    CHECK(std::set<int>({0, 1}) == cc[0]);
    CHECK(cc.largest() == cc[0]);
    CHECK(std::set<int>({2}) == cc[1]);
    CHECK(std::set<int>({3}) == cc[2]);
}


TEST_CASE("Connected: 4-2b")
{
    const int n = 4;
    const std::vector<int>
        head ({2}),
        tail ({3});
    BiAdjacent idx (head, tail, n);
    CHECK(idx.num_nodes() == n);
    CHECK(idx.num_edges() == 1);
    CHECK(idx.value == std::vector<int>({3, 2}));
    CHECK(idx.index == std::vector<int>({0, 0, 0, 1, 2}));
    CHECK(idx[0] == std::set<int>({}));
    CHECK(idx[1] == std::set<int>({}));
    CHECK(idx[2] == std::set<int>({3}));
    CHECK(idx[3] == std::set<int>({2}));

    CHECK(united(idx).mps() == std::vector<int>({0, 1, 2, 2}));

    auto cc = connected_components(idx);
    CHECK(cc.size() == 3);
    CHECK(cc.largest() == std::set<int>({3, 2}));
}
