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

#include <librexgen/iterator/iterator.h>
#include <librexgen/string/uchar.h>
#include <librexgen/string/simplestring.h>

#ifdef __cplusplus

class CaseIterator : public Iterator {
 public:

  CaseIterator(Iterator* _child);
  virtual ~CaseIterator();

  bool hasNext() const;
  bool next();
  void value(SimpleString& /* dst */ ) const;

  void updateReferences(IteratorState* /* iterState */){}

  virtual SerializableState* getCurrentState() const {
    return new SerializableState(getId());
  }

  virtual void setCurrentState(const SerializableState* s) {
    if (getId() != s->getIteratorId()) {
      throw InvalidIteratorIdException();
    }
  }


 private:

 bool readNextFromChild();

 Iterator* child;
 SimpleString word;
};

#endif /* __cplusplus */

#endif /* CASEITERATOR_H */
