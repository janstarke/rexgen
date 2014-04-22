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


#ifndef SIMPLESTRING_H
#define SIMPLESTRING_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <librexgen/string/uchar.h>
#include <librexgen/string/unicode.h>
#include <librexgen/osdepend.h>
#include <librexgen/api/c/simplestring.h>

#ifdef __cplusplus

class SimpleString {
 public:
  SimpleString(size_t msize=512)
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
    fast_append(firstByteAddressOf(&c), c.char_length);
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

  void fast_append(const byte* ch, const size_t& length) {
    if (length < max_size-current_size) {
      switch (length) {
      case 4:
        buffer[current_size++] = *ch++;
      case 3:
        buffer[current_size++] = *ch++;
      case 2:
        buffer[current_size++] = *ch++;
      case 1:
        buffer[current_size++] = *ch;
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
  void print(FILE* stream, bool force = false) {
    if (current_size > (max_size / 2) || force) {
      fwrite(buffer, sizeof(*buffer), current_size, stream);
      clear();
    }
  }

  const byte* __get_buffer_address() const { return buffer; }
  size_t __get_buffer_size() const { return current_size; }

 private:
  size_t max_size;
  size_t current_size;
  byte* buffer;
};

#endif /* __cplusplus */

#endif /* SIMPLESTRING_H */
