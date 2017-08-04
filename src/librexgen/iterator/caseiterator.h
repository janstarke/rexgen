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


#ifndef SRC_LIBREXGEN_ITERATOR_CASEITERATOR_H_
#define SRC_LIBREXGEN_ITERATOR_CASEITERATOR_H_

#include <librexgen/iterator/iteratorcontainer.h>
#include <librexgen/string/simplestring.h>
#include <cinttypes>
#include <vector>

#ifdef __cplusplus

class CaseIterator : public IteratorContainer {
 public:
  CaseIterator(Iterator* _child, int options);
  virtual ~CaseIterator();

  bool hasNext() const;
  bool next();
  void fast_next();

  void value(SimpleString* dst) const {
    dst->append(word);
  }

  virtual SerializableState* getCurrentState() const {
    return new SerializableState(getId(), getState());
  }

  virtual void setCurrentState(const SerializableState* s) {
    if (getId() != s->getIteratorId()) {
      throw InvalidIteratorIdException();
    }
  }

 private:
  Iterator* child;
  int handle_case;
  bool readNextFromChild();

#if __x86_64__
  typedef std::uint64_t counter_t;
  static const unsigned int max_fast_character_bytes = 64;
#else
  typedef std::uint32_t counter_t;
  static const unsigned int max_fast_character_bytes = 32;
#endif

  counter_t k;
  unsigned int j;
  unsigned int parity;
  std::vector<unsigned int> changeable_characters;
  SimpleString word;
};

#endif /* __cplusplus */

#endif /* SRC_LIBREXGEN_ITERATOR_CASEITERATOR_H_ */
