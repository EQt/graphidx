#pragma once
#include "../heap.hpp"
#include "aryheap.hpp"

namespace gidx {

struct OctaHeapT : public HeapT
{};


template <typename Item, typename Prio>
using OctaHeap = ::AryHeap<8, Item, Prio>;

} // namespace gidx


namespace detail {

template <typename Item, typename Prio>
struct Heap<gidx::OctaHeapT, Item, Prio> : public ::gidx::OctaHeap<Item, Prio>
{
    using ::gidx::OctaHeap<Item, Prio>::OctaHeap; // inherit constructor
};

} // namespace detail
