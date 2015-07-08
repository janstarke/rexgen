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


#include <ctype.h>
#include <librexgen/string/simplestring.h>

SimpleString::SimpleString(size_t msize)
  :characters(msize) {
  clear();
}

const uchar_t& SimpleString::getAt(const unsigned int& idx) const {
  return (const uchar_t&) characters[idx];
}

bool SimpleString::isalpha(unsigned int n) const {
  return (::isalpha(characters[n].codepoint));
}
bool SimpleString::islower(unsigned int n) const {
  return (::islower(characters[n].codepoint));
}

bool SimpleString::isupper(unsigned int n) const {
  return ( ::isupper(characters[n].codepoint));
}

void SimpleString::tolower(unsigned int n) {
  characters[n].codepoint = ::tolower(characters[n].codepoint);
}
void SimpleString::toupper(unsigned int n) {
 characters[n].codepoint = ::toupper(characters[n].codepoint);
}


void SimpleString::append(const char* ch) {
  while (*ch != '\0') {
    push_back(codepoint_to_uchar(*ch++));
  }
}

size_t SimpleString::get_buffer_size() const {
  return characters.size();
}

void SimpleString::push_back(char ch) {
  push_back(codepoint_to_uchar(ch));
}

void SimpleString::push_back(const uchar_t& c) {
  characters.push_back(c);
}

void SimpleString::newline() {
  return push_back('\n');
}

size_t SimpleString::to_binary_string(char* dst, size_t buffer_size, charset cs) const {
  size_t count = 0;
  static const uchar_t zero = codepoint_to_uchar('\0');

  /* guarantee space for terminating zero */
  buffer_size -= 4;

  for (auto ch: characters) {
    if (count >= buffer_size) {
      break;
    }
    count += encode_uchar(ch, cs, dst+count);
  }
  count += encode_uchar(zero, cs, dst+count);
  return count;
}

