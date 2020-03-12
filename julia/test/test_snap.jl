module TestSnap
using Test
import GraphIdx.Io.Snap:
  parse_snap_idx, parse_snap_header, parse_snap_edges
import GraphIdx


const TEST_SNAP = """# comments
# ... to be ignored
#
# Nodes: 4 Edges: 3
# FromNodeId    ToNodeId
1       2
1       4
3       4
"""

@testset "SNAP reader                    " begin
    idx = parse_snap_idx(IOBuffer(TEST_SNAP))
    n, m, head, tail = parse_snap_edges(IOBuffer(TEST_SNAP), Int)
    @test parse_snap_header(IOBuffer(TEST_SNAP)) == (4, 3)
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
