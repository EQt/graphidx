/**
 * Utility functions concerning permutations
 */
#pragma once
#include <vector>
#include <algorithm>        // for std::sort
#include "../std/uvector.hpp"


/** Concatenate two permutations */
template<typename int_ = int>
inline std::vector<int_>
concat(const std::vector<int_> &a, const std::vector<int_> &idx)
{
    static_assert(std::is_integral<int_>::value, "expected int type");
    const size_t n = idx.size();
    std::vector<int_> r (n);
    for (size_t i = 0; i < n; i++) {
        r[i] = a[idx[i]];
    }
    return r;
}


/** Set q to be the inverse permutation of p*/
template<typename int_ = int>
inline void
invperm(const size_t n, int_ *q, const int_ *p)
{
    for (int i = 0; i < int(n); i++) {
        q[p[i]] = i;
    }
}


template<typename int_ = int>
inline void
invperm(std::vector<int_> &q, const std::vector<int_> &p)
{
    invperm(q.size(), q.data(), p.data());
}


/** Return inverse permutation `invp`, it is `invp[p[i]] == i` */
template<typename int_ = int>
inline std::vector<int_>
invperm(const std::vector<int_> &p)
{
    static_assert(std::is_integral<int_>::value, "expected int type");

    const auto n = p.size();
    std::vector<int_> q (n);
    invperm(n, q.data(), p.data());
    return q;
}


template<typename int_ = int>
inline void
reverse(const size_t n, int_ *r, const int_ *a)
{
    for (size_t i = 0; i < n; i++) {
        r[i] = a[n-i-1];
    }
}


/** Reverse a vector, i.e. reverse({1,2,3}) == {3,2,1} */
template<typename int_ = int>
inline std::vector<int_>
reverse(const std::vector<int_> &a)
{
    static_assert(std::is_integral<int_>::value, "expected int type");
    const size_t n = a.size();
    std::vector<int_> r (n);
    reverse(n, r.data(), a.data());
    return r;
}



/** Return permutation of indexes that make `a` sorted.
 * In other words, the rank of the elements of a are computed.
 */
inline std::vector<int>
argsort(const std::vector<int> &a)
{
    const auto n = a.size();
    std::vector<int> order (n);
    for (unsigned i = 0; i < n; i++)
        order[i] = i;
    std::sort(order.begin(), order.end(),
              [&](int i, int j) {
                  return a[i] < a[j] || (a[i] == a[j] && i < j);
              });
    return order;
}


template <typename Iter>
inline bool
is_perm(const Iter &begin, const Iter &end)
{
    const size_t n = size_t(end - begin);
    std::vector<bool> b (n, false);
    for (auto i = begin; i != end; i++) {
        const auto j = *i;
        if (j < 0 || j >= decltype(j)(n) || b[j])
            return false;
        b[j] = true;
    }
    return true;
}



/** Check that a is a permutation */
template <typename int_ = int>
inline bool
is_perm(const std::vector<int_> &a)
{
    static_assert(std::is_integral<int_>::value, "expected int type");
    return is_perm(a.begin(), a.end());
}


/** Check that a is a permutation */
template <typename int_ = int>
inline bool
is_perm(const uvector<int_> &a)
{
    static_assert(std::is_integral<int_>::value, "expected int type");
    return is_perm(a.begin(), a.end());
}
