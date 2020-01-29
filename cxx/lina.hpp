/**
   Some linear algebra helpers
*/
#pragma once
#include <cmath>        // std::abs
#include <algorithm>    // std::max
#include <limits>       // numeric_limits<...>::infinity
#include <type_traits>  // std::is_arithmetic
#include <vector>


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


template <typename F = double>
inline F
max_abs_diff(const size_t n, const F *x, const F *y)
{
    static_assert(std::is_arithmetic<F>::value,
                  "Need integral or floating point type");

    F max_diff = F(0.0);
    for (size_t i = 0; i < n; i++)
        max_diff = std::max(max_diff, std::abs(x[i] - y[i]));
    return max_diff;
}


template <typename F = double>
inline F
max_abs_diff(const std::vector<F> &x, const std::vector<F> &y)
{
    if (x.size() != y.size())
        throw std::invalid_argument("max_abs_diff: not same size");
    return max_abs_diff(x.size(), x.data(), y.data());
}
    
