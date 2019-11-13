from __future__ import annotations


class Weights:
    @staticmethod
    def new(x) -> Weights:
        """
        Depending on the type of x, construct `ConstantWeights`
        or `ArrayWeights`
        """
        if isinstance(x, Weights):
            return x
        elif isinstance(x, type):
            return Ones(x)
        elif isinstance(x, (float, int)):
            return Const(x)
        elif hasattr(x, '__getitem__'):
            return Array(x)
        raise ValueError(type(x))

    def __call__(self, i):
        return self[i]


class Ones(Weights):
    def __init__(self, dtype=float):
        self.dtype = dtype

    def __getitem__(self, _):
        return dtype(1)


class Const(Weights):
    def __init__(self, c: float):
        self.c = c

    def __getitem__(self, _):
        return self.c


class Array(Weights):
    def __init__(self, a):
        self.a = a

    def __getitem__(self, i):
        return self.a[i]
