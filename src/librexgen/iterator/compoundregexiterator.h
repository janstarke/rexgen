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


#ifndef COMPOUNDREGEXITERATOR_H
#define COMPOUNDREGEXITERATOR_H

#include "iterator.h"
#include <deque>
#include <vector>
#include <algorithm>
#include "../regex/regex.h"
#include "../unicode.h"

using namespace std;

class CompoundRegexIterator : public Iterator
{

public:  
    CompoundRegexIterator(int id, bool rnd = true);
    
    virtual ~CompoundRegexIterator() {
      for_each(iterators.begin(), iterators.end(), [](Iterator* i){delete i;});
    }
    
    void reset();
    bool next();
    void value(SimpleString& dst) const;
    bool hasNext() const;
    
    void addChild(Iterator* i);
private:
  void shuffle() {random_shuffle(rnd_iterators.begin(), rnd_iterators.end());}
  vector<Iterator* > iterators;
  vector<unsigned int> rnd_iterators;
  const bool randomize;
};

#endif // COMPOUNDREGEXITERATOR_H
