module TestWeights

using Test
import GraphIdx

@testset "Weights                        " begin
    @test GraphIdx.Ones <: GraphIdx.Weights
    @test GraphIdx.Const <: GraphIdx.Weights
    @test GraphIdx.Vec <: GraphIdx.Weights
end


@testset "Weights: is_const              " begin
    @test GraphIdx.is_const(GraphIdx.Ones)
    @test GraphIdx.is_const(GraphIdx.Ones{Int8})
    let c = GraphIdx.Weights(Float64)
        @test GraphIdx.is_const(c)
    end

    @test GraphIdx.is_const(GraphIdx.Const)
    @test GraphIdx.is_const(GraphIdx.Const{Float64})
    let c = GraphIdx.Weights(2.0)
        @test GraphIdx.is_const(c)
    end

    @test !GraphIdx.is_const(GraphIdx.Vec)
    @test !GraphIdx.is_const(GraphIdx.Vec{Float64})
    let c = GraphIdx.Weights([2.0, 1.0])
        @test !GraphIdx.is_const(c)
    end
end

end
