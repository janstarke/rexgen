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
#include <stdexcept>

class IteratorState {
 public:
  IteratorState() : streamIterator(NULL) {
  }

  virtual ~IteratorState() {
    if (streamIterator != NULL) {
      delete streamIterator;
      streamIterator = NULL;
    }
  }

  void registerIterator(int id, Iterator* iterator) {
    groupIterators[id] = iterator;
  }

  Iterator* getIterator(int id) const {
    if (id == -1) {
      return getStreamIterator();
    } else {
      std::map<int, Iterator*>::const_iterator iter = groupIterators.find(id);
      if (iter != groupIterators.end()) {
        return iter->second;
      } else {
        return NULL;
      }
    }
  }

  void setStreamIterator(StreamRegexIterator* iter) {
    if (streamIterator == NULL) {
      streamIterator = iter;
    } else {
      throw std::runtime_error("multiple stream iterator assignment");
    }
  }

  StreamRegexIterator* getStreamIterator() const { return streamIterator; }

 private:
  std::map<int, Iterator*> groupIterators;
  StreamRegexIterator* streamIterator;
};

#endif  // SRC_LIBREXGEN_ITERATOR_ITERATORSTATE_H_
