/**
   Some path helper functions
*/
#pragma once
#include <cstdio>
#include <fstream>
#include <stdexcept>
#include <string>


class path
{
public:
    static bool exists(const char *fname) {
        std::ifstream f (fname);
        return f.good();
    }


    static int remove(const char *fname) {
        const auto r = ::remove(fname);
        if (r != 0)
            throw std::runtime_error(
                std::string("Could not delete \"") + fname + "\" (code " +
                std::to_string(r) + ")");
        return r;
    }
    
    static void remove_if_exists(const char *fname) {
        if (path::exists(fname))
            path::remove(fname);
    }
};


struct FileCleaner
{
    const char *fname;
    ~FileCleaner() { path::remove_if_exists(fname); }
};



inline void
write_file(const char *fname, const char *data, const std::streamsize n)
{
    std::ofstream io (fname);
    if (io)
        io.write(data, n);
    else
        throw std::runtime_error(
            std::string("Could not write to \"") + fname + "\"");
}


struct WriteFile : public FileCleaner
{
    WriteFile(const char *fname, const char *data, const std::streamsize n) :
        FileCleaner {fname} {
        write_file(fname, data, n);
    }
};
