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


TEST_CASE("biadj: cell4-induced subgraph")
{
    const std::vector<int>
        head {0, 1, 2, 3},
        tail {1, 2, 3, 0},
        sub {0, 1, 3};

    BiAdjacent b (head, tail);
    b.induced_subgraph(sub);
    CHECK(b.num_nodes() == sub.size());
    CHECK(b[0] == std::set<int>({1, 2}));
    CHECK(b[1] == std::set<int>({0}));
    CHECK(b[2] == std::set<int>({0}));
}


// Local Variables:
// compile-command: "cd ../../build && make doctests && ./doctests -nc -tc='biadj*'"
// End:
