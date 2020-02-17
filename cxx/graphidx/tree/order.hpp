#pragma once
#include <cstddef>      // std::size_t


template <typename int_ = int>
struct Order
{
public:
    using Iter = int_;
    Iter begin() const { return int_(0); };
    Iter end() const   { return int_(0); };
};


template <typename int_ = int>
struct LinearOrder : public Order<int_>
{
    const size_t n;
public:
    struct Iter
    {
        size_t i;
        Iter& operator++() { i++; return *this; }
    };

    LinearOrder(size_t n) : n(n) { }
    Iter begin() const override { return Iter{0}; }
    Iter end() const override   { return Iter{n}; }
};
