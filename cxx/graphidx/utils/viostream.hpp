/**
   Input/output in the style of `iostream` / `cstdio` on containers.
   As long as a container `C` has support of `std::begin(&C)` and `std::end(&C)`
   the functions `std::cout << printer(c)` and `std::to_string(printer(c))`
   should produce a sensible list format.
*/
#pragma once
#include <cstdio>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

#include "../std/uvector.hpp"


template <typename B, typename E>
inline std::ostream&
_print_list(std::ostream &o, const B &begin, const E &end)
{
    bool first = true;
    o << "[";
    for (auto it = begin; it != end; it++) {
        auto x = *it;
        if (first) {
            first = false;
        } else
            o << ", ";
        o << x;
    }
    return o << "]";
}


template <typename T>
struct _Vec
{
    const T *start;
    const size_t n;
    const T* begin() const { return start; }
    const T* end() const   { return start + n; }
};


template <typename T>
inline _Vec<T>
Vec(const T* start, size_t n)
{
    return _Vec<T> {start, n};
}


template<typename Container>
inline void
print_int_list(
    const Container &x,
    const char *sep = " ",
    FILE *out = stdout,
    const char * fmt = "%ld")
{
    fprintf(out, "[");
    bool first = true;
    for (auto xi : x) {
        if (first) { first = false; }
        else { fprintf(out, "%s", sep); }
        fprintf(out, fmt, (long int)xi);
    }
    fprintf(out, "]\n");
}


template<typename Container>
inline void
print_double_list(
    const Container &x,
    const int prec = 4,
    FILE *out = stdout,
    const char * fmt = "%.*f")
{
    fprintf(out, "[");
    bool first = true;
    for (double xi : x) {
        if (first) { first = false; }
        else { fprintf(out, ", "); }
        fprintf(out, fmt, prec, xi);
    }
    fprintf(out, "]\n");
}


template <typename T>
struct _Printer
{
    T &c;
    _Printer(T &c) : c(c) { }
};


template <typename T>
_Printer<T>
printer(T &c)
{
    return _Printer<T>(c);
}


namespace std {

template <typename E>
inline ostream&
operator<<(ostream &o, const _Printer<E> &v)
{
    return ::_print_list(o, begin(v.c), end(v.c));
}


template <typename E>
inline ostream&
operator<<(ostream &o, const std::vector<E> &v)
{
    return o << ::printer(v);
}


template <typename E>
inline ostream&
operator<<(ostream &o, const uvector<E> &v)
{
    return o << ::printer(v);
}


template<typename E>
std::string
to_string(const std::vector<E> &v) {
    ostringstream s;
    s << v;
    return s.str();
}


template<typename E>
std::string
to_string(const uvector<E> &v) {
    ostringstream s;
    s << v;
    return s.str();
}


template<typename E>
std::string
to_string(const _Printer<E> &v) {
    ostringstream s;
    s << v;
    return s.str();
}


}   // namespace std::
