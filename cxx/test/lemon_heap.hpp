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


template <typename int_t = int, typename priority_t = double>
struct FibonacciHeap : public lemon::FibHeap<int_t, VecNodeMap<int_t, int_t>>
{
    using map_t = VecNodeMap<int_t, int_t>;
    using base_t = lemon::FibHeap<int_t, VecNodeMap<int_t, int_t>>;

    map_t nmap;
public:
    explicit FibonacciHeap(size_t n) : base_t(nmap), nmap (n) { }
};
