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

bool SimpleString::isalpha(unsigned int n) const {
  return (::isalpha(codepoint_from_utf8(n)));
}
bool SimpleString::islower(unsigned int n) const {
  return (::islower(codepoint_from_utf8(n)));
}

bool SimpleString::isupper(unsigned int n) const {
  return (::isupper(codepoint_from_utf8(n)));
}

void SimpleString::tolower(unsigned int n) {
  const uint32_t codepoint_upper = codepoint_from_utf8(n);

  if (codepoint_upper<0x80) {
    at(n) = static_cast<char>(::tolower(codepoint_upper));
  } else {
    const uint32_t codepoint_lower = ::tolower(codepoint_upper);
    const std::string& lhs = substr(0, n);
    const std::string& rhs = substr(n + 1);
    clear();
    append(lhs);
    append_codepoint(codepoint_lower);
    append(rhs);
  }
}

void SimpleString::toupper(unsigned int n) {
  const uint32_t codepoint_lower = codepoint_from_utf8(n);

  if (codepoint_lower<0x80) {
    at(n) = static_cast<char>(::toupper(codepoint_lower));
  } else {
    const uint32_t codepoint_upper = ::toupper(codepoint_lower);
    const std::string& lhs = substr(0, n);
    const std::string& rhs = substr(n + 1);
    clear();
    append(lhs);
    append_codepoint(codepoint_upper);
    append(rhs);
  }
}

codepoint_t SimpleString::codepoint_from_utf8(size_type at_index) const {
  uint32_t codepoint = 0;
  if ((at(at_index + 0) & 0x80) == 0) {
    codepoint = at(at_index + 0);
  } else if (
          ((at(at_index + 0) & 0b11100000) == 0b11000000) &&
          ((at(at_index + 1) & 0b11000000) == 0b10000000)) {
    codepoint  = (at(at_index + 0)&0b00011111) << 6;
    codepoint |= (at(at_index + 1)&0b00111111);
  } else if (
          ((at(at_index + 0) & 0b11110000) == 0b11100000) &&
          ((at(at_index + 1) & 0b11000000) == 0b10000000) &&
          ((at(at_index + 2) & 0b11000000) == 0b10000000)) {
    codepoint  = (at(at_index + 0)&0b00001111) << 12;
    codepoint |= (at(at_index + 1)&0b00111111) << 6;
    codepoint |= (at(at_index + 2)&0b00111111);
  } else if (
          ((at(at_index + 0) & 0b11111000) == 0b11110000) &&
          ((at(at_index + 1) & 0b11000000) == 0b10000000) &&
          ((at(at_index + 2) & 0b11000000) == 0b10000000) &&
          ((at(at_index + 3) & 0b11000000) == 0b10000000)) {
    codepoint  = (at(at_index + 0)&0b00000111) << 15;
    codepoint |= (at(at_index + 1)&0b00111111) << 12;
    codepoint |= (at(at_index + 2)&0b00111111) << 6;
    codepoint |= (at(at_index + 3)&0b00111111);
  } else {
    codepoint = 0xFFFD;
  }

  return codepoint;
}

SimpleString& SimpleString::append_codepoint(const codepoint_t& codepoint) {
  const uint32_t byte_mask = 0xbf;
  const uint32_t byte_mark = 0x80;
  const uint32_t UNI_MAX_LEGAL_UTF32 = 0x0010FFFF;

  if (codepoint < 0x80) {
    push_back(static_cast<byte_t>(codepoint));
  } else if (codepoint < 0x800) {
    push_back(static_cast<byte_t>(codepoint>>6) | 0xc0);
    push_back((static_cast<byte_t>(codepoint) | byte_mark) & byte_mask);
  } else if (codepoint < 0x10000) {
    push_back(static_cast<byte_t>(codepoint>>12) | 0xE0);
    push_back((static_cast<byte_t>(codepoint>>6) | byte_mark) & byte_mask);
    push_back((static_cast<byte_t>(codepoint) | byte_mark) & byte_mask);
  } else if (codepoint < UNI_MAX_LEGAL_UTF32) {
    push_back(static_cast<byte_t>(codepoint>>18) | 0xf0);
    push_back((static_cast<byte_t>(codepoint>>12) | byte_mark) & byte_mask);
    push_back((static_cast<byte_t>(codepoint>>6) | byte_mark) & byte_mask);
    push_back((static_cast<byte_t>(codepoint) | byte_mark) & byte_mask);
  } else {
    push_back('?');
  }

  return *this;
}
