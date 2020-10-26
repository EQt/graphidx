#ifdef HAVE_LEMON
#include <doctest/doctest.h>

#include <lemon/concepts/graph_components.h>
#include <lemon/fib_heap.h>

#include <graphidx/utils/viostream.hpp>


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


TEST_CASE("Fib_Heap::sort")
{
    std::vector<int> perm {5, 2, 3, 4, 0, 1};
    VecNodeMap<int> nmap (perm.size());

    lemon::FibHeap<int, decltype(nmap)> heap (nmap);
    for (auto i : perm) {
        heap.push(i, i);
        std::cout << nmap.items << std::endl;
    }

    std::vector<int> sorted;
    while (!heap.empty()) {
        sorted.push_back(heap.top());
        heap.pop();
    }
    CHECK(sorted == std::vector<int>({0, 1, 2, 3, 4, 5}));
}


#endif
