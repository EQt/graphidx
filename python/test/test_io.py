import bz2
import numpy as np
import os
import pytest
import shutil
from os import path
from graphidx._graphidx import io as gio


if_bz2 = pytest.mark.skipif(
    not gio.__have_bzip2__,
    reason="Need BZIP2 support"
)


@pytest.fixture
def wheel5(tmpdir):
    origin = path.join(path.dirname(__file__), "wheel5.dimacs10")
    assert path.exists(origin)
    fn = str(tmpdir / "w5.dimacs10")
    shutil.copy(origin, fn)
    yield str(fn)
    os.remove(fn)


@pytest.fixture
def wheel5_bz2(tmpdir):
    origin = path.join(path.dirname(__file__), "wheel5.dimacs10")
    assert path.exists(origin)
    fn = str(tmpdir / "w5.dimacs10" + ".bz2")
    with open(origin, "rb") as io:
        w5 = io.read()
    with bz2.open(fn, "wb") as io:
        io.write(w5)
    yield str(fn)
    os.remove(fn)


@pytest.fixture
def wheel5_err(tmpdir):
    origin = path.join(path.dirname(__file__), "wheel5.dimacs10")
    assert path.exists(origin)
    fn = str(tmpdir / "w5.dimacs10" + ".err")
    with open(origin, "rb") as io:
        w5 = io.read().replace(b"%", b"#")
    with open(fn, "wb") as io:
        io.write(w5)
    yield str(fn)
    os.remove(fn)


def test_not_existing():
    with pytest.raises(RuntimeError):
        gio.parse_dimacs10("doesnotexist")


def test_parse_err(wheel5_err):
    with pytest.raises(RuntimeError):
        gio.parse_dimacs10(wheel5_err)


def test_parse_err_edges(wheel5_err):
    with pytest.raises(RuntimeError):
        gio.parse_dimacs10_edges(wheel5_err)


def test_wheel5_edges(wheel5):
    head, tail = gio.parse_dimacs10_edges(wheel5)
    assert isinstance(head, np.ndarray) 
    assert isinstance(tail, np.ndarray)
    assert head.dtype == np.int32
    assert tail.dtype == np.int32
    assert len(head) == 10
    assert len(tail) == 10


@if_bz2
def test_wheel5_edges_bzip2(wheel5_bz2):
    head, tail = gio.parse_dimacs10_edges(wheel5_bz2)
    assert isinstance(head, np.ndarray) 
    assert isinstance(tail, np.ndarray)
    assert head.dtype == np.int32
    assert tail.dtype == np.int32
    assert len(head) == 10
    assert len(tail) == 10


def test_wheel5(wheel5):
    idx = gio.parse_dimacs10(wheel5)
    assert idx.num_nodes() == 6
    assert idx.num_edges() == 10


@if_bz2
def test_wheel5_bz(wheel5_bz2):
    idx = gio.parse_dimacs10(wheel5_bz2)
    assert idx.num_nodes() == 6
    assert idx.num_edges() == 10
