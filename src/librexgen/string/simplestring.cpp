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

SimpleString::SimpleString()
  :length(0) {
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
    push_back((*ch++));
  }
}

size_t SimpleString::get_buffer_size() const {
  return characters.size();
}

void SimpleString::push_back(const uchar_t& c) {
  characters[length++] = c;
}

size_t SimpleString::to_ansi_string(char* dst, const size_t buffer_size) const {
  size_t idx;
	const size_t len = (length>=buffer_size) ? (buffer_size-1) : (length);

	for (idx=0; idx<len; ++idx) {
    dst[idx] = (char)characters[idx].codepoint;
  }

	dst[idx] = 0;
	return idx;
}

size_t SimpleString::to_utf8_string(char* dst, const size_t buffer_size) const {
  size_t idx;     /* index in source string,
	                 * must be <length
									 */
  size_t count;   /* number of bytes in the resulting output string,
	                 * must be <buffer_size
									 */

	for (idx=0, count=0; idx<length && count<buffer_size; ++idx) {
    if (characters[idx].plane==BMP && characters[idx].codepoint < 128) {
      *dst = static_cast<byte>(characters[idx].codepoint);
      ++count;
    } else {
      count += convert_utf32_to_utf8(dst, characters[idx].full_codepoint());
    }
  }

	dst[count] = 0;
	return count;
}

