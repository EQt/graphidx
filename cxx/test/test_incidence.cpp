#include <doctest/doctest.h>
#include <set>

#include "../graphidx/idx/incidence.hpp"


TEST_CASE("incidence: square")
{
    const std::vector<int>
        head {0, 0, 1, 2},
        tail {1, 2, 3, 3};
    const int n = 4;
    IncidenceIndex idx (head, tail);
    CHECK(idx.num_nodes() == n);
    CHECK(idx.num_edges() == 4);
    using inc_t = std::set<std::tuple<int, int>>;
    CHECK(idx[0] == inc_t({{1, 0}, {2, 1}}));
    CHECK(idx[1] == inc_t({{0, 0}, {3, 2}}));
    CHECK(idx[2] == inc_t({{0, 1}, {3, 3}}));
    CHECK(idx[3] == inc_t({{1, 2}, {2, 3}}));
}
