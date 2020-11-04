#pragma once

namespace detail {

template <typename Tag, typename Item, typename Prio>
struct Heap;
    
}

namespace gnux {

template <typename Tag, typename Item = int, typename Prio = double>
struct HeapTypedef
{
    using impl = typename ::detail::Heap<Tag, Item, Prio>;
};

}   // namespace detail


template <typename Tag, typename Item = int, typename Prio = double>
using Heap = typename gnux::HeapTypedef<Tag, Item, Prio>::impl;
