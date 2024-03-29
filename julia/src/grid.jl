"""
Computations related to grid graphs
"""
module Grid
using SparseArrays
import LinearAlgebra
import LinearAlgebra: norm
import ..GraphIdx: enumerate_edges, num_nodes, num_edges, Graph


"""
Position in a grid graph
"""
struct Pixel
    x::Int
    y::Int
end

Base.convert(::Type{Pixel}, p::Tuple{Int,Int}) = Pixel(p[1], p[2])

Base.convert(::Type{Tuple{Int,Int}}, p::Pixel) = (p.x, p.y)

@inline Base.getindex(p::Pixel, i::Int) =
    if i == 1
        p.x
    elseif i == 2
        p.y
    else
        throw(ArgumentErrow("i = $i"))
    end

@inline Base.iterate(p::Pixel, i::Int = 1) =
    if i == 1
        (p.x, 2)
    elseif i == 2
        (p.y, 3)
    else
        nothing
    end

LinearAlgebra.norm2(p::Pixel) = p.x^2 + p.y^2

LinearAlgebra.norm(x::Pixel) = sqrt(LinearAlgebra.norm2(x))


"""
    compute_dirs(dn)

Setting the neighborhood degree (`dn`) to `i` will set all numbers
less or equal `i` in the following diagram as neighbors of `[*]`.
```
[…] […] […] […] […] […] […]
[…] […] [4] [3] [4] […] […]
[…] [4] [2] [1] [2] [4] […]
[…] [3] [1] [*] [1] [3] […]
[…] [4] [2] [1] [2] [4] […]
[…] […] [4] [3] [4] […] […]
[…] […] […] […] […] […] […]
```

# Example

```jldoctest
julia> import GraphIdx.Grid: compute_dirs, Pixel

julia> compute_dirs(2)
2-element Array{Pixel,1}:
 Pixel(1, 0)
 Pixel(1, 1)
```
"""
function compute_dirs(dn::Int)::Vector{Pixel}
    if dn == 1
        Pixel[(1,0)]
    elseif dn == 2
        Pixel[(1,0), (1,1)]
    elseif dn == 3
        Pixel[(1,0), (1,1), (2,0)]
    elseif dn == 4
        Pixel[(1,0), (1,1), (2, 0), (2,1), (1,2)]
    else
        throw(ArgumentError("dn >= 4 not supported"))
    end
end


"""
Capture all we need to know about a grid graph.
"""
struct GridGraph <: Graph
    """Number of rows"""
    n1::Int

    """Number of columns"""
    n2::Int

    """Neighbors (in positive direction) of an inner node"""
    dirs::Vector{Pixel}

    """Include weights in `enumerate_edges`?"""
    weighted::Bool
end


GridGraph(n1, n2, dn::Int = Int(1), weighted::Bool = false) =
    GridGraph(n1, n2, compute_dirs(dn), weighted)

num_edges(g::GridGraph) =
    num_edges(g.n1, g.n2, g.dirs)

num_nodes(g::GridGraph) = g.n1 * g.n2

Base.size(g::GridGraph) = (g.n1, g.n2)

Base.size(g::GridGraph, i) = size(g)[i]

Base.length(g::GridGraph) = prod(size(g))

Base.adjoint(g::GridGraph) = GridGraph(g.n2, g.n1, g.dirs, g.weighted)


"""
    iter_edges_pixel(proc, n1, n2, dirs)

Call `proc(i1, j1, i2, j2, len)` for every grid edge
`(i1, j1) -- (i2, j2)` having `len`gth.
"""
@inline function iter_edges_pixel(
    proc::F, n1::Int, n2::Int, dirs::Vector{Pixel}
) where {F<:Function}
    for d::Pixel in dirs
        local len::Float64 = 1/norm(d)
        for i = 1:(n1-d.x)
            for j = 1:(n2-d.y)
                proc(i, j, i+d.x, j+d.y, len)
            end
        end
        for i = 1+d.y:n1
            for j = 1:(n2-d.x)
                proc(i, j, i-d.y, j+d.x, len)
            end
        end
    end
end


@inline function enumerate_edges(
    proc::F, n1::Int, n2::Int, dirs::Vector{Pixel}; weighted::Bool = true
) where {F<:Function}
    @inline pix2ind(i, j) = i + (j-1)*n1
    local no::Int = 0
    if weighted
        for d::Pixel in dirs
            local len::Float64 = 1/norm(d)
            for i = 1:(n1-d.x)
                for j = 1:(n2-d.y)
                    no += 1
                    proc(no, pix2ind(i, j), pix2ind(i+d.x, j+d.y), len)
                end
            end
            for i = 1+d.y:n1
                for j = 1:(n2-d.x)
                    no += 1
                    proc(no, pix2ind(i, j), pix2ind(i-d.y, j+d.x), len)
                end
            end
        end
    else
        for d::Pixel in dirs
            for i = 1:(n1-d.x)
                for j = 1:(n2-d.y)
                    no += 1
                    proc(no, pix2ind(i, j), pix2ind(i+d.x, j+d.y))
                end
            end
            for i = 1+d.y:n1
                for j = 1:(n2-d.x)
                    no += 1
                    proc(no, pix2ind(i, j), pix2ind(i-d.y, j+d.x))
                end
            end
        end
    end
end


@inline enumerate_edges(
    f::F, g::GridGraph; weighted::Bool = false
) where {F<:Function} =
    enumerate_edges(f, g.n1, g.n2, g.dirs, weighted=g.weighted || weighted)

"""
    iter_edges_pixel(proc, g::GridGraph)

Iterate over the edges on a grid graph.
Same as `iter_edges_pixel(::Function, ::Int, ::Int, ::Vector{Pixel}).

# Example

```jldoctest
julia> import GraphIdx.Grid: GridGraph, iter_edges_pixel

julia> iter_edges_pixel(GridGraph(2, 3)) do i1, j1, i2, j2, len
           println("(\$i1,\$j1) -- (\$i2,\$j2): \$len")
       end
(1,1) -- (2,1): 1.0
(1,2) -- (2,2): 1.0
(1,3) -- (2,3): 1.0
(1,1) -- (1,2): 1.0
(1,2) -- (1,3): 1.0
(2,1) -- (2,2): 1.0
(2,2) -- (2,3): 1.0


```
"""
iter_edges_pixel(f::F, g::GridGraph) where {F<:Function} =
    iter_edges_pixel(f, g.n1, g.n2, g.dirs)


"""
    iter_edges(proc, n1, n2, dirs)

Call `proc(u::Int, v::Int, len::Float64)` for every grid
edge `u -- v` having `len`gth.
Hereby `u` and `v` are the index of the corresponding grid-nodes.
"""
function iter_edges(proc::F, n1::Int, n2::Int, dirs::Vector{Pixel}) where {F<:Function}
    """Fortran index of the matrix entry `(i,j)`"""
    pix2ind(i, j) = i + (j-1)*n1

    iter_edges_pixel(n1, n2, dirs) do i1::Int, j1::Int, i2::Int, j2::Int, len::Float64
        proc(pix2ind(i1, j1), pix2ind(i2, j2), len)
    end
end


iter_edges(f::F, g::GridGraph) where {F<:Function} =
    iter_edges(f, g.n1, g.n2, g.dirs)


"""
    num_edges(n1, n2, dirs)
    num_edges(n1, n2, dn::Int)

Number of edges in a grid graph `n1×n2` along directions `dirs`.
If called with last argument a number, first generate `dirs`.
"""
function num_edges(n1::Int, n2::Int, dirs::Vector{Pixel})::Int
    local m::Int = 0
    for d::Pixel in dirs
        m += (n1-d.x)*(n2-d.y) + (n1-d.y)*(n2-d.x)
    end
    return m
end

num_edges(n1::Int, n2::Int, dn::Int = 1)::Int =
    num_edges(n1, n2, compute_dirs(dn))


function incmat(n1::Int, n2::Int, dn::Int = 1)
    local dirs::Vector{Pixel} = compute_dirs(dn)
    local n::Int = n1 * n2
    local m::Int = num_edges(n1, n2, dirs)

    local I::Vector{Int} = Vector{Int}(undef, 2m)
    local J::Vector{Int} = Vector{Int}(undef, 2m)
    local W::Vector{Float64} = zeros(Float64, 2m)

    enumerate_edges(n1, n2, dirs, weighted=true) do k::Int, u::Int, v::Int, l::Float64
        I[2k-1] = k
        J[2k-1] = u
        W[2k-1] = +l
        I[2k-0] = k
        J[2k-0] = v
        W[2k-0] = -l
    end
    D = sparse(I, J, W, m, n)
end


function adjlist(n1::Int, n2::Int, dirs::Vector{Pixel})
    local m::Int = num_edges(n1, n2, dirs)
    local head::Vector{Int} = Vector{Int}(undef, m)
    local tail::Vector{Int} = Vector{Int}(undef, m)
    local lam::Vector{Float64} =  Vector{Float64}(undef, m)

    enumerate_edges(n1, n2, dirs, weighted=true) do k::Int, u::Int, v::Int, l::Float64
        head[k] = u
        tail[k] = v
        lam[k] = l
    end
    head, tail, lam
end


adjlist(n1::Int, n2::Int, dn::Int = 1) =
    adjlist(n1, n2, compute_dirs(dn))


adjlist(g::GridGraph) =
    ajdlist(g.n1, g.n2, g.dirs)


"""
    line_D(n)

Return the incidence matrix for a line graph of length `n`.
Is equivalent to `incmat(1, n, 1)`.

# Example

```jldoctest
julia> import GraphIdx.Grid: line_D

julia> line_D(3)
2×3 SparseArrays.SparseMatrixCSC{Float64,Int64} with 4 stored entries:
  [1, 1]  =  1.0
  [1, 2]  =  -1.0
  [2, 2]  =  1.0
  [2, 3]  =  -1.0

```
"""
function line_D(n::Integer)
    D = spzeros(n-1, n)
    for i = 1:n-1
        D[i, i+0] = +1
        D[i, i+1] = -1
    end
    return D
end


"""
    lipschitz(n1, n2, [dn | dirs])

Compute an upper bound for the Lipschitz-constant for ...
TODO: Be more precise
"""
function lipschitz(n1, n2, dirs::Vector{Pixel})
    lmax = maximum(lam)
    Lip = lmax * 2 * 4 * sum([l for (d,l) in dirs])
    error("not implemented, yet")
end

lipschitz(n1::Int, n2::Int, dn::Int)::Float64 =
    lipschitz(n1, n2, compute_dirs(dn))


function neighboridx_lambda(g::Grid.GridGraph)
    local n::Int = num_nodes(g)
    local m::Int = num_edges(g)
    local idx::Vector{Int} = zeros(Int, n+1)
    iter_edges(g) do u::Int, v::Int, lam_i::Float64
        idx[u] += 1
        idx[v] += 1
    end
    acc = 1                        # accumulate degrgees ==> positions
    deg_i = 0
    deg_ii = idx[1]
    for i = 1:n
        idx[i] = acc
        acc += deg_i
        deg_i, deg_ii = deg_ii, idx[i+1]
    end
    idx[n+1] = acc
    @assert(idx[end] + deg_i == 2m + 1,
            "idx[$(length(idx))]: $(idx[end] + deg_i) != $(2m + 1)")
    local pi::Vector{Tuple{Int,Int}} = Vector{Tuple{Int,Int}}(undef, 2m)
    local lam::Vector{Float64} = Vector{Float64}(undef, m)
    enumerate_edges(g, weighted=true) do i::Int, u::Int, v::Int, lam_i::Float64
        lam[i] = lam_i
        pi[idx[u+1]] = (v, i)
        idx[u+1] += 1
        pi[idx[v+1]] = (u, i)
        idx[v+1] += 1
    end
    @assert(idx[end] == 2m + 1, "$(idx[end]) vs $(2m + 1)")
    return idx, pi, lam
end

"""How is a node within the grid?"""
@enum BorderType begin
    Middle      = 0b000
    North       = 0b100
    NorthWest   = 0b101
    NorthEast
    SouthWest
    SouthEast
    South
    West
    East
end


@inline coordinates(g::Grid.GridGraph, v::Int)::Tuple{Int,Int} =
    coordinates(g.n1, v)

@inline function coordinates(n1::Int, v::Int)::Tuple{Int,Int}
    i, j = divrem(v-1, n1)
    i += 1
    j += 1
    (i, j)
end


function BorderType(g::Grid.GridGraph, v::Int)::BorderType
    i, j = coordinates(g, v)
    if (i, j) == (1, 1)
        NorthWest
    elseif (i, j) == (1, g.n2)
        NorthEast
    elseif (i, j) == (g.n1, 1)
        SouthWest
    elseif (i, j) == (g.n1, g.n2)
        SouthEast
    elseif i == 1
        North
    elseif i == g.n1
        South
    elseif j == 1
        West
    elseif j == g.n2
        East
    else
        Middle
    end
end


"""
Idea: Do not store the graph explicitly but compute the neighbors as needed.
For avoiding too many allocations, return just a view to the buffer
"""
struct ImplicitGridGraph <: Graph
    grid::GridGraph
    _buffer::Vector{Tuple{Int,Int}}

    ImplicitGridGraph(n1::Int, n2::Int, dn::Int = Int(1)) =
        new(GridGraph(n1, n2, dn), [])
end


struct GridNeighbors
    p::Complex{Int}
    bt::BorderType
    graph::GridGraph
end


Base.Complex(p::Pixel)::Complex{Int} =
    Complex{Int}(p.x, p.y)

Pixel(p::Complex{Int}) =
    Pixel(real(p), imag(p))


num_edges(bt::BorderType) =
    if bt == Middle
        4
    elseif bt == South || bt == North || bt == West || bt == East
        2
    else
        1
    end


Base.length(gn::GridNeighbors) =
    num_edges(gn.bt) * length(gn.graph.dirs)


function Base.iterate(gn::GridNeighbors, state::Tuple{Int,Int} = (1, 1))
    pix2ind(p::Pixel) = pix2ind(p...)
    pix2ind(p::Complex{Int}) = pix2ind(Pixel(p))
    pix2ind(px::Int, py::Int) = px + (py-1) * gn.graph.n1
    let (di, ii) = state
        if di > length(gn.graph.dirs)
            return nothing
        end
        local dir::Complex{Int} = gn.graph.dirs[di]
        if gn.bt == Middle
            if ii > 4
                return iterate(gn, (di+1, 1))
            else
                return (pix2ind(gn.p + (1im^ii) .* Complex(dir)), (di, ii+1))
            end
        elseif gn.bt == North
            if ii > 3
                return iterate(gn, (di+1, 1))
            else
                return (pix2ind(gn.p + (1im^ii) .* Complex(dir)), (di, ii+1))
            end
            notimplemented("todo")
        end
    end
end


function Base.getindex(graph::GridGraph, v::Int = 2)
    bt = BorderType(graph, v)
    return GridNeighbors(Complex(coordinates(graph, v)...), bt, graph)
end


"""
    collect_edges(::GridGraph)

Return a `Vector{Tuple{Int,Int}}` of edges and `Vector{Float64}` of weights.
"""
function collect_edges(graph::GridGraph)
    local m = num_edges(graph)
    local n = num_nodes(graph)
    edges = Vector{Tuple{Int,Int}}(undef, m)
    lam = Vector{Float64}(undef, m)
    enumerate_edges(graph, weighted=true) do ei::Int, u::Int, v::Int, l::Float64
        edges[ei] = (u, v)
        lam[ei] = l
    end
    return edges, lam
end


end
