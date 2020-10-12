#include <iostream>
#include <string>   // std::stoul
#include <vector>

#include <graphidx/grid.hpp>
#include <graphidx/utils/popen.hpp>
#include <graphidx/utils/thousand.hpp>
#include <graphidx/utils/timer.hpp>

#include "prim_mst.hpp"


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
    BiAdjacentIndex<int> idx (graph);
    tim.stop();

    tim.start(distribution);
    const auto weights = julia_randn(graph.num_edges(), seed, distribution);
    tim.stop();

    std::cout << "graph:" << std::endl
              << " n = " << graph.num_nodes() << std::endl
              << " m = " << graph.num_edges() << std::endl;
    {
        Timer _ ("prim_mst\n");
        const auto parent = prim_mst_edges(weights.data(), idx);
    }

    return 0;
}
