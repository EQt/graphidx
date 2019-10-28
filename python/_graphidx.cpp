#include <algorithm>                // for std::sort
#include <pybind11/pybind11.h>
#include "py_np.hpp"

#include "../cxx/utils/compiler.hpp"

namespace py = pybind11;


void reg_timer(py::module &m);
void reg_order(py::module &m);
void reg_idx(py::module &m);
void reg_spanning(py::module &m);


/**
   For testing: create an array with 3 elements
 */
py::array_t<double>
_test_create_array()
{
    double *x = new double[3];
    x[0] = 13.0;
    x[1] = -1.0;
    x[2] = 42.0;
    return py::array_t<double>({3}, {sizeof(double)}, x);
}


PYBIND11_MODULE(_graphidx, m)
{
    m.doc() = R"pbdoc(
        Access the C++ implementation of GraphIdx
        -----------------------------------------

        https://github.com/eqt/treelas

        .. currentmodule:: _graphidx

        .. autosummary::
           :toctree: _generate

    )pbdoc";
    m.attr("__author__") = "Elias Kuthe <elias.kuthe@tu-dortmund.de>";
    m.attr("__compiler__") = compiler_info();

    m.def("_stdcxx_sort", [](py::array_f64 a) -> void {
        std::sort(a.mutable_data(), a.mutable_data()+a.size());
      },
      R"pbdoc(
        std::sort from libstdc++ (to be compared against numpy.sort)
      )pbdoc");

    reg_timer(m);
    reg_order(m);
    reg_idx(m);
    reg_spanning(m);
}
