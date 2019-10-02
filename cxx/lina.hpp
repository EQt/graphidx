/**
   Some linear algebra helpers
*/
#pragma once
#include <cmath>        // std::abs
#include <algorithm>    // std::max
#include <limits>       // numeric_limits<...>::infinity
#include <type_traits>  // std::is_arithmetic


template <typename F = double>
inline F
l1_diff(const size_t n, const F *x, const F *y)
{
    static_assert(std::is_arithmetic<F>::value,
                  "Need integral or floating point type");
    F l1 = -std::numeric_limits<F>::infinity();
    for (size_t i = 0; i < n; i++)
        l1 = std::max(std::abs(x[i] - y[i]), l1);
    return l1;
}
