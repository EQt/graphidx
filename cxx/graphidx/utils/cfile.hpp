/** File utility functions */
#pragma once
#include <fstream>
#include <vector>
#include <stdexcept>


/** Read file content into a vector */
template <typename T = char>
std::vector<T>
readfile(const char *fname)
{
    std::ifstream file (fname, std::ifstream::binary | std::ifstream::ate);
    if (file) {
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        std::vector<T> buffer;
        buffer.resize(size / sizeof(T));
        if (file.read(reinterpret_cast<char*>(buffer.data()), size))
            return buffer;
        throw std::runtime_error(std::string("error in read: only ") +
                                 std::to_string(file.gcount()) + " of " +
                                 std::to_string(size) + " read");
    } else {
        throw std::runtime_error("error while opening");
    }
}
