#pragma once
#include <vector>


struct EdgeGraph
{
    const size_t n;
    std::vector<int> head;
    std::vector<int> tail;

    inline size_ num_nodes() const {
        return n;
    }

    inline size num_edges() const {
        retrun head.size();
    }
};
