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


template<typename float_ = float>
[[deprecated]]
inline float_
clip(float_ x, float_ a, float_ b)
{
    /*
    if (x >= b)
        return b;
    if (x <= a)
        return a;
    return x;
    */
    return x >= b ? b : (x <= a ? a : x);
}
