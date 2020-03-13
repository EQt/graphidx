#pragma once
#include <fstream>
#include <memory>

#include "bz2istream.hpp"
#include "gzistream.hpp"
#include "magic.hpp"


inline std::streambuf*
make_sbuf(const char *fname)
{
    if (is_gzip(fname)) {
        return &(new GZIStreamBuf())->open(fname);
    }
    if (is_bzip2(fname))
        return &(new BZ2IStreamBuf())->open(fname);
    return (new std::filebuf)->open(fname, std::ios_base::in);
}


class AutoIStream : public std::istream
{
    std::unique_ptr<std::streambuf> io;

public:
    AutoIStream(const char *fname) : std::istream(nullptr), io(make_sbuf(fname)) {
        rdbuf(io.get());
    }
};
