/*
 *    Copyright (C) 2012-2013  Jan Starke <rexgen@outofbed.org>
 * 
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 * 
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 * 
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/
 */


#ifndef ASCIICLASSREGEXITERATOR_H
#define ASCIICLASSREGEXITERATOR_H

#include <librexgen/iterator/iterator.h>
#include <librexgen/unicode.h>
#include <librexgen/unicode/uchar.h>
#include <vector>
#include <algorithm>

using std::random_shuffle;

using namespace std;

class AsciiClassRegexIterator : public Iterator
{
  
public:
  AsciiClassRegexIterator(int _id,
                     const uchar_t* classcontent,
                     size_t elements,
                     bool rnd = true
  ) :Iterator(_id), randomize(rnd) {
    for (size_t n=0; n<elements; ++n) {
      characters.push_back(classcontent[n].character.ansi.value);
    }
    first = &(*characters.begin());
    last = &(*characters.rbegin());
    reset();
    current = first-1;
    state = usable;
  }
  virtual ~AsciiClassRegexIterator() {}
  
  inline void reset() { if(randomize) {shuffle();} current = first;}
  
  inline void value(SimpleString& dst) const { dst.push_back(*current); }
  
  bool next(){
    ++current;
    if (current > last) {
      reset();
      return false;
    }
    return true;
  }
  
  inline bool hasNext() const { return  (current < last); }
  inline bool canUseValue() const { return (current<=last); }
private:
  inline void shuffle() {
    random_shuffle(first, last+1);
  }
  
  uint8_t *current = nullptr, *first = nullptr, *last = nullptr;
  vector<uint8_t> characters;
  const bool randomize;
};

#endif // ASCIICLASSREGEXITERATOR_H
