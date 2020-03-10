#pragma once
#include <algorithm>        // std::max_element
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <vector>

#include "../utils/timer.hpp"


template <typename Timer = FakeTimer, typename int_ = int, typename sint_ = int>
void
groupby(int_ *value,
        const size_t n,
        int_ *index,
        const size_t k,
        const int_ *parent,
        const sint_ root = sint_(-1))
{
    static_assert(std::is_signed<sint_>::value, "root node must be signed");
    Timer::log(" int%d: %s (%s)\n",
               8*sizeof(int_), typeid(int_).name(), typeid(sint_).name());
#ifdef __GNUC__
    Timer::log(" &_return_addr = %p\n", __builtin_return_address(0));
#endif
    void (*gb)(int*, const size_t, int*, const size_t, const int*, const int) = groupby;
    Timer::log(" &groupby = %p\n", gb);
    Timer::log(" n = %ld\n", n);
    Timer::log(" k = %ld\n", k);
    Timer::log(" root = %ld\n", root);
    Timer::log(" index  = %p\n", index);
    Timer::log(" value  = %p\n", value);
    Timer::log(" parent = %p\n", parent);
    {   Timer _ ("count parents");
        for (size_t i = 0; i < n; i++)
            index[parent[i]]++;
    }

    if (root >= 0) {
        index[root]--;              // root isn't child of itself
        value[0] = int_(root);
    }

    {   Timer _ ("prefix sums");    // accumulate prefix sums
        int_ acc = root >= 0 ? 1 : 0,
             deg_i = 0,
             deg_ii = index[0];
        for (size_t i = 0; i < k; i++) {
            index[i] = acc;
            acc += deg_i;
            deg_i = deg_ii;
            deg_ii = index[i+1];
        }
        index[k] = acc;
    }

    {   Timer _ ("values");          // sort the values
        for (size_t v = 0; v < n; v++) {
            const auto p = parent[v];
            if (root >= 0 && v == size_t(root)) continue;      // skip root
            value[index[p+1]++] = int_(v);
        }
    }

    if (index[k] != int_(n)) {
        throw std::runtime_error(std::string("\n") +
                                 __FILE__ + ":" + std::to_string(__LINE__) +
                                 ": Severe Bug:\n  index[k] = " +
                                 std::to_string(index[k]) + " != " +
                                 std::to_string(n) + " = n   "
            );
    }

}


/** Group the elements in `parent`, stored in `value`, group index `index`.

    If `root >= 0` treat it as the root of the tree given by `parent`.
    The `root` node if `>= 0` will be stored at `index[0]`.

    Algorithm: [Counting Sort][c] (linear runtime)

    [c]: https://en.wikipedia.org/wiki/Counting_sort
*/
template <typename Timer = FakeTimer,
          typename int_ = int,
          typename vector_t = std::vector<int_>,
          typename sint_ = int>
inline void
groupby(vector_t &value,
        std::vector<int_> &index,
        const size_t n,
        const int_ *parent,
        const sint_ root = sint_(-1))
{
    static_assert(std::is_signed<sint_>::value, "root node must be signed");
    Timer _ ("groupby\n");
    value.resize(n);
    size_t k = n;
    if (root < 0) {
        Timer _ ("max_element");
        k = size_t(*std::max_element(parent, parent + n) + 1);
    }

    {   Timer _ ("assign = 0");
        index.assign(k+1, 0);        // compute histogram, i.e. number of children
    }

    groupby<Timer>(value.data(), n, index.data(), k, parent, root);
}
