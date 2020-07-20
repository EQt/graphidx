"""All graphs should inherit from this base class"""
abstract type Graph end

const Edge{I<:Integer} = Tuple{I, I}
