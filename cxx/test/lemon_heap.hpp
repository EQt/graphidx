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


template <typename int_t = int, typename priority_t = double>
struct FibonacciHeap : public HeapDispatch<int_t, priority_t, FibHeapTag>::type
{
    using map_t = VecNodeMap<int_t, int_t>;
    using base_t = typename HeapDispatch<int_t, priority_t, FibHeapTag>::type;

    map_t nmap;
public:
    explicit FibonacciHeap(size_t n) : base_t(nmap), nmap (n) { }
};
