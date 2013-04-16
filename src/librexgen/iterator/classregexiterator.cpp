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

#include <librexgen/iterator/classregexiterator.h>

ClassRegexIterator::ClassRegexIterator(
  int _id,
  const uchar_t* classcontent,
  size_t elements)
  :Iterator(_id) {
    buffer = new byte[elements*sizeof(char32_t)];
    buffer_length = 0;
    for (size_t n=0; n<elements; ++n) {
      byte* ptr = &buffer[buffer_length];
      buffer_length += uchar_to_utf(classcontent[n], ptr);
      ptrs.push_back(ptr);
      lengths.push_back(classcontent[n].char_length);
    }
    reset();
}

bool ClassRegexIterator::next() {
  if (state == resetted) {
    state = usable;
    return true;
  }
  ++current;
  if (current >= ptrs.size()) {
    current = 0;
    return false;
  }
  return true;
}