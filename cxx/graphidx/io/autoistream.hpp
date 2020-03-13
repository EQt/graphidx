#pragma once
#include <fstream>
#include <memory>

#include "magic.hpp"
#if __has_include(<bzlib.h>)
#  include "bz2istream.hpp"
#endif
#if __has_include(<zlib.h>)
#  include "gzistream.hpp"
#endif


inline std::streambuf*
make_sbuf(const char *fname)
{
    if (is_gzip(fname)) {
#if __has_include(<zlib.h>)
        return &(new GZIStreamBuf())->open(fname);
#else
        throw std::invalid_argument("Not compiled with GZIP");
#endif

    }
    if (is_bzip2(fname)) {
#if __has_include(<bzlib.h>)
        return &(new BZ2IStreamBuf())->open(fname);
#else
        throw std::invalid_argument("Not compiled with BZIP2");
#endif
    }
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
