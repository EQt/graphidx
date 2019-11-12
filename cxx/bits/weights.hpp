#pragma once
#include <cstddef>      // for size_t


/** Provide a uniform weighting of one */
template <typename T = double>
struct Ones
{
    constexpr T operator[](size_t) const { return T(1); }
};


template <typename T = double>
struct Const
{
    const T c;

    Const(const T &c) : c(c) { }

    T operator[](size_t) const { return c; }
};


template <typename T = double>
struct Array
{
    const T *a;

    Array(const T *a) : a(a) { }

    T operator[](size_t i) const { return a[i]; }
};


template <typename T, typename S>
T
create_weight(S);


template <typename T>
Ones<T>
create_weight()
{
    return Ones<T>();
}


template <typename T>
Const<T>
create_weight(T c)
{
    return Const<T>(c);
}


template <typename T>
Array<T>
create_weight(const T *a)
{
    return Array<T>(a);
}
