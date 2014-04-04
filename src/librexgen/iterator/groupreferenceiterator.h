/*
    rexgen - a tool to create words based on regular expressions    
    Copyright (C) 2012-2013  Jan Starke <jan.starke@outofbed.org>

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


#ifndef GROUPREFERENCEITERATOR_H
#define GROUPREFERENCEITERATOR_H

#include "iterator.h"
#include <librexgen/regex/regex.h>
#include <vector>
#include <librexgen/unicode.h>
#include <librexgen/iterator/iteratorstate.h>


class GroupReferenceIterator : public Iterator
{

public:
    GroupReferenceIterator(int _id, int group)
    : Iterator(_id), groupId(group), groupRef(NULL) { };
  
    inline bool hasNext() const { return (state == resetted); }
    inline bool next() {
      bool res = (state == resetted);
      state = usable;
      return res; }
    inline void value(SimpleString& dst) const { groupRef->value(dst);}
    
    void updateReferences(IteratorState* iterState);
private:
  int groupId;
  const Iterator* groupRef;
};

#endif // GROUPREFERENCEITERATOR_H
