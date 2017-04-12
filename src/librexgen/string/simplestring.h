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


#ifndef SRC_LIBREXGEN_STRING_SIMPLESTRING_H_
#define SRC_LIBREXGEN_STRING_SIMPLESTRING_H_

#include <librexgen/string/uchar.h>
#include <librexgen/string/unicode.h>
#include <librexgen/osdepend.h>
#include <librexgen/c/simplestring.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <algorithm>

#ifdef __cplusplus

/**
 * internal string representation. uses UTF-8 as character encoding
 */
class SimpleString : public std::string {
 public:

  bool can_change_case(size_t idx) const {
    return (character_length(idx) == 1 && isalpha(this->at(idx)));
  }

  size_t character_length(size_t idx) const {
    const char& first_byte = at(idx);
    const int lz = __builtin_clz(~first_byte);
    return lz - ((sizeof(first_byte)-1)*8) + 1;
  }

  void set_preserve_case() {
    /*
    for (size_t idx=0; idx < length; ++idx) {
      UCHAR_SET_PRESERVE_CASE(characters[idx]);
    }
     */
  }

  inline
  void toggle_case(size_t /*idx*/) {
    //characters[idx].toggle_case();
  }

  bool isalpha(unsigned int n) const;
  bool islower(unsigned int n) const;
  bool isupper(unsigned int n) const;

  void tolower(unsigned int n);
  void toupper(unsigned int n);

  // UTF-8 handling
  codepoint_t codepoint_from_utf8(size_type at_index) const;
  SimpleString& append_codepoint(const codepoint_t& codepoint);
};

#endif /* __cplusplus */

#endif  // SRC_LIBREXGEN_STRING_SIMPLESTRING_H_
