/**
   Utility methods regarding numpy arrays
 */
#pragma once
#include <cstdint>
#include <pybind11/numpy.h>


namespace pybind11 {

typedef array_t<double,  array::c_style | array::forcecast> array_f64;
typedef array_t<int32_t, array::c_style | array::forcecast> array_i32;

} // namespace pybind11::


namespace py = pybind11;

/**
   Create an array by coping the values
*/
template <typename T>
inline py::array_t<T>
create_ndarray(const std::vector<T> &arr)
{
    return py::array_t<T>({arr.size()}, {sizeof(T)}, arr.data());
}

/**
   Check whether the array is empty (i.e. size() == 0)
 */
inline bool
is_empty(const py::array &a)
{
    for (int d = 0; d < a.ndim(); d++) {
        if (a.shape(d) > 0)
            return false;
    }
    return true;
    // return a.size() == 0;
}


/**
   Assert that an array has a certain size.
 */
inline void
check_len(const ssize_t n,
          const py::array &a,
          const std::string &a_str = "?",
          const ssize_t ndim = 1)
{
    if (a.ndim() != ndim) {
        throw std::length_error(std::to_string(a.ndim()) + " = len(" +
                                a_str + ".shape) != " +
                                std::to_string(ndim));
    }
    if (a.size() != n) {
        throw std::length_error(std::to_string(a.shape(0)) +
                                std::string(" = len(") +
                                a_str + ") != " + std::to_string(n));
    }
}


/**
   Be sure that an array is one-dimensional and return its length
 */
inline size_t
check_1d_len(const py::array &a, const std::string &a_str = "?")
{
    if (a.ndim() != 1) {
        throw std::length_error(a_str +
                                " is supposed to be 1-dimensional array");
    }
    return size_t(a.shape(0));
}
