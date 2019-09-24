#include <doctest/doctest.h>
#include "../bits/bitstring.hpp"


/** Shift 0b1 to the left. */
extern uint64_t
shift1u64(int n)
{
    return n < 0 ? 0 : uint64_t(1) << n;
}


/** Like shift1u64 but with signed ints (to see whether it makes a difference). */
extern int
shift1int(int n)
{
    return n < 0 ? 0 : int(1) << n;
}


TEST_CASE("shift: shift_u64")
{
    // https://stackoverflow.com/a/7637
    // https://en.wikibooks.org/wiki/X86_Assembly/Shift_and_Rotate
    //   SAR (shift arithmetic right, or signed shift) vs
    //   SHR (shift [logical], or unsigned shift)
    //
    {
        uint64_t n = 64;
        CHECK(0 == (0x8000000000000000ULL >> (n-1)) >> 1);
        CHECK(0 == (0x8000000000000000ULL >> 63) >> 1);
        // undefined behavior: depends on the compiler
        CHECK(0ULL == (0x8000000000000000ULL >> (63)) >> 1);
    }

    CHECK(uint64_t(0) == shift1u64(63 - (int)64));
    CHECK(0x8000000000000000 == shift1u64(63));
    // const uint64_t nums[] = {0};
    // INFO(bitstring(shift1u64(63) >> leading_zeros(nums[0])));
    // CHECK(shift1u64(63) >> leading_zeros(nums[0]) == uint64_t(0));
}


TEST_CASE("shift: neg_int")
{
    CHECK(0 == shift1int(-1));
    int n = 64;
    CHECK(0 == shift1int(63 - n));
}


TEST_CASE("shift: neg_u64")
{
    INFO(bitstring(shift1u64(-1)));
    CHECK(uint64_t(0) == shift1u64(-1));

    {
        const int n = 64;
        INFO(bitstring(shift1u64(63 - n)));
        CHECK(uint64_t(0) == shift1u64(63 - n));
    }
}
