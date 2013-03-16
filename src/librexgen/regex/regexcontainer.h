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

#ifndef __regexcontainer_h__
#define __regexcontainer_h__

#include "regex.h"
#include <algorithm>
#include "../debug.h"

using namespace std;

template <class T>
class RegexContainer : public Regex {
public:
  typedef T container_type;
  
  virtual int getMaxSize() const {
    typename T::const_iterator iter = regexObjects.begin();
    int __size = 0;
    while (iter != regexObjects.end()) {
      __size += (*iter)->getMaxSize();
      iter++;
    }
    return __size * getMaxOccurs();
  }
  
  virtual int appendContent(char_type* dst, size_t dst_size, int level) const {
    typename T::const_iterator iter = regexObjects.begin();
    size_t l, length = 0;
    while(iter != regexObjects.end()) {
      l = appendSpace(dst, dst_size, level);
      if (dst_size <= l) break;
      length += l;
      dst_size -= l;
      dst += l;
      
      l = (*iter)->appendRawValue(dst, dst_size, level);
      length += l;
      if (dst_size <= l) break;
      dst_size -= l;
      dst += l;
      
      iter++;
    }
    return length;
  }
  
  unsigned int size() { return getChildren()->size(); }

protected:
  T* getChildren() { return &regexObjects; }
  T regexObjects;
};

#endif
