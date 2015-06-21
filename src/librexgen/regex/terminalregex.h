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

#ifndef __TerminalRegex_h__
#define __TerminalRegex_h__

#include <vector>
#include <librexgen/regex/regex.h>
#include <librexgen/iterator/terminalregexiterator.h>
#include <librexgen/iterator/iteratorpermuter.h>
#include <librexgen/string/unicode.h>
#include <librexgen/string/uchar.h>

using std::vector;

class TerminalRegex : public Regex {
 public:
  TerminalRegex(uint32_t ch, charset encoding) {
    uchar_t uch;
    codepoint_to_uchar(&uch, ch, encoding);
    value.push_back(uch);
  }

  void prepend(const TerminalRegex* tre);

  inline const char_type* getValue() const { return NULL; }

  RegexType getRegexType() const { return Terminal; }

  Iterator* singleIterator(IteratorState* /* state */) const
  { return new TerminalRegexIterator(getId(), &value[0], value.size()); }

 private:
  vector<uchar_t> value;
};

#endif
