#if __has_include(<bzlib.h>)

#include <doctest/doctest.h>
#include <fstream>
#include "../graphidx/io/path.hpp"
#include "../graphidx/io/bz2istream.hpp"
#include "../graphidx/io/autoistream.hpp"
#include "../graphidx/io/magic.hpp"


const unsigned char msg_bz2[] = {
    0x42, 0x5A, 0x68, 0x39, 0x31, 0x41, 0x59, 0x26,
    0x53, 0x59, 0x0D, 0x64, 0xB8, 0xC6, 0x00, 0x00,
    0x03, 0x51, 0x80, 0x00, 0x10, 0x40, 0x00, 0x26,
    0xE4, 0xD0, 0x40, 0x20, 0x00, 0x31, 0x00, 0xD0,
    0x01, 0x43, 0x46, 0x87, 0xEA, 0x9F, 0xA8, 0x88,
    0x4C, 0xB0, 0x36, 0x16, 0x85, 0xDC, 0x91, 0x4E,
    0x14, 0x24, 0x03, 0x59, 0x2E, 0x31, 0x80
};

constexpr char msg_txt[] = "hello graphidx\n";


TEST_CASE("magic: bz2")
{
    const char *fname = "msg.bz2";
    WriteFileClean _ (fname, (const char *) msg_bz2, sizeof(msg_bz2));
    CHECK(is_bzip2(fname));
    CHECK(!is_gzip(fname));
}


TEST_CASE("bz2istream: small msg")
{
    WriteFileClean _ ("msg.bz2", (const char *) msg_bz2, sizeof(msg_bz2));
    BZ2IStream io ("msg.bz2");
    CHECK(read_string(io, sizeof(msg_txt)) == msg_txt);
}


TEST_CASE("bz2istream: auto istream")
{
    WriteFileClean _ ("msg.bz2", (const char *) msg_bz2, sizeof(msg_bz2));
    AutoIStream io ("msg.bz2");
    CHECK(read_string(io, sizeof(msg_txt)) == msg_txt);
}

#endif
