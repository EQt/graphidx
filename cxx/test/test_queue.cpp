#include <doctest/doctest.h>
#include "../graphidx/std/queue.hpp"

TEST_CASE("queue: nothing")
{
    queue<int> queue;
    REQUIRE(0 == queue.capacity());
    REQUIRE(0 == queue.size());
}


TEST_CASE("queue: just_allocate")
{
    queue<int> queue;
    REQUIRE(queue.empty());
    REQUIRE(0 == queue.size());
    queue.reserve(1);
    REQUIRE(0 == queue.size());
    REQUIRE(1 == queue.capacity());
}


TEST_CASE("queue: push1")
{
    queue<int> queue;
    REQUIRE(queue.empty());
    REQUIRE(0 == queue.size());

    queue.reserve(1);
    REQUIRE(0 == queue.size());
    REQUIRE(1 == queue.capacity());

    REQUIRE(0 == queue.head);
    REQUIRE(0 == queue.tail);
    queue.push(-42);
    REQUIRE(1 == queue.tail);
    REQUIRE(0 == queue.head);
    REQUIRE(1 == queue.size());
    REQUIRE(-42 == queue.front());
}


TEST_CASE("queue: push2")
{
    queue<int> queue;
    REQUIRE(queue.empty());
    REQUIRE(0 == queue.size());
    REQUIRE(0 == queue.capacity());

    queue.reserve(3);
    REQUIRE(3 == queue.capacity());
    REQUIRE(0 == queue.size());

    queue.push(1);
    REQUIRE(1 == queue.size());
    REQUIRE(1 == queue.tail);
    REQUIRE(0 == queue.head);
    queue.push(2);
    REQUIRE(2 == queue.size());
    REQUIRE(3 == queue.capacity());

    REQUIRE(1 == queue.front());
    queue.pop();
    REQUIRE(1 == queue.size());
    REQUIRE(2 == queue.front());

    queue.push(3);
    REQUIRE(2 == queue.size());
    queue.pop();
    REQUIRE(1 == queue.size());
    queue.pop();
    REQUIRE(0 == queue.size());
    REQUIRE(queue.empty());
}
