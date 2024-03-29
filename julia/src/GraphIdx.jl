"""
Index-based Graphs
==================

Nodes
-----

A node (sometimes also *vertex* called) in a graph is always represented as an integer.
To be able to use a node as an index, the nodes should be within `1:n` whereby `n` is the number of nodes.
Furtheron, we always use **signed** integers because we might include extra information within the first (sign) bit.


Edges
-----

By convention, a graph is considered *undirected* (unless specified else).
Hence we only need to store one direction of every edge `(u, v)`; by default we assume `u < v`.

TODO:
- differences
- incidence matrix

If any *flow* `α``for an edge `(u, v)` has to be computed, the orientation is defined as going from `v` to `u` (big to small), i.e. we compute

```julia
x[u] += α
x[v] -= α
```

Submodules
----------

The most important submodules are
- [`Tree`](@ref): Rooted Trees (including minimum spanning trees).
- [`Grid`](@ref): Specialized code for grid graphs.
- [`LinA`](@ref): Linear algebra (e.g. incidence matrix)
"""
module GraphIdx

include("weights.jl")

include("incidence.jl")
include("biadjacent.jl")
include("cluster.jl")
include("Utils.jl")
include("Tree.jl")

include("graph.jl")
include("weightedgraph.jl")
include("edgegraph.jl")
include("prim_mst.jl")
include("kruskal_mst.jl")

include("bits.jl")
include("lina.jl")
include("grid.jl")
include("grididx.jl")
include("stats.jl")
include("Io.jl")

include("graphviz.jl")

include("precompile.jl")

end
