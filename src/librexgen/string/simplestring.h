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

#include <librexgen/c/simplestring.h>
#include <librexgen/string/unicode.h>
#include <librexgen/osdepend.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <xlocale.h>
#include <cassert>

#ifdef __cplusplus

class SimpleString : public std::string {

 public:
  bool can_change_case(size_t idx) const {
    const wchar_t wc = widechar_at(idx);
    return (::towupper(wc) != ::towlower(wc));
  }

  size_t character_length(size_t idx) const {
    int size = mblen(&(at(idx)), MB_CUR_MAX);
    assert(size > 0);
    return size;
  }

  void toggle_case(size_t idx);

  bool isalpha(unsigned int n) const;
  bool islower(unsigned int n) const;
  bool isupper(unsigned int n) const;

  wchar_t widechar_at(size_t index) const;
  SimpleString& append_widechar(const wchar_t& codepoint);
};

#endif /* __cplusplus */

#endif  // SRC_LIBREXGEN_STRING_SIMPLESTRING_H_
