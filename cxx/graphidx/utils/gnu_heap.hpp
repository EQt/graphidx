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


template <typename tag_t = __gnu_pbds::pairing_heap_tag,
          typename int_t = int,
          typename priority_t = double,
          typename queue_t = priority_queue<tag_t, int_t, priority_t>>
class heap_t : public priority_queue<tag_t, int_t, priority_t>
{
    static_assert(std::is_integral<int_t>::value, "need integers");
    static_assert(std::is_signed<int_t>::value, "need the sign bit");

    using base_t = priority_queue<tag_t, int_t, priority_t>;

    std::vector<typename base_t::point_iterator> pnode;

public:
    explicit heap_t(size_t n) : pnode(n, nullptr) {
        if (this->max_size() < n)
            throw std::runtime_error(std::string("max_size() = ") +
                                     std::to_string(this->max_size()) + ", n = " +
                                     std::to_string(n));
    }

    inline typename base_t::point_iterator push(typename base_t::const_reference r_val) {
        return pnode[(size_t) r_val.id] = base_t::push(r_val);
    }

    inline bool contains(size_t v) const { return pnode[v] != nullptr; }
    inline bool contains(int_t v) const { return contains((size_t) v); }

    inline priority_t operator[](size_t v) const { return pnode[v]->dist; }
    inline priority_t operator[](int_t v) const { return (*this)[(size_t) v]; }

    inline void decrease(int_t v, priority_t prio) {
        base_t::modify(pnode[(size_t) v], {v, prio});
    }

    inline int_t top() const {
        return base_t::top().id;
    }
};


#else
#  error "need GNU ext/pb_ds"
#endif
