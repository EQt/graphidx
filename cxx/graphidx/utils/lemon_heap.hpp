#pragma once

#include <lemon/concepts/graph_components.h>
#include <lemon/fib_heap.h>
#include <lemon/bin_heap.h>
#include <lemon/pairing_heap.h>


template <typename int_t, typename value_t = int_t>
struct VecNodeMap
{
    using Key = int_t;
    using Value = value_t;

    std::vector<int_t> items;

    explicit VecNodeMap(size_t n) : items(n, -1) { }

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


struct HeapTag { };

struct FibHeapTag : public HeapTag { };

struct BinHeapTag : public HeapTag { };

struct PairingHeapTag : public HeapTag { };


namespace detail {

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
    using Pair = typename Base::Pair;

public:
    Heap(size_t n) : HeapDispatch<Item, Prio, Tag>::type(nmap), nmap(n) { }

    void push(const Pair &p) { push(p.first, p.second); }
};


}   // namespace detail


template <typename int_t = int, typename priority_t = double>
using FibonacciHeap = detail::Heap<FibHeapTag, int_t, priority_t>;

template <typename int_t = int, typename priority_t = double>
using BinaryHeap = detail::Heap<BinHeapTag, int_t, priority_t>;

template <typename int_t = int, typename priority_t = double>
using PairingHeap = detail::Heap<PairingHeapTag, int_t, priority_t>;
