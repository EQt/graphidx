try:
    from numba import njit
except ImportError:
    import warnings

    warnings.warn("Please install `numba` for fast computation")

    def njit(cache=True):
        """Fake just-in-time compilation"""
        def _njit(f):
            return f
        return _njit
