#!/bin/bash
# -*- mode: julia -*-
#=
exec julia --color=yes --startup-file=no "${BASH_SOURCE[0]}" "$@"
=#
using Test


include("test_parse.jl")
include("test_weights.jl")
include("test_children.jl")
include("test_inorder.jl")
include("test_unionfind.jl")
include("test_root.jl")
include("test_cluster.jl")
include("test_incmat.jl")
include("test_grid.jl")
include("test_incidence.jl")
include("test_lca.jl")
include("test_mst.jl")
include("test_hierarchy.jl")
include("test_stats.jl")
include("test_magick.jl")
include("test_dimacs10.jl")
include("test_snap.jl")
