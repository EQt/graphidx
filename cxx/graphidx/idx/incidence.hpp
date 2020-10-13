#pragma once
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
    size_t num_edges() const { return this->value.size() / 2; }
    size_t num_nodes() const { return this->size(); }
};
