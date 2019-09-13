from graphidx.tree import Tree


def test_children3():
    t = Tree.from_prufer([1, 2])
    assert t.root == 3
    assert (t.parent == [1, 2, 3, 3]).all()
    list(t.children[0]) == []
    for i in range(1, 4):
        assert list(t.children[i]) == [i-1]


def test_degree3():
    t = Tree.from_prufer([1, 2])
    assert all(t.degree == [1, 2, 2, 1]), str(t.degree)


def test_rtree(n=5, seed=2018, eps=1e-14):
    """Random tree creation"""
    t = Tree.random(n, seed=seed)
    assert t.n == n
