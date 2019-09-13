from os import path
from setuptools import setup
from setuptools.extension import Extension


sources = [
    "_graphidx.cpp",
    "idx.cpp",
    "order.cpp",
    "spanning.cpp",
]


includes = [
    path.join(path.dirname(__file__), "..", "deps", "pybind11", "include"),
]

if __name__ == '__main__':
    _graphidx = Extension(
        "graphidx._graphidx",
        sources=sources,
        include_dirs=includes,
        language='c++',
        extra_compile_args=['-std=c++14', '-fvisibility=hidden'],
    )

    setup(
        name="graphidx",
        version="0.1.0",
        author="Elias Kuthe",
        author_email="elias.kuthe@tu-dortmund.de",
        license="MIT",
        packages=['graphidx'],
        ext_modules=[_graphidx],
    )
