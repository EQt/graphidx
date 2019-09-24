#include <doctest/doctest.h>
#include <set>
#include "../idx/partition.hpp"


TEST_CASE("partition: num5")
{
    //                     0  1  2  3  4
    std::vector<int> num5 {1, 2, 0, 0, 2};
    PartitionIndex<> pidx {num5};

    CHECK(std::set<int>({2, 3}) == pidx[0]);
    CHECK(std::set<int>({0}) == pidx[1]);
    CHECK(std::set<int>({1, 4}) == pidx[2]);
}
