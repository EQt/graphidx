#include <pybind11/pybind11.h>

#include "../cxx/utils/timer.hpp"
#include "../cxx/utils/perftimer.hpp"

namespace py = pybind11;


void
reg_timer(py::module &m)
{
    py::module mt = m.def_submodule("timer",
            R"pbdoc(
            Access the C++ timer functionality, e.g. `Timer` and `TimerQuiet`.
            )pbdoc");

    py::class_<TimerQuiet>(mt, "TimerQuiet", py::module_local())
        .def(py::init([](const bool verbose)
             {
                 return TimerQuiet(verbose);
             }),
            py::arg("verbose") = false
            )
        .def("__enter__", &TimerQuiet::enter)
        .def("__exit__", [](TimerQuiet &self_, py::args) { self_.exit(); })
        ;

    py::class_<Timer>(mt, "Timer", py::module_local())
        .def(py::init([]() -> Timer { return Timer(); }))
        .def("__float__",
             [](const Timer &self) -> double {
                 return double(self);
             })
        ;

    py::class_<PerfTimer>(mt, "PerfTimer", py::module_local())
        .def(py::init([]() -> PerfTimer { return PerfTimer(); }))
        .def("__float__",
             [](const PerfTimer &self) -> double {
                 return double(self);
             })
        ;
}
