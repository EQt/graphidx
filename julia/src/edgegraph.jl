
"""
Graph represanted by an explicit vector of edges
"""
struct EdgeGraph
    n::UInt
    edges::Vector{Pair{Int,Int}}
end


num_nodes(g::EdgeGraph) =
    g.n


num_edges(g::EdgeGraph) =
    length(g.edges)


function enumerate_edges(f::Function, g::EdgeGraph)
    for (i, (u, v)) in enumerate(g.edges)
        f(i, u, v)
    end
end

