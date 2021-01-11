#pragma once
#include <limits>
#include <stdexcept> // std::runtime_error
#include <string>
#include <type_traits> // std::is_integral
#include <vector>

#include "../idx/incidence.hpp"
#include "../utils/heap.hpp" // for Heap<...>


template <
    typename Tag,
    typename float_t,
    typename int_t = int,
    typename Queue = Heap<Tag, int_t, float_t>>
void
prim_mst_edges(
    int_t *parent,
    const float_t *edge_weight,
    const IncidenceIndex<int_t> &idx,
    const int_t root = int_t(0))
{
    Queue queue(idx.num_nodes());
    for (size_t i = 0; i < idx.num_nodes(); i++)
        parent[i] = ~0;

    queue.push({root, std::numeric_limits<float_t>::min()});
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
}


template <
    typename Tag,
    typename float_t,
    typename int_t = int,
    typename Queue = Heap<Tag, int_t, float_t>>
std::vector<int_t>
prim_mst_edges(
    const float_t *edge_weight,
    const IncidenceIndex<int_t> &idx,
    const int_t root = int_t(0))
{
    const size_t n = idx.num_nodes();
    std::vector<int_t> parent;
    parent.resize(n);
    prim_mst_edges<Tag, float_t, int_t, Queue>(parent.data(), edge_weight, idx, root);
    return parent;
}


// Local Variables:
// compile-command: "cd ../../../build && COLOR=0 make spantree &&
// ./cxx/benchmark/spantree" End:
