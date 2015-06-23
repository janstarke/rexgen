/*
    rexgen - a tool to create words based on regular expressions
    Copyright (C) 2012-2014  Jan Starke <jan.starke@outofbed.org>

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


#ifndef CASEITERATOR_H
#define CASEITERATOR_H

#include <librexgen/iterator/iteratorcontainer.h>
#include <librexgen/string/uchar.h>
#include <librexgen/string/simplestring.h>

#ifdef __cplusplus

class CaseIterator : public IteratorContainer {
 public:

  CaseIterator(Iterator* _child, int options);
  virtual ~CaseIterator();

  bool hasNext() const;
  bool next();
  void fast_next();

  void value(SimpleString& /* dst */ ) const;

  virtual SerializableState* getCurrentState() const {
    return new SerializableState(getId());
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
  SimpleString word;

#if __x86_64__
  typedef long long unsigned int counter_t;
  static const unsigned int max_fast_character_bytes = 64;
#else
  typedef long unsigned int counter_t;
  static const unsigned int max_fast_character_bytes = 32;
#endif

  counter_t k;
  unsigned int j;
  unsigned int parity;
  vector<int> changeable_characters;

};

#endif /* __cplusplus */

#endif /* CASEITERATOR_H */
