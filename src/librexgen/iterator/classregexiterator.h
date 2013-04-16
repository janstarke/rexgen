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

using namespace std;

class ClassRegexIterator : public Iterator
{

public:
    ClassRegexIterator(int _id,
                       const uchar_t* classcontent,
                       size_t elements
		      );
    virtual ~ClassRegexIterator() {delete[] buffer;}
  
   void reset() { state = resetted; current = 0;}
    
    inline void value(SimpleString& dst) const {
      dst.append(ptrs[current], lengths[current]);
    }
    
    bool next();
    
    inline bool hasNext() const { return  (current+1 < ptrs.size()); }
    inline bool canUseValue() const { return (current<ptrs.size()); }
private:
  byte *buffer;
  size_t buffer_length;
  vector<byte*> ptrs;
  vector<uint8_t> lengths;
  unsigned int current;
};

#endif // CLASSREGEXITERATOR_H
