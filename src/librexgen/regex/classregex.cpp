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

#include <librexgen/regex/classregex.h>
#include <algorithm>
#include <vector>

void ClassRegex::merge(const ClassRegex* other) {
  for (auto  i =  other->characters.crbegin();
       i != other->characters.crend();
       ++i) {
    addCharacter(*i);
  }

  for (CharacterClassType ct : other->ranges) {
    addRange(ct);
  }
}

bool ClassRegex::contains(const wchar_t& ch) const {
  return (std::find(characters.begin(), characters.end(),
                    ch) != characters.end());
}

void ClassRegex::__append_character(const wchar_t& ch) {
  removeCharacterInstances(ch);
  characters.push_back(ch);
  if (ch > 0x80) {
    requires_multibyte = true;
  }
}
void ClassRegex::__insert_character(const wchar_t& ch) {
  removeCharacterInstances(ch);
  characters.insert(characters.begin(), ch);
}

void ClassRegex::removeCharacterInstances(const wchar_t& ch) {
  auto match_fct = [&ch](const wchar_t& x) {
    return x == ch;
  };

  characters.erase(
    std::remove_if(characters.begin(), characters.end(), match_fct),
    characters.end());
}

void ClassRegex::removeCharacterInstances(
        const wchar_t& min, const wchar_t& max) {
  auto match_fct = [&min, &max](const wchar_t& x) {
    return (min <= x) && (x <= max);
  };

  characters.erase(
          std::remove_if(characters.begin(), characters.end(), match_fct),
          characters.end());
}

void ClassRegex::addCharacter(const wchar_t& ch) {
  __insert_character(ch);
}

void ClassRegex::addRange(const wchar_t& uch_a, const wchar_t& uch_b) {
  if (uch_a == L'0' && uch_b == L'9') {
    ranges.push_back(DIGITS);
  } else if (uch_a == L'A' && uch_b == L'Z') {
    ranges.push_back(UPPERCASE);
  } else if (uch_a == L'a' && uch_b == L'z') {
    ranges.push_back(LOWERCASE);
  } else {
    wchar_t a = uch_a;
    int diff = +1;

    if (a > uch_b) {
      diff = -1;
    }

    while (a != uch_b + diff) {
      __append_character(a);
      a += diff;
    }
  }
}

void ClassRegex::addRange(CharacterClassType ct) {
  for (CharacterClassType classType : ranges) {
    if (classType == ct) { /* nothing to do*/
      return;
    }

    if (classType == WORDCHARACTERS) {
      if (ct == DIGITS || ct == UPPERCASE || ct == LOWERCASE) {
        return;
      }
    }
  }
  ranges.push_back(ct);
  removeCharacterInstances(ct);
}

Iterator* ClassRegex::singleIterator(IteratorState* /* state */) const {
  Iterator* single = NULL;

  if (characters.size() == 1 && ranges.size() == 0) {
    return new ClassRegexIterator(getId(), &characters[0], characters.size());
  } else if (characters.size() == 0 && ranges.size() == 1) {
    switch (ranges[0]) {
      case DIGITS:
        return new RangeIterator<'0', '9'>(getId());
      case UPPERCASE:
        return new RangeIterator<'A', 'Z'>(getId());
      case LOWERCASE:
        return new RangeIterator<'a', 'z'>(getId());
      case WORDCHARACTERS: {
        auto child = new RegexAlternativesIterator(getId());
        child->addChild(new RangeIterator<'0', '9'>(getId()));
        child->addChild(new RangeIterator<'a', 'z'>(getId()));
        child->addChild(new RangeIterator<'A', 'Z'>(getId()));
        child->addChild(new TerminalRegexIterator(getId(), L"_", 1));
        return child;
      }
      case SPACES:
         return new ClassRegexIterator(getId(), L" \t", 2);
      default:
          return NULL;
    }
  } else { /* we must combine at least two different iterators */
    RegexAlternativesIterator *child = new RegexAlternativesIterator(getId());
    single = child;
    if (characters.size() > 0) {
      child->addChild(new ClassRegexIterator(
              getId(), &characters[0], characters.size()));
    }
    for (CharacterClassType classType : ranges) {
      switch (classType) {
        case DIGITS:
          child->addChild(new RangeIterator<'0', '9'>(getId()));
          break;

        case UPPERCASE:
          child->addChild(new RangeIterator<'A', 'Z'>(getId()));
          break;

        case LOWERCASE:
          child->addChild(new RangeIterator<'a', 'z'>(getId()));
          break;

        case WORDCHARACTERS: {
          child->addChild(new RangeIterator<'0', '9'>(getId()));
          child->addChild(new RangeIterator<'a', 'z'>(getId()));
          child->addChild(new RangeIterator<'A', 'Z'>(getId()));
          child->addChild(new TerminalRegexIterator(getId(), L"_", 1));
          break;
        }
        case SPACES:
          child->addChild(new ClassRegexIterator(getId(), L" \t", 2));
          break;
      }
    }
  }

  return single;
}
