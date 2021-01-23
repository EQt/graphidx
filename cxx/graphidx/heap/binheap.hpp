#pragma once
#include "../heap.hpp"
#include "aryheap.hpp"

namespace gidx {

struct BinaryHeapT : public HeapT
{};


template <typename Item, typename Prio>
using BinaryHeap = ::AryHeap<4, Item, Prio>;

} // namespace gidx


namespace detail {

template <typename Item, typename Prio>
struct Heap<gidx::BinaryHeapT, Item, Prio> : public ::gidx::BinaryHeap<Item, Prio>
{
    using ::gidx::BinaryHeap<Item, Prio>::BinaryHeap; // inherit constructor
};

} // namespace detail
