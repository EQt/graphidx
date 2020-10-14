#include <iostream>

#include <graphidx/grid.hpp>
#include <graphidx/utils/thousand.hpp>
#include <graphidx/utils/timer.hpp>


int
main(int argc, char *argv[])
{
    set_thousand_sep(std::cout);
    const size_t n1 = argc > 1 ? std::stoul(argv[1]) : 1000;
    const size_t n2 = n1;

    const auto graph = GridGraph(n1, n2);
    std::cout << "graph:" << std::endl
              << " n = " << graph.num_nodes() << std::endl
              << " m = " << graph.num_edges() << std::endl;
    {
        Timer _ ("adjidx");
        BiAdjacentIndex<int> idx (graph);
    }
    {
        Timer _ ("incidx");
        IncidenceIndex<int> idx (graph);
    }

    return 0;
}
