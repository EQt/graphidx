module TestVarArgs
using Test

f() = println("()")
f(a::Vararg{T,N}) where {T,N} = println("v", tuple(typeof(a).types...))
f(a::Tuple) =  println(tuple(typeof(a).types...))
f(a...) = println(tuple(typeof(a).types...), "...")

end
