#pragma once
#include <vector>

#include "heap.hpp"


template <typename int_t = int, typename queue_t = priority_queue<int_t, double>>
std::vector<int_t>
prim_mst_edges(
    const double *edge_weight,
    IncidenceIndex<int_t> &idx,
    int_t root = int_t(0))
{
    const size_t n = idx.num_nodes();

    queue_t queue;
    std::vector<int_t> parent (n, ~0);
    std::vector<typename decltype(queue)::point_iterator> pnode (idx.num_nodes(), nullptr);

    pnode[(size_t) root] = queue.push({root, 0.0});
    parent[(size_t) root] = -root;
    while (!queue.empty()) {
        const auto u = queue.top().id;
        queue.pop();
        parent[(size_t) u] *= -1;
        for (const auto [v, eidx] : idx[u]) {
            if (parent[(size_t) v] >= 0)
                continue;
            const auto node = pnode[(size_t) v];
            if (node == nullptr) {
                parent[(size_t) v] = -u;
                pnode[(size_t) v] = queue.push({v, edge_weight[eidx]});
            } else if (edge_weight[eidx] < node->dist) {
                parent[(size_t) v] = -u;
                queue.modify(pnode[(size_t) v], {v, edge_weight[eidx]});
            }
        }
    }
    return parent;
}
    

// Local Variables:
// compile-command: "cd ../../build && COLOR=0 make spantree && ./cxx/benchmark/spantree"
// End:
