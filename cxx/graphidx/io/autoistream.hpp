#pragma once
#include <fstream>
#include <memory>

#include "magic.hpp"
#if __has_include(<bzlib.h>)
#  include "bz2istream.hpp"
#  define HAVE_BZIP2 1
#else
#  define HAVE_BZIP2 0
#endif
#if __has_include(<zlib.h>)
#  include "gzistream.hpp"
#  define HAVE_GZIP 1
#else
#  define HAVE_GZIP 0
#endif


inline std::streambuf*
make_sbuf(const char *fname, const size_t buf_size)
{
    if (is_gzip(fname)) {
#if __has_include(<zlib.h>)
        return &(new GZIStreamBuf(buf_size))->open(fname);
#else
        throw std::invalid_argument("Not compiled with GZIP");
#endif

    }
    if (is_bzip2(fname)) {
#if __has_include(<bzlib.h>)
        return &(new BZ2IStreamBuf(buf_size))->open(fname);
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
    AutoIStream(const char *fname, const size_t buf_size = 8192) :
        std::istream(nullptr), io(make_sbuf(fname, buf_size)) { rdbuf(io.get()); }
};
