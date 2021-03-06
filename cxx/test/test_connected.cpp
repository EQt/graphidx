#include <doctest/doctest.h>
#include <vector>
#include "../graphidx/idx/biadjacent.hpp"
#include "../graphidx/spanning/connected.hpp"


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
    BiAdjacent idx (head, tail);
    CHECK(idx.num_nodes() == n);
    CHECK(idx.num_edges() == head.size());
    const uvector<int> idx_value ({3, 2});
    const std::vector<int> idx_index ({0, 0, 0, 1, 2});
    CHECK(idx.value == idx_value);
    CHECK(idx.index == idx_index);
    {
        std::vector<int> degs (idx.num_nodes());
        idx.degrees(degs.data());
        CHECK(degs == std::vector<int>({0, 0, 1, 1}));
    }
    {
        Index<int> aidx {idx_value.copy(), idx_index};
        bool found = false;
        for (int v : aidx[2]) {
            CHECK(v == 3);
            found = true;
        }
        CHECK(found);
        CHECK(aidx[2].size() == 1);
    }
    CHECK(idx[0] == std::set<int>({}));
    CHECK(idx[1] == std::set<int>({}));
    {
        Index<int> &idX = idx;
        CHECK(idX[2] == std::set<int>({3}));
        CHECK(idX[3] == std::set<int>({2}));
    }

    CHECK(united(idx).mps() == std::vector<int>({0, 1, 3, 3}));

    auto cc = connected_components(idx);
    CHECK(cc.size() == 3);
    CHECK(cc.largest() == std::set<int>({3, 2}));
}
