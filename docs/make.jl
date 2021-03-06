#!/usr/bin/env julia

using Documenter
import GraphIdx

const build = get(ENV, "HTML_DIR", "html/julia")

DocMeta.setdocmeta!(GraphIdx, :DocTestSetup, :(import GraphIdx);
                    recursive=true, warn=true)
makedocs(
    modules=[GraphIdx],
    sitename="GraphIdx",
    authors="Elias Kuthe",
    build=build,
    clean=true,
    source="src/julia",
    pages=[
        "GraphIdx" => "index.md",
        "Graph Indexes" => "idx.md",
        "Grid Graphs" => "grid.md",
        "Tree Graphs" => "tree.md",
        "Minimum Spanning Trees" => "mst.md",
        "Linear Algebra" => "lina.md",
        "Order Statistics" => "stats.md",
        "Bits and Bytes" => "bits.md",
        "File IO" => "io.md",
        "Utils" => "utils.md",
    ],
    format = Documenter.HTML(
        prettyurls = get(ENV, "CI", nothing) == "true"
    )
)


#=
deploydocs(
    repo="github.com/EQt/treelas",
    target=build,
    # forcepush = true,
)
=#
