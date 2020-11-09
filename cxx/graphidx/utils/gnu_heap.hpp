#pragma once

#if __has_include(<ext/pb_ds/priority_queue.hpp>)
#  define HAVE_GNUX 1
#  include <ext/pb_ds/priority_queue.hpp>
#  include "heap.hpp"


template <typename int_t = int, typename float_t = double>
struct PqElement
{
    int_t id;
    float_t dist;

#if 0
    inline PqElement swap(PqElement other) {
        return *this = other;
    }
#endif
};


template <typename int_t = int, typename float_t = double>
inline bool
operator<(const PqElement<int_t, float_t> &a, const PqElement<int_t, float_t> &b) {
    return a.dist > b.dist;
}


template <typename Tag = __gnu_pbds::pairing_heap_tag,
          typename int_t = int,
          typename float_t = double>
using PriorityQueue = __gnu_pbds::priority_queue<
    PqElement<int_t, float_t>,
    std::less<PqElement<int_t, float_t>>,
    Tag
>;


template <typename Tag = __gnu_pbds::pairing_heap_tag,
          typename int_t = int,
          typename priority_t = double>
class heap_t : public PriorityQueue<Tag, int_t, priority_t>
{
    static_assert(std::is_integral<int_t>::value, "need integers");
    static_assert(std::is_signed<int_t>::value, "need the sign bit");

    using Base = PriorityQueue<Tag, int_t, priority_t>;

    std::vector<typename Base::point_iterator> pnode;

public:
    explicit heap_t(size_t n) : pnode(n, nullptr) {
        if (this->max_size() < n)
            throw std::runtime_error(std::string("max_size() = ") +
                                     std::to_string(this->max_size()) + ", n = " +
                                     std::to_string(n));
    }

    inline typename Base::point_iterator push(typename Base::const_reference r_val) {
        return pnode[(size_t) r_val.id] = Base::push(r_val);
    }

    inline bool contains(size_t v) const { return pnode[v] != nullptr; }
    inline bool contains(int_t v) const { return contains((size_t) v); }

    inline priority_t operator[](size_t v) const { return pnode[v]->dist; }
    inline priority_t operator[](int_t v) const { return (*this)[(size_t) v]; }

    inline void decrease(int_t v, priority_t prio) {
        Base::modify(pnode[(size_t) v], {v, prio});
    }

    inline int_t top() const {
        return Base::top().id;
    }
};


namespace gnux {

using ::__gnu_pbds::pairing_heap_tag;
using ::__gnu_pbds::thin_heap_tag;

struct PairHeapT : public ::HeapT { };

template <typename Item, typename Prio>
struct HeapTypedef<PairHeapT, Item, Prio>
{
    using impl = typename ::heap_t<pairing_heap_tag, Item, Prio>;
};


struct ThinHeapT : public ::HeapT { };

template <typename Item, typename Prio>
struct HeapTypedef<ThinHeapT, Item, Prio>
{
    using impl = typename ::heap_t<thin_heap_tag, Item, Prio>;
};


struct BinomialHeapT : public ::HeapT { };

template <typename Item, typename Prio>
struct HeapTypedef<BinomialHeapT, Item, Prio>
{
    using impl = typename ::heap_t<__gnu_pbds::binomial_heap_tag, Item, Prio>;
};


struct RcBinomHeapT : public ::HeapT { };

template <typename Item, typename Prio>
struct HeapTypedef<RcBinomHeapT, Item, Prio>
{
    using impl = typename ::heap_t<__gnu_pbds::rc_binomial_heap_tag, Item, Prio>;
};


} // namespace gnux



#else
#  undef HAVE_GNUX
#endif
