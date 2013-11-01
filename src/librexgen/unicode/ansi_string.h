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


#ifndef ANSI_STRING_H
#define ANSI_STRING_H

#include <iostream>
#include "uchar.h"

using std::ostream;

class ansi_string
{
public:
  ansi_string(size_t msize=256)
  :max_size(msize), current_size(0) {
    buffer = new char[msize];
  }
  virtual ~ansi_string() { delete[] buffer; }
  
  void push_back(char ch) {
    if (current_size < max_size) {
      buffer[current_size] = ch;
      current_size++;
    }
  }
  
  void push_back(u_char ch) {
    if (ch.variant == UTF8 && ch.length == 1) {
      push_back(ch.character.ansi.value);
    } else {
      push_back('?');
    }
  }
  
  size_t size() { return current_size; }
  void clear() { current_size = 0; }
  friend ostream& operator<<(ostream& stream, const ansi_string& str) const;
  
  virtual size_t size() = 0;
  virtual void clear() = 0;
  virtual char& operator[](size_t index) = 0;
  friend ostream& operator<<(ostream& stream, const char* str);
  
private:
  size_t max_size;
  size_t current_size;
  char* buffer;
};

ostream& operator<<(ostream& stream, const ansi_string& str) const {
  stream << str.buffer;
}

#endif // ANSI_STRING_H
