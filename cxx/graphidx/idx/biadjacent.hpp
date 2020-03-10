#pragma once
#include <vector>
#include <stdexcept>
#include <algorithm>        // for std::max_element

#include "index.hpp"


/**
   Bidirected adjacency vectors
 **/
template <typename int_ = int>
struct BiAdjacentIndex : public AdjacencyIndex<int_>
{
    BiAdjacentIndex(uvector<int_> &&value, std::vector<int_> &&index)
        : AdjacencyIndex<int_> {std::forward<uvector<int_>>(value),
                                std::forward<std::vector<int_>>(index) } { }

    BiAdjacentIndex(const size_t m, const int_ *head, const int_ *tail, size_t n = 0)
        { reset(m, head, tail, n); }

    bool operator==(const BiAdjacentIndex<int_> &other) const
        { return this->value == other.value && this->index == other.index; }

    BiAdjacentIndex<int_>&
    reset(const size_t m, const int_ *head, const int_ *tail, size_t n = 0) {
        if (head == nullptr)
            throw std::runtime_error("head == nullptr");
        if (tail == nullptr)
            throw std::runtime_error("tail == nullptr");
        auto &value = this->value;
        auto &index = this->index;

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
        {                               // shift, accumulate
            int acc = 0,
                deg_i = 0;
            for (size_t i = 0; i < n; i++) {
                index[i] = acc;
                acc += deg_i;
                deg_i = index[i+1];
            }
            index[n] = acc;
        }
        for (size_t i = 0; i < m; i++) {
            const int_
                u = head[i],
                v = tail[i];
            value[size_t(index[size_t(u+1)]++)] = v;
            value[size_t(index[size_t(v+1)]++)] = u;
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

    BiAdjacentIndex(const std::vector<int> &head,
                    const std::vector<int> &tail,
                    const size_t n = 0)
        : BiAdjacentIndex(head.size(), head.data(), tail.data(), n) {
        if (head.size() != tail.size()) {
            throw std::invalid_argument(std::string("len(head) = ") +
                                        std::to_string(head.size()) + " != " +
                                        std::to_string(tail.size()) +
                                        " = len(tail)");
        }
    }

    size_t num_edges() const { return this->value.size() / 2; }
    size_t num_nodes() const { return this->index.size() - 1; }

    template <typename Idx>
    BiAdjacentIndex<int_>& induced_subgraph(const Idx &sub) {
        if (sub.size() > num_nodes())
            throw std::invalid_argument(
                std::string("induced_subgraph(..): ") +
                std::to_string(sub.size()) + " vs " +
                std::to_string(num_nodes()));
        // inverse index:
        //   inv[i] = j iff sub[j] = i or
        //   inv[i] = -1 iff j not in sub
        std::vector<int_>
            head, tail, inv (num_nodes(), -1);
        {
            int_ i = 0;
            for (const auto v : sub)
                inv[(size_t) v] = i++;
        }
        head.reserve(num_edges());
        tail.reserve(num_edges());
        auto &self = *this;
        for (size_t v = 0; v < num_nodes(); v++) {
            if (inv[v] < 0)
                continue;
            for (const int_ ui : self[v]) {
                const size_t u = (size_t) ui;
                if (v > u)
                    continue;
                if (inv[u] >= 0) {
                    head.push_back(inv[v]);
                    tail.push_back(inv[u]);
                }
            }
        }
        return reset(head.size(), head.data(), tail.data(), sub.size());
    }
};


using BiAdjacent = BiAdjacentIndex<int>;

// Local Variables:
// compile-command: "cd ../../build && make -j3 doctests && ./doctests -nc"
// End:
