#include <doctest/doctest.h>
#include "../graphidx/bits/weights.hpp"


TEST_CASE("weights: ones")
{
    auto w = create_weight<double>();
    REQUIRE(w[5] == 1.0);
    REQUIRE(w[42] == 1.0);
    REQUIRE((w[42] = 5.0) == 1.0);
}


TEST_CASE("weights: const13")
{
    auto w = create_weight(13.5);
    REQUIRE(13.5 == w[5]);
    REQUIRE(13.5 == w[0]);
    REQUIRE((w[42] = 5.0) == 13.5);
}


TEST_CASE("weights: array123")
{
    const int a[] = {1, 2, 5};
    auto w = create_weight(a);
    REQUIRE(5 == w[2]);
    REQUIRE(1 == w[0]);
    REQUIRE(2 == w[1]);
}


TEST_CASE("weights: modify")
{
    int a[] = {1, 2, 5};
    auto w = create_weight(a);
    REQUIRE(w[1] == 2);
    REQUIRE(5 == (w[1] = 5));
    REQUIRE(w[1] == 5);
}


TEST_CASE("weights: is_const<Const>")
{
    const Const<float> c (2.0);
    REQUIRE(is_const(c));
    REQUIRE(Const<float>::is_const());
}


TEST_CASE("weights: is_const<Ones>")
{
    const Ones<float> c;
    REQUIRE(is_const(c));
    REQUIRE(Ones<float>::is_const());
}


TEST_CASE("weights: is_const<Ones>")
{
    int a[] = {1, 2, 5};
    auto w = create_weight(a);
    REQUIRE(!is_const(w));
    REQUIRE(!Array<float>::is_const());
}
