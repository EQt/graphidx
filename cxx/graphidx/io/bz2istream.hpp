/**

   Inspiring codes

   https://stackoverflow.com/q/39017752
   http://www.mathematik.uni-kassel.de/~fifr/fossils/cpp-util
   https://www.codeproject.com/KB/stl/zipstream/bzip2stream_src.zip
*/
#pragma once
#include <algorithm>    // std::min
#include <cstring>      // memcpy
#include <streambuf>
#include <istream>
#include <vector>

#include <bzlib.h>


class BZ2IStreamBuf : public std::streambuf
{
public:
    BZ2IStreamBuf(size_t bs = 8192) : buf(bs) {
        setp(buf.data(), buf.data() + (buf.size() - 1));
        setg(buf.data() + 4, buf.data() + 4, buf.data() + 4);
    }

    BZ2IStreamBuf& open(const char *fname) {
        bzfile = BZ2_bzopen(fname, "rb");
        if (!bzfile)
            throw std::runtime_error(std::string("bz_open \"") + fname + "\"");
        return *this;
    }

    void close() {
        if (bzfile) {
            int errnum;
            BZ2_bzclose(bzfile);
            auto msg = BZ2_bzerror(bzfile, &errnum);
            if (errnum != BZ_OK)
                throw std::runtime_error(std::string("bzclose: ") + msg);
        }
    }

    virtual ~BZ2IStreamBuf() {
        close();
    }

    BZ2IStreamBuf& operator=(BZ2IStreamBuf const &) = delete;

    BZ2IStreamBuf& operator=(BZ2IStreamBuf &&) = delete;

    BZ2IStreamBuf(BZ2IStreamBuf &&) = delete;

    BZ2IStreamBuf(BZ2IStreamBuf const&) = delete;

protected:
    /* Starting point: Josuttis' implementation
       http://www.josuttis.com/cppcode/fdstream.hpp.html
    */
    virtual std::streambuf::int_type underflow() override {
        // is read position before end of buffer?
        if (gptr() >= egptr()) {
            if (!bzfile) return EOF;

            const size_t n_putback = (std::min)(size_t(gptr() - eback()), size_t(4));
            memcpy(buf.data() + (4 - n_putback), gptr() - n_putback, n_putback);

            int num;
            {   // actual decompression
                int bzerror;
                num = BZ2_bzRead(&bzerror, bzfile,
                                 buf.data() + 4,
                                 int(buf.size() - 4));
                if (!(bzerror == BZ_OK || (bzerror == BZ_STREAM_END && num > 0)))
                    return EOF;
            }

            // reset buffer pointers
            setg(buf.data() + (4 - n_putback),  // beginning of putback area
                 buf.data() + 4,                // read position
                 buf.data() + 4 + num);         // end of buffer
        }
        return traits_type::to_int_type(*gptr());  // return next character
    }

private:
    BZFILE *bzfile = nullptr;
    std::vector<char> buf = {};
};


class BZ2IStream : public std::istream
{
public:
    BZ2IStream(const char *fname, size_t bs = 8192) :
        std::istream(&buf_), buf_(std::max(bs + 4, size_t(8)))  { buf_.open(fname); }

private:
    BZ2IStreamBuf buf_;
};
