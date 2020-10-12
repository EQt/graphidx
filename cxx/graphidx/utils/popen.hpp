#pragma once

#include <cstdio>
#include <cstdint>
#include <cstdlib>      /* for errno() */
#include <vector>
#include <string>
#include <stdexcept>


/* Microsoft Compiler:
   https://msdn.microsoft.com/en-us/en-en/library/96ayss4b.aspx */
#ifdef _MSC_VER
#  define popen  _popen
#  define pclose _pclose
#endif


template <typename T>
std::vector<T>
reinterpret_vector(std::vector<uint8_t> &&in)
{
    if (in.size() % sizeof(T) != 0)
        throw std::runtime_error(std::string("Wrong size: ") +
                                 std::to_string(in.size()));
    std::vector<T> out((T*)(in.data()),
                       (T*)(in.data() + in.size()));
    return out;
}


class Popen
{
public:
    Popen(const std::string &cmd, const char *mode = "r")
        : Popen(cmd.c_str(), mode) {}
    Popen(const char *cmd, const char *mode = "r") {
        f = popen(cmd, mode);
        if (f == nullptr) {
            std::string msg = std::string("Could not start process `")
              + cmd + "`";
            throw std::runtime_error(msg);
        }
    }
    ~Popen() {
        if (f != nullptr)
            pclose(f);
    }


    template <typename T = uint8_t>
    size_t
    readinto(std::vector<T> &buf, const std::size_t delta = 4096) {
        std::size_t cursor = 0;
        std::size_t n;
        while ((n = fread(buf.data()+cursor, sizeof(T), buf.size()-cursor, f)) > 0) {
            cursor += n;
            
            if (cursor == buf.size()) {
                if (buf.capacity() == buf.size()) {
                    buf.reserve(buf.size() + delta);
                }
                buf.resize(buf.capacity());
            }
        }
        if (cursor == 0) {
            int status = pclose(f);
            f = nullptr;
// https://www.gnu.org/software/libc/manual/html_node/Process-Completion-Status.html
            throw std::runtime_error("read failed: "
                                     + std::to_string(status)
                                     + " >> "
                                     + std::to_string(WEXITSTATUS(status))
                                     + " =? "
                                     + std::to_string(EINVAL)
                                     + " =? "
                                     + std::to_string(errno));
        }
        buf.resize(cursor);
        return buf.size();
    }


    std::vector<uint8_t> read(const std::size_t delta = 4096) {
        // http://stackoverflow.com/a/37236189
        std::vector<uint8_t> buf (delta);
        this->readinto(buf, delta);
        return buf;
    }


    template <typename T>
    std::vector<T> read_cast(std::size_t delta = 4096) {
        auto buf = read(delta);
        return reinterpret_vector<T>(std::move(buf));
    }


    /** Read into a string.*/
    std::string read_str(std::size_t delta = 4096) {
        auto buf = read(delta);
        char *data = reinterpret_cast<char*>(buf.data());
        std::string s (data, buf.size());
        return std::string(std::move(s));
    }

    /** Same as read_str but with newlines chomped.*/
    std::string chomp(std::size_t delta = 4096) {
        auto s = read_str(delta);
        auto end_pos = s.find_last_not_of(" \t\n\r");
        s.resize(end_pos+1);
        return s;
    }

private:
    std::FILE* f = nullptr;
};
