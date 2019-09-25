import numpy as np
import numba


@numba.jitclass([('p', numba.uint64[:]), ('rank', numba.uint64[:])])
class UnionFind:
    """
    Classical Union-Find data structure with path compression as described
    e.g. in CLRS in Chapter 21 "Disjooint Sets" (3rd edition).

    >>> u = UnionFind(2);

    >>> u.find(1) == u.find(2)
    False
    """
    def __init__(self, n: int):
        self.p = np.empty(n, dtype=np.uint64)
        self.rank = np.empty(n, dtype=np.uint64)
        self.reset()

    def reset(self):
        for i in range(len(self.p)):
            self.p[i] = i

        for i in range(len(self.rank)):
            self.rank[i] = 0

    def find(self, x: int):
        if self.p[x] != x:
            self.p[x] = self.find(self.p[x])
        return self.p[x]
