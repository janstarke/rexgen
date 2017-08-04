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

#include <librexgen/iterator/compoundregexiterator.h>

CompoundRegexIterator::CompoundRegexIterator(int _id)
  : IteratorContainer(_id) {
}

bool CompoundRegexIterator::next() {
  if (state == resetted) {
    state = usable;
    bool res = false;
    for (auto i : iterators) {
      res |= i->next();
    }
    return res;
  }
  for (auto i : iterators) {
    if (i->next()) {
      return true;
    }
  }
  return false;
}

void CompoundRegexIterator::value(SimpleString* dst) const {
  // assert(canUseValue());
  for (auto i : iterators) {
    i->value(dst);
  }
}

bool CompoundRegexIterator::hasNext() const {
  bool has_next = false;
  if (state == not_usable) {
    return false;
  }
  for (auto i : iterators) {
    has_next |= i->hasNext();
  }
  return has_next;
}

SerializableState* CompoundRegexIterator::getCurrentState() const {
  SerializableState* s = Iterator::getCurrentState();
  for (auto i : iterators) {
    s->addValue(i->getCurrentState());
  }
  return s;
}

void CompoundRegexIterator::setCurrentState(const SerializableState* s) {
  Iterator::setCurrentState(s);

  for (auto i : iterators) {
    i->setCurrentState(s->getChildState(i->getId()));
  }
}

