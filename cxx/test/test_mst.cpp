#include <doctest/doctest.h>
#include <sstream>

#include <graphidx/edges.hpp>
#include <graphidx/grid.hpp>
#include <graphidx/spanning/prim_mst.hpp>
#include <graphidx/utils/lemon_heap.hpp>


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


const char *MST_37 =
R"(fin: 0 pi = 0 was 2.22507e-308
new: 1 --> -0 pi = 0
new: 3 --> -0.11 pi = 0
fin: 3 pi = 0 was -0.11
new: 4 --> -1 pi = 3
chk: 0 finished
new: 6 --> -0.02 pi = 3
fin: 4 pi = 3 was -1
chk: 3 finished
new: 5 --> -1.41 pi = 4
upd: 1 --> -1.11 was -0
new: 7 --> -0.78 pi = 4
fin: 5 pi = 4 was -1.41
chk: 4 finished
new: 2 --> -0.58 pi = 5
new: 8 --> -0.8 pi = 5
fin: 1 pi = 4 was -1.11
chk: 0 finished
chk: 2 no upd
chk: 4 finished
fin: 8 pi = 5 was -0.8
upd: 7 --> -1.43 was -0.78
chk: 5 finished
new: 11 --> -1.43 pi = 8
fin: 7 pi = 8 was -1.43
upd: 6 --> -0.24 was -0.02
chk: 8 finished
chk: 4 finished
new: 10 --> -0.51 pi = 7
fin: 11 pi = 8 was -1.43
chk: 10 no upd
chk: 8 finished
new: 14 --> -0.13 pi = 11
fin: 2 pi = 5 was -0.58
chk: 1 finished
chk: 5 finished
fin: 10 pi = 7 was -0.51
new: 9 --> -0.04 pi = 10
chk: 11 finished
chk: 7 finished
new: 13 --> -0.14 pi = 10
fin: 6 pi = 7 was -0.24
chk: 7 finished
chk: 3 finished
upd: 9 --> -0.79 was -0.04
fin: 9 pi = 6 was -0.79
chk: 10 finished
chk: 6 finished
new: 12 --> -0.33 pi = 9
fin: 12 pi = 9 was -0.33
upd: 13 --> -0.43 was -0.14
chk: 9 finished
new: 15 --> -0.74 pi = 12
fin: 15 pi = 12 was -0.74
new: 16 --> -0.73 pi = 15
chk: 12 finished
new: 18 --> -0.65 pi = 15
fin: 16 pi = 15 was -0.73
chk: 15 finished
new: 17 --> -1.14 pi = 16
upd: 13 --> -0.44 was -0.43
new: 19 --> -0.78 pi = 16
fin: 17 pi = 16 was -1.14
chk: 16 finished
upd: 14 --> -1.06 was -0.13
new: 20 --> -0.38 pi = 17
fin: 14 pi = 17 was -1.06
upd: 13 --> -0.52 was -0.44
chk: 11 finished
chk: 17 finished
fin: 19 pi = 16 was -0.78
upd: 18 --> -0.7 was -0.65
chk: 20 no upd
chk: 16 finished
fin: 18 pi = 19 was -0.7
chk: 19 finished
chk: 15 finished
fin: 13 pi = 14 was -0.52
chk: 12 finished
chk: 14 finished
chk: 10 finished
chk: 16 finished
fin: 20 pi = 17 was -0.38
chk: 19 finished
chk: 17 finished
)";


TEST_CASE("Prim MST on a 3x7 Grid")
{
    using Queue = QuadHeapT;
    const GridGraph g(3, 7);
    const IncidenceIndex<int> idx(g);
    const int root = 0;

    REQUIRE(g.num_edges() == 32);
    std::vector<int> parent(g.num_nodes(), -1);
    const static double weights[32] = {
        -0.0,  -1.0,  -0.24, -0.04, -0.43, -0.73, -0.7,  -0.28, -1.41, -1.43, -0.51,
        -0.52, -1.14, -0.02, -0.11, -0.02, -0.79, -0.33, -0.74, -0.65, -1.11, -0.78,
        -0.51, -0.14, -0.44, -0.78, -0.58, -0.80, -1.43, -0.13, -1.06, -0.38};
    SUBCASE("Debuggin version")
    {
        std::ostringstream buf;
        prim_mst_dbg<Queue>(parent.data(), weights, idx, root, buf);
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
    SUBCASE("No output version")
    {
        prim_mst_edges<Queue>(parent.data(), weights, idx, root);
        const int expect[21] = {0, 4, 5,  0,  3,  4,  7,  8,  5,  6, 7,
                                8, 9, 14, 17, 12, 15, 16, 19, 16, 17};
        for (size_t i = 0; i < g.num_nodes(); i++) {
            CAPTURE(i);
            CHECK(parent[i] == expect[i]);
        }
    }
}
