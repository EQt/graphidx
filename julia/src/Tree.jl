"""
Bundle functions regarding (rooted) tree graphs.
"""
module Tree

include("Tree/root.jl")

"""
A rooted tree represanted by its parent vector, i.e. if `u` is the parent node of `v` then `parent[v] == u`.
We always require that root is its own parent (`parent[root] == root`) and `length(parent) == n`.

Often you might want to have a [`ChildrenIndex`](@ref).
For debugging, the [`hierarchy`](@ref) function might be useful.
"""
struct RootedTree
    root::Int
    parent::Vector{Int}
end


RootedTree(parent::Vector{Int}) =
    RootedTree(find_root(parent), parent)


Base.length(t::RootedTree) =  length(t.parent)


struct WeightedTree{W}
    tree::RootedTree
    lam::W
end



include("Tree/degrees.jl")
include("Tree/children.jl")
include("Tree/dfs.jl")
include("Tree/lca.jl")
include("Tree/inorder.jl")
include("Tree/hierarchy.jl")

end
