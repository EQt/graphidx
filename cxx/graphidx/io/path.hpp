/**
   Some path helper functions
*/
#pragma once
#include <cstdio>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>


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


template <typename T = char>
std::vector<T>
read_file(std::istream &file, const size_t size)
{
    std::vector<T> buffer;
    buffer.resize(size_t(size) / sizeof(T));
    if (file.read(reinterpret_cast<char*>(buffer.data()), std::streamsize(size)))
        return buffer;
    throw std::runtime_error(std::string("error in read: only ") +
                             std::to_string(file.gcount()) + " of " +
                             std::to_string(size) + " read");
}


template <typename T = char>
std::vector<T>
read_file(const char *fname)
{
    std::ifstream file (fname, std::ifstream::binary | std::ifstream::ate);
    if (file) {
        const std::streamsize size = file.tellg();
        if (size <= 0)
            throw std::runtime_error(
                std::string("read_file: size = ") + std::to_string(size));
        file.seekg(0, std::ios::beg);
        return read_file(file, size_t(size));
    }
    throw std::runtime_error("error while opening");
}


std::string
read_string(std::istream &file, const size_t size)
{
    std::vector<char> buffer (size, '\0');
    if (file.read(reinterpret_cast<char*>(buffer.data()), std::streamsize(size-1)))
        return {buffer.data()};
    throw std::runtime_error(std::string("error in read: only ") +
                             std::to_string(file.gcount()) + " of " +
                             std::to_string(size-1) + " read");
}    
