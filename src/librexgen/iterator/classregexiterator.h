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


#ifndef CLASSREGEXITERATOR_H
#define CLASSREGEXITERATOR_H

#include <librexgen/iterator/iterator.h>
#include <librexgen/iterator/iteratorstate.h>
#include <librexgen/unicode.h>
#include <librexgen/unicode/uchar.h>
#include <vector>
#include <algorithm>

using std::random_shuffle;

using namespace std;

class ClassRegexIterator : public Iterator
{

public:
    ClassRegexIterator(int _id,
                       IteratorState* iterstate,
                       const uchar_t* classcontent,
                       size_t elements
		      );
    virtual ~ClassRegexIterator() {}
  
  //inline void reset() { fprintf(stderr, "reset\n"); if(randomize) {shuffle();} current = first;}
    
    inline void value(SimpleString& dst) const {
      dst.fast_append(current->value, current->length);
    }
    
    bool next();
    
    inline bool hasNext() const { return  (current < last); }
    inline bool canUseValue() const { return (current<=last); }
    
    virtual void updateReferences(IteratorState* /* iterState */) {}
    
    SerializableState* getCurrentState() const;
    void setCurrentState(const SerializableState* state);    
private:
  inline void shuffle() {
    random_shuffle(characters.begin(), characters.end()); 
    first = &(*characters.begin());
    last = &(*characters.rbegin());
  }

  struct buffered_character {
    byte value[4];
    uint8_t length;
  };
  buffered_character *current, *first, *last;
  vector<buffered_character> characters;
  const bool randomize;
};

#endif // CLASSREGEXITERATOR_H
