#pragma once
#include <string>


inline bool
ends_with(const std::string &str, const std::string &end)
{
    return str.size() >= end.size() &&
        str.compare(str.size() - end.size(), end.size(), end) == 0;
}
