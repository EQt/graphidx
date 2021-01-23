#ifdef HAVE_LEMON // Can't test without lemon library
#include <doctest/doctest.h>
#include <sstream>

#include <graphidx/edges.hpp>
#include <graphidx/grid.hpp>
#include <graphidx/heap/lemon_heap.hpp>
#include <graphidx/heap/binheap.hpp>
#include <graphidx/spanning/prim_mst.hpp>

#include "test_mst37.hpp"


const static double weights37[32] = {
    -0.0,  -1.0,  -0.24, -0.04, -0.43, -0.73, -0.7,  -0.28, -1.41, -1.43, -0.51,
    -0.52, -1.14, -0.02, -0.11, -0.02, -0.79, -0.33, -0.74, -0.65, -1.11, -0.78,
    -0.51, -0.14, -0.44, -0.78, -0.58, -0.80, -1.43, -0.13, -1.06, -0.38};


double
tree_costs(const int *parent, const double *weights, const IncidenceIndex<int> &idx)
{
    double sum = 0.0;
    edges<int>(idx, [&](int u, int v, int e) {
        if (u < v && (parent[u] == v || parent[v] == u))
            sum += weights[e];
    });
    return sum;
}


TEST_CASE("Prim MST on a 3x7 Grid")
{
    using Queue = lemo::QuadHeapT;
    const GridGraph g(3, 7);
    const IncidenceIndex<int> idx(g);
    const int root = 0;
    std::vector<double> w(weights37, weights37 + idx.num_edges());
    const auto weights = w.data();

    REQUIRE(g.num_edges() == 32);
    std::vector<int> parent(g.num_nodes(), -1);
    SUBCASE("Debugging version")
    {
        std::ostringstream buf;
        prim_mst_dbg<Queue>(parent.data(), weights37, idx, root, buf);
        CHECK(buf.str() == MST_37);
        const int expect[21] = {0, 4, 5,  0,  3,  4,  7,  8,  5,  6, 7,
                                8, 9, 14, 17, 12, 15, 16, 19, 16, 17};
        for (size_t i = 0; i < g.num_nodes(); i++) {
            CAPTURE(i);
            CHECK(parent[i] == expect[i]);
        }
        CHECK(doctest::Approx(tree_costs(expect, weights, idx)) == -15.79);
        CHECK(
            doctest::Approx(tree_costs(parent.data(), weights, idx)) ==
            tree_costs(expect, weights, idx));
    }
}


TEST_CASE_TEMPLATE_DEFINE("Prim's MST on a 3x7 Grid", Queue, test_mst37)
{
    const IncidenceIndex<int> idx(GridGraph(3, 7));
    const int root = 0;
    std::vector<int> parent(idx.num_nodes(), -1);
    std::vector<double> w(weights37, weights37 + idx.num_edges());
    const auto weights = w.data();

    prim_mst_edges<Queue>(parent.data(), weights, idx, root);
    const int expect[21] = {0, 4, 5,  0,  3,  4,  7,  8,  5,  6, 7,
                            8, 9, 14, 17, 12, 15, 16, 19, 16, 17};
    for (size_t i = 0; i < idx.num_nodes(); i++) {
        CAPTURE(i);
        CHECK(parent[i] == expect[i]);
    }
}


TEST_CASE_TEMPLATE_INVOKE(test_mst37, lemo::QuadHeapT, gidx::BinaryHeapT);


#endif
