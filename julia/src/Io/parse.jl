"""
    parse_uints(f, io)

Call function `f(i::UInt, nl::Bool)` for every number `i` in the stream `io`
whereby `nl` tells whether it was the last number in that line
"""
@inline function parse_uints(f::Function, io::IO)
    local i::UInt = 0
    local first::Bool = true
    local finished::Bool = false
    local newline::Bool = false
    while !eof(io)
        local c::UInt8 = read(io, UInt8)
        if c == UInt8(' ') || c == UInt8(',') || c == UInt8('\t')
            finished = true
        elseif c == UInt8('\n') || c == UInt8('\r')
            finished = true
            newline = true
        elseif c == UInt('_')
            nothing
        elseif UInt8('0') <= c <= UInt8('9')
            if finished
                if !first
                    f(i, newline)
                end
                finished = false
                newline = false
                i = 0
            end
            first = false
            i *= 10
            i += c - UInt8('0')
        else
            error("Unknown character: $c")
        end
    end
    if !first
        f(i, true)
    end
end
