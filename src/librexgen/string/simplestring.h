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
#include <vector>
#include <array>
#include <librexgen/string/uchar.h>
#include <librexgen/string/unicode.h>
#include <librexgen/osdepend.h>
#include <librexgen/c/simplestring.h>

#ifdef __cplusplus

using std::vector;
using std::array;

class SimpleString {
 public:
  SimpleString();
  uchar_t& operator[](const unsigned int& idx) { return characters[idx]; }

  const uchar_t& getAt(const unsigned int& idx) const;
  size_t to_ansi_string(char* buffer, size_t buffer_size) const;
  size_t to_utf8_string(char* buffer, size_t buffer_size) const;

  bool isalpha(unsigned int n) const;
  bool islower(unsigned int n) const;
  bool isupper(unsigned int n) const;

  void tolower(unsigned int n);
  void toupper(unsigned int n);

  void push_back(const uchar_t& c);
  void append(const char* ch);

  void clear()        { length=0; }
  size_t size() const { return length;  }
  bool empty() const  { return (length == 0); }
  size_t get_buffer_size() const;

 protected:
  array<uchar_t, 512> characters;
	size_t length;
};

#endif /* __cplusplus */

#endif /* SIMPLESTRING_H */
