"""All graphs should inherit from this base class"""
abstract type Graph end

const Edge{I<:Integer} = Tuple{I, I}


num_nodes(g::Graph) =
    error("$(typeof(g)) should implement num_nodes")

num_edges(g::Graph) =
    error("$(typeof(g)) should implement num_edges")

enumerate_edges(f::Function, g::Graph) =
    error("$(typeof(g)) should implement enumerate_edges")
