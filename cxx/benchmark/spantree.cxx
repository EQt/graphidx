#include <algorithm>
#include <iostream>
#include <string>   // std::stoul
#include <vector>

#include <graphidx/grid.hpp>
#include <graphidx/spanning/prim_mst.hpp>
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
#ifdef BINARY_HEAP_FIX
    {
        Timer _ ("prim_mst<binary_heap>\n");
        using tag_t = __gnu_pbds::binary_heap_tag;
        const auto parent = prim_mst_edges<tag_t>(weights.data(), idx);
    }
#endif
    {
        Timer _ ("prim_mst<thin_heap>\n");
        using tag_t = __gnu_pbds::thin_heap_tag;
        const auto parent = prim_mst_edges<tag_t>(weights.data(), idx);
        print_arr(parent, 5, "pi = ", "\n");
    }
    {
        Timer _ ("prim_mst<binomial_heap>\n");
        using tag_t = __gnu_pbds::binomial_heap_tag;
        const auto parent = prim_mst_edges<tag_t>(weights.data(), idx);
        print_arr(parent, 5, "pi = ", "\n");
    }
    {
        Timer _ ("prim_mst<rc_binomial_heap>\n");
        using tag_t = __gnu_pbds::rc_binomial_heap_tag;
        const auto parent = prim_mst_edges<tag_t>(weights.data(), idx);
        print_arr(parent, 5, "pi = ", "\n");
    }
    {
        Timer _ ("prim_mst<pairing_heap>\n");
        using tag_t = __gnu_pbds::pairing_heap_tag;
        const auto parent = prim_mst_edges<tag_t>(weights.data(), idx);
        print_arr(parent, 5, "pi = ", "\n");
    }
    {
        Timer _ ("prim_mst<fib_heap>\n");
        using Tag = FibHeapTag;
        using Queue = detail::Heap<Tag, int, double>;
        const auto parent = prim_mst_edges<Tag, int, Queue>(weights.data(), idx);
        print_arr(parent, 5, "pi = ", "\n");
    }
    {
        Timer _ ("prim_mst<bin_heap>\n");
        using Tag = BinHeapTag;
        using Queue = detail::Heap<Tag, int, double>;
        const auto parent = prim_mst_edges<Tag, int, Queue>(weights.data(), idx);
        print_arr(parent, 5, "pi = ", "\n");
    }

    return 0;
}
