#pragma once
#include <doctest/doctest.h>
#include <sstream>
#include <vector>


namespace doctest {

template <typename T>
struct StringMaker<std::vector<T>>
{
    static String convert(const std::vector<T> &in)
    {
        std::ostringstream oss;

        oss << "asdf";
        for (const auto &v : in)
            oss << v << ", ";
        oss << "}";

        return oss.str().c_str();
    }
};

} // namespace doctest
