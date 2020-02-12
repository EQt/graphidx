#pragma once
#include <vector>
#include <initializer_list>

/**
   A vector replacement that does not initialize on resize/reserve.
*/
template <typename T>
struct uvector
{
    uvector() { }

    uvector(size_t n) { resize(n); }

    uvector(uvector &&other) {
        this->n = other.n;
        if (this->elem) delete[] this->elem;
        this->elem = other.elem;
        other.elem = nullptr;
        other.n = 0;
    }

    /** Avoid implicit copy */
    uvector(const uvector<T> &other) = delete;

    /** Avoid implicit copy */
    uvector& operator=(const uvector<T> &other) = delete;

    uvector(std::initializer_list<T> l) {
        resize(l.size());
        std::copy(l.begin(), l.end(), begin());
    }

    uvector<T> copy() const {
        uvector<T> r (size());
        std::copy(begin(), end(), r.begin());
        return r;
    }

    inline void resize(size_t n) {
        if (this->n != n) {
            if (elem) delete[] elem;
            elem = new T[n];
            this->n = n;
        }
    }

    inline void reserve(size_t n) { resize(n); }

    size_t size() const { return n; }

    T& operator[](size_t i) { return elem[i]; }

    const T& operator[](size_t i) const { return elem[i]; }

    ~uvector() { if (elem) delete[] elem; }

    T* data() const { return elem; }

    T* begin() { return data(); }

    T const* begin() const { return data(); }

    T const* end() const { return data() + n; }

    bool operator==(const std::vector<T> &other) const {
        return other.size() == this->size() &&
            std::equal(begin(), end(), other.begin());
    }

    bool operator==(const uvector<T> &other) const {
        return other.size() == this->size() &&
            std::equal(begin(), end(), other.begin());
    }

private:
    size_t n = 0;
    T *elem = nullptr;
};


template <typename T>
bool operator==(const std::vector<T> &a, const uvector<T> &b)
{
    return b == a;
}
