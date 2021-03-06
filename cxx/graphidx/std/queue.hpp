#pragma once
#include <cstddef>      // size_t
#include <string>       // std::to_string
#include <stdexcept>    // std::invalid_argument

#ifndef RING_BUFFER
#  define RING_BUFFER 0
#endif

/** LIFO (last in first out) data structure.

    Similar to
    [std::queue](http://www.cplusplus.com/reference/queue/queue)
    but with pre-allocated memory.
*/
template<typename T = int>
class queue
{
#ifdef DOCTEST_REQUIRE
public:
#endif

    size_t
        max = 0,        // maximum number of elements
        n = 0;          // number of inserted elements
    size_t head = 0;    // front element's index
    size_t tail = 0;    // index where to push the next element
    T *e = nullptr;     // elements

public:
    queue() { }

    queue(const size_t max_n) { reserve(max_n); }

    ~queue() { free(); }

    void free() { if (e) delete[] e; e = nullptr; }

    inline void clear() { head = tail = n = 0; }

    inline void reserve(size_t max_n) {
        if (max_n <= 0)
            throw std::invalid_argument(std::string("queue::reserve(") +
                                        std::to_string(n) + ")");
        if (this->max < max_n) {
            free();
            e = new T[max_n];
            this->max = max_n;
            clear();
        }
    }

    inline void push(T x) {
        e[tail++
#if RING_BUFFER
          % max
#endif
         ] = x;
        n++;
    }

    inline T front() const { return e[head]; }

    inline void pop() { head = (head + 1)
#if RING_BUFFER
            % max
#endif
            ; n--; }

    inline bool empty() const { return n == 0; }

    inline size_t size() const { return n; }

    inline size_t capacity() const { return max; }
};

