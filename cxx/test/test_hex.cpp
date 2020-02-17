#include <doctest/doctest.h>
#include "../graphidx/bits/hex.hpp"


TEST_CASE("hex: hex_u32")
{
    REQUIRE("0xfa" == hex(0xfau));
    REQUIRE("0xaabbcc" == hex(0xaabbccu));
    REQUIRE("0x12345678" == hex(0x12345678u));
}


TEST_CASE("hex: hex_i32")
{
    REQUIRE("0xfa" == hex(0xfa));
    REQUIRE("0xaabbcc" == hex(0xaabbcc));
    REQUIRE("0x12345678" == hex(0x12345678));
}


TEST_CASE("hex: hex_u64")
{
    REQUIRE("0xfa" == hex(uint64_t(0xfa)));
    REQUIRE("0xaabbcc" == hex(uint64_t(0xaabbcc)));
    REQUIRE("0x12345678" == hex(uint64_t(0x12345678)));
}


TEST_CASE("hex: hex_i64")
{
    REQUIRE("0xfa" == hex(int64_t(0xfa)));
    REQUIRE("0xaabbcc" == hex(int64_t(0xaabbcc)));
    REQUIRE("0x12345678" == hex(int64_t(0x12345678)));
}


TEST_CASE("hex: hex_f64")
{
    REQUIRE("f64(0x3ff0000000000000)" == hex(1.0));
    REQUIRE("f64(0x3fb999999999999a)" == hex(0.1));
    REQUIRE("f64(0x4000000000000000)" == hex(2.0));
}


TEST_CASE("hex: hex_f32")
{
    REQUIRE("f32(0x3f800000)" == hex(1.0f));
    REQUIRE("f32(0x3dcccccd)" == hex(0.1f));
    REQUIRE("f32(0x40000000)" == hex(2.0f));
}
