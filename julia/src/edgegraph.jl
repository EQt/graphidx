
"""
Graph represanted by an explicit vector of edges
"""
struct EdgeGraph <: Graph
    n::Int
    edges::Vector{Edge{Int}}
end


@inline num_nodes(g::EdgeGraph) =
    g.n


@inline num_edges(g::EdgeGraph) =
    length(g.edges)


@inline function enumerate_edges(f::Function, g::EdgeGraph)
    for (i, (u, v)) in enumerate(g.edges)
        f(i, u, v)
    end
end

