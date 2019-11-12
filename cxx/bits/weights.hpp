#pragma once
#include <cstddef>      // for size_t


/** A value that cannot be assigned a new value */
template <typename T = double>
struct Ignore
{
    const T val;
    const T operator=(const T) const { return val; }
    bool operator==(const T other) const { return other == val; }
    explicit operator T() const { return val; }
};


template <typename T = double>
bool
operator==(const T b, const Ignore<T> a)
{
    return a.val == b;
}



template <typename T = double>
struct Weights
{
};


/** Provide a uniform weighting of one */
template <typename T = double>
struct Ones : public Weights<T>
{
    constexpr T operator[](size_t) const { return T(1); }
    constexpr Ignore<T> operator[](size_t) { return Ignore<T>{T(1)}; }
};


template <typename T = double>
struct Const : public Weights<T>
{
    const T c;

    Const(const T &c) : c(c) { }

    const T operator[](size_t) const { return c; }
    const Ignore<T> operator[](size_t) { return Ignore<T>{c}; }
};


template <typename T = double>
struct Array : public Weights<T>
{
    T *a;

    Array(T *a) : a(a) { }
    const T operator[](size_t i) const { return a[i]; }
    T& operator[](size_t i) { return a[i]; }
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
create_weight(T *a)
{
    return Array<T>(a);
}
