module TestWeights

using Test
import GraphIdx

@testset "Weights                        " begin
    @test GraphIdx.Ones <: GraphIdx.Weights
    @test GraphIdx.Const <: GraphIdx.Weights
    @test GraphIdx.Vec <: GraphIdx.Weights
end

end
