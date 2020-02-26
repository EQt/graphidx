from graphidx import GridGraph
from graphidx.idx import BiAdjacent


def test_grid3x2():
    grid = GridGraph(3, 2)
    assert repr(grid) == "GridGraph(3, 2)"
    assert grid.num_nodes() == 6
    assert grid.shape == (3, 2)


def test_grid3x2_idx():
    grid = GridGraph(3, 2)
    graph = BiAdjacent(grid)
    assert graph.num_nodes() == 6
    assert graph.num_edges() == 7
