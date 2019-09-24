#include <doctest/doctest.h>
#include "../idx/biadjacent.hpp"


TEST_CASE("biadj: unequal_len")
{
    const std::vector<int>
        head {0, 1, 2, 3},
        tail {1, 2, 3, 0, 5};
    REQUIRE_THROWS_AS(BiAdjacent(head, tail), std::invalid_argument);
}


TEST_CASE("biadj: cell4")
{
    const std::vector<int>
        head {0, 1, 2, 3},
        tail {1, 2, 3, 0};

    const int n = 4;
    BiAdjacent b (head, tail);
    for (int i = 0; i < n; i++) {
        INFO("i = " << i);
        CHECK(std::set<int>(b[i]) == std::set<int>({(i+n-1)%n, (i+n+1)%n}));
    }
}

// Local Variables:
// compile-command: "cd ../../build && make doctests && ./doctests -nc -tc='biadj*'"
// End:
