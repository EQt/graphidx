#pragma once
#include <stdexcept>        // std::runtime_error
#include <string>
#include <type_traits>      // std::is_integral
#include <vector>

#include "../utils/heap.hpp"



template <typename tag_t = __gnu_pbds::pairing_heap_tag,
          typename int_t = int,
          typename priority_t = double,
          typename queue_t = priority_queue<tag_t, int_t, priority_t>>
struct heap_t : public priority_queue<tag_t, int_t, priority_t>
{
    static_assert(std::is_integral<int_t>::value, "need integers");
    static_assert(std::is_signed<int_t>::value, "need the sign bit");

    using base_t = priority_queue<tag_t, int_t, priority_t>;

    std::vector<typename base_t::point_iterator> pnode;

    explicit heap_t(size_t n) : pnode(n, nullptr) {
        if (this->max_size() < n)
            throw std::runtime_error(std::string("max_size() = ") +
                                     std::to_string(this->max_size()) + ", n = " +
                                     std::to_string(n));
    }
};


template <typename tag_t = __gnu_pbds::pairing_heap_tag,
          typename int_t = int,
          typename queue_t = heap_t<tag_t, int_t, double>>
std::vector<int_t>
prim_mst_edges(
    const double *edge_weight,
    const IncidenceIndex<int_t> &idx,
    const int_t root = int_t(0))
{
    const size_t n = idx.num_nodes();
    queue_t queue (idx.num_nodes());
    std::vector<int_t> parent (n, ~0);

    queue.pnode[(size_t) root] = queue.push({root, 0.0});
    parent[(size_t) root] = -root;
    while (!queue.empty()) {
        const auto u = queue.top().id;
        queue.pop();
        parent[(size_t) u] *= -1;
        for (const auto [v, eidx] : idx[u]) {
            if (parent[(size_t) v] >= 0)
                continue;
            const auto node = queue.pnode[(size_t) v];
            if (node == nullptr) {
                parent[(size_t) v] = -u;
                queue.pnode[(size_t) v] = queue.push({v, edge_weight[eidx]});
            } else if (edge_weight[eidx] < node->dist) {
                parent[(size_t) v] = -u;
                queue.modify(queue.pnode[(size_t) v], {v, edge_weight[eidx]});
            }
        }
    }
    return parent;
}
    

// Local Variables:
// compile-command: "cd ../../../build && COLOR=0 make spantree && ./cxx/benchmark/spantree"
// End:
