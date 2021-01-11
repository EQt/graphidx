module TestGrid

using Test
import LinearAlgebra: norm, norm2
import GraphIdx.Grid: Pixel, line_D, incmat
import GraphIdx.Grid: GridGraph, iter_edges, iter_edges_pixel
import GraphIdx: num_edges, num_nodes


@testset "Pixel                          " begin
    p0 = Pixel(0, 0)
    @test norm(p0) == 0.0
    @test norm2(p0) == 0.0

    p1 = Pixel(1, 1)
    @test norm2(p1) == 2.0
    @test norm(p1) ≈ √2

    p3 = Pixel(1, 3)
    @test norm2(p3) == 10
    @test norm(p3)  ≈ √10
end


@testset "line_D                         " begin
    D = line_D(3)
    @test D ≈ [1  -1   0
               0  +1  -1]
    D = line_D(5)
    @test D ≈ [1  -1   0   0   0
               0  +1  -1   0   0
               0   0  +1  -1   0
               0   0   0  +1  -1]

    for n in [11, 13, 42]
        @test line_D(n) == incmat(n, 1)
        @test line_D(n) == incmat(1, n)
    end
end


@testset "GridGraph: 3x2                 " begin
    g = GridGraph(3, 2)
    @test (g |> collect).edges == [(1, 2), (4, 5), (2, 3), (5, 6), (1, 4), (2, 5), (3, 6)]
end


@testset "GridGraph: 2x3                 " begin
    g = GridGraph(2, 3)
    m = 2*2 + 3
    n = 6
    @test num_nodes(g) == n
    @test num_edges(g) == m
    @test (g |> collect).edges == [
        (1, 2), (3, 4), (5, 6), (1, 3), (3, 5), (2, 4), (4, 6)
    ]
    @testset "iter edge pixels" begin
        local k = 0
        iter_edges_pixel(g) do i1, j1, i2, j2, lam::Float64
            k += 1
            @test lam ≈ 1
            if k == 1
                @test (i1, j1) == (1, 1)
                @test (i2, j2) == (2, 1)
            elseif k == 4
                @test (i1, j1) == (1, 1)
                @test (i2, j2) == (1, 2)
            elseif k == 5
                @test (i1, j1) == (1, 2)
                @test (i2, j2) == (1, 3)
            end
        end
        @test k == m
    end

    @testset "iter edges" begin
        local k = 0
        iter_edges(g) do u, v, lam::Float64
            k += 1
            if k == 1
                @test u == 1
                @test v == 2
            elseif k == 4
                @test u == 1
                @test v == 3
            elseif k == 5
                @test u == 3
                @test v == 5
            else
                @test u < v
            end
            @test lam ≈ 1
        end
        @test k == m
    end
end


end
