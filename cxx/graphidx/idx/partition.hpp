#pragma once
#include "index.hpp"
#include "groupby.hpp"

template <typename int_>
struct PartitionIter;           // forward declaration


template <typename int_ = int>
class PartitionIndex : public Index<int_>
{
public:
    PartitionIndex(PartitionIndex &&) = default;
    PartitionIndex(const std::vector<int_> &ungrouped) :
        PartitionIndex(ungrouped.size(), ungrouped.data()) { }

    PartitionIndex(const size_t n, const int_ *ungrouped) {
        reset(n, ungrouped);
    }

    void reset(const size_t n, const int_ *ungrouped) {
        groupby(this->value,
                this->index,
                n,
                ungrouped);
    }

    /** Remove empty partitions */
    PartitionIndex<int_>& unique() {
        auto &index = this->index;
        size_t j = 1;
        for (size_t i = 0; i < this->size(); i++) {
            if (index[i] == index[i+1])
                continue;
            index[j] = index[i+1];
            j++;
        }
        index.resize(j);
        return *this;
    }

    /** Return iterator to the partition with largest number of elements */
    IndexIter<int_> largest() const {
        const auto &index = this->index;
        size_t max_i = 0;
        size_t max_size = 0;
        for (size_t i = 0; i < this->size(); i++) {
            const size_t i_size = size_t(index[i+1] - index[i]);
            if (i_size > max_size) {
                max_i = i;
                max_size = i_size;
            }
        }
        auto d = this->value.data();
        return {d + index[max_i+0], d + index[max_i+1]};
    }

    PartitionIter<int_> begin() const {
        return {this, 0};
    }

    PartitionIter<int_> end() const {
        return {this, this->size()};
    }
};


template<typename int_ = int>
struct PartitionIter
{
    const PartitionIndex<int_> *p;
    size_t i;

    PartitionIter(const PartitionIndex<int_> *p, size_t j) :
        p(p), i(j) { }

    IndexIter<int_> operator*() const {
        const int_
            *start = p->value.data() + p->index[i+0],
            *stop  = p->value.data() + p->index[i+1];

        return {start, stop};
    }

    PartitionIter<int_>& operator++() {
        this->i++;
        return *this;
    }

    bool operator==(const PartitionIter<int_> &other) const {
        return other.i == this->i;
    }
};
