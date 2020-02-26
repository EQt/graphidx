#include <doctest/doctest.h>

#include "../graphidx/idx/grid.hpp"


TEST_CASE("GridIndex: grid_3x2")
{
    GridIndex g(3, 2);
}


TEST_CASE("GridIndex: binnotation")
{
    REQUIRE(9 == 0b1001);
    REQUIRE(8 == 0b1000);
    REQUIRE(0 == 0b0000);
}


TEST_CASE("GridIndex: kinds")
{
    REQUIRE(2 == ML);
    REQUIRE(9 == LR);
}


/*
  >>> np.array(range(6)).reshape(3, 2, order='F')
  array([[0, 3],
         [1, 4],
         [2, 5]])
*/
TEST_CASE("GridIndex: kind_3x2")
{
    GridIndex g {3, 2};
    REQUIRE(LL == g.kind(0 + 0*3));
    REQUIRE(LR == g.kind(0 + 1*3));
    REQUIRE(MR == g.kind(1 + 1*3));
    REQUIRE(RR == g.kind(2 + 1*3));
}


TEST_CASE("GridIndex: num_neighbors")
{
    REQUIRE(4 == num_neighbors(MM));
    {
        const int k1 = 0b10;
        {
            const int k2 = 0;
            REQUIRE(3 == num_neighbors(GridPointKind(k1 << 2 | k2)));
            REQUIRE(3 == num_neighbors(GridPointKind(k2 << 2 | k1)));
        }
    }
    {
        const int k1 = 0b01;
        {
            const int k2 = 0;
            REQUIRE(3 == num_neighbors(GridPointKind(k1 << 2 | k2)));
            REQUIRE(3 == num_neighbors(GridPointKind(k2 << 2 | k1)));
        }
    }
}
