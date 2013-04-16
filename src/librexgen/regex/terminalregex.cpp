/*
    Copyright (C) 2012-2013  Jan Starke <rexgen@outofbed.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/
*/

#include <librexgen/regex/terminalregex.h>
#include <librexgen/iterator/iteratorpermuter.h>
#include <librexgen/unicode.h>
#include <vector>


void TerminalRegex::prepend(const TerminalRegex* tre) {
  for_each((tre->value.cbegin()), (tre->value.cend()),
    [&](const uchar_t ch){value.insert(value.begin(), ch); });
}

Iterator* TerminalRegex::iterator(IteratorState* state) const {
  if (getMinOccurs() == 1 && getMaxOccurs() == 1) {
    return new TerminalRegexIterator(getId(), &value[0], value.size());
  } else {
    return new IteratorPermuter(
      getId(), this, state, getMinOccurs(), getMaxOccurs());
  }
}

void TerminalRegex::appendContent(
  SimpleString& dst, int level) const {
    appendSpace(dst, level);
    for_each(value.cbegin(), value.cend(), [&dst](uchar_t c) {dst.push_back(c);});
    dst.newline();
}
