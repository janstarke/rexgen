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


#ifndef SIMPLESTRING_H
#define SIMPLESTRING_H

#include <librexgen/unicode/uchar.h>
#include <librexgen/unicode.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
class SimpleString {
public:
  SimpleString(size_t msize=256)
    :max_size(msize), current_size(0) {
      buffer = new byte[msize];
  }
  virtual ~SimpleString() { delete[] buffer; }
  
  SimpleString& newline() {
    return push_back('\n');
  }

  SimpleString& push_back(byte ch) {
    if (current_size < max_size) {
      buffer[current_size] = ch;
      current_size++;
    }
    return *this;
  }

  SimpleString& push_back(const uchar_t& c) {
    append(firstByteAddressOf(c), c.char_length);
    return *this;
  }

  SimpleString& terminate() {
    buffer[current_size] = 0;
    return *this;
  }
  
  SimpleString& append(const byte* ch, size_t length) {
    if (length < max_size-current_size) {
      memcpy(&buffer[current_size], ch, length);
      current_size += length;
    }
    return *this;
  }

  SimpleString& append(const char* ch) {
     while (*ch != '\0') {
       push_back(char_to_uchar(*ch++));
     }
     return *this;
  }

  SimpleString& append(int n) {
    char buffer[32];
    _itoa_s(n, buffer, sizeof(buffer)/sizeof(buffer[0])-1, 10);
    return append(buffer);
  }
  
  unsigned int size() { return current_size; }
  void clear() { current_size = 0; }
  void print(FILE* stream) const { fwrite(buffer, sizeof(*buffer), current_size, stream); }
  
private:
  size_t max_size;
  size_t current_size;
  byte* buffer;
};

#endif // SIMPLESTRING_H
