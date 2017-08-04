/*
    rexgen - a tool to create words based on regular expressions
    Copyright (C) 2012-2017  Jan Starke <jan.starke@outofbed.org>

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


#include <librexgen/string/simplestring.h>
#include <ctype.h>
#include <wchar.h>
#include <cstdlib>
#include <climits>
#include <cwctype>

bool SimpleString::isalpha(unsigned int n) const {
  return (std::iswalpha(widechar_at(n)));
}
bool SimpleString::islower(unsigned int n) const {
  return (std::iswlower(widechar_at(n)));
}

bool SimpleString::isupper(unsigned int n) const {
  return (std::iswupper(widechar_at(n)));
}

void SimpleString::toggle_case(size_t idx) {
  wint_t (*toggle_fct)(wint_t) =
  this->islower(idx) ? (std::towupper) : (std::towlower);

  const wchar_t this_widechar = widechar_at(idx);
  if (this_widechar < 0x80) {
    at(idx) = static_cast<char>(toggle_fct(this_widechar));
  } else {
    int ch_size = mblen(&(at(idx)), MB_CUR_MAX);
    const std::string& lhs = substr(0, idx);
    const std::string& rhs = substr(idx + ch_size);
    clear();
    append(lhs);
    append_widechar(toggle_fct(this_widechar));
    append(rhs);
  }
}

SimpleString& SimpleString::append_widechar(const wchar_t &widechar) {
  char buffer[MB_LEN_MAX];
  int ch_size = std::wctomb(&buffer[0], widechar);

  if (ch_size == -1) {
    ch_size = 1;
    buffer[0] = '?';
  }

  this->append(&buffer[0], ch_size);
  return *this;
}

wchar_t SimpleString::widechar_at(size_t index) const {
  wchar_t widechar = 0;
  const int ch_size = std::mbtowc(&widechar, & (at(index)), MB_LEN_MAX);
  if (ch_size == -1) {
    const char questionmark = '?';
    std::mbtowc(&widechar, & questionmark, sizeof(questionmark));
  }
  return widechar;
}

size_t SimpleString::character_length(size_t idx) const {
  int ch_size;
  int pos = 0;
  for (size_t i=0; i < idx; ++i) {
    ch_size = mblen(&(at(pos)), MB_CUR_MAX);
    assert(ch_size > 0 && ch_size <= 8);
    pos += ch_size;
  }
  ch_size = mblen(&(at(pos)), MB_CUR_MAX);
  return static_cast<size_t>(ch_size);
}
