#pragma once
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <set>

#include "../std/uvector.hpp"
#include "../utils/viostream.hpp"   // for printer


template<typename int_ = int>
struct IndexIter
{
    const int_ *start;
    const int_ *stop;

    IndexIter(const int_ *start, const int_ *stop) :
        start(start), stop(stop) { }

    const int_* begin() const { return start; }

    const int_* end() const { return stop; }

    size_t size() const { return stop - start; }

    operator std::set<int_>() const {
        return std::set<int_>(this->begin(), this->end());
    }

    operator std::vector<int_>() const {
        return std::vector<int_>(this->begin(), this->end());
    }

    bool operator==(const std::set<int_> &o) const {
        return std::set<int_>(*this) == o;
    }

    std::vector<int_> sorted() const {
        std::vector<int_> v(*this);
        std::sort(v.begin(), v.end());
        return v;
    }
};


namespace std {
    template<typename int_ = int>
    bool operator==(const std::set<int_> &a, const IndexIter<int_> &b) {
        return b == a;
    }
}


template<typename int_ = int>
inline std::ostream&
operator<<(std::ostream &o, const IndexIter<int_> &it)
{
    return o << printer(it);
}


template<typename int_ = int>
struct AdjacencyIndex
{
    uvector<int_> value;
    std::vector<int_> index;

    inline IndexIter<int_> operator[](size_t i) const {
        if (i >= index.size())
            return {nullptr, nullptr};
        const int_
            *start = value.data() + index[i+0],
            *stop  = value.data() + index[i+1];
        return {start, stop};
    }

    inline IndexIter<int_> operator[](int i) const {
        if (i < 0)
            return {nullptr, nullptr};
        return (*this)[size_t(i)];
    }

    inline IndexIter<int_> operator[](int64_t i) const {
        if (i < 0)
            return {nullptr, nullptr};
        return (*this)[size_t(i)];
    }

    size_t size() const { return index.size() -1; }

    void degrees(int_ *deg) const {
        for (size_t i = 0; i < size(); i++)
            deg[i] = index[i+1] - index[i];
    }
};
