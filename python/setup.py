from os import path
from setuptools import setup
from setuptools.extension import Extension
from setuptools.command.build_ext import build_ext
from distutils import sysconfig as sc


sources = [
    "_graphidx.cpp",
    "idx.cpp",
    "order.cpp",
    "spanning.cpp",
    "timer.cpp",
    "io.cpp",
]


includes = [
    path.join(path.dirname(__file__), "..", "deps", "pybind11", "include"),
    path.join(sc.get_config_var('INCLUDEPY'), "..", "Library", "include"),
]


packages = ['graphidx', 'graphidx.py']


class BuildExt(build_ext):
    """A custom build extension for adding compiler-specific options."""
    def build_extensions(self):
        ct = self.compiler.compiler_type
        opts = list()
        links = list()
        if ct == 'unix':
            opts.append('-std=c++17')
            opts.append('-fvisibility=hidden')
            links.append('-fvisibility=hidden')
            links.append('-lbz2')
            links.append('-flto')
        elif ct == 'msvc':
            opts.append('/EHsc')
            opts.append('/std:c++17')
            libbz2 = path.join(sc.get_config_var('INCLUDEPY'),
                               "..", "Library", "lib", "libbz2.lib")
            if path.exists(libbz2):
                links.append(libbz2)
        else:
            print('Unknown compiler type:', ct)
        for ext in self.extensions:
            ext.extra_compile_args = opts
            ext.extra_link_args = links
        build_ext.build_extensions(self)


def git_submodule():
    if not path.exists(path.join(includes[0], "pybind11", "pybind11.h")):
        import subprocess as sp

        deps = path.join(path.dirname(__file__), '..', 'deps')
        cmd = 'git submodule update --init pybind11'
        try:
            sp.check_call(cmd.split(), cwd=deps)
        except:
            print("cd", deps, "&&", cmd)
            raise


def graphidx_setup(_graphidx, root='.'):
    setup(
        name="graphidx",
        version="0.1.0",
        author="Elias Kuthe",
        author_email="elias.kuthe@tu-dortmund.de",
        license="MIT",
        package_dir={'': root},
        packages=packages,
        ext_modules=[_graphidx],
        cmdclass={'build_ext': BuildExt},
    )


if __name__ == '__main__':
    git_submodule()
    _graphidx = Extension(
        "graphidx._graphidx",
        sources=sources,
        include_dirs=includes,
        language='c++',
    )
    graphidx_setup(_graphidx)
