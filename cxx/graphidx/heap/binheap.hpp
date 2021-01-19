#pragma once
#include <algorithm>
#include <tuple>
#include <vector>

#include "../heap.hpp"

namespace gidx {

struct BinaryHeapT : public HeapT
{};

} // namespace gidx

namespace detail {

/**
   Binary heap.
   In contrast to `std::priority_queue`, the priority of an element can be
   updated.
 */
template <typename Item, typename Prio>
struct BinaryHeap
{
    static_assert(std::is_integral<Item>::value, "need integers");

    using Pair = std::pair<Item, Prio>;
    std::vector<Pair> xs;
    std::vector<size_t> idx; // map elements to their index in xs

    BinaryHeap() = delete;

    BinaryHeap(const size_t n) { reserve(n); }

    void reserve(const size_t n)
    {
        xs.reserve(n);
        idx.resize(n, 0);
    }

    Prio &operator[](const Item &key) { return xs[idx[key] - 1].second; }

    const Prio &operator[](const Item &key) const { return xs[idx[key] - 1].second; }

    inline void push(const Item &item, const Prio &prio) { push({item, prio}); }

    inline void push(const Pair p)
    {
        const auto key = p.first;
        xs.push_back(p);
        idx[key] = xs.size();
        perculate_up(xs.size());
    }

    inline void pop();

    inline void decrease(Item v, Prio prio);

    inline bool contains(Item v) const { return idx[v] > 0; }

    size_t size() const { return xs.size(); }

    inline bool empty() const { return size() > 0; }

    inline Item top() const { return 0; }

  private:
    void swap(size_t i, size_t j)
    {
        std::swap(xs[i], xs[j]);
        std::swap(idx[i], idx[j]);
    }

    void perculate_down(size_t i);

    void perculate_up(size_t) {}
};

template <typename int_t, typename priority_t>
struct Heap<gidx::BinaryHeapT, int_t, priority_t> : public BinaryHeap<int_t, priority_t>
{
    Heap(const size_t n) : BinaryHeap<int_t, priority_t>(n) {}
};

} // namespace detail
