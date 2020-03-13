#pragma once
#include <fstream>
#include <memory>

#include "bz2istream.hpp"
#include "gzistream.hpp"
#include "magic.hpp"


inline std::istream*
make_istream(const char *fname)
{
    if (is_gzip(fname))
        return new GZIStream(fname);
    if (is_bzip2(fname))
        return new BZ2IStream(fname);
    return new std::ifstream(fname);
}


class AutoIStream : public std::istream
{
    std::unique_ptr<std::istream> io;

public:
    AutoIStream(const char *fname) : io(make_istream(fname)) {
        rdbuf(io.get()->rdbuf());
    }
};
