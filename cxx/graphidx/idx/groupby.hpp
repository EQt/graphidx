#pragma once
#include <vector>
#include <stdexcept>
#include <algorithm>        // std::max_element
#include <string>

#include "../utils/timer.hpp"


/** Group the elements in `parent`, stored in `value`, group index `index`.

    If `root >= 0` treat it as the root of the tree given by `parent`.
    The `root` node if `>= 0` will be stored at `index[0]`.

    Algorithm: [Counting Sort][c] (linear runtime)

    [c]: https://en.wikipedia.org/wiki/Counting_sort
*/
template <typename int_ = int, typename vector_t = std::vector<int_>>
inline void 
groupby(vector_t &value,
        std::vector<int_> &index,
        const size_t n,
        const int_ *parent,
        const int_ root = -1)
{
    Timer _ ("\ngroupby\n");
    value.resize(n);
    size_t k = n;
    if (root < 0) {
        Timer _ ("max_element");
        k = size_t(*std::max_element(parent, parent + n) + 1);
    }

    {   Timer _ ("assign = 0");
        index.assign(k+1, 0);        // compute histogram, i.e. number of children
    }
    {   Timer _ ("count parents");
        for (size_t i = 0; i < n; i++)
            index[parent[i]]++;
    }

    if (root >= 0) {
        index[root]--;              // root isn't child of itself
        value[0] = root;
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
        for (int_ v = 0; v < int_(n); v++) {
            const auto p = parent[v];
            if (v == root) continue;      // skip root
            value[index[p+1]++] = v;
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
