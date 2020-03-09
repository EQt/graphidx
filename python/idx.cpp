#include <string>
#include <stdexcept>
#include <pybind11/pybind11.h>
#include "py_np.hpp"

#include "../cxx/graphidx/idx/biadjacent.hpp"
#include "../cxx/graphidx/idx/cluster.hpp"
#include "../cxx/graphidx/idx/children.hpp"
#include "../cxx/graphidx/idx/partition.hpp"
#include "../cxx/graphidx/tree/root.hpp"
#include "../cxx/graphidx/grid.hpp"

namespace py = pybind11;


void
reg_idx(py::module &m)
{
    using IndexIter_int = IndexIter<int>;
    using AdjacencyIndex_int = AdjacencyIndex<int>;
    using PartitionIndex_int = PartitionIndex<int>;

    py::class_<AdjacencyIndex_int> PyAdjacencyIndex_int (m, "AdjacencyIndex_int",
                                                         py::module_local());
    PyAdjacencyIndex_int
        .def("__getitem__",
             [](const AdjacencyIndex_int &b, const int i) -> IndexIter_int
             {
                 return b[i];
             })
        .def("__len__",
             [](const AdjacencyIndex_int &self) -> size_t
             {
                 return self.size();
             })
        .def("degrees",
             [](const AdjacencyIndex_int &b, py::array_i32 &d) -> py::array_t<int>
             {
                 const auto n = b.size();
                 if (is_empty(d))
                     d = py::array_t<int32_t>({n}, {sizeof(int32_t)});
                 check_len(n, d, "d");
                 b.degrees(d.mutable_data());
                 return d;
             },
             R"pbdoc(
                The number of neighbors in each node
             )pbdoc",
             py::arg("d") = py::array_i32()
            )
        .def("__ptr__",
             [](const AdjacencyIndex_int &self, const bool verbose) -> py::tuple
             {
                 if (verbose) {
                     printf(" idx = %p\n", (void*) self.index.data());
                     printf(" val = %p\n", (void*) self.value.data());
                 }
                 return py::make_tuple(size_t(self.index.data()),
                                       size_t(self.value.data()));
             },
             py::arg("verbose") = false)
        ;

    py::class_<GridGraph> (m, "GridGraph", py::module_local())
        .def(py::init([](size_t n1, size_t n2){ return GridGraph(n1, n2); }))
        .def("num_nodes", &GridGraph::num_nodes)
        .def_property_readonly("n1", [](const GridGraph &grid){ return grid.n1; })
        .def_property_readonly("n2", [](const GridGraph &grid){ return grid.n2; })
        .def_property_readonly("shape", [](const GridGraph &g){
                                            return py::make_tuple(g.n1, g.n2);
                                        })
        .def("__repr__",
             [](const GridGraph &g) {
                 return std::string("GridGraph(") +
                     std::to_string(g.n1) + ", " + std::to_string(g.n2) + ")";
             })
        ;

    py::class_<BiAdjacent> (m, "BiAdjacent", PyAdjacencyIndex_int, py::module_local())
        .def(py::init([](const py::array_i32 &head,
                         const py::array_i32 &tail)
                      {
                          const auto m = check_1d_len(head);
                          check_len(m, tail, "tail");
                          return new BiAdjacent(int(m), head.data(), tail.data());
                      }),
             py::arg("head"),
             py::arg("tail"))
        .def(py::init([](const GridGraph &grid)
                      { return new BiAdjacentIndex<int>(grid); }),
             py::arg("grid"))
        .def("__repr__",
             [](const BiAdjacent &b) -> std::string
             {
                 return std::string("BiAdjacent[") +
                     "m = " + std::to_string(b.num_edges()) + ", " +
                     "n = " + std::to_string(b.num_nodes()) + "]";
             })
        .def("num_nodes",
             [](const BiAdjacent &b) -> std::size_t
             {
                 return b.num_nodes();
             })
        .def("num_edges",
             [](const BiAdjacent &b) -> std::size_t
             {
                 return b.num_edges();
             })
        ;

    py::class_<ChildrenIndex> (m, "ChildrenIndex", PyAdjacencyIndex_int,
                               py::module_local())
        .def(py::init(
             [](const py::array_i32 &parent,
                const int root_,
                const bool verbose)
              {
                  const auto n = check_1d_len(parent);
                  const int root = root_ < 0 ? find_root(n, parent.data()) :
                      root_;
                  if (root < 0)
                      throw std::runtime_error("root not found");
                  return ChildrenIndex(n, parent.data(), root, verbose);
              }),
             py::arg("parent"),
             py::arg("root") = -1,
             py::arg("verbose") = false)
        .def("__repr__",
             [](const ChildrenIndex &cidx) -> std::string
             {
                 return std::string("ChildrenIndex[ n = ") +
                     std::to_string(cidx.size()) + " ]";
             })
        .def_property_readonly("root", &ChildrenIndex::root_node)
        .def("degrees",
             [](const ChildrenIndex &b, py::array_i32 &d) -> py::array_t<int>
             {
                 const auto n = b.size();
                 if (is_empty(d))
                     d = py::array_t<int32_t>({n}, {sizeof(int32_t)});
                 check_len(n, d, "d");
                 b.degrees(d.mutable_data());
                 return d;
             },
             R"pbdoc(
                The number of neighbors in each node
             )pbdoc",
             py::arg("d") = py::array_i32()
            )
        .def("reset",
             [](ChildrenIndex &self,
                const py::array_i32 &parent,
                int32_t root,
                const bool verbose)
                -> ChildrenIndex&
             {
                 TimerQuiet _ (verbose);
                 const size_t n = check_1d_len(parent);
                 {
                     Timer _ ("ChildrenIndex::reset\n");
                     self.reset(n, parent.data(), root, verbose);
                 }
                 return self;
             },
             R"pbdoc(
                Reset this children index to a new tree given by `parent`.
             )pbdoc",
             py::arg("parent"),
             py::arg("root") = -1,
             py::arg("verbose") = false
            )
        ;

    py::class_<PartitionIndex_int> (m, "PartitionIndex", PyAdjacencyIndex_int,
                                    py::module_local())
        .def(py::init(
                 [](const py::array_i32 &ungrouped) {
                     const size_t n = check_1d_len(ungrouped);
                     return PartitionIndex_int(n, ungrouped.data());
                 }),
             py::arg("ungrouped"))
        .def("__repr__",
             [](const PartitionIndex_int &self) -> std::string
             {
                 return std::string("PartionIndex[ n = ") +
                     std::to_string(self.size()) + " ]";
             })
        .def("__iter__",
             [](const PartitionIndex_int &self) {
                 return py::make_iterator(self.begin(), self.end());
             })
        ;

    py::class_<IndexIter_int>(m, "IndexIter_int", py::module_local())
        .def("__repr__",
             [](const IndexIter_int &self) -> std::string
             {
                 std::ostringstream os;
                 os << "<IndexIter_int(" << self.size()
                    <<") @" << (void*)&self << ">";
                 return os.str();
             })
        .def("__len__",
             [](const IndexIter_int &self) -> size_t
             {
                 return self.size();
             })
        .def("__iter__",
             [](const IndexIter_int &self)
             {
                 return py::make_iterator(self.begin(), self.end());
             })
        ;

    m.def("cluster",
          [](const py::array_f64 &x,
             const BiAdjacent &neighidx,
             const double eps,
             const int seed) -> PartitionIndex_int {
              return cluster<int, BiAdjacent>(
                  size_t(x.size()),
                  x.data(),
                  neighidx,
                  eps,
                  seed);
          },
          R"pbdoc(
            Find a partition of x such that TO BE CONTINUED
          )pbdoc",
          py::arg("x"),
          py::arg("neighidx"),
          py::arg("eps") = 1e-5,
          py::arg("seed") = 42)
        ;

    m.def("groupby",
          [](const py::array_i32 &parent,
             int32_t root,
             py::array_i32 &idx,
             py::array_i32 &value,
             const bool verbose) -> py::tuple
          {
              TimerQuiet tq (verbose);
              Timer _ ("groupby\n");
              const size_t n = check_1d_len(parent);
              {
                  Timer _ ("allocation");
                  if (is_empty(idx))
                      idx = py::array_t<int32_t>({n+1}, {sizeof(int32_t)});
                  check_len(n+1, idx, "idx");
                  
                  if (is_empty(value))
                      value = py::array_t<int32_t>({n}, {sizeof(int32_t)});
                  check_len(n, value, "value");
              }
              int32_t *idx_data = idx.mutable_data();
              {   Timer _ ("assign = 0");
                  for (size_t i = 0; i < n+1; i++)
                      idx_data[i] = 0;
              }

              if (root < 0) {
                  Timer _ ("find root");
                  root = find_root(n, parent.data());
              }
              groupby<Timer>(
                  value.mutable_data(),
                  n,
                  idx_data,
                  n,
                  parent.data(),
                  root
              );
              return py::make_tuple(idx, value);
          },
          py::arg("parent"),
          py::arg("root") = int32_t(-1),
          py::arg("idx") = py::array_i32(),
          py::arg("value") = py::array_i32(),
          py::arg("verbose") = false
        )
        ;
}


#ifdef OWN_MODULE
PYBIND11_MODULE(idx, m)
{
    reg_idx(m);
}
#endif

// Local Variables:
// compile-command: "make -C ../build pysetup"
// End:
