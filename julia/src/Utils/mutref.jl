"""
Mutable reference to an array element.
In Julia v1.4 we had some performance regressions problems that could be solved using
a `MutRef`.
"""
mutable struct MutRef{T} <: Ref{T}
    x::Vector{T}
    i::Int
end


@inline Base.getindex(b::MutRef) = b.x[b.i]
@inline Base.setindex!(b::MutRef, x) = (b.x[b.i] = x; b)
