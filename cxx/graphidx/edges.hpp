/**
   Additional functions to iter over edges.
 */
#pragma once
#include <functional>
#include <graphidx/idx/biadjacent.hpp>
#include <graphidx/idx/incidence.hpp>


template <typename int_t>
void
edges(const IncidenceIndex<int_t> &idx, std::function<void(int_t, int_t, int_t)> f)
{
    for (size_t u = 0; u < idx.num_nodes(); u++) {
        for (const auto &[v, ei] : idx[u]) {
            f(u, v, ei);
        }
    }
}


template <typename int_t>
void
edges(const BiAdjacentIndex<int_t> &idx, std::function<void(int_t, int_t)> f)
{
    for (size_t v = 0; v < idx.num_nodes(); v++) {
        for (int_t u : idx[v]) {
            f(v, u);
        }
    }
}
