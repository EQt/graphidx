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
    CHECK(std::set<int>({2}) == cc[1]);
    CHECK(std::set<int>({3}) == cc[2]);
}
