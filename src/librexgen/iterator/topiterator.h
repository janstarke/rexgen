/*
 *  Copyright (C) 2012-2013  Jan Starke <rexgen@outofbed.org>
 * 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/
 */


#ifndef TOPITERATOR_H
#define TOPITERATOR_H

#include <librexgen/iterator/iterator.h>
#include <librexgen/iterator/iteratorstate.h>
#include <librexgen/simplestring.h>


class TopIterator : public Iterator
{
public:
  TopIterator(int __id, Iterator* __child, IteratorState* __state)
    :Iterator(__id), child(__child), state(__state) {
  }
  
  ~TopIterator() {delete child;}
  bool next() {
    bool res = child->next();
    if (res) { return res; }
    
    if (state->getStreamIterator() == nullptr) { return false; }
    return state->getStreamIterator()->forceNext();
  }
  
  void value(SimpleString& dst) const { child->value(dst); }
  bool hasNext() const { return child->hasNext(); }
private:
  Iterator* child;
  const IteratorState* state;
};

#endif // TOPITERATOR_H
