abstract type Weights{F<:Real} end

# (u::W)(i::Integer) where {W<:Weights} = u[i]

"""
Uniform one weights.

## Example
```jldoctest
julia> w = GraphIdx.Ones{Int}(); w[3]
1

julia> w[5] = -2; w[5]
1
```
"""
struct Ones{F<:Real} <: Weights{F}
end

@inline Base.getindex(::Ones{F}, ::Integer) where {F} = one(F)
@inline Base.setindex!(::Ones{F}, ::F, ::Integer) where {F} = one(F)
Base.collect(w::Ones{F}, n::Integer) where {F} = ones(F, n)


"""
Represent weighting that is indexable and callable where each index has the same value.

Usually, weights are assumed to be positive!

## Example
```jldoctest
julia> w = GraphIdx.Const(5.4);

julia> w[3]
5.4

julia> w[5] = 2.1; w[5]
5.4
```
"""
struct Const{F<:Real} <: Weights{F}
    w::F
end

@inline Base.getindex(c::Const{F}, ::Integer) where {F} = c.w
@inline Base.setindex!(c::Const{F}, ::F, ::Integer) where {F} = c.w
Base.collect(w::Const{F}, n::Integer) where {F} = fill(w.w, n)


"""
Weighting of nodes where every weight can be different.
The actual value of a node can be accessed via call - or index syntax.

## Example
```jldoctest
julia> w = GraphIdx.Vec([0.1, 0.2, 0.3]);

julia> w[3]
0.3

julia> w[1]
0.1

julia> w[1] = 0; w[1]
0.0
```
"""
struct Vec{F<:Real} <: Weights{F}
    a::Vector{F}
end


@inline Base.getindex(v::Vec{F}, i::Integer) where {F} = v.a[i]
@inline Base.setindex!(v::Vec{F}, c::W, i::Integer) where {F, W} = (v.a[i] = F(c))
@inline Base.collect(w::Vec{F}, n::Integer) where {F} = (@assert n == length(w.a); a)

Weights(::Type{F}) where {F<:Real} = Ones{F}()
Weights(w::F) where {F<:Real} = Const(w)
Weights(w::Vector{F}) where {F<:Real} = Vec(w)

@deprecate create_weights(x) Weights(x)
