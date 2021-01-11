module TestMST

include("../src/GraphIdx.jl")

using Test
import .GraphIdx: kruskal_mst, prim_mst_edges


function from_networkx(graph; print_it = false)
    graph = reshape(reinterpret(Int, graph), 3, length(graph))'
    if print_it
        for i in 1:size(graph, 1)
            e = graph[i, :]
            println("$('A' + e[1]) -- $('A' + e[2]): $(e[3])")
        end
    end
    edges = vec(mapslices(Tuple, graph[:, 1:2] .+ 1, dims = [2]))
    weights = Float64.(graph[:, 3])
    n = maximum(map(maximum, edges))
    return n, edges, weights
end


# Adapted from
# https://github.com/networkx/networkx/blob/master/
#   networkx/algorithms/tree/tests/test_mst.py
const graph_x = [
    (0, 1, 7),
    (0, 3, 5),
    (1, 2, 8),
    (1, 3, 9),
    (1, 4, 7),
    (2, 4, 5),
    (3, 4, 15),
    (3, 5, 6),
    (4, 5, 8),
    (4, 6, 9),
    (5, 6, 11),
]

const expected_min_x = [
    (0, 1, 7),
    (0, 3, 5),
    (1, 4, 7),
    (2, 4, 5),
    (3, 5, 6),
    (4, 6, 9),
]

const expected_max_x = [
    (0, 1, 7),
    (1, 2, 8),
    (1, 3, 9),
    (3, 4, 15),
    (4, 6, 9),
    (5, 6, 11),
]


@testset "MST: Kruskal Wikipedia         " begin
    n, edges, weights = from_networkx(graph_x)

    selected = kruskal_mst(n, edges, +weights)
    expected = [e in expected_min_x for e in graph_x]
    # println(Int.(selected .⊻ expected))
    @test selected == expected

    selected = kruskal_mst(n, edges, -weights)
    expected = [e in expected_max_x for e in graph_x]
    @test selected == expected
end


@testset "MST: Prim    Wikipedia         " begin
    n, edges, weights = from_networkx(graph_x)

    _, selected = prim_mst_edges(n, edges, +weights)
    expected = Set(i for (i, e) in enumerate(graph_x) if e in expected_min_x)
    @test Set(selected) == expected

    _, selected = prim_mst_edges(n, edges, -weights)
    expected = Set(i for (i, e) in enumerate(graph_x) if e in expected_max_x)
    @test Set(selected) == expected
end


function capture_stdout(f::Function)
    STDOLD = stdout
    rd, wr = redirect_stdout()
    local ret
    try
        ret = f()
    finally
        redirect_stdout(STDOLD)
    end
    close(wr)
    (read(rd, String), ret)
end


@testset "MST: Own 3x7 Graph             " begin
    n1, n2 = 3, 7
    n = n1 * n2
    m = 32
    root = 1
    edges = GraphIdx.Edge{Int}[
        (1,  2),  (4,  5),  (7, 8), (10, 11), (13, 14), (16, 17),
        (19, 20), (2,  3),  (5, 6), (8,   9), (11, 12), (14, 15),
        (17, 18), (20, 21), (1, 4), (4,   7), (7,  10), (10, 13),
        (13, 16), (16, 19), (2, 5), (5,   8), (8,  11), (11, 14),
        (14, 17), (17, 20), (3, 6), (6,   9), (9,  12), (12, 15),
        (15, 18), (18, 21)
    ]
    @test GraphIdx.Grid.GridGraph(n1, n2) |> collect |> g -> g.edges == edges
    γ = [0.0, 1.0, 0.24, 0.04, 0.43, 0.73, 0.7, 0.28, 1.41, 1.43, 0.51, 0.52, 1.14,
    0.02, 0.11, 0.02, 0.79, 0.33, 0.74, 0.65, 1.11, 0.78, 0.51, 0.14, 0.44, 0.78, 0.58,
    0.80, 1.43, 0.13, 1.06, 0.38]

    @testset "prim_mst" begin
        pi, selected = GraphIdx.prim_mst_edges(n, edges, -γ, root)
        @test pi == [1, 5, 6, 1, 4, 5, 8, 9, 6, 7, 8, 9, 10, 15, 18, 13, 16, 17, 20, 17, 18]
        @test sum(γ[selected]) ≈ 15.79
        @test sum(
            γ[e] for (e, (u, v)) in enumerate(edges) if pi[u] == v || pi[v] == u
        ) ≈ 15.79
    end

    @testset "prim_mst_dbg" begin
        mem = GraphIdx.PrimMstMem(edges, n)
        dist = zeros(Float64, m)
        idx = GraphIdx.IncidenceIndex(n, edges)
        pi = zeros(Int, n)
        pq = GraphIdx.PriorityQueue{Int, Float64}(n)
        out, pi = capture_stdout() do
            GraphIdx._prim_mst_dbg(-γ, dist, pi, idx, pq)
        end
        @test pi == [1, 5, 6, 1, 4, 5, 8, 9, 6, 7, 8, 9, 10, 15, 18, 13, 16, 17, 20, 17, 18]
        @test out == """
            fin: 0 pi = 0 was -Inf
            new: 1 --> -0.0
            new: 3 --> -0.11
            fin: 3 pi = 0 was -0.11
            new: 4 --> -1.0
            new: 6 --> -0.02
            fin: 4 pi = 3 was -1.0
            new: 5 --> -1.41
            upd: 1 --> -1.11 was -0.0
            new: 7 --> -0.78
            fin: 5 pi = 4 was -1.41
            new: 2 --> -0.58
            new: 8 --> -0.8
            fin: 1 pi = 4 was -1.11
            fin: 8 pi = 5 was -0.8
            upd: 7 --> -1.43 was -0.78
            new: 11 --> -1.43
            fin: 7 pi = 8 was -1.43
            upd: 6 --> -0.24 was -0.02
            new: 10 --> -0.51
            fin: 11 pi = 8 was -1.43
            new: 14 --> -0.13
            fin: 2 pi = 5 was -0.58
            fin: 10 pi = 7 was -0.51
            new: 9 --> -0.04
            new: 13 --> -0.14
            fin: 6 pi = 7 was -0.24
            upd: 9 --> -0.79 was -0.04
            fin: 9 pi = 6 was -0.79
            new: 12 --> -0.33
            fin: 12 pi = 9 was -0.33
            upd: 13 --> -0.43 was -0.14
            new: 15 --> -0.74
            fin: 15 pi = 12 was -0.74
            new: 16 --> -0.73
            new: 18 --> -0.65
            fin: 16 pi = 15 was -0.73
            new: 17 --> -1.14
            upd: 13 --> -0.44 was -0.43
            new: 19 --> -0.78
            fin: 17 pi = 16 was -1.14
            upd: 14 --> -1.06 was -0.13
            new: 20 --> -0.38
            fin: 14 pi = 17 was -1.06
            upd: 13 --> -0.52 was -0.44
            fin: 19 pi = 16 was -0.78
            upd: 18 --> -0.7 was -0.65
            fin: 18 pi = 19 was -0.7
            fin: 13 pi = 14 was -0.52
            fin: 20 pi = 17 was -0.38
            """            
    end
end


end
