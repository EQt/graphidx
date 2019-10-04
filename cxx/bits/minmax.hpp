#pragma once
#include <algorithm>        // for std::min_element


using std::max;
using std::min;


template<typename float_ = float,
         typename int_ = int>
inline void
find_minmax(const float_ *y,
            const int_ n,
            float_ &y_min, float_ &y_max)
{
    y_min = *std::min_element(y, y + n);
    y_max = *std::max_element(y, y + n);
}
