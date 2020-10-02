module BenchSpanTree
import Random
import GraphIdx


function grid_tree(
    n1::Integer,
    n2::Integer,
    weights::Vector{Float64} = Float64[],
    root::Integer = 1
)
    if length(weights) < 2 * n1 * n2
        @time weights = randn(2 * n1 * n2)
    end
    graph = GraphIdx.Grid.GridGraph(n1, n2)
    @assert GraphIdx.num_edges(graph) <= length(weights)
    @time mem = GraphIdx.PrimMstMem(graph)
    @time tree = GraphIdx.prim_mst_edges(weights, root, mem)
end


end


w = randn(Random.MersenneTwister(42), 4_000_000)
@time BenchSpanTree.grid_tree(1000, 1000, w)
