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
template <typename int_ = int>
struct ChildrenIdx : public Index<int_>
{
    ChildrenIdx() {}

    /** Allocate enough space for a tree with `n` nodes.
     * Before it is usable you need to call `ChildrenIndex::reset`!
     */
    ChildrenIdx(const size_t n) {
        this->index.reserve(n+1);
        this->value.reserve(n);
    }


    ChildrenIdx(const size_t n,
                  const int_ *parent,
                  const int_ root = -1,
                  const bool verbose = false)
        {  reset(n, parent, root, verbose); }


    ChildrenIdx(const std::vector<int_> &parent, const int_ root = -1) :
        ChildrenIdx(parent.size(), parent.data(), root) {}


    /** Update the index values to the tree given by `parent`. */
    void reset(
        const size_t n,
        const int_ *parent,
        int_ root = -1,
        const bool verbose = false);

    /** @return the index of the root node */
    int_ root_node() const { return this->value[0]; }

    void degrees(int_ *deg) const {
        Index<int_>::degrees(deg);
        for (size_t i = 0; i < this->size(); i++)
            deg[i] += 1;
        deg[root_node()] -= 1;
    }
};


template <typename int_>
void
ChildrenIdx<int_>::reset(
    const size_t n,
    const int_ *parent,
    int_ root,
    const bool verbose)
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
        groupby<Timer>(this->value, this->index, n, parent, root);
    else
        groupby<FakeTimer>(this->value, this->index, n, parent, root);
}


using ChildrenIndex = ChildrenIdx<int>;
