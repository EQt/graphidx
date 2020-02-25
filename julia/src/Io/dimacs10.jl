module Dimacs10

import CodecBzip2
using ..Io: parse_uints
using ...GraphIdx: BiAdjacentIndex

"""
    open_dimacs10(f, fname; as_process = false)

Open file `fname` to perform reading with function `f`.
If `fname` ends with `".bz2"`, start a corresponding decompressor.
If `fname == "-"`, read from `stdin`.
"""
function open_dimacs10(f::Function, fname::String;
                        as_process::Bool=false)
    if endswith(fname, ".bz2")
        if as_process
            open(`bzip2 -d -c $fname`) do io
                return f(io)
            end
        else
            open(fname) do bz2
                io = CodecBzip2.Bzip2DecompressorStream(bz2)
                return f(io)
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
    parse_dimacs10_header(io)

Read lines until lines does not start with comment character "%" and
then return the first two integers (number of nodes, number of edges).
"""
function parse_dimacs10_header(io::IO)::Tuple{Int,Int}
    line = ""
    while startswith(line, "%") || line == ""
        line = readline(io)
    end
    n, m = map(x-> parse(Int, x), split(line))
    n, m
end


"""
    parse_dimacs10_idx(io)

Parse a Dimacs10 file into a bidirectional index.
"""
function parse_dimacs10_idx(io::IO)::BiAdjacentIndex
    n, m = parse_dimacs10_header(io)
    pi = Vector{Int}()
    idx = Vector{Int}()
    sizehint!(pi, n+1)
    sizehint!(idx, 2m)
    parse_uints(io) do u::UInt, last::Bool
        push!(idx, u)
        if last
            push!(pi, length(idx) + 1)
        end
    end
    return BiAdjacentIndex(pi, idx)
end


"""
    parse_dimacs10_edges(io)

Return the graph as `n, m, head, tail`.
"""
function parse_dimacs10_edges(io::IO)
    n, m = parse_dimacs10_header(io)
    head = Vector{Int32}()
    tail = Vector{Int32}()
    sizehint!(head, m)
    sizehint!(tail, m)
    local i::Ref{Int32} = Ref{Int32}(0)
    parse_uints(io) do u::UInt, last::Bool
        u -= 1
        if i[] < u
            push!(head, Int32(i[]))
            push!(tail, Int32(u))
        end
        if last
            i[] += 1
        end
    end
    return n, m, head, tail
end


end
