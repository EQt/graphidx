#pragma once
#include <algorithm>
#include <tuple>
#include <vector>


/**
   Binary heap: K = 2.
   Quad heap: K = 4.
   In contrast to `std::priority_queue`, the priority of an element can be
   updated.
 */
template <int K, typename Item, typename Prio>
struct AryHeap
{
    static_assert(std::is_integral<Item>::value, "need integers");

    using Pair = std::pair<Item, Prio>;
    std::vector<Pair> arr;
    std::vector<size_t> idx; // map elements to their index in xs

    AryHeap() = delete;

    AryHeap(const size_t n) { reserve(n); }

    void reserve(const size_t n)
    {
        arr.reserve(n);
        idx.resize(n, 0);
    }

    Prio &operator[](const Item &key) { return arr[at(key)].second; }

    const Prio &operator[](const Item &key) const { return arr[at(key)].second; }

    inline void push(const Item &item, const Prio &prio) { push({item, prio}); }

    inline void push(const Pair p)
    {
        arr.push_back(p);
        idx[size_t(p.first)] = arr.size();
        percolate_up(arr.size() - 1);
    }

    inline void pop()
    {
        const size_t last = size() - 1;
        idx[size_t(arr[0].first)] = 0; // xs[0] will be removed
        arr[0] = arr[last];            // fill the hole with last element
        idx[size_t(arr[0].first)] = 1;
        arr.pop_back(); // actually remove
        percolate_down(0);
    }

    inline void decrease(Item v, Prio prio)
    {
        if (contains(v)) {
            const size_t i = at(v);
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

    inline bool contains(Item v) const { return idx[size_t(v)] > 0; }

    size_t size() const { return arr.size(); }

    inline bool empty() const { return size() == 0; }

    inline Item top() const { return arr[0].first; }

  protected:
    inline size_t at(Item v) const { return idx[size_t(v)] - 1; }

    static inline size_t heapleft(size_t i) { return K * i + 1; }

    static inline size_t heapright(size_t i) { return K * i + K; }

    static inline size_t heapparent(size_t i) { return (i - 1) / K; }

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
                idx[size_t(arr[c].first)] = i + 1;
                arr[i] = arr[c];
            } else {
                break;
            }
        }
        idx[size_t(x.first)] = i + 1;
        arr[i] = x;
    }

    void percolate_up(size_t i)
    {
        const auto x = arr[i];
        for (size_t p; i > 0; i = p) {
            p = heapparent(i);
            if (x.second < arr[p].second) {
                idx[size_t(arr[p].first)] = i + 1;
                arr[i] = arr[p];
            } else {
                break;
            }
        }
        idx[size_t(x.first)] = i + 1;
        arr[i] = x;
    }
};
