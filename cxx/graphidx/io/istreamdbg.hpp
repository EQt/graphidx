#pragma once
#include <iostream>
#include <istream>
#include <streambuf>


class IStreamDbgBuf : public std::streambuf
{
    std::streambuf *buf;
    std::ostream &cerr = std::cerr;

public:
    IStreamDbgBuf(std::istream &io) : buf(io.rdbuf()) {
        io.rdbuf(this);
    }

protected:
    virtual std::streambuf::int_type underflow() override {
        cerr << " underflow " << std::endl;
        return buf->sgetc();
    }

    virtual std::streampos seekoff(
        std::streamoff off,
        std::ios_base::seekdir way,
        std::ios_base::openmode which
    ) override {
        std::cerr << " seekpos ";
        return buf->pubseekoff(off, way, which);
    }

    virtual std::streampos seekpos(
        std::streampos sp,
        std::ios_base::openmode which
    ) override {
        std::cerr << " seekpos ";
        return buf->pubseekpos(sp, which);
    }

};


/**
   Debug how std::istream works by printing status messages to
   std::cerr
 */
class IStreamDbg : public std::istream
{
    IStreamDbgBuf buf;

public:
    IStreamDbg(std::istream &io) : std::istream(&buf), buf(io) { }
};
