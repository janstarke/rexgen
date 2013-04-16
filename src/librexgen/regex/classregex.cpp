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

#include <librexgen/regex/classregex.h>
#include <librexgen/unicode/uchar.h>
#include <algorithm>
#include <vector>

bool ClassRegex::contains(const uchar_t& ch) const
{
  for (auto iter = characters.cbegin(); iter != characters.cend(); ++iter) {
    if ((*iter).codepoint == ch.codepoint) {
      return true;
    }
  }
  return false;
}

void ClassRegex::__append_character(const uchar_t& ch)
{
  if (! contains(ch)) {
    characters.push_back(ch);
  }
}
void ClassRegex::__insert_character(const uchar_t& ch)
{
  if (! contains(ch)) {
    characters.insert(characters.begin(), ch);
  }
}

void ClassRegex::addCharacter(const uchar_t& ch, bool ignoreCase) {
  __insert_character(ch);
  if (ignoreCase && uchar_isascii(ch)) {
    uchar_t uch;
    
    if (islower(ch.character.ansi.value)) {
      codepoint_to_uchar(&uch, toupper(ch.character.ansi.value), encoding);
      __insert_character(uch);
    } 
    
    else if (isupper(ch.character.ansi.value)) {
      codepoint_to_uchar(&uch, tolower(ch.character.ansi.value), encoding);
      __insert_character(uch);
    }
  }
}
void ClassRegex::addRange(const uchar_t& uch_a, const uchar_t& uch_b, bool ignoreCase) {
  uint16_t a = uch_a.codepoint;
  while (a <= uch_b.codepoint) {
    uchar_t ch;
    uchar_t uch;
    codepoint_to_uchar(&ch, a++, uch_a.variant);
    characters.push_back(ch);
    
    if (ignoreCase && uchar_isascii(ch)) {
      if (islower(ch.character.ansi.value)) {
        codepoint_to_uchar(&uch, toupper(ch.character.ansi.value), encoding);
        __append_character(uch);
      }
      
      else if (isupper(ch.character.ansi.value)) {
        codepoint_to_uchar(&uch, tolower(ch.character.ansi.value), encoding);
        __append_character(uch);
      }
    }
  }
}

void ClassRegex::appendContent(SimpleString& dst, int level) const {
  auto iter = characters.begin();

  appendSpace(dst, level);

  for_each(characters.begin(), characters.end(), [&dst](uchar_t c){dst.push_back(c);});
  dst.newline();
}

Iterator* ClassRegex::iterator(IteratorState* state) const {
  if (getMinOccurs() == 1 && getMaxOccurs() == 1) {
    return new ClassRegexIterator(
      getId(), &characters[0], characters.size());
  } else {
    return new IteratorPermuter(
      getId(), this, state, getMinOccurs(), getMaxOccurs());
  }
}

