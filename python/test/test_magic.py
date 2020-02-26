import bz2
import gzip
import pytest
import os
from graphidx._graphidx import io as gio


@pytest.fixture
def bz2file():
    fname = "graphidx.bz2"
    with bz2.BZ2File(fname, "w") as io:
        io.write(b"GraphIdx is very fast")
    yield fname
    os.remove(fname)


@pytest.fixture
def gzfile():
    fname = "graphidx.gz"
    with gzip.GzipFile(fname, "w") as io:
        io.write(b"GraphIdx is very fast")
    yield fname
    os.remove(fname)


@pytest.fixture
def plain():
    fname = "graphidx.txt"
    with open(fname, "wb") as io:
        io.write(b"GraphIdx is very fast")
    yield fname
    os.remove(fname)


def test_is_bzip2(bz2file):
    assert gio.is_bzip2(bz2file)


def test_is_not_bzip2(plain):
    assert not gio.is_bzip2(plain)


def test_is_not_bzip2_(gzfile):
    assert not gio.is_bzip2(gzfile)


def test_is_gzip(gzfile):
    assert gio.is_gzip(gzfile)


def test_is_not_gzip_(bz2file):
    assert not gio.is_gzip(bz2file)

