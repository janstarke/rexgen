/*
    rexgen - a tool to create words based on regular expressions
    Copyright (C) 2012-2017  Jan Starke <jan.starke@outofbed.org>

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the Free
    Software Foundation; either version 2 of the License, or (at your option)
    any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
    more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin St, Fifth Floor, Boston, MA 02110, USA
*/

#ifndef SRC_LIBREXGEN_ITERATOR_ITERATORSTATE_H_
#define SRC_LIBREXGEN_ITERATOR_ITERATORSTATE_H_

#include <librexgen/iterator/iterator.h>
#include <librexgen/iterator/streamregexiterator.h>
#include <librexgen/regex/regex.h>
#include <map>
#include <algorithm>
#include <functional>
#include <stdexcept>
namespace rexgen {
  class IteratorState {
  public:
    explicit IteratorState() : streamIterator(nullptr) {}

    /* prevent copying of IteratorState */
    IteratorState(const IteratorState&) = delete;
    IteratorState(IteratorState&&) = delete;
    IteratorState& operator=(const IteratorState&) = delete;
    IteratorState& operator=(IteratorState&&) = delete;

    void registerIterator(int id, std::reference_wrapper<Iterator> iterator) {
      groupIterators.insert(std::make_pair(id, iterator));
    }

    bool hasId(int id) const {
      return (groupIterators.find(id) != groupIterators.end());
    }

    std::reference_wrapper<Iterator> operator[](int id) const {
      if (id == -1) {
        return std::ref(static_cast<Iterator&>(getStreamIterator().get()));
      } else {
        auto iter = groupIterators.find(id);
        if (iter != groupIterators.end()) {
          return iter->second;
        } else {
          throw std::runtime_error("invalid iterator reference");
        }
      }
    }

    void setStreamIterator(std::unique_ptr<StreamRegexIterator>& iter) {
      if (streamIterator != nullptr) {
        throw std::runtime_error("multiple stream iterator assignment");
      }
      streamIterator = std::move(iter);
    }

    bool hasStreamIterator() const { return streamIterator != nullptr; }

    std::reference_wrapper<StreamRegexIterator> getStreamIterator() const {
      return std::ref(*streamIterator);
    }

  private:
    std::map<int, std::reference_wrapper<Iterator> > groupIterators;
    mutable std::unique_ptr<StreamRegexIterator> streamIterator;
  };
}

#endif  // SRC_LIBREXGEN_ITERATOR_ITERATORSTATE_H_
