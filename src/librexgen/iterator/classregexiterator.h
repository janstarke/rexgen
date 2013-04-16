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


#ifndef CLASSREGEXITERATOR_H
#define CLASSREGEXITERATOR_H

#include <librexgen/iterator/iterator.h>
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
                       const uchar_t* classcontent,
                       size_t elements,
                       bool rnd = true
		      );
    virtual ~ClassRegexIterator() {delete[] buffer;}
  
    inline void reset() { state = resetted; current = 0; if(randomize) {shuffle();}}
    
    inline void value(SimpleString& dst) const {
      dst.append(characters[current].ptr, characters[current].length);
    }
    
    bool next();
    
    inline bool hasNext() const { return  (current+1 < characters.size()); }
    inline bool canUseValue() const { return (current<characters.size()); }
private:
  inline void shuffle() { random_shuffle(characters.begin(), characters.end()); }

  struct class_character {
    byte* ptr;
    uint8_t length;
  };
  byte *buffer;
  size_t buffer_length;
  vector<class_character> characters;
  unsigned int current;
  const bool randomize;
};

#endif // CLASSREGEXITERATOR_H
