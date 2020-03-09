#pragma once
#include <vector>
#include <stdexcept>

#include "groupby.hpp"
#include "index.hpp"
#include "../tree/root.hpp"


/**
   Access the children of each node of the tree.

   By convention, the root node is stored at `ChildrenIndex::value[0]`;
   it can be accessed via `ChildrenIndex::root_node()`.
*/
struct ChildrenIndex : public AdjacencyIndex<int>
{
    ChildrenIndex() {}

    /** Allocate enough space for a tree with `n` nodes.
     * Before it is usable you need to call `ChildrenIndex::reset`!
     */
    ChildrenIndex(const size_t n) {
        index.reserve(n+1);
        value.reserve(n);
    }


    ChildrenIndex(const size_t n,
                  const int *parent,
                  const int root = -1,
                  const bool verbose = false)
        {  reset(n, parent, root, verbose); }


    ChildrenIndex(const std::vector<int> &parent, const int root = -1) :
        ChildrenIndex(parent.size(), parent.data(), root) {}


    /** Update the index values to the tree given by `parent`. */
    void reset(
        const size_t n,
        const int *parent,
        int root = -1,
        const bool verbose = false)
    {
        if (root < 0) {
            if (verbose) {
                Timer _ ("find root");
                root = find_root(n, parent);
            } else
                root = find_root(n, parent);
        }

        if (root < 0 || parent[root] != root)
            throw std::invalid_argument(std::string("\n" __FILE__) + ":" +
                                        std::to_string(__LINE__) +
                                        ":\n  root = " + std::to_string(root) +
                                        " != " + std::to_string(parent[root]) +
                                        " = parent[root];  n = " +
                                        std::to_string(n));
        if (verbose)
            groupby<Timer>(value, index, n, parent, root);
        else
            groupby<FakeTimer>(value, index, n, parent, root);
    }


    /** @return the index of the root node */
    int root_node() const { return this->value[0]; }

    void degrees(int *deg) const {
        AdjacencyIndex<int>::degrees(deg);
        for (size_t i = 0; i < size(); i++)
            deg[i] += 1;
        deg[root_node()] -= 1;
    }
};
