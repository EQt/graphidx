"""
    minimum_spantree(n, edges, weights, [root = 1])

[Prim's algorithm](https://en.wikipedia.org/wiki/Prim%27s_algorithm)
for minimum spanning tree.
Start from node `root` (will become the root node of the spanning tree).
Return the parent vector of the tree.
"""
function minimum_spantree(n, edges, weights, root = 1)::Vector{Int}
    finished, dist, parent, neighbors, pq = _init_spantree(edges, n)
    return _minimum_spantree(weights, finished,
                             dist, parent, neighbors, pq, root)
end

function _minimum_spantree(weights, finished, dist, parent, neighbors,
                           pq::PriorityQueue{Int, Float64}, root = 1)
    @assert isempty(pq)
    sizehint!(pq, length(parent))
    finished .= false
    finished[root] = true
    dist .= Inf
    dist[root] = 0.0
    parent[root] = root
    pq[root] = dist[root]
    while !isempty(pq)
        u = dequeue!(pq)
        for (v, eidx) in neighbors[u]
            v == u && continue
            if !finished[v] && weights[eidx] < dist[v]
                dist[v] = weights[eidx]
                pq[v] = dist[v]    # decrease_key!(v)
                parent[v] = u
            end
        end
        finished[u] = true
    end
    return parent
end
