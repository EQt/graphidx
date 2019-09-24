#include <doctest/doctest.h>
#include <cstdint>
#include <limits>
#include "../bits/neg.hpp"


TEST_CASE("neg: negneg")
{
    REQUIRE(int64_t(123) == neg(neg(int64_t(123))));
    REQUIRE(int8_t(123) == neg(neg(int8_t(123))));
    REQUIRE(int32_t(123) == neg(neg(int32_t(123))));
    REQUIRE(int32_t(0) == neg(neg(int32_t(0))));
}


TEST_CASE("neg: not_same")
{
    REQUIRE(int64_t(123) != neg(int64_t(123)));
    REQUIRE(int8_t(123) != neg(int8_t(123)));
    REQUIRE(int32_t(123) != neg(int32_t(123)));
    REQUIRE(int64_t(0) != neg(int64_t(0)));

}


TEST_CASE("neg: digits")
{
    REQUIRE(8 == std::numeric_limits<uint8_t>::digits);
    REQUIRE(7 == std::numeric_limits<int8_t>::digits);
    REQUIRE(15 == std::numeric_limits<int16_t>::digits);
    REQUIRE(31 == std::numeric_limits<int32_t>::digits);
    REQUIRE(63 == std::numeric_limits<int64_t>::digits);
}


TEST_CASE("neg: is_pos")
{
    REQUIRE(is_pos(int32_t(34)));
    REQUIRE(is_pos(int32_t(0)));
    REQUIRE(!is_pos(neg(int32_t(0))));
    REQUIRE(!is_pos(neg(int64_t(34))));
}
