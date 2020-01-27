#pragma once
#include "unionfind.hpp"
#include "../idx/biadjacent.hpp"


void
connected_components(const BiAdjacent &neigh)
{
    const size_t n = neigh.num_nodes();
    UnionFind<int> uf (n);
    for (int v = 0; v < int(n); v++)
        for (const int u : neigh[v]) {
            const auto fv = uf.find(v);
            const auto fu = uf.find(u);
            if (fv != fu)
                uf.unite(fv, fu);
        }
}
