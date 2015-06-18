/*
  rexgen - a tool to create words based on regular expressions
  Copyright (C) 2012-2015  Jan Starke <jan.starke@outofbed.org>

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

#include <librexgen/iterator/terminalregexiterator.h>

TerminalRegexIterator::TerminalRegexIterator(int _id, const uchar_t* _terminal, size_t elements)
    : Iterator(_id) {
    for (size_t idx = 0; idx < elements; ++idx) {
      terminal.push_back(_terminal[idx]);
    }
  }
 
void TerminalRegexIterator::value(SimpleString& dst) const {
  for (auto ch: terminal) {
    dst.push_back(ch);
  }
}

