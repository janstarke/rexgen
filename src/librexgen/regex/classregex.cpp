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

#include <algorithm>
#include <vector>
#include <librexgen/regex/classregex.h>
#include <librexgen/string/uchar.h>

bool ClassRegex::contains(const uchar_t& ch) const {
  for (vector<uchar_t>::const_iterator iter = characters.begin();
       iter != characters.end(); ++iter) {
    if ((*iter).codepoint == ch.codepoint) {
      return true;
    }
  }
  return false;
}

int ClassRegex::__append_character(const uchar_t& ch) {
	int count = 1 - removeCharacterInstances(ch);
	characters.push_back(ch);
  return count;
}
int ClassRegex::__insert_character(const uchar_t& ch) {
	int count = 1 - removeCharacterInstances(ch);
	characters.insert(characters.begin(), ch);
  return count;
}

int ClassRegex::removeCharacterInstances(const uchar_t& ch) {
	auto match_fct = [&ch](uchar_t x){return x.codepoint==ch.codepoint;};
	int count = std::count_if( characters.begin(), characters.end(), match_fct);
  if (count > 0) {
		characters.erase(
			std::remove_if(characters.begin(), characters.end(), match_fct),
			characters.end());
  }
	return count;
}

void ClassRegex::addCharacter(const uchar_t& ch) {
  __insert_character(ch);
}

int ClassRegex::addRange(const uchar_t& uch_a, const uchar_t& uch_b) {
  uint32_t a = uch_a.codepoint;
  int count = 0;
	int diff = +1;

	if (a > uch_b.codepoint) {
		diff = -1;
	}

  while (a != uch_b.codepoint + diff) {
    uchar_t ch;
    codepoint_to_uchar(&ch, a, uch_a.variant);
    count += __append_character(ch);
		a += diff;
  }

  return count;
}

Iterator* ClassRegex::singleIterator(IteratorState* /*state*/) const {
  return new ClassRegexIterator(getId(), &characters[0],
                                characters.size());
}



