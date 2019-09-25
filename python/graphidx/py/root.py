from numba import njit
import numpy as np


@njit(cache=True)
def find_root(parent: np.ndarray) -> int:
    """
    Return the smallest i with `parent[i] == i`, or `-1` if none exists

    >>> find_root(np.array([1, 2, 0, 3]))
    3
    """
    for i, p in enumerate(parent):
        if i == p:
            return i
    return -1
