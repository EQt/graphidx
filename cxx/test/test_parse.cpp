#include <doctest/doctest.h>
#include <vector>
#include <sstream>
#include "../io/parse.hpp"


using Records = std::vector<std::tuple<uint64_t, bool>>;


Records
record_ints(std::istream &io)
{
    Records args;
    parse_uints(io, [&](uint64_t u, bool b) -> void { args.emplace_back(u, b); });
    return args;
}


Records
record_ints(const char *str)
{
    std::istringstream s (str);
    return record_ints(s);
}


TEST_CASE("istringstream")
{
    std::istringstream s ("");
    char c = 0;
    REQUIRE(s.good());
    REQUIRE(!s.eof());
    REQUIRE(!s.fail());
    REQUIRE(s.get() == -1);
    REQUIRE(s.get() == -1);
    REQUIRE(!s.get(c));
}


TEST_CASE("parse_uints")
{
    REQUIRE(record_ints("") == Records({}));
    REQUIRE(record_ints("0") == Records{{0, true}});
    REQUIRE(record_ints("3") == Records{{3, true}});
    REQUIRE(record_ints("0120 3") == Records({{120, false}, {3, true}}));
    REQUIRE(record_ints("0120 \n 3") == Records({{120, true}, {3, true}}));
    REQUIRE(record_ints(", 0120 3") == Records({{120, false}, {3, true}}));
    REQUIRE(record_ints(", 0120 , 3") == Records({{120, false}, {3, true}}));
    REQUIRE(record_ints(", 0120 ,\n 3") == Records({{120, true}, {3, true}}));
    REQUIRE(record_ints(", 0120 ,\n 3_000") == Records({{120, true}, {3000, true}}));
}

