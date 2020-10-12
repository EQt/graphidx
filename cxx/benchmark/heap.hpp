#pragma once

#include <ext/pb_ds/priority_queue.hpp>


template <typename int_t = int, typename float_t = double>
struct pq_element
{
    int_t id;
    float_t dist;
};


template <typename int_t = int, typename float_t = double>
inline bool
operator<(const pq_element<int_t, float_t> &a, const pq_element<int_t, float_t> &b) {
    return a.dist > b.dist;
}