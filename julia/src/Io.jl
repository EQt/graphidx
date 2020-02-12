"""
Input/output
"""
module Io

"""
    prettyarr(a::Array)

Get a string represantation of an array similar to the REPL output
"""
function prettyarr(a::Array)::String
    buf = IOBuffer()
    show(buf, MIME("text/plain"), a)
    read(seekstart(buf), String)
end


include("Io/parse.jl")
include("Io/dimacs.jl")
include("Io/dimacs10.jl")

end
