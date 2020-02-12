#include <doctest/doctest.h>
#include "../utils/perm.hpp"


TEST_CASE("perm")
{
    REQUIRE(is_perm(std::vector<int>({4, 3, 2, 1, 0})));
    REQUIRE(is_perm(std::vector<int>({3, 0, 2, 1, 4})));
    REQUIRE(!is_perm(std::vector<int>({3, 0, 2, 1, 5})));
    REQUIRE(!is_perm(std::vector<int>({3, 0, 2, 1, 2})));
}
