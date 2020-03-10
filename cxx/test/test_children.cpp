#include <doctest/doctest.h>
#include <set>
#include "../graphidx/idx/children.hpp"
#include "../graphidx/utils/perm.hpp"


TEST_CASE("children: generate5")
{
    // generate 5

    // ┌───┐
    // │ 5 │
    // └───┘
    //   │
    //   │
    //   ▼
    // ┌───┐
    // │ 0 │
    // └───┘
    //   ▲
    //   │
    //   │
    // ┌───┐
    // │ 1 │
    // └───┘
    //   ▲
    //   │
    //   │
    // ┌───┐
    // │ 2 │
    // └───┘
    //   ▲
    //   │
    //   │
    // ┌───┐
    // │ 3 │ ◀─────┐
    // └───┘       │
    //   ▲         │
    //   │         │
    //   │         │
    // ┌───┐       │
    // │ 4 │       │
    // └───┘       │
    //             │
    //             │
    //             │
    // ┌───┐     ┌───┐
    // │ 9 │ ──▶ │ 8 │
    // └───┘     └───┘
    //             ▲
    //             │
    //             │
    // ┌───┐     ┌───┐
    // │ 6 │ ──▶ │ 7 │
    // └───┘     └───┘
    const std::vector<int> parent = {0, 0, 1, 2, 3, 0, 7, 8, 3, 8};
    const size_t n = 10;
    CHECK(n == parent.size());

    std::vector<std::set<int>> cidx_expect (n);
    cidx_expect[0] = {1, 5};
    cidx_expect[1] = {2};
    cidx_expect[2] = {3};
    cidx_expect[3] = {4, 8};
    cidx_expect[8] = {7, 9};
    cidx_expect[7] = {6};

    ChildrenIndex cidx(parent);
    REQUIRE(parent.size() == cidx.size());
    CHECK(0 == cidx.root_node());
    if (false) {
        printf("children[3]:\n");
        for (const auto c : cidx[3]) {
            printf("c = %d\n", c);
        }
    }
    for (size_t i = 0; i < n; i++) {
        std::set<int> children(cidx[i]);
        INFO("i = " << i);
        CHECK(children == cidx_expect[i]);
    }
}


TEST_CASE("children: binary")
{
    const std::vector<int> parent = {0, 0, 0, 1, 1, 2, 2};
    const ChildrenIndex cidx (parent);
    REQUIRE(parent.size() == cidx.size());
    CHECK(0 == cidx.root_node());
    for (int i : {0, 1, 2}) {
        INFO("i = " << i);
        CHECK(2 == cidx[i].size());
    }
    for (int i = 3; i < (int) parent.size(); i++) {
        INFO("i = " << i);
        CHECK(0 == cidx[i].size());
    }
}


TEST_CASE("children: root1")
{
    const std::vector<int> parent =
        {6,  6,  6,  7,  7,  7,  8,  8,  8};
    const int root = 8;
    REQUIRE(9 == parent.size());
    REQUIRE(parent[root] == root);
    ChildrenIndex cidx (parent, root);
    REQUIRE(parent.size() == cidx.size());
    REQUIRE(root == cidx.root_node());

    const std::vector<int>
        idx_x ({1, 1, 1, 1, 1, 1, 1, 4, 7, 9}),
        value_x  ({8, 0, 1, 2, 3, 4, 5, 6, 7});

    CHECK(idx_x == cidx.index);
    CHECK(value_x == cidx.value);
}


TEST_CASE("children: root2")
{
    const std::vector<int> parent =
    //   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17
        {6,  6,  6,  7,  7,  7,  8,  8, 17, 15, 15, 15, 16, 16, 16, 17, 17, 17};
    const int root = 17;
    REQUIRE(18 == parent.size());
    REQUIRE(parent[root] == root);
    ChildrenIndex cidx (parent, root);
    REQUIRE(parent.size() == cidx.size());
    REQUIRE(root == cidx.root_node());
    REQUIRE(is_perm(cidx.value));

    const int c = 9;
    for (int i = 0; i < 6; i++) {
        CHECK(0 == cidx[i+0].size());
        INFO("i + c" << i+c);
        CHECK(std::set<int>() == std::set<int>(cidx[i+c]));
    }
    CHECK(std::set<int>({0+0, 1+0, 2+0}) == cidx[6+0]);
    CHECK(std::set<int>({0+c, 1+c, 2+c}) == cidx[6+c]);
    CHECK(std::set<int>({3+0, 4+0, 5+0}) == cidx[7+0]);
    CHECK(std::set<int>({3+c, 4+c, 5+c}) == cidx[7+c]);
    CHECK(std::set<int>({6+0, 7+0}) == cidx[8+0]);
    CHECK(std::set<int>({6+c, 7+c, 8}) == cidx[8+c]);
}
