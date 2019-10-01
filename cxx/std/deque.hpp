#pragma once
#include <vector>


/***
 *  Double ended queue.
**/
template <typename E>
struct DeQue
{
private:
    std::vector<E> _e;
    size_t _front = 1, _back = 0;

public:
    DeQue() {}
    DeQue(std::initializer_list<E> l) : _e(l), _front(0), _back(l.size()-1) { }
    DeQue(size_t n) { reserve(n); }

    /// allocate space for 2*n elements; resetting to the middle
    void reserve(const size_t n) { _e.reserve(2*n); _front = n; _back = n-1; }

    /// first or last element (depending on forward)
    template <bool forward = true>
    const E& front() const { return forward ? _e[_front] : _e[_back]; }

    /// first or last element (depending on forward)
    template <bool forward = true>
    #if __cplusplus >= 201402L
    [[deprecated]]
    #endif
    const E& peek() const { return this->front<forward>(); }

    /// oposite to ::peek()
    template <bool forward = true>
    const E& back() const { return forward ? _e[_back] : _e[_front]; }

    /// remove first/last element
    template <bool forward = true>
    E pop() { return forward ? _e[_front++] : _e[_back--]; }

    /// append an element to _front/_back of the queue
    template <bool forward = true>
    void push(E x) { if (forward) _e[--_front] = x; else _e[++_back] = x; }

    /// is the queue empty?
    operator bool() const { return _front <= _back; }

    /// number of elements present at the moment
    size_t size() const { return _back - _front + 1; }

    /// number of elements that could fit in
    size_t capacity() const { return _e.capacity(); }
};
