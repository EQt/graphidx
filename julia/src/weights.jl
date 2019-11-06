abstract type Weights{F<:Real} end

"""
Represent weighting that is indexable and callable where each index has the same value.

Usually, weights are assumed to be positive!

## Example
```jldoctest
julia> w = GraphIdx.ConstantWeights(5.4);

julia> w(3)
5.4

julia> w[3]
5.4
```
"""
struct ConstantWeights{F<:Real} <: Weights{F}
    w::F
end


(c::ConstantWeights{F})(_::Integer) where {F} = c.w

Base.getindex(c::ConstantWeights{F}, _::Integer) where {F} = c.w



"""
Weighting of nodes where every weight can be different.
The actual value of a node can be accessed via call - or index syntax.

## Example
```jldoctest
julia> w = GraphIdx.ArrayWeights([0.1, 0.2, 0.3]);

julia> w(3)
0.3

julia> w[1]
0.1
```
"""
struct ArrayWeights{F<:Real} <: Weights{F}
    a::Vector{F}
end


(c::ArrayWeights{F})(i::Integer) where {F} = c.a[i]

Base.getindex(c::ArrayWeights{F}, i::Integer) where {F} = c.a[i]


struct UnitWeights{F<:Real} <: Weights{F} end

@inline Base.getindex(::UnitWeights{F}, ::Integer) where {F} = one(F)

@inline (u::UnitWeights{F})(::Integer) where {F} = u[1]

create_weights(::Type{F}) where {F<:Real} = UnitWeights{F}()
create_weights(w::F) where {F<:Real} = ConstantWeights(w)
create_weights(w::Vector{F}) where {F<:Real} = ArrayWeights(w)
