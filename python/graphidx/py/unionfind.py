"""
Classical Union-Find data structure with path compression as described
e.g. in CLRS in Chapter 21 "Disjooint Sets" (3rd edition).

>>> from graphidx.py.unionfind import UnionFind
>>> u = UnionFind(3)
>>> u.find(1) == u.find(2)
False
>>> u.unite(u.find(1), u.find(2))
>>> u.find(1) == u.find(2)
True
"""
import numpy as np
import numba


@numba.njit(cache=False)
def _uf_find(pi, x):
    if pi[x] != x:
        pi[x] = _uf_find(pi, pi[x])
    return pi[x]


@numba.jitclass([('p', numba.uint64[:]), ('rank', numba.uint64[:])])
class UnionFind:
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
        return _uf_find(self.p, x)

    def unite(self, fx: int, fy: int):
        if self.rank[fx] > self.rank[fy]:
            self.p[fy] = fx
        else:
            self.p[fx] = fy
            if self.rank[fx] == self.rank[fy]:
                self.rank[fy] += 1

    def __getitem__(self, i: int):
        return self.find(i)
