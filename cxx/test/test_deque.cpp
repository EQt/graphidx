#include <doctest/doctest.h>
#include "../std/deque.hpp"


TEST_CASE("DeQue: empty_bool")
{
    DeQue<int> q;
    REQUIRE(!q);
    REQUIRE(0 == q.size());
}


TEST_CASE("DeQue: one_push")
{
    DeQue<int> q (1);
    REQUIRE(!q);
    REQUIRE(0 == q.size());

    q.push<false>(42);
    REQUIRE(q);
    REQUIRE(1 == q.size());
    REQUIRE(42 == q.peek<true>());
    REQUIRE(42 == q.peek<false>());
}


TEST_CASE("DeQue: fbf")
{
    DeQue<int> q (2);
    q.push<true>(1);
    q.push<false>(5);
    q.push(2);

    REQUIRE(q);
    REQUIRE(3 == q.size());
    REQUIRE(2 == q.peek<true>());
    REQUIRE(5 == q.peek<false>());
}
