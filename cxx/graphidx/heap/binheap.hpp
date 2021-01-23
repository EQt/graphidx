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
    std::vector<Pair> arr;
    std::vector<size_t> idx; // map elements to their index in xs

    BinaryHeap() = delete;

    BinaryHeap(const size_t n) { reserve(n); }

    void reserve(const size_t n)
    {
        arr.reserve(n);
        idx.resize(n, 0);
    }

    Prio &operator[](const Item &key) { return arr[idx[key] - 1].second; }

    const Prio &operator[](const Item &key) const { return arr[idx[key] - 1].second; }

    inline void push(const Item &item, const Prio &prio) { push({item, prio}); }

    inline void push(const Pair p)
    {
        arr.push_back(p);
        idx[p.first] = arr.size();
        percolate_up(arr.size() - 1);
    }

    inline void pop()
    {
        const size_t last = size() - 1;
        idx[arr[0].first] = 0; // xs[0] will be removed
        arr[0] = arr[last];    // fill the hole with last element
        idx[arr[0].first] = 1;
        arr.pop_back(); // actually remove
        percolate_down(0);
    }

    inline void decrease(Item v, Prio prio)
    {
        if (contains(v)) {
            const auto i = idx[v] - 1;
            const Prio old_prio = arr[i].second;
            arr[i].second = prio;
            if (old_prio < prio)
                percolate_down(i);
            else
                percolate_up(i);
        } else {
            push(v, prio);
        }
    }

    inline bool contains(Item v) const { return idx[v] > 0; }

    size_t size() const { return arr.size(); }

    inline bool empty() const { return size() == 0; }

    inline Item top() const { return arr[0].first; }

private:
    static constexpr size_t K = 2;

    static size_t heapleft(size_t i) { return K * i + 1; }

    static size_t heapright(size_t i) { return K * i + K; }

    static size_t heapparent(size_t i) { return (i - 1) / K; }

    void percolate_down(size_t i)
    {
        const auto n = size();
        const auto x = arr[i];
        for (size_t c; heapleft(i) <= n; i = c) {
            c = heapleft(i); // smallest child's index
            for (size_t j = c + 1; j < n && j <= heapright(i); j++)
                if (arr[j].second < arr[c].second)
                    c = j;
            if (arr[c].second < x.second) {
                idx[arr[c].first] = i + 1;
                arr[i] = arr[c];
            } else {
                break;
            }
        }
        idx[x.first] = i + 1;
        arr[i] = x;
    }

    void percolate_up(size_t i) {
        const auto x = arr[i];
        for (size_t p; i > 0; i = p) {
            p = heapparent(i);
            if (x.second < arr[p].second) {
                idx[arr[p].first] = i + 1;
                arr[i] = arr[p];
            } else {
                break;
            }
        }
        idx[x.first] = i + 1;
        arr[i] = x;
    }
};

template <typename int_t, typename priority_t>
struct Heap<gidx::BinaryHeapT, int_t, priority_t> : public BinaryHeap<int_t, priority_t>
{
    Heap(const size_t n) : BinaryHeap<int_t, priority_t>(n) {}
};

} // namespace detail
