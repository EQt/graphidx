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


function benchmark(n1)
    n = n1^2
    @info "normal" n
    w = randn(Random.MersenneTwister(42), 2n)
    @time BenchSpanTree.grid_tree(n1, n1, w)
end


end


import Random

@info "precompile"
@time BenchSpanTree.grid_tree(2, 2)

@info "uniform"
w = rand(Random.MersenneTwister(42), 4_000_000)
@time BenchSpanTree.grid_tree(1000, 1000, w)

for n1 in [1000, 2000, 3000]
    BenchSpanTree.benchmark(n1)
end
