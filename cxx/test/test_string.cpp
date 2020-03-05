#include <doctest/doctest.h>
#include "../graphidx/utils/string.hpp"


TEST_CASE("ends_with: empty strings")
{
    CHECK(ends_with("", ""));
    CHECK(ends_with("a", ""));
    CHECK(!ends_with("", "a"));
}


TEST_CASE("ends_with: file endings")
{
    CHECK(ends_with("bla.gz", ".gz"));
    CHECK(!ends_with("bla.gzip", ".gz"));
}
