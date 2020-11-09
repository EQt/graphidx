#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>   // std::stoul
#include <vector>

#include <graphidx/grid.hpp>
#include <graphidx/spanning/prim_mst.hpp>
#include <graphidx/utils/heap.hpp>
#include <graphidx/utils/gnu_heap.hpp>
#include <graphidx/utils/lemon_heap.hpp>
#include <graphidx/utils/popen.hpp>
#include <graphidx/utils/thousand.hpp>
#include <graphidx/utils/timer.hpp>


std::vector<double>
julia_randn(
    const std::size_t size,
    const std::size_t seed = 42,
    const char *distribution = "randn")
{
    std::string cmd = "julia -e ";
    cmd += "'import Random: MersenneTwister; write(stdout, ";
    cmd += distribution;
    cmd += "(MersenneTwister(";
    cmd += std::to_string(seed);
    cmd += "), ";
    cmd += std::to_string(size);
    cmd += "))'";
    #ifdef DEBUG
    std::cerr << "DEBUG cmd = " << cmd << std::endl;
    #endif

    std::vector<double> a (size);
    Popen(cmd, "r").readinto(a, 8 * size);
    return a;
}


size_t
digest(const std::vector<int> &v)
{
    const auto a = 13;
    const auto b = 42;
    size_t d = 0;
    for (size_t i = 0; i < v.size(); i++)
        d = (i * a + b) * d + (size_t) v[i];
    return d;
}


template <typename int_>
void
print_arr(
    std::vector<int_> const &a, const size_t limit = 4, const char *prefix = "",
    const char *suffix = "")
{
    std::cout << prefix << "[";
    for (size_t i = 0; i < std::min(a.size(), limit); i++)
        std::cout << a[i] << (i == a.size() - 1 ? "" : ", ");
    if (a.size() > limit) {
        std::cout << "…, ";
        for (size_t i = std::max(limit, a.size() - limit); i < a.size(); i++)
            std::cout << a[i] << (i == a.size() - 1 ? "" : ",");
    }
    std::cout << "]" << suffix;
}


int
main(int argc, char *argv[])
{
    set_thousand_sep(std::cout);
    const size_t n1 = argc > 1 ? std::stoul(argv[1]) : 1000;
    const size_t n2 = n1;
    const size_t seed = 42;
    const auto distribution = "randn";

    auto graph = GridGraph(n1, n2);
    Timer tim ("index");
    IncidenceIndex<int> idx (graph);
    tim.stop();

    tim.start(distribution);
    const auto weights = julia_randn(graph.num_edges(), seed, distribution);
    tim.stop();

    std::cout << "graph:" << std::endl
              << " n = " << graph.num_nodes() << std::endl
              << " m = " << graph.num_edges() << std::endl;
    #ifdef HAVE_GNUX
    {
        Timer t ("\nprim_mst<thin_heap>\n");
        const auto parent = prim_mst_edges<gnux::ThinHeapT>(weights.data(), idx);
        t.stop();
        std::cout << std::hex << digest(parent) << std::endl;
    }
    {
        Timer t ("\nprim_mst<binomial_heap>\n");
        const auto parent = prim_mst_edges<gnux::BinomialHeapT>(weights.data(), idx);
        t.stop();
        std::cout << std::hex << digest(parent) << std::endl;
    }
    {
        Timer t ("\nprim_mst<rc_binomial_heap>\n");
        const auto parent = prim_mst_edges<gnux::RcBinomHeapT>(weights.data(), idx);
        print_arr(parent, 5, "pi = ", "\n");
    }
    {
        Timer t ("\nprim_mst<pairing_heap>\n");
        const auto parent = prim_mst_edges<gnux::PairHeapT>(weights.data(), idx);
        t.stop();
        std::cout << std::hex << digest(parent) << std::endl;
    }
    #else
    {
        Timer::log("<not compiled with gnu ext/pb_ds>\n");
    }
    #endif
    #ifdef HAVE_LEMON
    {
        Timer t ("\nprim_mst<fib_heap>\n");
        const auto parent = prim_mst_edges<FibHeapT>(weights.data(), idx);
        t.stop();
        std::cout << std::hex << digest(parent) << std::endl;
    }
    {
        Timer t ("\nprim_mst<bin_heap>\n");
        const auto parent = prim_mst_edges<BinHeapT>(weights.data(), idx);
        t.stop();
        std::cout << std::hex << digest(parent) << std::endl;
    }
    {
        Timer t ("\nprim_mst<quad_heap>\n");
        const auto parent = prim_mst_edges<QuadHeapT>(weights.data(), idx);
        t.stop();
        std::cout << std::hex << digest(parent) << std::endl;
    }
    #else
    {
        Timer::log("<not compiled with lemon>\n");
    }
    #endif

    return 0;
}
