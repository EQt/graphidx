#pragma once
#include "../heap.hpp"
#include "aryheap.hpp"

namespace gidx {

struct QuadHeapT : public HeapT
{};


template <typename Item, typename Prio>
using QuadHeap = ::AryHeap<4, Item, Prio>;

} // namespace gidx


namespace detail {

template <typename Item, typename Prio>
struct Heap<gidx::QuadHeapT, Item, Prio> : public ::gidx::QuadHeap<Item, Prio>
{
    using ::gidx::QuadHeap<Item, Prio>::QuadHeap; // inherit constructor
};

} // namespace detail
