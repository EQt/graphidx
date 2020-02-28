import numpy as np


def reorder_parent(parent: np.ndarray, order: np.ndarray) -> np.ndarray:
    iorder = np.argsort(order)
    return iorder[np.asarray(parent)[order]]


def test_reversed_bfs_pi():
    """
    Check that the transformed parent is consistent
    """
    parent = [0, 0, 1, 2, 3, 0, 7, 8, 3, 8]
    bfs =    [6, 9, 7, 8, 4, 3, 2, 5, 1, 0]
    pi =     [2, 3, 3, 5, 5, 6, 8, 9, 9, 9]
    assert all(reorder_parent(parent, bfs) == pi)


def test_reversed_dfs_pi():
    """
    Check that the transformed parent is consistent
    """
    parent = [0, 0, 1, 2, 3, 0, 7, 8, 3, 8]
    dfs =    [4, 6, 7, 9, 8, 3, 2, 1, 5, 0]
    pi =     [2, 3, 3, 5, 5, 6, 8, 9, 9, 9]
    assert all(reorder_parent(parent, dfs) == pi)

