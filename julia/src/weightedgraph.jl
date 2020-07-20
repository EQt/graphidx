import .Tree


struct WeightedGraph <: Graph
    idx::IncidenceIndex
    lam::Vector{Float64}
end


@inline num_nodes(g::WeightedGraph) =
    num_nodes(g.idx)

@inline num_edges(g::WeightedGraph) =
    num_edges(g.idx)

@inline function enumerate_edges(f::F, g::WeightedGraph) where {F<:Function}
    for u in 1:num_nodes(g)
        for (v, ei) in g.idx[u]
            if u < v
                f(ei, u, v, g.lam[ei])
            end
        end
    end
end


@inline function enumerate_edges(f::F, t::Tree.WeightedTree{W}) where {F<:Function, W}
    for (u, v) in enumerate(t.tree.parent)
        if u == t.tree.root
            continue
        end
        f(u, u, v, t.lam[u])
    end
end
