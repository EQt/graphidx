#include <fstream>
#include <stdexcept>
#include <pybind11/pybind11.h>
#include "py_np.hpp"

#include "../cxx/graphidx/io/dimacs10.hpp"
#include "../cxx/graphidx/io/bz2istream.hpp"


void
reg_io(py::module &m)
{
    m.def("parse_dimacs10",
          [](const char *fname) -> BiAdjacentIndex<int>
          {
              const int buf_size = 8192;
              const bool is_bz2 = true;
              if (is_bz2) {
                  BZ2IStream io (fname, buf_size);
                  return parse_dimacs10_idx(io);
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
          py::arg("fname")
        );
}
