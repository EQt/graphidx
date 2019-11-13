const LC_ALL = 6


function setlocale(l="")
    path = ccall(:setlocale, Cstring, (Cint, Cstring), LC_ALL, l)
    unsafe_string(path)
end


function fmt_thousands(d::Integer)
    setlocale()
    local len = let n = ndigits(d)
        n + div(n-1, 3)
    end
    str = Vector{UInt8}(undef, len+1)
    i = ccall(:snprintf, Cint,
              (Ptr{UInt8}, Csize_t, Cstring, Cint), str, len+1, "%'d\n", d)
    @assert i == len+1
    return String(str[1:len])
end
