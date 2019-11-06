"""
In a graph provide access to neighbors, i.e. the *adjacent nodes*,
for a specified node.

!!! note

    [`BiAdjacentIndex`](@ref) always includes both directions, i.e.
    for an edge `(u, v)` it is `u ∈ neighbors[v]` and `v ∈ neighbors[u]`.
"""
struct BiAdjacentIndex
    idx::Vector{Int}
    pi::Vector{Int}
end

@inline Base.getindex(c::BiAdjacentIndex, j::Int) =
    view(c.pi, c.idx[j]:c.idx[j+1]-1)


"""
    num_edges(::BiAdjacentIndex)

Actual number of (undirected) edges (**not counting** both directions).
"""
num_edges(c::BiAdjacentIndex) = length(c.pi) ÷ 2

num_nodes(c::BiAdjacentIndex) = length(c.idx) - 1

Base.length(c::BiAdjacentIndex) = num_nodes(c)


"""
    BiAdjacentIndex(n, head, tail)

Construct an index for `n` nodes of the (undirected) neighbors given
by the edges `zip(head, tail)`.
If `head[i] <= 0` then edge `i` is excluded.
""" 
function BiAdjacentIndex(n::Int, head::Vector{Int}, tail::Vector{Int})
    @assert length(head) == length(tail)
    BiAdjacentIndex(n, () -> zip(head, tail))
end


"""
    BiAdjacentIndex(n, edges)

Same but for edges like `[(1, 2), (2, 3)]`
"""
BiAdjacentIndex(n::Int, edges::Vector{Tuple{Int, Int}}) =
    BiAdjacentIndex(n, () -> edges)

BiAdjacentIndex(n::Int, edges::Vector{Pair{Int, Int}}) =
    BiAdjacentIndex(n, () -> edges)


"""
    BiAdjacentIndex(n, m, iter::Function)

Provide an iterator over the edges.
If the first node of an edge is zero, skip that edge.
"""
function BiAdjacentIndex(n::Int, iter::Function)
    local m::Int = 0
    idx = zeros(Int, n+1)
    for (h::Int, t::Int) in iter()
        h <= 0 && continue
        m += 1
        idx[h] += 1
        idx[t] += 1
    end
    acc = 1                        # accumulate degrees ==> positions
    deg_i = 0
    deg_ii = idx[1]
    for i = 1:n
        idx[i] = acc
        acc += deg_i
        deg_i, deg_ii = deg_ii, idx[i+1]
    end
    idx[n+1] = acc
    pi = Vector{Int}(undef, 2m)
    @assert(idx[end] + deg_i == 2m + 1,
            "idx[$(length(idx))]: $(idx[end] + deg_i) != $(2m + 1)")
    for (i, (u, v)) in enumerate(iter())
        u <= 0 && continue
        pi[idx[u+1]] = v
        idx[u+1] += 1
        pi[idx[v+1]] = u
        idx[v+1] += 1
    end
    @assert(idx[end] == 2m + 1, "$(idx[end]) vs $(2m + 1)")
    return BiAdjacentIndex(idx, pi)
end


import Base.==

==(a::BiAdjacentIndex, b::BiAdjacentIndex) =
    a.pi == b.pi && a.idx == b.idx
