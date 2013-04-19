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
  
  SimpleString& append(const byte* ch, const size_t& length) {
    if (length < max_size-current_size) {
      memcpy(&buffer[current_size], ch, length);
      current_size += length;
    }
    return *this;
  }
  
  inline void fast_append(const byte* ch, const size_t& length) {
    if (length < max_size-current_size) {
      switch(length) {
        case 4: buffer[current_size++] = *ch++;
        case 3: buffer[current_size++] = *ch++;
        case 2: buffer[current_size++] = *ch++;
        case 1: buffer[current_size++] = *ch++;
      }
    }
  }

  SimpleString& append(const char* ch) {
     while (*ch != '\0') {
       push_back(char_to_uchar(*ch++));
     }
     return *this;
  }

  SimpleString& append(int n) {
    char buf[32];
#ifdef _WIN32
    _itoa_s(n, buf, sizeof(buf)/sizeof(buf[0])-1, 10);
#else
    snprintf(buf, sizeof(buf)-1, "%d", n);
#endif
    return append(buf);
  }
  
  unsigned int size() { return current_size; }
  void clear() { current_size = 0; }
  void print(FILE* stream) const { fwrite(buffer, sizeof(*buffer), current_size, stream); }
  
  const byte* __get_buffer_address() const { return buffer; }
  size_t __get_buffer_size() const { return current_size; }
  
private:
  size_t max_size;
  size_t current_size;
  byte* buffer;
};

#endif // SIMPLESTRING_H
