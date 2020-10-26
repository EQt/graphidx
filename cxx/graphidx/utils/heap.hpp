#pragma once

#if __has_include(<ext/pb_ds/priority_queue.hpp>)
#  include <ext/pb_ds/priority_queue.hpp>


template <typename int_t = int, typename float_t = double>
struct pq_element
{
    int_t id;
    float_t dist;

#if 0
    inline pq_element swap(pq_element other) {
        return *this = other;
    }
#endif
};


template <typename int_t = int, typename float_t = double>
inline bool
operator<(const pq_element<int_t, float_t> &a, const pq_element<int_t, float_t> &b) {
    return a.dist > b.dist;
}


template <typename tag_t = __gnu_pbds::pairing_heap_tag,
          typename int_t = int,
          typename float_t = double>
using priority_queue = __gnu_pbds::priority_queue<
    pq_element<int_t, float_t>,
    std::less<pq_element<int_t, float_t>>,
    tag_t
>;

#else
#  error "need GNU ext/pb_ds"
#endif
