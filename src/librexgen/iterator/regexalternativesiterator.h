/*
    Copyright (C) 2012-2013  Jan Starke <rexgen@outofbed.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/
*/


#ifndef REGEXALTERNATIVESITERATOR_H
#define REGEXALTERNATIVESITERATOR_H

#include "iterator.h"
#include <librexgen/regex/regexalternatives.h>
#include <algorithm>
#include <deque>
#include <vector>
#include "../unicode.h"

using namespace std;

class RegexAlternativesIterator : public Iterator
{
public:
  
    RegexAlternativesIterator(int id);
    
    virtual ~RegexAlternativesIterator();
    
    bool next();
    void value(SimpleString& dst) const;
    bool hasNext() const;
    
    void addChild(Iterator* re);
    void updateReferences(IteratorState* iterState);
private:  
  deque<Iterator*> iterators;
  deque<Iterator*>::iterator iter;
  
  bool canUseValue() const;
};

#endif // REGEXALTERNATIVESITERATOR_H
