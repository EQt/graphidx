#include <iostream>
#include <string>   // std::stoul
#include <graphidx/grid.hpp>
#include <graphidx/utils/thousand.hpp>
#include <graphidx/utils/timer.hpp>


int
main(int argc, char *argv[])
{
    set_thousand_sep(std::cout);
    const size_t n1 = argc > 1 ? std::stoul(argv[1]) : 1000;
    const size_t n2 = n1;

    auto graph = GridGraph(n1, n2);
    Timer tim ("index");
    BiAdjacentIndex<int> idx (graph);
    tim.stop();

    std::cout << "spantree"
              << " n = " << graph.num_nodes()
              << " m = " << graph.num_edges()
              << std::endl;

    return 0;
}
