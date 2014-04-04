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


#ifndef COMPOUNDREGEXITERATOR_H
#define COMPOUNDREGEXITERATOR_H

#include "iterator.h"
#include <deque>
#include <vector>
#include <algorithm>
#include <librexgen/regex/regex.h>
#include <librexgen/unicode.h>

using namespace std;

class CompoundRegexIterator : public Iterator
{

public:  
    CompoundRegexIterator(int id, bool rnd = true);
    
    virtual ~CompoundRegexIterator();
    
    bool next();
    void value(SimpleString& dst) const;
    bool hasNext() const;
    
    void addChild(Iterator* i);
    
    void updateReferences(IteratorState* iterState);
    
    SerializableState* getCurrentState() const;
    void setCurrentState(const SerializableState* state);
    
private:
  void shuffle() {random_shuffle(rnd_iterators.begin(), rnd_iterators.end());}
  vector<Iterator* > iterators;
  vector<unsigned int> rnd_iterators;
  const bool randomize;
};

#endif // COMPOUNDREGEXITERATOR_H
