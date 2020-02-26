from urllib.request import urlretrieve
from os import path
from graphidx._graphidx import io as gio
from graphidx.tree import ChildrenIndex
import graphidx


url = "https://www.cc.gatech.edu/dimacs10/archive/data/streets/" + \
    "belgium.osm.graph.bz2"
fname = "belgium.bz2"
if not path.exists(fname):
    print("downloading", url)
    urlretrieve(url, fname)


idx = gio.parse_dimacs10(fname)
parent = graphidx.random_spanning_tree(idx, seed=2020)
cidx = ChildrenIndex(parent)
assert list(cidx[cidx.root]) == [188343, 205091]
