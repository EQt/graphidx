"""
Helper functions to visualize graphs in [dot language][dot].

[dot]: https://en.wikipedia.org/wiki/DOT_(graph_description_language)
"""
module GraphViz

import GraphIdx: Graph
import GraphIdx.Grid: GridGraph

const INDENT = " "^4

dot(g::Graph) = dot(stdout, g)

dot(io::IO, g::Graph) = error("dot(::IO, $(typeof(g))) not implemented yet")

dot(print_edges::F, io::IO, g::GridGraph) where {F<:Function} =
    dot(io, g, print_edges)

"""
    dot([print_edges], [io], g)

Visualize graph `g` in dot language.

Example
-------

```julia
julia> open(`dot  -Tx11`, "w") do io
           dot(io, GraphIdx.Grid.GridGraph(3, 5))
       end

```
"""
function dot(io::IO, g::GridGraph, print_edges::F = io -> nothing) where {F<:Function}
    pix2ind(i, j) = i + (j-1)*g.n1
    println(io, "digraph {")
    for attr in ["rankdir=LR", "ranksep=0.3", "splines=ortho"]
        println(io, INDENT, attr)
    end
    println(io, INDENT, "edge [dir=none constraint=false colorscheme=dark28]")
    println(io, INDENT, "node [width=0.3 shape=circle fixedsize=true]")
    for i2 in 1:g.n2
        println(io, INDENT, "{ rank=same")
        for i1 in g.n1:-1:1
            println(io, INDENT, INDENT, pix2ind(i1, i2), " [pos=\"$i2,-$(i1)!\"]")
        end
        println(io, INDENT, "}")
    end
    print_edges(io)
    println(io, INDENT, "{ edge [style=invis constraint=true]")
    print(io, INDENT, INDENT, pix2ind(g.n1, 1))
    for i2 in 2:g.n2
        print(io, " -> ", pix2ind(g.n1, i2))
    end
    println(io)
    println(io, INDENT, "}")
    println(io, "}")
end


end
