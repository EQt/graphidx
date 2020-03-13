#include <fstream>
#include <stdexcept>
#include <pybind11/pybind11.h>
#include "py_np.hpp"

#include "../cxx/graphidx/io/dimacs10.hpp"
#include "../cxx/graphidx/io/autoistream.hpp"


void
reg_io(py::module &m)
{
    py::module mo = m.def_submodule("io",
            R"pbdoc(
            Input/Output of graphs in different formats.
            )pbdoc");

    mo.attr("__have_bzip2__") = bool(HAVE_BZIP2);
    mo.attr("__have_gzip__") = bool(HAVE_GZIP);
    mo.def("parse_dimacs10",
          [](const char *fname, const size_t buf_size)
             -> BiAdjacentIndex<int>
          {
              AutoIStream io (fname, buf_size);
              if (io)
                  return parse_dimacs10_idx(io);
              throw std::runtime_error(std::string("Could not open ") + fname);
          },
          R"pbdoc(
              Load a DIMACS'10 instance
          )pbdoc",
          py::arg("fname"),
          py::arg("buf_size") = 8192
        );

    mo.def("parse_dimacs10_edges",
          [](const char *fname, const size_t buf_size) -> py::tuple
          {
              std::vector<int> head, tail;
              AutoIStream io (fname, buf_size);
              if (io) {
                  parse_dimacs10_edges(io, head, tail);
                  return py::make_tuple(create_ndarray<int>(head),
                                        create_ndarray<int>(tail));
              }
              throw std::runtime_error(std::string("Could not open ") + fname);
          },
          R"pbdoc(
              Load a DIMACS'10 instance as arrays (head, tail)
          )pbdoc",
          py::arg("fname"),
          py::arg("buf_size") = 8192
        );

    mo.def("is_bzip2", &is_bzip2,
          R"pbdoc(
              Test whether a f file is BZIP2 compressed
          )pbdoc",
           py::arg("fname")
        );
    mo.def("is_gzip", &is_gzip,
          R"pbdoc(
              Test whether a f file is GZIP compressed
          )pbdoc",
           py::arg("fname")
        );
}
