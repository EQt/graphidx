#pragma once
#include <stdexcept>        // std::runtime_error
#include <string>
#include <type_traits>      // std::is_integral
#include <vector>

#include "../utils/gnu_heap.hpp"


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
    std::vector<int_t> _parent (n, ~0);
    int_t *parent = _parent.data();

    queue.push({root, 0.0});
    parent[root] = -root;
    while (!queue.empty()) {
        const auto u = queue.top();
        queue.pop();
        parent[u] *= -1;
        for (const auto [v, eidx] : idx[u]) {
            if (parent[v] >= 0)
                continue;
            if (!queue.contains(v)) {
                parent[v] = -u;
                queue.push({v, edge_weight[eidx]});
            } else if (edge_weight[eidx] < queue[v]) {
                parent[v] = -u;
                queue.decrease(v, edge_weight[eidx]);
            }
        }
    }
    return _parent;
}
    

// Local Variables:
// compile-command: "cd ../../../build && COLOR=0 make spantree && ./cxx/benchmark/spantree"
// End:
