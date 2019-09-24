#include <doctest/doctest.h>
#include <vector>
#include "../utils/vecalloc.hpp"


TEST_CASE("vecalloc: null")
{
    REQUIRE_THROWS_AS(VecAlloc<int>(nullptr, 5), std::invalid_argument);
}


TEST_CASE("vecalloc: with_null")
{
    const int *p = nullptr;
    {
        VecAlloc<const int> _ (&p, 5);
        REQUIRE(nullptr != p);
    }
    REQUIRE(nullptr == p);
}


TEST_CASE("std_remove_point: const_int")
{
    const int *p = nullptr;
    using T = typename std::remove_pointer<decltype(p)>::type;
    static_assert(std::is_same<std::remove_pointer<int*>::type,
                  int>::value, "strange...");
    static_assert(std::is_same<T, const int>::value, "strange...");
}


TEST_CASE("vecalloc: with_allocated")
{
    std::vector<int> hidden (5);
    const int *p = hidden.data();
    REQUIRE(hidden.data() == p);
    {
        using T = typename std::remove_pointer<decltype(p)>::type;
        VecAlloc<T> _ (&p, 5);
        REQUIRE(hidden.data() == p);
    }
    REQUIRE(hidden.data() == p);
}    
            
