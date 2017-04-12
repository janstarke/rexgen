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

template <char __MIN, char __MAX>
class RangeIterator : public Iterator {
  public:
  RangeIterator(int _id) : Iterator(_id), current(0), offset(__MIN), max(__MAX-__MIN) {}

  void value(SimpleString* dst) const {
    dst->push_back(static_cast<const byte_t>(current+offset));
  }

  bool next() {
    current = current<max ? current+1 : 0;
    return current;
  }

  virtual void updateReferences(IteratorState* /* iterState */) {}
  virtual void updateAttributes(IteratorState* /* iterState */) {}

  private:
  char current;
  const char offset;
  const char max;
};

#endif //SRC_LIBREXGEN_ITERATOR_RANGEITERATOR_H_
