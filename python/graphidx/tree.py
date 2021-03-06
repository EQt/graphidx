from __future__ import annotations
import numpy as np

from .graphviz import show_tree
from ._graphidx import prufer2parent
from ._graphidx import find_root
from .idx import ChildrenIndex


class Tree:
    """Rooted tree, stored as a parent np.array"""
    def __init__(self, parent, root=-1, n=None):
        self.parent = np.asarray(parent, dtype=np.int32)
        if isinstance(n, int):
            assert len(self.parent) == n
        if root < 0:
            root = find_root(parent)
            assert root >= 0
            assert root < len(parent)
        self.root = np.int32(root)
        self.childidx = None
        assert self.parent[self.root] == self.root

    @property
    def children(self):
        if self.childidx is None:
            self.childidx = ChildrenIndex(self.parent, self.root)
        return self.childidx

    @property
    def degree(self):
        return self.children.degrees()

    @property
    def n(self):
        """Number of nodes"""
        return len(self)

    def __len__(self):
        return len(self.parent)

    def __repr__(self):
        return f"""Tree(n={self.n},
     root={self.root},
     parent={repr(self.parent)})""".strip()

    def show(self, wait=True, **kwargs):
        """Show the tree using graphviz' dot"""
        show_tree(self.parent, wait=wait, **kwargs)
        return self

    @staticmethod
    def from_prufer(prufer):
        """If choose root by the Prüfer sequence"""
        parent, root = prufer2parent(np.asarray(prufer, dtype=np.int32))
        return Tree(parent, root=root)

    @classmethod
    def generate(cls, degrees, seed=42):
        from .py.prufer import prufer_from_children_spec
        return cls.from_prufer(prufer_from_children_spec(degrees, seed=seed))

    @staticmethod
    def random(n, seed=None):
        if seed is not None:
            np.random.seed(seed)
        t = Tree.from_prufer(np.random.randint(0, n, size=n-2, dtype=np.int32))
        return t

    @staticmethod
    def load(fname):
        import h5py

        with h5py.File(fname) as io:
            parent = io['parent'][:]
            root = io['root'][:] if 'root' in io else find_root(parent)
        return Tree(parent=parent, root=root)

    def save(self, fname: str):
        if fname.endswith("h5") or fname.endswith("hdf5"):
            self.save_h5(fname)
        else:
            raise NotImplementedError("Only HDF5 output supported yet")

    def save_h5(self, fname: str, compression=1):
        import h5py

        with h5py.File(fname, "w") as io:
            if "parent" in io:
                del io["parent"]
            io.create_dataset("parent",
                              data=self.parent,
                              compression=compression)
