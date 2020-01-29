/*
  Utility functions around breadth-first-search (BFS), and tree level
  computation.
*/
#pragma once
#ifndef STD_QUEUE
#  define STD_QUEUE 0
#endif

#include <vector>
#include <stdexcept>
#if STD_QUEUE
#  include <queue>
   using std::queue;
#else
#  include "../std/queue.hpp"
#endif

#include "root.hpp"
#include "../idx/children.hpp"


template <typename int_ = int>
inline std::vector<int>
compute_bfs(const std::vector<int_> &parent, const int_ root)
{
    const auto n = parent.size();
    ChildrenIndex children (parent, root);
    std::vector<int_> bfs (n, -1);
    int_ b = int_(0);
    queue<int_> q (n);

    q.push(root);
    while (!q.empty()) {
        auto u = q.front(); q.pop();
        bfs[b++] = u;
        for (auto v : children[u])
            q.push(v);
    }
    return bfs;
}


template <typename int_ = int>
inline std::vector<int>
compute_bfs(const std::vector<int_> &parent)
{
    return compute_bfs(parent, find_root(parent));
}


inline std::vector<int>
compute_levels(const std::vector<int> &bfs,
               const std::vector<int> &parent)
{
    const auto n = bfs.size();
    std::vector<int> levels, depth(n, 0);
    levels.reserve(n);
    int d = 0;
    levels.push_back(0);   // 0th level: consists only of root = bfs[0]
    for (unsigned i = 1; i < n; i++) {
        const auto b = bfs[i];
        const auto db = 1 + depth[parent[b]];
        depth[b] = db;
        if (db > d) {
            d++;
            levels.push_back(i);
        }
    }
    levels.push_back(int(n));
    return levels;
}
