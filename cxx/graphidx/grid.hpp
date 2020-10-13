#pragma once
#include <functional>   // std::function
#include <vector>

#include "./idx/biadjacent.hpp"
#include "./idx/incidence.hpp"


/** Call `proc` for all neighbored grid pixels `(i1, j1, i2, j2)` */
template <typename int_ = int>
void
iter_grid_edges_pixel(const int_ n1,
                      const int_ n2,
                      std::function<void(int_, int_, int_, int_)> proc)
{
    constexpr int_ dx = int_(1), dy = int_(0);
    for (int_ i = 0; i < n1 - dx; i++)
        for (int_ j = 0; j < n2 - dy; j++)
            proc(i, j, i+dx, j+dy);
    for (int_ i = dy; i < n1; i++)
        for (int_ j = 0; j < n2 - dx; j++)
            proc(i, j, i-dy, j+dx);
}


/** Call `proc` for all neihbored pixels `(u, v)` */
template <typename int_ = int>
void
iter_grid_edges(const int_ n1,
                const int_ n2,
                std::function<void(int_, int_)> proc)
{
    iter_grid_edges_pixel<int_>(n1, n2,
                                [=](int_ x1, int_ y1, int_ x2, int_ y2) {
                                    proc(x1 + y1*n1, x2 + y2*n1);
                                });
}


struct GridGraph
{
    const size_t n1, n2;

    GridGraph(size_t n1, size_t n2) : n1(n1), n2(n2) { }

    size_t num_nodes() const { return n1 * n2; }

    size_t num_edges() const { return n1 * (n2 - 1) + (n1 - 1) * n2; }

    template <typename int_ = int>
    operator BiAdjacentIndex<int_>() const {
        std::vector<int_> head, tail;
        head.reserve(2*num_nodes());
        tail.reserve(2*num_nodes());
        iter_grid_edges<int_>(int_(n1), int_(n2),
                              [&](int_ u, int_ v) {
                                  head.push_back(u);
                                  tail.push_back(v);
                              });
        return {std::move(head), std::move(tail), num_nodes()};
    }

    template <typename int_ = int>
    operator IncidenceIndex<int_>() const;
};


template <typename int_ = int>
GridGraph::operator IncidenceIndex<int_>() const
{
    const size_t n = num_nodes();
    uvector<std::tuple<int_, int_>> value;

    value.resize(2 * num_edges());
    std::vector<int_> index (n + 1, 0);

                                    // compute degrees
    iter_grid_edges<int_>(int_(n1), int_(n2), [&](int_ u, int_ v) {
        index[size_t(u + 1)]++;
        index[size_t(v + 1)]++;
    });

    {                               // shift, accumulate
        int_ acc = 0,
            deg_i = 0;
        for (size_t i = 0; i < n; i++) {
                index[i] = acc;
                acc += deg_i;
                deg_i = index[i+1];
        }
        index[n] = acc;
    }
    {
        int_ e = 0;   // current edge index
        iter_grid_edges<int_>(int_(n1), int_(n2), [&](int_ u, int_ v) {
            value[size_t(index[size_t(u+1)]++)] = {v, e};
            value[size_t(index[size_t(v+1)]++)] = {u, e};
            e++;
        });
    }

    return {std::move(value), std::move(index)};
}
