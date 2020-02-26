#pragma once

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
