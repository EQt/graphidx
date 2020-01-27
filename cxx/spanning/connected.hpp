#pragma once
#include <vector>

#include "unionfind.hpp"
#include "../idx/biadjacent.hpp"


inline UnionFind<int>
united(const BiAdjacent &neigh)
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
    return uf;
}


PartitionIndex<int>
connected_components(const BiAdjacent &neigh)
{
    return united(neigh).partitions();
}
