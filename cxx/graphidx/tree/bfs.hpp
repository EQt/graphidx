/*
  Utility functions around breadth-first-search (BFS), and tree level
  computation.
*/
#pragma once
#ifndef STD_QUEUE
#  define STD_QUEUE 1
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
void
compute_bfs(int_ *bfs, const ChildrenIndex &cidx, queue<int_> &q)
{
#if !STD_QUEUE    
    q.reserve(cidx.size());
#endif
    int_ b = int_(0);
    q.push(cidx.root_node());
    while (!q.empty()) {
        auto u = q.front(); q.pop();
        bfs[b++] = u;
        for (auto v : cidx[u])
            q.push(v);
    }
}


template <typename int_ = int>
void
compute_bfs(std::vector<int_> &bfs, const ChildrenIndex &cidx, queue<int_> &q)
{
    bfs.resize(cidx.size());
    compute_bfs(bfs.data(), cidx, q);
}


template <typename int_ = int>
inline void
reversed_bfs_pi(int_ *bfs, const ChildrenIndex &cidx, int_ *pi)
{
    const size_t n = cidx.size();
    bfs[n - 1] = cidx.root_node();
    pi[n - 1] = int_(n - 1);
    for (size_t p = 1, q = 1; q < n; p++)
        for (auto v : cidx[bfs[n - p]]) {
            ++q;
            bfs[n - q] = int_(v);
            pi[n - q] = int_(n - p);
        }
}


template <typename int_ = int>
inline void
reversed_bfs(int_ *bfs, const ChildrenIndex &cidx)
{
    const size_t n = cidx.size();
    bfs[n - 1] = cidx.root_node();
    for (size_t p = 1, q = 1; q < n; p++)
        for (auto v : cidx[bfs[n - p]])
            bfs[n - ++q] = int_(v);
}


template <typename int_ = int>
inline void
reversed_bfs(std::vector<int_> &bfs, const ChildrenIndex &cidx)
{
    bfs.resize(cidx.size());
    reversed_bfs(bfs.data(), cidx);
}


template <typename int_ = int>
inline std::vector<int_>
reversed_bfs(const std::vector<int_> &parent)
{
    ChildrenIndex cidx (parent);
    std::vector<int_> bfs;
    reversed_bfs(bfs, cidx);
    return bfs;
}


template <typename int_ = int>
void
compute_bfs(std::vector<int_> &bfs, const ChildrenIndex &cidx)
{
    queue<int_> q;
    compute_bfs(bfs, cidx, q);
}


template <typename int_ = int>
inline std::vector<int_>
compute_bfs(const std::vector<int_> &parent, const int_ root)
{
    ChildrenIndex cidx (parent, root);
    queue<int_> q;
    std::vector<int_> bfs;

    compute_bfs(bfs, cidx, q);
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
