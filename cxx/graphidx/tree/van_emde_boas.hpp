#pragma once
#include "../bits/clz.hpp"


/** Binary van Emde Boas Layout from an Inorder traverse (sorted nodes).

   @param[out]  a_out   Array to store the output.
   @param[in]   a_in    Binary inorder (as produced by `binary_inorder`)
   @param[in]   height  Height of the **complete binary** tree.
   @param[in]   step    Distance between siblings on the lowest level.
                        Start with `step == 1`.


   Copied and adapted from
   Frederik Rønn: "Cache-Oblivious Searching and Sorting", Master's Thesis,
   Department of Computer Science University of Copenhagen, 2003. (Page 76)

   See also:
     [github.com:sriravic/FAST-Van-Emde-Boas](https://github.com/sriravic/FAST-Van-Emde-Boas/blob/master/van-emde-boas.cpp)

*/
template<typename T>
void binveb_from_inord(T *a_out,
                       const T *a_in,
                       const size_t height,
                       const size_t step = 1)
{
    const size_t bottom_height = height == 2 ? 1 : hyperfloor(height-1);
    const size_t top_height    = height - bottom_height;
    const size_t bottom_size   = (size_t(1) << bottom_height) -1;
    const size_t top_size      = (size_t(1) << top_height) -1;

    if (top_height == 1 && bottom_height == 1) {
        a_out[1] = a_in[0];
        a_out[0] = a_in[1*step];
        a_out[2] = a_in[2*step];
        return;
    }
    if (top_height == 1) {
        a_out[0] = a_in[bottom_size*step];
    } else {
        binveb_from_inord(a_out,
                          a_in + bottom_size*step,
                          top_height,
                          bottom_size*step + step);
    }
    for (size_t i = 0; i <= top_size; i++) {
        binveb_from_inord(a_out + top_size + i*bottom_size,
                          a_in + step * (i + i*bottom_size),
                          bottom_height,
                          step);
    }
}
