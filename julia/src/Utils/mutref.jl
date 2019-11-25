"""
Mutable array ref
"""
mutable struct MutRef{T} <: Ref{T}
    x::Vector{T}
    i::Int
end


@inline Base.getindex(b::MutRef) = b.x[b.i]
@inline Base.setindex!(b::MutRef, x) = (b.x[b.i] = x; b)
