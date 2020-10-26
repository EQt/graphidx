#pragma once
#include <stdexcept>        // std::runtime_error
#include <string>
#include <type_traits>      // std::is_integral
#include <vector>

#include "../utils/heap.hpp"


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

    queue.push({root, 0.0});
    parent[(size_t) root] = -root;
    while (!queue.empty()) {
        const auto u = queue.top().id;
        queue.pop();
        parent[(size_t) u] *= -1;
        for (const auto [v, eidx] : idx[u]) {
            if (parent[(size_t) v] >= 0)
                continue;
            const auto node = queue[v];
            if (node == nullptr) {
                parent[(size_t) v] = -u;
                queue.push({v, edge_weight[eidx]});
            } else if (edge_weight[eidx] < node->dist) {
                parent[(size_t) v] = -u;
                queue.decrease(v, edge_weight[eidx]);
            }
        }
    }
    return parent;
}
    

// Local Variables:
// compile-command: "cd ../../../build && COLOR=0 make spantree && ./cxx/benchmark/spantree"
// End: