#pragma once

#include <lemon/concepts/graph_components.h>
#include <lemon/fib_heap.h>


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


template <typename int_t, typename priority_t, typename Tag>
struct HeapDispatch;


// partial specialization
template <typename int_t, typename priority_t>
struct HeapDispatch<int_t, priority_t, FibHeapTag>
{
    using type = lemon::FibHeap<priority_t, VecNodeMap<int_t, int_t>>;
};


template <typename Tag, typename int_t = int, typename priority_t = double>
struct Heap : public HeapDispatch<int_t, priority_t, Tag>::type
{
    VecNodeMap<int_t, int_t> nmap;
    public:
    Heap(size_t n) : HeapDispatch<int_t, priority_t, FibHeapTag>::type(nmap), nmap(n) { }
};


template <typename int_t = int, typename priority_t = double>
using FibonacciHeap = Heap<FibHeapTag, int_t, priority_t>;
