#ifdef HAVE_LEMON
#include <doctest/doctest.h>
#include <graphidx/heap/lemon_heap.hpp>



TEST_CASE("Fib_Heap::sort")
{
    std::vector<int> perm {5, 2, 3, 4, 0, 1};
    FibonacciHeap<int, int> heap (perm.size());

    for (auto i : perm)
        heap.push(i, i);

    std::vector<int> sorted;
    while (!heap.empty()) {
        sorted.push_back(heap.top());
        heap.pop();
    }
    CHECK(sorted == std::vector<int>({0, 1, 2, 3, 4, 5}));
}


TEST_CASE("Bin_Heap::sort")
{
    std::vector<int> perm {5, 2, 3, 4, 0, 1};
    BinaryHeap<int, int> heap (perm.size());

    for (auto i : perm)
        heap.push(i, i);

    std::vector<int> sorted;
    while (!heap.empty()) {
        sorted.push_back(heap.top());
        heap.pop();
    }
    CHECK(sorted == std::vector<int>({0, 1, 2, 3, 4, 5}));
}


TEST_CASE("Pairing_Heap::sort")
{
    std::vector<int> perm {5, 2, 3, 4, 0, 1};
    PairingHeap<int, int> heap (perm.size());

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
