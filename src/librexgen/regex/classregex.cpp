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

void ClassRegex::__append_character(const wchar_t& ch) {
  if (! hasCharacter(ch)) {
    characters.push_back(ch);
  }
}

void ClassRegex::__insert_character(const wchar_t& ch) {
  if (! hasCharacter(ch)) {
    characters.insert(characters.begin(), ch);
  }
}

bool ClassRegex::hasCharacter(const wchar_t &ch) const {
  for (const wchar_t c: characters) {
    if (ch == c) {
      return true;
    }
  }

  for (CharacterClassType ct: ranges) {
    switch (ct) {
      case DIGITS:
        if (L'0' <= ch && ch <= L'9') {
          return true;
        }
        break;

      case LOWERCASE:
        if (L'a' <= ch && ch <= L'z') {
          return true;
        }
        break;

      case UPPERCASE:
        if (L'A' <= ch && ch <= L'Z') {
          return true;
        }
        break;

      case SPACES:
        if (L'\t' == ch || ch == L' ') {
          return true;
        }
        break;

      case WORDCHARACTERS:
        if (        (L'0' <= ch && ch <= L'9')
                ||  (L'a' <= ch && ch <= L'z')
                ||  (L'A' <= ch && ch <= L'Z')
                ||  (L'_' == ch)) {
          return true;
        }
        break;
    }
  }
  return false;
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

void ClassRegex::removeCharacterInstances(CharacterClassType ct) {
  switch (ct) {
    case DIGITS:
      removeCharacterInstances(L'0', L'9');
      break;
    case UPPERCASE:
      removeCharacterInstances(L'A', L'Z');
      break;
    case LOWERCASE:
      removeCharacterInstances(L'a', L'z');
      break;
    case WORDCHARACTERS:
      removeCharacterInstances(DIGITS);
      removeCharacterInstances(UPPERCASE);
      removeCharacterInstances(LOWERCASE);
      removeCharacterInstances(L'_');
      break;
    case SPACES:
      removeCharacterInstances(L' ');
      removeCharacterInstances(L'\t');
      break;
  }
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
    for (wchar_t a = uch_a; a <= uch_b; ++a) {
      __append_character(a);
    }
  }
}

void ClassRegex::addRange(CharacterClassType newClassType) {
  /* remove all subsets of characters */
  if (newClassType == WORDCHARACTERS) {
    ranges.erase( std::remove_if(ranges.begin(), ranges.end(),
        [] (CharacterClassType const & ct) {
          return ct == DIGITS || ct == UPPERCASE || ct == LOWERCASE;
        }), ranges.end());
  }

  for (CharacterClassType existingClassType : ranges) {
    if (existingClassType == newClassType) {
      /* nothing to do,
       * because this character class type has already been added*/
      return;
    }

    if (existingClassType == WORDCHARACTERS) {
      if (newClassType == DIGITS || newClassType == UPPERCASE || newClassType == LOWERCASE) {
        return;
      }
    }
  }
  ranges.push_back(newClassType);
  removeCharacterInstances(newClassType);
}

Iterator* ClassRegex::singleIterator(IteratorState* /* state */) const {
  Iterator* single = NULL;

  if (characters.size() == 1 && ranges.size() == 0) {
    return new ClassRegexIterator(getId(), &characters[0], characters.size());
  } else if (characters.size() == 0 && ranges.size() == 1) {
    switch (ranges[0]) {
      case DIGITS:
        single = new RangeIterator<'0', '9'>(getId());
        break;
      case UPPERCASE:
        single = new RangeIterator<'A', 'Z'>(getId());
        break;
      case LOWERCASE:
        single = new RangeIterator<'a', 'z'>(getId());
        break;
      case WORDCHARACTERS: {
        auto child = new RegexAlternativesIterator(getId());
        child->addChild(new RangeIterator<'0', '9'>(getId()));
        child->addChild(new RangeIterator<'a', 'z'>(getId()));
        child->addChild(new RangeIterator<'A', 'Z'>(getId()));
        child->addChild(new TerminalRegexIterator(getId(), L"_", 1));
        single = child;
        break;
      }
      case SPACES:
        single = new ClassRegexIterator(getId(), L" \t", 2);
        break;
    }
  } else { /* we must combine at least two different iterators */
    RegexAlternativesIterator *child = new RegexAlternativesIterator(getId());
    single = child;
    if (characters.size() > 0) {
      child->addChild(new ClassRegexIterator(
              Regex::createId(), &characters[0], characters.size()));
    }
    for (CharacterClassType classType : ranges) {
      switch (classType) {
        case DIGITS:
          child->addChild(new RangeIterator<'0', '9'>(Regex::createId()));
          break;

        case UPPERCASE:
          child->addChild(new RangeIterator<'A', 'Z'>(Regex::createId()));
          break;

        case LOWERCASE:
          child->addChild(new RangeIterator<'a', 'z'>(Regex::createId()));
          break;

        case WORDCHARACTERS: {
          child->addChild(new RangeIterator<'0', '9'>(Regex::createId()));
          child->addChild(new RangeIterator<'a', 'z'>(Regex::createId()));
          child->addChild(new RangeIterator<'A', 'Z'>(Regex::createId()));
          child->addChild(new TerminalRegexIterator(Regex::createId(), L"_", 1));
          break;
        }
        case SPACES:
          child->addChild(new ClassRegexIterator(Regex::createId(), L" \t", 2));
          break;
      }
    }
  }

  return single;
}
