#ifdef HAVE_LEMON
#include <doctest/doctest.h>
#include "lemon_heap.hpp"



TEST_CASE("Fib_Heap::sort")
{
    std::vector<int> perm {5, 2, 3, 4, 0, 1};
    FibonacciHeap<int, double> heap (perm.size());

    for (auto i : perm)
        heap.push(i, i);

    std::vector<int> sorted;
    while (!heap.empty()) {
        sorted.push_back(heap.top());
        heap.pop();
    }
    CHECK(sorted == std::vector<int>({0, 1, 2, 3, 4, 5}));
}


#endif
