#pragma once

#include <cstdint>
#include <type_traits>
#include <vector>

#include "../idx/partition.hpp"

/**
 * Union-Find data structure over ints from range 0..n with path compression.
 * See Cormen, Leiserson, Rivest und Stein: "Introduction to Algorithms",
 * Section 21.3, in particular pseudocode on page 571.
 */
template <typename int_ = uint32_t>
class UnionFind
{
    using uint_ = typename std::make_unsigned<int_>::type;
    std::vector<uint_> p;
    std::vector<uint_> rank;

public:
    /** Represantant of a partition */
    struct Rep
    {
        uint_ i;

        bool operator!=(const Rep &other) const { return i != other.i; }
        bool operator==(const Rep &other) const { return i == other.i; }
        bool operator==(const int_ &other) const { return i >= 0 && uint_(i) == other; }
    };

    /** Initialize as n singleton sets. */
    UnionFind(const size_t n);

    /** Find representant for x. */
    UnionFind<int_>::Rep find(int_ x);

    /** Unit the sets with representants fx und fy. */
    void unite(UnionFind<int_>::Rep fx, UnionFind<int_>::Rep fy);

    /** Reset such that every element is separated, again */
    void reset();

    /** Number of elements */
    size_t size() const { return p.size(); }

    /** Represantatives */
    std::vector<int_> mps();

    /** Partitions */
    PartitionIndex<int_> partitions();
};


template <typename int_>
UnionFind<int_>::UnionFind(const size_t n)
    : p(n), rank(n)
{
    reset();
}


template <typename int_>
void
UnionFind<int_>::reset()
{
    const auto n = size();
    for (size_t i = 0; i < n; i++) {
        p[i] = i;
        rank[i] = 0;
    }
}


template <typename int_>
inline void
UnionFind<int_>::unite(UnionFind<int_>::Rep fx, UnionFind<int_>::Rep fy)
{
    if (rank[fx.i] > rank[fy.i])
        p[fy.i] = fx.i;
    else {
        p[fx.i] = fy.i;
        if (rank[fx.i] == rank[fy.i])
            rank[fy.i]++;
    }
}


template <typename int_>
typename UnionFind<int_>::Rep
UnionFind<int_>::find(int_ x)
{
    auto &px = p[(size_t) x];
    if (px != x)
        px = find(px).i;
    return Rep {px};
}


template <typename int_>
std::vector<int_>
UnionFind<int_>::mps()
{
    const auto n = this->size();
    std::vector<int_> reps;
    reps.resize(n);
    for (size_t v = 0; v < n; v++)
        reps[v] = find(v).i;
    return reps;
}


template <typename int_>
PartitionIndex<int_>
UnionFind<int_>::partitions()
{
    auto parts = PartitionIndex<int_> {this->mps()};
    return std::move(parts.unique());
}
