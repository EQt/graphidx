#pragma once


template<typename float_ = float>
inline float_
clamp(float_ x, float_ a, float_ b)
{
    x = x > b ? b : x;
    x = x < a ? a : x; 
    return x;
}
