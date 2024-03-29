precompile(Grid.compute_dirs, (Int64,))
precompile(Grid.GridGraph, (Int64, Int64, Int64))
precompile(Utils.setlocale, (String,))
precompile(Utils.fmt_thousands, (Int64,))
precompile(PrimMstMem, (IncidenceIndex,))
precompile(prim_mst_edges, (Vector{Float64}, Int64, PrimMstMem))
precompile(Tree.reset!, (Tree.ChildrenIndex, Vector{Int64}, Int64))
precompile(
    Base.sizehint!,
    (Utils.Heap.PriorityQueue{Int64,Float64,Base.Order.ForwardOrdering}, Int64),
)
precompile(
    Utils.Heap.percolate_down!,
    (Utils.Heap.PriorityQueue{Int64,Float64,Base.Order.ForwardOrdering}, Int64),
)
precompile(
    Utils.Heap.dequeue!,
    (Utils.Heap.PriorityQueue{Int64,Float64,Base.Order.ForwardOrdering},),
)
precompile(
    Utils.Heap.percolate_up!,
    (Utils.Heap.PriorityQueue{Int64,Float64,Base.Order.ForwardOrdering}, Int64),
)
precompile(
    Utils.Heap.enqueue!,
    (
        Utils.Heap.PriorityQueue{Int64,Float64,Base.Order.ForwardOrdering},
        Base.Pair{Int64,Float64},
    ),
)
precompile(
    prim_mst_edges,
    (
        Vector{Float64},
        Vector{Bool},
        Vector{Float64},
        Vector{Int64},
        IncidenceIndex,
        Vector{Int64},
        Utils.Heap.PriorityQueue{Int64,Float64,Base.Order.ForwardOrdering},
        Int64,
    ),
)
