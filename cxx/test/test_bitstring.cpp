#include <doctest/doctest.h>
#include "../bits/bitstring.hpp"


TEST_CASE("bitstring: std_bitset1")
{
    std::bitset<8> bits {0x81};
    REQUIRE("10000001" == bits.to_string());
}


TEST_CASE("bitstring: std_bitset2")
{
    std::bitset<8> bits {std::string("10101111")};
    REQUIRE("10101111" == bits.to_string());
}


TEST_CASE("bitstring: bitset_u8")
{
    REQUIRE("10000001" == bitstring(uint8_t(0x81)));
}


TEST_CASE("bitstring: bitset_i8")
{
    REQUIRE("11111111" == bitstring(int8_t(-1)));
}


TEST_CASE("bitstring: bitset_i32_neg")
{
    REQUIRE("11111111111111111111111111111111" == bitstring(int32_t(-1)));
}


TEST_CASE("bitstring: bitset_i32_long")
{
    REQUIRE("00010001001000100011001101000100" == bitstring(int32_t(0x11223344)));
}


TEST_CASE("bitstring: bitset_f32_1")
{
    REQUIRE("00111111100000000000000000000000" == bitstring(1.0f));
}


TEST_CASE("bitstring: bitset_f32_2")
{
    REQUIRE("01000000000000000000000000000000" == bitstring(2.0f));
}


TEST_CASE("bitstring: bitset_f64_1")
{
    REQUIRE(bitstring(1.0) ==
            "0011111111110000000000000000000000000000000000000000000000000000");
}


TEST_CASE("bitstring: bitset_f64_2")
{
    REQUIRE(bitstring(2.0) ==
            "0100000000000000000000000000000000000000000000000000000000000000");
}
