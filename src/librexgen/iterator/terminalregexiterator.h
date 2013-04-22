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


#ifndef TERMINALREGEXITERATOR_H
#define TERMINALREGEXITERATOR_H

#include "iterator.h"
#include <string.h>
#include "../debug.h"
#include <vector>
#include <librexgen/unicode.h>
#include <librexgen/simplestring.h>

class TerminalRegexIterator : public Iterator
{
public:
  
  TerminalRegexIterator(int _id, const uchar_t* _terminal, size_t elements)
    : Iterator(_id) {
    terminal = new byte[elements*sizeof(uchar_t)];
    terminal_length = 0;
    for (size_t n = 0; n < elements; ++n) {
      terminal_length += uchar_to_utf(_terminal[n], &terminal[terminal_length]);
    }
  }
  
  ~TerminalRegexIterator() { delete[] terminal; }
    
  bool next() {
    const bool res = (state == resetted);
    state = usable;
    return res;
  }
  void value(SimpleString& dst) const { dst.append(terminal, terminal_length); }
  bool hasNext() const { return state == resetted; }
  //void reset() { state = resetted; }
private:
  byte* terminal;
  size_t terminal_length;
};

#endif // TERMINALREGEXITERATOR_H
