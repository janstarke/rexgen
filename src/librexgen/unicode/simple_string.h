/*
    Copyright (c) 2013, Jan Starke <jan.starke@outofbed.org>
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


#ifndef SIMPLE_STRING_H
#define SIMPLE_STRING_H

#include <cstdio>
#include "uchar.h"

template <class CHAR>
class simple_string
{
public:
  simple_string(size_t msize=256)
    :max_size(msize), current_size(0) {
      buffer = new CHAR[msize];
    }
  ~simple_string() { delete[] buffer; }
    
  void push_back(CHAR ch) {
    if (current_size < max_size) {
      buffer[current_size] = ch;
      ++current_size;
    }
  }
  void push_front(CHAR ch) {
    if (current_size < max_size) {
      for (size_t idx = current_size; idx > 0; idx--) {
        buffer[idx] = buffer[idx-1];
      }
      buffer[0] = ch;
      ++current_size;
    }
  }
  
  virtual size_t size() const { return current_size; }
  virtual void clear() { current_size = 0; }
  
  size_t print(FILE* stream) {
    return fwrite(buffer, current_size, sizeof(CHAR), stream);
  }
private:
  size_t max_size;
  size_t current_size;
  CHAR* buffer;
};

template <>
class simple_string <uchar_t> {
  simple_string(size_t msize=256)
  :max_size(msize), current_size(0) {
    buffer = new char[msize];
    end = buffer;
  }
  ~simple_string() { delete[] buffer; }
  
  void push_back(uchar_t ch) {
    if (current_size+ch.char_length <= max_size) {
      current_size += uchar_to_utf(ch, &buffer[current_size]);
    }
  }
  void push_front(uchar_t ch) {
    uint8_t len = ch.char_length;
    size_t idx;
    if (current_size+len <= max_size) {
      for (idx = current_size+len-1; idx >= len; idx--) {
        buffer[idx] = buffer[idx-len];
      }
      current_size += uchar_to_utf(ch, &buffer[idx]);
    }
  }
  
  virtual size_t size() const { return current_size; }
  virtual void clear() { current_size = 0; }
  
  size_t print(FILE* stream) {
    return fwrite(buffer, current_size, sizeof(char), stream);
  }  
private:
  size_t max_size;
  size_t current_size;
  char* end;
  char* buffer;
};

#endif // SIMPLE_STRING_H
