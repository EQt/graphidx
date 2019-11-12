#include <doctest/doctest.h>
#include "../bits/weights.hpp"


TEST_CASE("weights: ones")
{
    auto w = create_weight<double>();
    REQUIRE(w[5] == 1.0);
    REQUIRE(w[42] == 1.0);
}


TEST_CASE("weights: const13")
{
    auto w = create_weight(13.5);
    REQUIRE(13.5 == w[5]);
    REQUIRE(13.5 == w[0]);
}


TEST_CASE("weights: array123")
{
    const int a[] = {1, 2, 5};
    auto w = create_weight(a);
    REQUIRE(5 == w[2]);
    REQUIRE(1 == w[0]);
    REQUIRE(2 == w[1]);
}
