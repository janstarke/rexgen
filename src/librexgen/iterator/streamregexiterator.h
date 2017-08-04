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


#ifndef SRC_LIBREXGEN_ITERATOR_STREAMREGEXITERATOR_H_
#define SRC_LIBREXGEN_ITERATOR_STREAMREGEXITERATOR_H_

#include <librexgen/iterator/iterator.h>
#include <librexgen/c/iterator.h>
#include <librexgen/defs.h>

static const size_t STREAMREGEXITERATOR_MAXLEN = 1024;

class StreamRegexIterator : public Iterator {
 public:
  StreamRegexIterator(int _id, callback_fp_mb cb)
    : Iterator(_id), callback(cb) {
    state = resetted;
    readNextWord();
  }

  bool next() {
    const bool res = (state == resetted);
    state = usable;
    return res;
  }
  bool forceNext() {
    readNextWord();
    return __hasNext;
  }
  bool hasNext() const { return state == resetted; }
  void value(SimpleString* dst) const {
    dst->append(&buffer[0], length);
  }
  void updateReferences(IteratorState* /* iterState */) {}
  void updateAttributes(IteratorState* /* iterState */) {}
  bool isSingleton() const { return true; }

  SerializableState* getCurrentState() const;
  void setCurrentState(const SerializableState* state);

 private:
  void readNextWord();

  callback_fp_mb callback;
  byte_t buffer[STREAMREGEXITERATOR_MAXLEN];
  size_t length;
  bool __hasNext;
};

#endif  // SRC_LIBREXGEN_ITERATOR_STREAMREGEXITERATOR_H_
