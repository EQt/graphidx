#include <doctest/doctest.h>

#include <vector>


TEST_CASE_TEMPLATE_DEFINE("heap sort", Queue, test_heap_sort)
{
    std::vector<int> perm {5, 2, 3, 4, 0, 1};
    Queue heap(perm.size());

    for (auto i : perm)
        heap.push(i, i);

    std::vector<int> sorted;
    while (!heap.empty()) {
        sorted.push_back(heap.top());
        heap.pop();
    }
    CHECK(sorted == std::vector<int>({0, 1, 2, 3, 4, 5}));
}


#ifdef HAVE_LEMON
#include <graphidx/heap/lemon_heap.hpp>

TEST_CASE_TEMPLATE_INVOKE(
    test_heap_sort,
    lemo::FibonacciHeap<int, int>,
    lemo::BinaryHeap<int, int>,
    lemo::PairingHeap<int, int>,
    Heap<lemo::QuadHeapT, int, int>);

#endif


#include <graphidx/heap/gnu_heap.hpp>
#ifdef HAVE_GNUX

TEST_CASE_TEMPLATE_INVOKE(
    test_heap_sort,
    Heap<gnux::ThinHeapT, int, int>,
    Heap<gnux::RcBinomHeapT, int, int>,
    Heap<gnux::PairHeapT, int, int>,
    Heap<gnux::BinomialHeapT, int, int>);

#endif
