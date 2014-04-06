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


#ifndef REGEXALTERNATIVESITERATOR_H
#define REGEXALTERNATIVESITERATOR_H

#include <algorithm>
#include <deque>
#include <vector>
#include <librexgen/iterator/iterator.h>
#include <librexgen/regex/regexalternatives.h>
#include <librexgen/string/unicode.h>

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
    
    SerializableState* getCurrentState() const;
    void setCurrentState(const SerializableState* state);
private:  
  deque<Iterator*> iterators;
  deque<Iterator*>::iterator iter;
  
  bool canUseValue() const;
};

#endif // REGEXALTERNATIVESITERATOR_H
