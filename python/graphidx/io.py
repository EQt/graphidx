import bz2

from ._graphidx import io as gio


def _decompress(fname: str, CHUNK_SIZE: int = 16384):
    outfn = fname + ".plain"
    dec = bz2.BZ2Decompressor()
    with open(fname, 'rb') as inf:
        with open(outfn, 'wb') as out:
            for chunk in iter(lambda: inf.read(CHUNK_SIZE), b''):
                dat = dec.decompress(chunk)
                out.write(dat)
    return outfn


def parse_dimacs10(fname: str):
    is_bz = gio.is_bzip2(fname)
    if is_bz and not gio.__have_bzip2__:
        fname = _decompress(fname)
    return gio.parse_dimacs10(fname, is_bz2=is_bz)
