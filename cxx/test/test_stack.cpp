#include <doctest/doctest.h>
#include "../std/stack.hpp"
#if !_STACK_DEBUG
#  error "Need to compile stack.hpp with #define _STACK_DEBUG 1"
#endif


TEST_CASE("stack: debugging")
{
    #ifndef _STACK_DEBUG
    REQUIRE(false);
    #endif
    REQUIRE(_STACK_DEBUG);
    REQUIRE(stack<int>::debug_mode());
    static_assert(sizeof(int*) + sizeof(size_t) + sizeof(size_t) == sizeof(stack<int>),
                  "wrong size");
}


TEST_CASE("stack: nothing")
{
    stack<int> stack;
}


TEST_CASE("stack: nothing_dbg")
{
    stack<int> stack;
}


TEST_CASE("stack: just_allocate")
{
    stack<int> stack;
    REQUIRE(stack.empty());
    REQUIRE(0 == stack.size());
    stack.reserve(1);
    REQUIRE(0 == stack.size());
}


/*
TEST_CASE("stack: underflow0")
{
    stack<int> s;
    REQUIRE(0 == s.size());
    REQUIRE(s.empty());
    REQUIRE(0 == s.pos);
    REQUIRE_THROWS_AS(s.back(), std::underflow_error);
    REQUIRE_THROWS_AS(s.pop_back(), std::underflow_error);
}
*/

TEST_CASE("stack: push1")
{
    stack<int> stack;
    REQUIRE(stack.empty());
    REQUIRE(0 == stack.size());
    stack.reserve(1);
    REQUIRE(0 == stack.size());
    REQUIRE(1 == stack.capacity());
    stack.push_back(-42);
    REQUIRE(1 == stack.size());
    REQUIRE(-42 == stack.back());
}


TEST_CASE("stack: throws")
{
    stack<int> stack;
    REQUIRE(stack.empty());
    REQUIRE(0 == stack.size());
    REQUIRE_THROWS_AS(stack.back(), std::underflow_error);
    REQUIRE(0 == stack.size());
    REQUIRE(0 == stack.capacity());
    REQUIRE_THROWS_AS(stack.reserve(0), std::invalid_argument);
    stack.reserve(2);
    REQUIRE(2 == stack.capacity());
    REQUIRE(0 == stack.size());
    stack.push_back(1);
    REQUIRE(1 == stack.size());
    stack.push_back(2);
    REQUIRE(2 == stack.size());
    REQUIRE(2 == stack.capacity());
    REQUIRE_THROWS_AS(stack.push_back(3), std::overflow_error);
}
