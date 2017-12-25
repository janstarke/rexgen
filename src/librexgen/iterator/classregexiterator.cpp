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

#include <librexgen/iterator/classregexiterator.h>

ClassRegexIterator::ClassRegexIterator(int _id,
                     const wchar_t * classcontent,
                     size_t elements)
          :Iterator(_id), current(-1), characters() {
  size_t n;
  std::string::size_type index = 0;
  for (n = 0; n < elements; ++n) {
    characters.append_widechar(classcontent[n]);

    /*
     * TODO(jasa):
     * the call to character_length is very slow and shoud be removed
     */
    lengths.push_back(characters.character_length(n));

    indices.push_back(index);
    index += characters.character_length(n);
  }
  characters_count = static_cast<size_t>(elements);
  setState(usable);
}

void ClassRegexIterator::value(SimpleString* dst) const {
  /**
   * FIXME(jasa):
   * this condition may be expensive and should be unnecessary
   */
  if (current >= 0) {
    const std::string::size_type &length = lengths[current];
    const std::string::size_type &index = indices[current];

    for (std::string::size_type n = 0; n < length; ++n) {
      dst->push_back(characters[index + n]);
    }
  }
}

bool ClassRegexIterator::next() {
  ++current;

  if (current >= static_cast<int>(characters_count)) {
    current = 0;
    return false;
  }
  return true;
}

SerializableState* ClassRegexIterator::getCurrentState() const {
  SerializableState *s = Iterator::getCurrentState();
  s->addValue(current);
  return s;
}

void ClassRegexIterator::setCurrentState(const SerializableState* s) {
  Iterator::setCurrentState(s);
  current = s->getValue(0);
}
