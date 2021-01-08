#pragma once
#include <algorithm>	// std::max_element
#include <tuple>

#include "index.hpp"


/**
   In contrast to a general neighbor `Index`, an `IncidenceIndex` is able to yield,
   given a node `v`, the neighbor nodes `u` as well as the edge index `eidx` connecting
   `v` and `u`.
*/
template <typename int_ = int>
struct IncidenceIndex : public Index<int_, std::tuple<int_, int_>>
{
    using val_t = std::tuple<int_, int_>;

    size_t num_edges() const { return this->value.size() / 2; }
    size_t num_nodes() const { return this->size(); }

    IncidenceIndex(
	uvector<val_t> &&value,  std::vector<int_> &&index)
	: Index<int_, val_t>{
	    std::forward<uvector<val_t>>(value), std::forward<std::vector<int_>>(index)} { }

    IncidenceIndex(const size_t m, const int_ *head, const int_ *tail, size_t n = 0)
        { reset(m, head, tail, n); }

    IncidenceIndex(
	const std::vector<int_> &head, const std::vector<int_> &tail, size_t n = 0)
	: IncidenceIndex(head.size(), head.data(), tail.data(), n) { }

    IncidenceIndex& reset(const size_t m, const int_ *head, const int_ *tail, size_t n = 0);
};


template <typename int_>
IncidenceIndex<int_>&
IncidenceIndex<int_>::reset(const size_t m, const int_ *head, const int_ *tail, size_t n)
{
    auto &value = this->value;
    auto &index = this->index;
    if (head == nullptr)
	throw std::runtime_error("head == nullptr");
    if (tail == nullptr)
	throw std::runtime_error("tail == nullptr");
    if (n <= 0) {                   // number of nodes
	n = size_t(*std::max_element(head, head + m));
	n = std::max(n, size_t(*std::max_element(tail, tail + m)));
	n++;
    }
    value.resize(2*m);
    index.assign(n+1, 0);
    for (size_t i = 0; i < m; i++) {   // compute degree
	index[size_t(head[i]+1)]++;
	index[size_t(tail[i]+1)]++;
    }
    Index<int_, val_t>::shift_acc();
    for (size_t i = 0; i < m; i++) {
	const int_
	    u = head[i],
	    v = tail[i];
	value[size_t(index[size_t(u+1)]++)] = {v, i};
	value[size_t(index[size_t(v+1)]++)] = {u, i};
    }
    if (index[n] != int_(2*m)) {
	std::cerr << index << std::endl;
	throw std::runtime_error(std::string("\n" __FILE__) + ":" +
				 std::to_string(__LINE__) +
				 ": Severe Bug:\n  index[n] = " +
				 std::to_string(index[n]) + " != " +
				 std::to_string(2*m) + " = 2*m   ");
    }
    return *this;
}
