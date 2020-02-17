#include <pybind11/pybind11.h>

#include "../cxx/graphidx/utils/timer.hpp"
#include "../cxx/graphidx/utils/perftimer.hpp"

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

    py::class_<Seconds>(mt, "Seconds", py::module_local(),
            "Represent a time intervall in seconds."
        )
        .def(py::init([]() { return Seconds(); }))
        .def("__float__", [](const Seconds d) { return d.d; })
        .def_readwrite("value", &Seconds::d)
        ;

    m.def("_pass_double_pointer",
          [](Seconds *ptr) -> bool
          {
              if (ptr) {
                  ptr->d = 123.4;
                  return true;
              }
              return false;
          },
          "For tessting purposes only!: Receive a double pointer",
          py::arg("ptr") = nullptr)
        ;
}
