#include <doctest/doctest.h>
#include "../graphidx/utils/timer.hpp"


TEST_CASE("Timer: endsnewline")
{
    REQUIRE(!endsnewline(""));
    REQUIRE(!endsnewline("asdf"));
    REQUIRE(!endsnewline("a"));
    REQUIRE(endsnewline("a\n"));
    REQUIRE(!endsnewline("a\na"));
    REQUIRE(endsnewline("a\na\n"));
}
