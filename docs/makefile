.PHONY: cxx rust

cxx:
	doxygen
	sphinx-build -b html src/cxx html/cxx

rust:
	cd $(realpath .)/.. && cargo doc
	cp -R $(realpath .)/../rust/target/doc/* html/rust/

julia:
	julia --color=yes make.jl

python:
	sphinx-build -b html src/python html/python


welcome:
	sphinx-build -b html src/welcome html/
