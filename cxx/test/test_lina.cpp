#include <doctest/doctest.h>

#include "../lina.hpp"


TEST_CASE("lina: l1_diff")
{
    SUBCASE("zero size") {
        const auto zero = l1_diff(0, (double*) NULL, (double*) NULL);
        CHECK(std::isinf(zero));
        CHECK(zero < 0.0);
    }
    SUBCASE("one element") {
        const double x[] = {3.0};
        const double y[] = {-1.0};
        CHECK(l1_diff(1, x, y) == 4.0);
    }
    SUBCASE("2d") {
        const double x[] = {3.0, 1.0};
        const double y[] = {-1.0, 0.0};
        CHECK(l1_diff(2, x, y) == 4.0);
    }
    SUBCASE("2d:2") {
        const int x[] = {0, 1};
        const int y[] = {0, 1};
        CHECK(l1_diff(2, x, y) == 0);
    }
    SUBCASE("2d:3") {
        const int x[] = {0, +1};
        const int y[] = {0, -1};
        CHECK(l1_diff(2, x, y) == 2);
    }
}
