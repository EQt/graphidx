#pragma once
#include <algorithm>
#include <tuple>
#include <vector>

/**
   Binary heap.
   In contrast to `std::priority_queue`, the priority of an element can be updated.
 */
template <typename K, typename V>
struct BinaryHeap
{
    using Pair = std::tuple<K, V>;
    std::vector<Pair> xs;
    std::vector<size_t> idx; // map elements to their index in xs
    BinaryHeap() = default;
    BinaryHeap(const size_t n) { reserve(n); }

    void reserve(const size_t n)
    {
        xs.reserve(n);
        idx.reserve(n);
    }

    size_t size() const { return xs.size(); }
};
