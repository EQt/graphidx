/**

   Inspiring codes

   https://stackoverflow.com/q/39017752
   http://www.mathematik.uni-kassel.de/~fifr/fossils/cpp-util
*/
#pragma once
#include <algorithm>    // std::min
#include <cstring>      // memcpy
#include <streambuf>
#include <istream>
#include <vector>

#include <zlib.h>


class GZIStreamBuf : public std::streambuf
{
public:
    GZIStreamBuf(size_t bs = 8192) : buf(bs) {
        setp(buf.data(), buf.data() + (buf.size() - 1));
        setg(buf.data() + 4, buf.data() + 4, buf.data() + 4);
    }

    GZIStreamBuf& open(const char *fname) {
        gzfile = gzopen(fname, "rb");
        if (!gzfile)
            throw std::runtime_error(std::string("gzopen \"") + fname + "\"");
        return *this;
    }

    void close() {
        if (gzfile) {
            if (gzclose(gzfile) != Z_OK)
                throw std::runtime_error("gzclose");
            gzfile = nullptr;
        }
    }

    virtual ~GZIStreamBuf() {
        close();
    }

    GZIStreamBuf& operator=(GZIStreamBuf const &) = delete;

    GZIStreamBuf& operator=(GZIStreamBuf &&) = delete;

    GZIStreamBuf(GZIStreamBuf &&) = delete;

    GZIStreamBuf(GZIStreamBuf const&) = delete;

protected:
    virtual std::streambuf::int_type underflow() override {
        // is read position before end of buffer?
        if (gptr() >= egptr()) {
            if (!gzfile) return EOF;

            const size_t n_putback = (std::min)(size_t(gptr() - eback()), size_t(4));
            memcpy(buf.data() + (4 - n_putback), gptr() - n_putback, n_putback);

            // actual decompression
            int num = gzread(gzfile, buf.data() + 4, (unsigned) buf.size() - 4);
            if (num <= 0)
                return EOF;

            // reset buffer pointers
            setg(buf.data() + (4 - n_putback),  // beginning of putback area
                 buf.data() + 4,                // read position
                 buf.data() + 4 + num);         // end of buffer
        }
        return traits_type::to_int_type(*gptr());  // return next character
    }


    // https://stackoverflow.com/a/44712099
    virtual std::streampos seekoff(
        std::streamoff off,
        std::ios_base::seekdir way,
        std::ios_base::openmode
    ) override {
        if (this->gptr() - this->eback() < -off
            || this->egptr() - this->gptr() < off
            || way != std::ios_base::cur) {
            return pos_type(off_type(-1));
        }
        auto dir = (way == std::ios_base::cur) ? SEEK_CUR :
            (way == std::ios_base::beg) ? SEEK_SET : SEEK_END;
        gzseek(gzfile, off, dir);
        const auto base = gztell(gzfile);
        return base + (this->gptr() - this->egptr());
    }

    virtual std::streampos seekpos(
        std::streampos sp,
        std::ios_base::openmode which
    ) override {
        return seekoff(sp, std::ios_base::beg, which);
    }

private:
    gzFile gzfile = nullptr;
    std::vector<char> buf = {};
};


class GZIStream : public std::istream
{
public:
    GZIStream(const char *fname, size_t bs = 8192) :
        std::istream(&buf_), buf_(std::max(bs + 4, size_t(8))) { buf_.open(fname); }

private:
    GZIStreamBuf buf_;
};
