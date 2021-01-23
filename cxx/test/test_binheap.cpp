#include <doctest/doctest.h>
#include <graphidx/heap/binheap.hpp>
#include <graphidx/heap/quadheap.hpp>


TEST_CASE_TEMPLATE_DEFINE("heap basic", Heap, test_heap_basics)
{
    constexpr size_t N = 6;
    Heap h(N);
    REQUIRE(h.empty());
    REQUIRE_EQ(h.size(), 0);

    for (size_t i = 0; i < N; i++) {
        REQUIRE(!h.contains(i));
    }

    h.push(5, 0.2f);
    REQUIRE(!h.empty());
    REQUIRE(h.contains(5));
    REQUIRE(!h.contains(3));
    REQUIRE_EQ(h.size(), 1);
    REQUIRE_EQ(h[5], 0.2f);
    REQUIRE_EQ(h.top(), 5);

    h.push(3, -1.0f);
    REQUIRE(!h.empty());
    REQUIRE_EQ(h.size(), 2);
    REQUIRE(h.contains(5));
    REQUIRE(h.contains(3));
    REQUIRE_EQ(h[5], 0.2f);
    REQUIRE_EQ(h[3], -1.0f);
    REQUIRE_EQ(h.top(), 3);

    h.pop();
    REQUIRE(!h.empty());
    REQUIRE(h.contains(5));
    REQUIRE(!h.contains(3));
    REQUIRE_EQ(h.size(), 1);
    REQUIRE_EQ(h[5], 0.2f);

    h.push(3, 1.0f);
    h.push(1, 0.1f);
    REQUIRE_EQ(h.size(), 3);
    REQUIRE_EQ(h.top(), 1);

    h.decrease(5, -2.0f);
    REQUIRE(!h.empty());
    REQUIRE_EQ(h.top(), 5);
}


TEST_CASE_TEMPLATE_INVOKE(
    test_heap_basics, gidx::BinaryHeap<int, float>, gidx::QuadHeap<int, float>);
