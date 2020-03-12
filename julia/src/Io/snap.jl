module Snap

import CodecZlib: GzipDecompressorStream
using ..Io: parse_uints
using ...GraphIdx: BiAdjacentIndex

"""
    open_snap(f, fname; as_process = false)

Open file `fname` to perform reading with function `f`.
If `fname` ends with `".bz2"`, start a corresponding decompressor.
If `fname == "-"`, read from `stdin`.
"""
function open_snap(f::Function, fname::String;
                        as_process::Bool=false)
    if endswith(fname, ".gz")
        if as_process
            open(`gunzip -d -c $fname`) do io
                return f(io)
            end
        else
            open(fname) do gz
                return f(GzipDecompressorStream(gz))
            end
        end
    else
        if fname == "-"
            f(stdin)
        else
            @assert ispath(fname)
            open(f, fname, "r")
        end
    end
end


"""
    parse_snap_header(io)

Read lines until lines does not start with comment character "%" and
then return the first two integers (number of nodes, number of edges).
"""
function parse_snap_header(io::IO)::Tuple{Int,Int}
    line = ""
    n, m = -1, -1
    while startswith(line, "#") || line == ""
        if (g = match(r"# Nodes: (\d+) Edges: (\d+)", line)) != nothing
            n, m = [parse(Int, g[i]) for i = 1:2]
        end
        mark(io)
        line = readline(io)
    end
    reset(io)
    unmark(io)
    n, m
end


"""
    parse_snap_idx(io)

Parse a Snap file into a bidirectional index.
"""
function parse_snap_idx(io::IO)::BiAdjacentIndex
    n, m, head, tail = parse_snap_edges(io, Int)
    return BiAdjacentIndex(n, head, tail)
end


"""
    parse_snap_edges(io)

Return the graph as `n, m, head, tail`.
"""

function parse_snap_edges(io::IO, ::Type{T} = Int32) where {T<:Integer}
    n, m = parse_snap_header(io)
    head = Vector{T}()
    tail = Vector{T}()
    sizehint!(head, m)
    sizehint!(tail, m)
    parse_uints(io) do u::UInt, last::Bool
        if last
            push!(tail, T(u))
        else
            push!(head, T(u))
        end
    end
    return n, m, head, tail
end


end
