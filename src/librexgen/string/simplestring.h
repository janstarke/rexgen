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
#include <librexgen/string/uchar.h>
#include <librexgen/string/unicode.h>
#include <librexgen/osdepend.h>
#include <librexgen/c/simplestring.h>

#ifdef __cplusplus

using std::vector;

class SimpleString {
 public:
  SimpleString(size_t msize=512);
  uchar_t& operator[](const unsigned int& idx) { return characters[idx]; }

  const uchar_t& getAt(const unsigned int& idx) const;
  size_t to_binary_string(char* buffer, size_t buffer_size, charset cs=CHARSET_UTF8) const;

  void newline();

  bool isalpha(unsigned int n) const;
  bool islower(unsigned int n) const;
  bool isupper(unsigned int n) const;

  void tolower(unsigned int n);
  void toupper(unsigned int n);

  void push_back(char ch);
  void push_back(const uchar_t& c);
  void append(const char* ch);

  void clear()        {        characters.clear(); }
  size_t size() const { return characters.size();  }
  bool empty() const  { return characters.empty(); }
  size_t get_buffer_size() const;

 private:
  vector<uchar_t> characters;
};

#endif /* __cplusplus */

#endif /* SIMPLESTRING_H */
