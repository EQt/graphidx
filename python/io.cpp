#include <fstream>
#include <stdexcept>
#include <pybind11/pybind11.h>
#include "py_np.hpp"

#include "../cxx/graphidx/io/magic.hpp"
#include "../cxx/graphidx/io/dimacs10.hpp"
#if __has_include(<bzlib.h>)
#  define HAVE_BZIP2 1
#  include "../cxx/graphidx/io/bz2istream.hpp"
#else
#  define HAVE_BZIP2 0
#endif


void
reg_io(py::module &m)
{
    py::module mo = m.def_submodule("io",
            R"pbdoc(
            Input/Output of graphs in different formats.
            )pbdoc");

    mo.attr("__have_bzip2__") = bool(HAVE_BZIP2);
    mo.def("parse_dimacs10",
          [](const char *fname, const bool is_bz2, const int buf_size) -> BiAdjacentIndex<int>
          {
              if (is_bz2) {
#if HAVE_BZIP2
                  BZ2IStream io (fname, buf_size);
                  return parse_dimacs10_idx(io);
#else
                  throw std::runtime_error(
                      "BZIP2 is not supported. Please install bzip2 (via conda)"
                      );
#endif
              }
              std::ifstream io (fname);
              if (io) {
                  return parse_dimacs10_idx(io);
              }
              throw std::runtime_error(std::string("Could not open ") + fname);
          },
          R"pbdoc(
              Load a DIMACS'10 instance
          )pbdoc",
          py::arg("fname"),
          py::arg("is_bz2") = true,
          py::arg("buf_size") = 8192
        );

    mo.def("parse_dimacs10_edges",
          [](const char *fname, const bool is_bz2, const int buf_size) -> py::tuple
          {
              std::vector<int> head, tail;
              if (is_bz2) {
#if HAVE_BZIP2
                  BZ2IStream io (fname, buf_size);
                  parse_dimacs10_edges(io, head, tail);
                  return py::make_tuple(create_ndarray<int>(head),
                                        create_ndarray<int>(tail));
#else
                  throw std::runtime_error(
                      "BZIP2 is not supported. Please install bzip2 (via conda)"
                      );
#endif
              }
              std::ifstream io (fname);
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
          py::arg("is_bz2") = true,
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
