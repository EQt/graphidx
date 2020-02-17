#include <doctest/doctest.h>
#include "../graphidx/spanning/kruskal_mst.hpp"


TEST_CASE("KruskalMST: square1")
{
    const std::vector<int>
        head {0, 0, 1, 2},
        tail {2, 1, 3, 3};

    const size_t n = 4;

    {
        const std::vector<double> weights = {0, 0, 0, 1};

        const auto included = minimum_spanning_tree(n, head, tail, weights);
        REQUIRE(std::vector<bool>({true, true, true, false}) == included);
    }
    {
        const std::vector<double> weights = {0, 0, 1, 0};

        const auto included = minimum_spanning_tree(n, head, tail, weights);
        REQUIRE(std::vector<bool>({true, true, false, true}) == included);
    }
    {
        const std::vector<double> weights = {1, 0, 0, 0};

        const auto included = minimum_spanning_tree(n, head, tail, weights);
        REQUIRE(std::vector<bool>({false, true, true, true}) == included);
    }
}
