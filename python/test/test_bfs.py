import numpy as np


def test_reversed_bfs_pi():
    """
    Check that the transformed parent is consistent
    """
    parent = np.array([0, 0, 1, 2, 3, 0, 7, 8, 3, 8])
    bfs = np.array([6, 9, 7, 8, 4, 3, 2, 5, 1, 0])
    pi = np.array([2, 3, 3, 5, 5, 6, 8, 9, 9, 9])
    ibfs = np.argsort(bfs)
    assert (ibfs[parent[bfs]] == pi).all()
