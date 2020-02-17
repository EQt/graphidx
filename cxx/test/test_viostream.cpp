#include <doctest/doctest.h>

#include "../graphidx/utils/viostream.hpp"


TEST_CASE("viostream: vector")
{
    std::vector<int> v {1, 3, 5, 13};
    SUBCASE("to_string") {
        REQUIRE(std::to_string(v) == "[1, 3, 5, 13]");
    }

    SUBCASE("operator<<") {
        std::ostringstream s;
        s << v;
        REQUIRE(s.str() == "[1, 3, 5, 13]");
    }
}
