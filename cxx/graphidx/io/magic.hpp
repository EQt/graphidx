#pragma once
#include <fstream>


/** Check whether a file is BZIP2 compressed */
inline bool
is_bzip2(const char *fname)
{
    std::ifstream f (fname, std::ifstream::binary);
    if (f) {
        constexpr int length = 3;
        char buf [length];
        f.read(buf, length);
        if (f) // successfully read
            return buf[0] == 'B' && buf[1] == 'Z' && buf[2] == 'h';
    }
    return false;
}


/** Check whether a file is GZIP compressed */
inline bool
is_gzip(const char *fname)
{
    std::ifstream f (fname, std::ifstream::binary);
    if (f) {
        constexpr int length = 2;
        char buf [length];
        f.read(buf, length);
        if (f) // successfully read
            return buf[0] == 0x1f && buf[1] == (char) 0x8b;
    }
    return false;
}
