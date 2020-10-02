
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


@inline function enumerate_edges(f::F, g::EdgeGraph) where {F<:Function}
    for (i, (u, v)) in enumerate(g.edges)
        f(i, u, v)
    end
end


function Base.collect(g::Graph)::EdgeGraph
    m = num_edges(g)
    n = num_nodes(g)
    edges = Vector{Edge{Int}}(undef, m)
    enumerate_edges(g) do i::Int, u::Int, v::Int
        edges[i] = Edge((u, v))
    end
    EdgeGraph(n, edges)
end

Base.collect(g::EdgeGraph)::EdgeGraph = g


EdgeGraph(g::Graph) =
    collect(g)
