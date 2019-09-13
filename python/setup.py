from setuptools import setup


sources = [
    "idx.cpp",
    "order.cpp",
    "spanning.cpp",
]


includes = [
    path.join(path.dirname(__file__), "..", "deps", "pybind", "cxx"),
]

if __name__ == '__main__':
    setup(
        name="graphidx",
        version="0.1.0",
        author="Elias Kuthe",
        author_email="elias.kuthe@tu-dortmund.de",
        license="MIT",
        packages=['graphidx'],
    )
