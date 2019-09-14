"""
Read/write DIMACS files
"""
module Dimacs

import Mmap


function num_nodes_edges(preambel::String)::Tuple{Int,Int}
    found = match(r"\np \w* (\d+) (\d+)", preambel)
    return parse(Int, found[1]), parse(Int, found[2])
end


function read_edges_bin(proc::F, n::Int, bitmap::Vector{UInt8}) where {F<:Function}
    local off::Int = 1
    for i = 0:(n-1)
        for j = 0:(i-1)
            if bitmap[off + (j >> 3)] & (1 << (7 - (j % 8))) != 0
                proc(i, j)
            end
        end
        off += i ÷ 8 + 1
    end
end


"""read_dimacs_bin(proc, fname)

Read the binary file located at `fname` and call `proc(u::Int, v::Int)`
on every edge `(u, v)` of the graph.
"""
function read_dimacs_bin(proc::Function, fname::String;
                         show_preambel::Function = s -> nothing)
    open(fname) do io::IOStream
        offset = parse(Int, readline(io))
        preambel = String(read(io, offset))
        n, m = num_nodes_edges(preambel)
        show_preambel(preambel)
        bitmap = Mmap.mmap(io, Vector{UInt8})
        read_edges_bin(proc, n, bitmap)
    end
end


@inline function printf_edge(u::Int, v::Int, out::IO = stdout::IO)
    @inline _dec(i::Int) = Base.dec(Unsigned(i), 1, false)
    write(out, 'e')
    write(out, ' ')
    write(out, _dec(u+1))
    write(out, ' ')
    write(out, _dec(v+1))
    write(out, '\n')
end


"""bin2asc(fname, out::IO)

Transform from binary into asci representation.
"""
function bin2asc(fname::String, out::IO = stdout::IO)
    read_dimacs_bin(fname, show_preambel= s-> print(out, s)) do u::Int, v::Int
        printf_edge(u, v, out)
    end
end

end
