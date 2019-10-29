#include <pybind11/pybind11.h>

#include "../cxx/utils/timer.hpp"

namespace py = pybind11;


void
reg_timer(py::module &m)
{
    py::class_<TimerQuiet>(m, "TimerQuiet", py::module_local())
        .def(py::init([](const bool verbose)
             {
                 return TimerQuiet(verbose);
             }),
            py::arg("verbose") = false
            )
        .def("__enter__", &TimerQuiet::enter)
        .def("__exit__", [](TimerQuiet &self_, py::args) { self_.exit(); })
        ;
}
