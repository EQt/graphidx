from numba import njit


@njit(cache=True)
def find_root(parent):
    """Return the smallest i with parent[i] == i, or -1 if none exists"""
    for i, p in enumerate(parent):
        if i == p:
            return i
    return -1
