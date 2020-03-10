#pragma once
#include <vector>

#include "unionfind.hpp"
#include "../idx/biadjacent.hpp"


template <typename int_ = int>
UnionFind<int_>
united(const AdjacencyIndex<int_> &neigh)
{
    const size_t n = neigh.size();
    UnionFind<int_> uf (n);
    for (size_t v = 0; v < n; v++)
        for (const auto ui : neigh[v]) {
            const auto u = (typename decltype(uf)::uint_) ui;
            const auto fv = uf.find(v);
            const auto fu = uf.find(u);
            if (fv != fu)
                uf.unite(fv, fu);
        }
    return uf;
}


template <typename int_ = int>
PartitionIndex<int_>
connected_components(const BiAdjacentIndex<int_> &neigh)
{
    return united(neigh).partitions();
}
