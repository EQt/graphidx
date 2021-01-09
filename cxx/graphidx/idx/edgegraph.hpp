#pragma once
#include <vector>


struct EdgeGraph
{
    const size_t n;
    std::vector<int> head;
    std::vector<int> tail;

    inline size_t num_nodes() const {
        return n;
    }

    inline size_t num_edges() const {
        return head.size();
    }
};
