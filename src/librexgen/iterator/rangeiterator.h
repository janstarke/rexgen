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

#ifndef SRC_LIBREXGEN_ITERATOR_RANGEITERATOR_H_
#define SRC_LIBREXGEN_ITERATOR_RANGEITERATOR_H_

#include <librexgen/iterator/iterator.h>
namespace rexgen {
  template<char __MIN, char __MAX>
  class RangeIterator : public Iterator {
  public:
    explicit RangeIterator()
            : Iterator(), current(__MIN - 1), minimum(__MIN), maximum(__MAX) {}

    void value(std::string& dst) const override {
      dst.push_back(static_cast<const byte_t>(current));
    }

    bool next() override {
      const bool has_next = (current < maximum);
      current = has_next ? (current + 1) : minimum;
      return has_next;
    }

    void updateReferences(IteratorState& /* iterState */) override {}

    void updateAttributes(IteratorState& /* iterState */) override {}

  private:
    char current;
    const char minimum;
    const char maximum;
  };
}

#endif /* SRC_LIBREXGEN_ITERATOR_RANGEITERATOR_H_ */
