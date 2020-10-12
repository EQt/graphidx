#pragma once
#include <limits>
#include <vector>

#include "heap.hpp"

template <typename int_t = int>
std::vector<int_t>
prim_mst_edges(
    const double *edge_weight,
    BiAdjacentIndex<int_t> &idx,
    int_t root = int_t(0))
{
    using pq_v = pq_element<int_t, double>;
    using pq_t = __gnu_pbds::priority_queue<pq_v, std::less<pq_v>>;
    constexpr auto INF = std::numeric_limits<double>::max();
    const size_t n = idx.num_nodes();

    pq_t queue;
    std::vector<int_t> parent (n, ~0);
    std::vector<typename pq_t::point_iterator> pnode;
    pnode.reserve(idx.num_nodes());
    for (int_t i = 0; i < (int_t) idx.num_nodes(); i++)
        pnode.push_back(queue.push({i, INF}));

    queue.modify(pnode[(size_t) root], {root, 0.0});
    parent[(size_t) root] = -root;
    while (!queue.empty()) {
        const auto u = queue.top().id;
        queue.pop();
        parent[(size_t) u] *= -1;
        for (const auto v : idx[u]) {
            if (parent[(size_t) v] >= 0)
                continue;
            // std::cout << u << " " << v << std::endl;
            const auto eidx = 0;    // TODO: actually extract it
            if (edge_weight[eidx] < pnode[(size_t) v]->dist) {
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
