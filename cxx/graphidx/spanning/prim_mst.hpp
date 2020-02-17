#pragma once
#include <random>
#include <stdexcept>

#include "../std/stack.hpp"


void
random_spanning_tree(const BiAdjacent &index,
                     const int seed,
                     int *parent,
                     const int magic = 3)
{
    const auto n = index.num_nodes();
    std::mt19937_64 rng (seed);
    stack<int> stack (n);

    for (size_t i = 0; i < n; i++)
        parent[i] = -1;

    int root = int(rng() % n);
    parent[root] = -root -2;
    stack.push_back(root);
    size_t num_nodes = 0;
    while (!stack.empty()) {
        const int v = stack.pop_back();
        parent[v] = -parent[v] - 2;
        num_nodes++;
        for (const int u : index[v]) {
            if (u == v || parent[u] >= 0)
                continue;
            if (parent[u] == -1) {
                stack.push_back(u);
                parent[u] = -v -2;
            } else if (rng() % magic) {
                parent[u] = -v -2;
            }
            if (stack.size() > 0)
                stack.swap(rng() % stack.size(), stack.size()-1);
        }
    }
    if (num_nodes != n)
        throw std::runtime_error(
            std::string("random_spanning_tree(..): ") +
            "Graph is not connected: " +
            "Found " + std::to_string(num_nodes) +
            " expected " + std::to_string(n));
}


std::vector<int>
random_spanning_tree(const BiAdjacent &index,
                     const int seed = 2018)
{
    std::vector<int> parent (index.num_nodes());
    random_spanning_tree(index, seed, parent.data());
    return parent;
}
