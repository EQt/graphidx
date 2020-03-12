module TestDimacs10
using Test
import GraphIdx.Io.Dimacs10:
  parse_dimacs10_idx, parse_dimacs10_header, parse_dimacs10_edges
import GraphIdx

const test_str = """% some comments
%  ... to be ignored
% integer node numbers start at one
% number of nodes, number of edges
4 3
2 4
2
4
"""

@testset "DIMACS10 reader                " begin
    idx = parse_dimacs10_idx(IOBuffer(test_str))
    n, m, head, tail = parse_dimacs10_edges(IOBuffer(test_str), Int)
    @test parse_dimacs10_header(IOBuffer(test_str)) == (4, 3)
    @test GraphIdx.num_nodes(idx) == 4
    @test GraphIdx.num_edges(idx) == 3
    @test n == 4
    @test m == 3
    @test head == [1, 1, 3]
    @test tail == [2, 4, 4]
    @test idx == GraphIdx.BiAdjacentIndex([0, 2, 3, 4, 6] .+ 1,
                                          [1, 3, 0, 3, 0, 2] .+ 1)

end

end
