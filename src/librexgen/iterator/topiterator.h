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


#ifndef SRC_LIBREXGEN_ITERATOR_TOPITERATOR_H_
#define SRC_LIBREXGEN_ITERATOR_TOPITERATOR_H_

#include <librexgen/iterator/iterator.h>
#include <librexgen/iterator/iteratorstate.h>
#include <librexgen/string/simplestring.h>


class TopIterator : public Iterator {
 public:
  explicit TopIterator(Regex* re) : Iterator(re->getId()) {
    needWord = false;
    state = new IteratorState();
    child = re->iterator(state);
  }

  ~TopIterator() {
    /* StreamIterator is managed by IteratorState; it will be deleted there */
    if (child != NULL && child != state->getStreamIterator()) {
      delete child;
    }

    if (state != NULL) {
      delete state;
    }
  }

  bool next() {
    if (needWord) {
      bool res = state->getStreamIterator()->forceNext();
      if (res) {
        needWord = false;
      }
      return res;
    }
    bool res = child->next();
    if (res) { return res; }

    if (state->getStreamIterator() == NULL) { return false; }
    res = state->getStreamIterator()->forceNext();
    if (res) { return res; }
    needWord = true;
    return false;
  }

  void value(SimpleString* dst) const { child->value(dst); }
  bool hasNext() const { return child->hasNext(); }
  void updateReferences(IteratorState* /* ignore */) {
    if (child != NULL && state != NULL) {
      child->updateReferences(state);
    }
  }

  void updateAttributes(IteratorState* /* ignore */ ) {
    if (child != NULL && state != NULL) {
      child->updateAttributes(state);
    }
  }

  SerializableState* getCurrentState() const {
    return child->getCurrentState();
  }

  void setCurrentState(const SerializableState* s) {
    child->setCurrentState(s);
  }

 private:
  Iterator* child;
  IteratorState* state;
  bool needWord;
};

#endif  // SRC_LIBREXGEN_ITERATOR_TOPITERATOR_H_
