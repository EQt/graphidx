module TestParseUInts

import GraphIdx.Io: parse_uints
using Test


function record_ints(io::IO)
    args = Vector{Tuple{UInt,Bool}}()
    parse_uints(io) do u::UInt, b::Bool
        push!(args, (u, b))
    end
    return args
end


@testset "parse_uints                    " begin
    @test record_ints(IOBuffer("")) == []
    @test record_ints(IOBuffer("0")) == [(0, true)]
    @test record_ints(IOBuffer("0120 3")) == [(120, false), (3, true)]
    @test record_ints(IOBuffer("0120 \n 3")) == [(120, true), (3, true)]
    @test record_ints(IOBuffer(", 0120 3")) == [(120, false), (3, true)]
    @test record_ints(IOBuffer(", 0120 , 3")) == [(120, false), (3, true)]
    @test record_ints(IOBuffer(", 0120 ,\n 3")) == [(120, true), (3, true)]
    @test record_ints(IOBuffer(", 0120 ,\n 3_000")) == [(120, true), (3000, true)]
end


end
