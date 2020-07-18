const LC_CTYPE = 0
const LC_NUMERIC = 1
const LC_ALL = 6


function setlocale(l="en_US.utf8", lc=LC_NUMERIC)
    path = ccall(:setlocale, Cstring, (Cint, Cstring), lc, l)
    @assert path != C_NULL
    unsafe_string(path)
end


struct Lconv
    decimal_point::Ptr{Cchar}
    thousands_sep::Ptr{Cchar}
    grouping::Ptr{Cchar}
end


function Lconv(s::String = ".\0_\0\3\3\0")
    fcount = 3  # field count
    @assert count(r"\0", s) == fcount
    @assert s[end] == '\0'
    ms = ccall(:malloc, Ptr{Cchar}, (Cint,), length(s))
    unsafe_copyto!(ms, typeof(ms)(pointer(s)), length(s))
    Lconv((ms + u.offset for u in split(s, '\0')[1:fcount])...)
end


function setlconv(l::Lconv)
    error("setlconv does not work")
    lc = ccall(:localeconv, Ptr{Lconv}, ())
    unsafe_store!(lc, l)
end


function localeconv()
    lc = ccall(:localeconv, Ptr{Lconv}, ())
    unsafe_load(lc)
end


function Base.show(io::IO, l::Lconv)
    indent = 2
    println(io, "struct lconv {")
    for fn in fieldnames(Lconv)
        println(io, " "^indent, String(fn), " = ",  '"',
                unsafe_string(getfield(l, fn)),
                '"', ",")
    end
    println(io, "}")
end


function fmt_thousands(d::Integer)
    setlocale()
    local len = let n = ndigits(d)
        n + div(n-1, 3)
    end
    str = Vector{UInt8}(undef, len+1)
    i = ccall(:snprintf, Cint,
              (Ptr{UInt8}, Csize_t, Cstring, Cint), str, len+1, "%'d", d)
    @assert i == len "i=$i, len=$len"
    return String(str[1:len])
end
