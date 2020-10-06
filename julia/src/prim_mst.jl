import .Utils.Heap: PriorityQueue, dequeue!


"""
    prim_mst_edges(n, edges, weights, [root = 1])

[Prim's algorithm](https://en.wikipedia.org/wiki/Prim%27s_algorithm)
for minimum spanning tree.
Start from node `root` (will become the root node of the spanning
tree).  Return the parent vector and a Boolean vector indicating for
each edge whether the edge is part of the spanning tree.
"""
function prim_mst_edges(
    n::Integer,
    edges::Vector{E},
    weights::Array{Float64},
    root::Int = 1,
) where {E}
    mem = PrimMstMem(edges, n)
    prim_mst_edges(weights, root, mem)
    # swap root element to front
    mem.selected[1], mem.selected[root] = mem.selected[root], mem.selected[1]
    return mem.parent, view(mem.selected, 2:length(mem.selected))
end


struct PrimMstMem
    dist::Vector{Float64}
    parent::Vector{Int}
    neighbors::IncidenceIndex
    selected::Vector{Int}
    pq::PriorityQueue{Int, Float64}

    PrimMstMem(g::EdgeGraph) =
        PrimMstMem(IncidenceIndex(num_nodes(g), g.edges))

    PrimMstMem(g::Graph) =
        PrimMstMem(EdgeGraph(g))

    PrimMstMem(edges::Vector{E}, n::Integer) where {E} =
        PrimMstMem(IncidenceIndex(n, edges))

    PrimMstMem(head::Vector{I}, tail::Vector{I}, n::Integer) where {I} =
        PrimMstMem(IncidenceIndex(n, head, tail))

    function PrimMstMem(neighbors::IncidenceIndex)
        local n = num_nodes(neighbors)
        dist = Vector{Float64}(undef, n)
        parent = Vector{Int}(undef, n)
        selected = Vector{Int}(undef, n)
        pq = PriorityQueue{Int, Float64}(n)
        return new(dist, parent, neighbors, selected, pq)
    end
end


prim_mst_edges(
    weights::Vector{Float64}, root::Int, edges::Vector{E}, n::Integer,
) where {E} =
    prim_mst_edges(weights, root, PrimMstMem(edges, n))


prim_mst_edges(weights::Vector{Float64}, root::Int, mem::PrimMstMem) = 
    prim_mst_edges(
        weights,
        mem.dist,
        mem.parent,
        mem.neighbors,
        mem.selected,
        mem.pq,
        root
    )


function prim_mst_edges(
    edge_weight::Vector{Float64},
    dist::Vector{Float64},
    parent::Vector{Int},
    neighbors::IncidenceIndex,
    selected::Vector{Int},
    pq::PriorityQueue{Int, Float64},
    root::Int = 1,
)::Vector{Int}
    @assert length(selected) == length(parent)
    @assert isempty(pq)
    sizehint!(pq, length(parent))

    # see CLRS page 572 (2nd edition)
    parent .= 0
    parent[root] = root
    selected[root] = -1
    dist .= typemax(Float64)
    dist[root] = typemin(Float64)
    parent[root] = -root
    pq[root] = dist[root]
    while !isempty(pq)
        u = dequeue!(pq)
        for (v, eidx) in neighbors[u]
            v == u && continue
            if parent[v] <= 0 && edge_weight[eidx] < dist[v]
                dist[v] = edge_weight[eidx]
                pq[v] = dist[v]    # decrease_key!(v)
                parent[v] = -u
                selected[v] = eidx
            end
        end
        parent[u] *= -1
    end
    return parent
end
