import numpy as np
from itertools import combinations
from graphidx import GridGraph
from graphidx.idx import BiAdjacent, ChildrenIndex
from graphidx import random_spanning_tree, find_root
from graphidx.tree import Tree


def test_clique5():
    edges = zip(*combinations(range(5), 2))
    head, tail = map(lambda l: np.array(l, dtype=np.int32), edges)
    assert (head < tail).all()

    index = BiAdjacent(head, tail)
    assert list(index[4]) == [0, 1, 2, 3]

    parent = random_spanning_tree(index)
    assert (parent >= 0).all()
    assert (parent < 5).all()
    assert find_root(parent) >= 0
    assert (parent == [3, 4, 1, 4, 4]).all(), parent


def test_grid_5x3():
    graph = BiAdjacent(GridGraph(5, 3))
    assert graph.shape == (5, 3)
    pi = random_spanning_tree(graph, seed=0)
    assert all(pi == [1, 2, 3, 8, 9, 6, 1, 8, 9, 9, 5, 6, 7, 14, 9])
    t = Tree(pi)
    assert t.root == 9
    assert t.degree.sum() == 2*(t.n - 1)


def test_grid_200x200():
    graph = BiAdjacent(GridGraph(200, 200))
    pi = random_spanning_tree(graph, seed=0)
    t = Tree(pi)
    cidx = ChildrenIndex(pi)
    assert t.degree.sum() == 2*(t.n - 1)
