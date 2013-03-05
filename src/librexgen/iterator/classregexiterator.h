/*
    Copyright (c) 2012, Jan Starke <jan.starke@outofbed.org>
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
        * Neither the name of the <organization> nor the
        names of its contributors may be used to endorse or promote products
        derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY Jan Starke <jan.starke@outofbed.org> ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL Jan Starke <jan.starke@outofbed.org> BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#ifndef CLASSREGEXITERATOR_H
#define CLASSREGEXITERATOR_H

#include <librexgen/iterator/iterator.h>
#include <librexgen/unicode.h>
#include <vector>

using namespace std;

class ClassRegexIterator : public Iterator
{

public:
    ClassRegexIterator(int _id,
                       const char_type* classcontent,
                       size_t size
		      )
    :Iterator(_id), begin(classcontent), current(classcontent-1), end(classcontent+size){}
  
   void reset() { current = begin - 1; }
    
    inline void value(string_type& dst) const {
      if (current != end) { 
        dst.push_back(*current);
      }      
    }
    inline void next() {assert(hasNext()); ++current;}
    inline bool hasNext() const { return  (current+1 < end); }
    inline bool canUseValue() const { return (current>=begin && current<end); }
    
    int toString(char_type* dst, ssize_t size) const {
      return utf_snprintf(dst, size, "ClassRegexIterator %d",
                          getId());}
private:
  const char_type *begin;
  const char_type *current;
  const char_type *end;
};

#endif // CLASSREGEXITERATOR_H
