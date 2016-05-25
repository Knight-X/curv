// Copyright Doug Moen 2016.
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENCE.md or http://www.boost.org/LICENSE_1_0.txt

#ifndef AUX_RANGE_H
#define AUX_RANGE_H

#include <cstddef>
#include <string>

namespace aux {

/// A Range references a contiguous subsequence of a collection
/// using a pair of iterators.
///
/// Compatible with range-based for loops.
/// TODO: rbegin(), possibly others.
///
/// It's the simplest possible range implementation
/// (boost/iterator_range.hpp is 40,000 lines of code).
template <class Iter>
struct Range
{
    Range(Iter f, Iter l) : first(f), last(l) {}
    Iter first;
    Iter last;
    Iter begin() const { return first; }
    Iter end() const { return last; }
    bool empty() const { return first == last; }
    std::size_t size() const { return last - first; }

    /// convert Range<const char*> to std::string
    operator std::string() { return std::string(begin(), size()); }
};

} // namespace aux
#endif // header guard
