
#if __has_include(<zlib.h>)
#include <doctest/doctest.h>
#include <fstream>
#include "../graphidx/io/autoistream.hpp"
#include "../graphidx/io/gzistream.hpp"
#include "../graphidx/io/magic.hpp"
#include "../graphidx/io/path.hpp"


const unsigned char msg_gz[] = {
    0x1F, 0x8B, 0x08, 0x08, 0x36, 0xBF, 0x68, 0x5E,
    0x00, 0x03, 0x6D, 0x73, 0x67, 0x2E, 0x74, 0x78,
    0x74, 0x00, 0xCB, 0x48, 0xCD, 0xC9, 0xC9, 0x57,
    0x48, 0x2F, 0x4A, 0x2C, 0xC8, 0xC8, 0x4C, 0xA9,
    0xE0, 0x02, 0x00, 0xCC, 0x85, 0x6F, 0x30, 0x0F,
    0x00, 0x00, 0x00,
};

constexpr char msg_txt[] = "hello graphidx\n";


TEST_CASE("magic: gz")
{
    const char *fname = "msg.gz";
    WriteFileClean _ (fname, (const char *) msg_gz, sizeof(msg_gz));
    CHECK(!is_bzip2(fname));
    CHECK(is_gzip(fname));
}


TEST_CASE("gzistream: small msg")
{
    WriteFileClean _ ("msg.gz", (const char *) msg_gz, sizeof(msg_gz));
    GZIStream io ("msg.gz");
    CHECK(read_string(io, sizeof(msg_txt)) == msg_txt);
}


TEST_CASE("gzistream: small msg tellg")
{
    for (size_t block_size : {1u, 2u, 3u, 7u, 10u}) {
        CAPTURE(block_size);
        WriteFileClean _ ("msg.gz", (const char *) msg_gz, sizeof(msg_gz));
        GZIStream io ("msg.gz", block_size);
        CHECK(io.tellg() == 0);
        char prefix[5] = {0};
        CHECK(io.read(prefix, 4).good());
        CHECK(std::string(prefix) == std::string(msg_txt, msg_txt+4));
        CHECK(io.tellg() == 4);
        prefix[3] = 0;
        CHECK(io.read(prefix, 3).good());
        CHECK(std::string(prefix) == std::string(msg_txt+4, msg_txt+7));
        CHECK(io.tellg() == 7);
    }
}


TEST_CASE("gzistream: auto istream")
{
    WriteFileClean _ ("msg.gz", (const char *) msg_gz, sizeof(msg_gz));
    AutoIStream io ("msg.gz");
    CHECK(read_string(io, sizeof(msg_txt)) == msg_txt);
}

#endif
