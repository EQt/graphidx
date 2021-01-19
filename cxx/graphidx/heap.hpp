#pragma once


/** Tag denoting type of Heap, e.g. FibHeapT */
struct HeapT { };


namespace detail {

template <typename Tag, typename Item, typename Prio>
struct Heap;
    
}   // namespace detail


namespace gnux {

template <typename Tag, typename Item = int, typename Prio = double>
struct HeapTypedef
{
    using impl = typename ::detail::Heap<Tag, Item, Prio>;
};

}   // namespace gnux

namespace detail {

template <typename int_t, typename priority_t, typename Tag>
struct HeapDispatch;

}


template <typename Tag, typename Item = int, typename Prio = double>
using Heap = typename gnux::HeapTypedef<Tag, Item, Prio>::impl;
