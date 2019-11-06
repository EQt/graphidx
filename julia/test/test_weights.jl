module TestWeights

using Test
import GraphIdx

@testset "Weights                        " begin
    @test GraphIdx.UnitWeights <: GraphIdx.Weights
    @test GraphIdx.ConstantWeights <: GraphIdx.Weights
    @test GraphIdx.ArrayWeights <: GraphIdx.Weights
end

end
