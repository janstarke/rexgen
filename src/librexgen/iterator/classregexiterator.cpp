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
  size_t elements,
  bool rnd )
  :Iterator(_id), randomize(rnd) {
    for (size_t n=0; n<elements; ++n) {      
      buffered_character c;
      c.length = uchar_to_utf(classcontent[n], &(c.value[0]));
      characters.push_back(c);
    }
    first = &(*characters.begin());
    last = &(*characters.rbegin());
    reset();
    current = first-1;
    state = usable;
}

bool ClassRegexIterator::next() {
  ++current;
  if (current > last) {
    reset();
    return false;
  }
  return true;
}