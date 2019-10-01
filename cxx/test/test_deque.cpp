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
    REQUIRE(42 == q.front<true>());
    REQUIRE(42 == q.front<false>());
    REQUIRE(42 == q.back<true>());
    REQUIRE(42 == q.back<false>());
}


TEST_CASE("DeQue: fbf")
{
    DeQue<int> q (2);
    q.push<true>(1);
    q.push<false>(5);
    q.push(2);

    REQUIRE(q);
    REQUIRE(3 == q.size());
    REQUIRE(2 == q.front<true>());
    REQUIRE(5 == q.front<false>());
    REQUIRE(5 == q.back<true>());
    REQUIRE(2 == q.back<false>());
}


TEST_CASE("DeQue: initializer list")
{
    DeQue<int> q {1, 2, 3, 4, 5};
    REQUIRE(q);
    REQUIRE(q.size() == 5);
    REQUIRE(q.front() == 1);
    REQUIRE(q.back() == 5);
}
