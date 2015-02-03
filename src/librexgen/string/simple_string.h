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


#ifndef SIMPLE_STRING_H
#define SIMPLE_STRING_H

#include <cstdio>
#include "uchar.h"

template <class CHAR>
class simple_string {
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
      current_size += uchar_to_binary(ch, &buffer[current_size]);
    }
  }
  void push_front(uchar_t ch) {
    uint8_t len = ch.char_length;
    size_t idx;
    if (current_size+len <= max_size) {
      for (idx = current_size+len-1; idx >= len; idx--) {
        buffer[idx] = buffer[idx-len];
      }
      current_size += uchar_to_binary(ch, &buffer[idx]);
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
