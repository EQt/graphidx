/*
  Utility functions around Depth First Search (DFS)
*/
#pragma once
#include <vector>
#include <stdexcept>

#include "root.hpp"
#include "../std/stack.hpp"
#include "../idx/children.hpp"
#include "../utils/timer.hpp"


template <typename int_ = int>
void
dfs_discover(std::vector<int_> &dfs, const ChildrenIndex &cidx, stack<int_> &s)
{
    s.reserve(cidx.size());
    dfs.reserve(cidx.size());

    s.push_back(cidx.root_node());
    while (!s.empty()) {
        auto u = s.back(); s.pop_back();
        dfs.push_back(u);
        for (auto v : cidx[u])
            s.push_back(v);
    }
}


template <typename int_ = int>
inline std::vector<int>
dfs_discover(const std::vector<int_> &parent, const int_ root = int_(-1))
{
    if (root < 0)
        return dfs_discover(parent, find_root(parent));
    ChildrenIndex cidx (parent, root);
    stack<int_> s;
    std::vector<int_> dfs;
    dfs_discover(dfs, cidx, s);
    return dfs;
}
