#pragma once

#include <lemon/concepts/graph_components.h>
#include <lemon/fib_heap.h>
#include <lemon/bin_heap.h>
#include <lemon/quad_heap.h>
#include <lemon/pairing_heap.h>


struct HeapTag { };

struct FibHeapTag : public HeapTag { };

struct BinHeapTag : public HeapTag { };

struct PairingHeapTag : public HeapTag { };

struct QuadHeapTag : public HeapTag { };


namespace detail {

template <typename int_t, typename value_t = int_t>
struct VecNodeMap
{
    static_assert(std::is_integral<int_t>::value, "need integers");
    static_assert(std::is_integral<value_t>::value, "need integers");
    static_assert(std::is_signed<value_t>::value, "need the sign bit");

    using Key = int_t;
    using Value = value_t;

    std::vector<int_t> items;

    explicit VecNodeMap(size_t n) : items(n, int_t(-1)) { }

    Value& operator[](const Key& key) {
        return items[key];
    }

    const Value& operator[](const Key& key) const {
        return items[key];
    }

    void set(const Key &key, const Value &val) {
        (*this)[key] = val;
    }
};

template <typename int_t, typename priority_t, typename Tag>
struct HeapDispatch;


// partial specialization: Fibonacci heap
template <typename int_t, typename priority_t>
struct HeapDispatch<int_t, priority_t, FibHeapTag>
{
    using type = ::lemon::FibHeap<priority_t, VecNodeMap<int_t, int_t>>;
};


// partial specialization: Binary heap
template <typename int_t, typename priority_t>
struct HeapDispatch<int_t, priority_t, BinHeapTag>
{
    using type = ::lemon::BinHeap<priority_t, VecNodeMap<int_t, int_t>>;
};


// partial specialization: Four-ary heap
template <typename int_t, typename priority_t>
struct HeapDispatch<int_t, priority_t, QuadHeapTag>
{
    using type = ::lemon::QuadHeap<priority_t, VecNodeMap<int_t, int_t>>;
};



// partial specialization: Pairing heap
template <typename int_t, typename priority_t>
struct HeapDispatch<int_t, priority_t, PairingHeapTag>
{
    using type = ::lemon::PairingHeap<priority_t, VecNodeMap<int_t, int_t>>;
};


template <typename Tag, typename Item = int, typename Prio = double>
struct Heap : public HeapDispatch<Item, Prio, Tag>::type
{
    VecNodeMap<Item, Item> nmap;
    using Base = typename HeapDispatch<Item, Prio, Tag>::type;
    using Pair = typename std::pair<Item, Prio>;

public:
    Heap(size_t n) : HeapDispatch<Item, Prio, Tag>::type(nmap), nmap(n) { }

    inline void push(const Pair &p) { Base::push(p.first, p.second); }

    inline void push (const Item& item, const Prio& prio) { Base::push(item, prio); }

    inline bool contains(Item v) const { return nmap[v] >= 0; }
};


}   // namespace detail


template <typename int_t = int, typename priority_t = double>
using FibonacciHeap = detail::Heap<FibHeapTag, int_t, priority_t>;

template <typename int_t = int, typename priority_t = double>
using BinaryHeap = detail::Heap<BinHeapTag, int_t, priority_t>;

template <typename int_t = int, typename priority_t = double>
using PairingHeap = detail::Heap<PairingHeapTag, int_t, priority_t>;

template <typename int_t = int, typename priority_t = double>
using QuadHeap = detail::Heap<QuadHeapTag, int_t, priority_t>;
