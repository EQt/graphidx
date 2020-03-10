#pragma once

#include <random>                   // std::default_random_engine
#include <algorithm>                // std::shuffle

#include "../idx/biadjacent.hpp"
#include "../idx/partition.hpp"
#include "../std/stack.hpp"


template <typename int_, typename Idx>
inline PartitionIndex<int_>
cluster(const size_t n,
        const double *x,
        const BiAdjacent &neighidx,
        const double eps,
        const size_t seed)
{
    stack<int_> s {n};
    std::vector<int_> parts (n, -1);

    // One could avoid the allocation of n*sizeof(int) by computing a
    // random permutation dynamically.  However, then we would need to
    // compute the rank operation efficiently.
    std::vector<int_> randperm;
    randperm.resize(n);
    for (size_t i = 0; i < n; i++)
        randperm[i] = (int_) i;
    std::shuffle(randperm.begin(), randperm.end(),
                 std::default_random_engine(seed));

    size_t nextp = 0;
    for (const auto i : randperm) {
        if (parts[(size_t) i] < 0) {         // unexplored?
            s.push_back(i);         // DFS starting at i
            while (!s.empty()) {
                const size_t v = (size_t) s.pop_back();
                parts[v] = (int_) nextp;
                for (const auto ui : neighidx[v]) {
                    const size_t u = (size_t) ui;
                    if (std::abs(x[v] - x[u]) <= eps && parts[u] < 0)
                        s.push_back(ui);
                }
            }                       // connected component is finished
            nextp++;
        }
    }
    // Can't we reuse the stack's memory for computing the PartitionIndex?
    return PartitionIndex<int_>(parts);
}
