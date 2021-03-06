#include <pybind11/pybind11.h>
#include "py_np.hpp"

#include "../cxx/graphidx/idx/biadjacent.hpp"
#include "../cxx/graphidx/spanning/rand_prim_mst.hpp"


void
reg_spanning(py::module &m)
{
    m.def("random_spanning_tree",
          [](const BiAdjacent &index,
             const size_t seed,
             py::array_i32 &parent) -> py::array_i32
          {
              const size_t n = index.num_nodes();
              if (is_empty(parent))
                  parent = py::array_i32({n}, {sizeof(int32_t)});
              check_len(n, parent, "parent");
              random_spanning_tree(index, seed, parent.mutable_data());
              return parent;
          },
          R"pbdoc(
              Compute a random spanning tree (similar to Prim's algorithm)
          )pbdoc",
          py::arg("index"),
          py::arg("seed") = 2018,
          py::arg("parent") = py::array_i32());
}
