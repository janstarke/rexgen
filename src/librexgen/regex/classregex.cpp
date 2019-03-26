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
namespace rexgen {

  void ClassRegex::merge(const std::shared_ptr<ClassRegex>& other) {
    characters.insert(other->characters.cbegin(), other->characters.end());
    ranges.insert(other->ranges.cbegin(), other->ranges.end());
    minimize();
  }

  void ClassRegex::minimize() {
    if (ranges.find(WORDCHARACTERS) != ranges.end()) {
      ranges.erase(UPPERCASE);
      ranges.erase(LOWERCASE);
      ranges.erase(DIGITS);
    }

    /* ranges are faster than single characters, so prefer ranges */
    if (ranges.find(WORDCHARACTERS) != ranges.end()) { removeCharacterInstances(WORDCHARACTERS); }
    if (ranges.find(UPPERCASE) != ranges.end())      { removeCharacterInstances(UPPERCASE); }
    if (ranges.find(LOWERCASE) != ranges.end())      { removeCharacterInstances(LOWERCASE); }
    if (ranges.find(DIGITS) != ranges.end())         { removeCharacterInstances(DIGITS); }
    if (ranges.find(SPACES) != ranges.end())         { removeCharacterInstances(SPACES); }
  }

  bool ClassRegex::contains(const wchar_t &ch) const {
    return (std::find(characters.begin(), characters.end(),
                      ch) != characters.end());
  }

  void ClassRegex::removeCharacterInstances(const wchar_t min, const wchar_t max) {
    for (auto iter = characters.begin(); iter != characters.end();) {
      if ((min <= *iter) && (*iter <= max)) {
        iter = characters.erase(iter);
      } else {
        ++iter;
      }
    }
  }

  void ClassRegex::addCharacter(const wchar_t &ch) {
    characters.insert(ch);
    minimize();
  }

  void ClassRegex::addRange(const wchar_t &uch_a, const wchar_t &uch_b) {
    if (uch_a == L'0' && uch_b == L'9') {
      ranges.insert(DIGITS);
    } else if (uch_a == L'A' && uch_b == L'Z') {
      ranges.insert(UPPERCASE);
    } else if (uch_a == L'a' && uch_b == L'z') {
      ranges.insert(LOWERCASE);
    } else {
      for (wchar_t a = uch_a; a<= uch_b; ++a) {
        addCharacter(a);
      }
    }

    minimize();
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
        removeCharacterInstances(L'0', L'9');
        removeCharacterInstances(L'A', L'Z');
        removeCharacterInstances(L'a', L'z');
        characters.erase(L'_');
        break;
      case SPACES:
        characters.erase(L' ');
        characters.erase(L'\t');
        break;
    }
  }

  std::shared_ptr<Iterator> ClassRegex::singleIterator(IteratorState& /* state */) const {
    std::shared_ptr<Iterator> single;

    if (ranges.size() == 0) {
      return std::make_shared<ClassRegexIterator>(characters.begin(), characters.end());
    }

    assert (ranges.size() > 0);

    if (characters.size() == 0 && ranges.size() == 1) {
      /* we have exactly one single range */
      switch (*(ranges.begin())) {
        case DIGITS:
          return std::make_shared<RangeIterator<'0', '9'>>();
        case UPPERCASE:
          return std::make_shared<RangeIterator<'A', 'Z'>>();
        case LOWERCASE:
          return std::make_shared<RangeIterator<'a', 'z'>>();
        case WORDCHARACTERS: {
          auto child = std::make_shared<RegexAlternativesIterator>();
          child->addChild(std::make_shared<RangeIterator<'0', '9'>>());
          child->addChild(std::make_shared<RangeIterator<'a', 'z'>>());
          child->addChild(std::make_shared<RangeIterator<'A', 'Z'>>());
          child->addChild(std::make_shared<TerminalRegexIterator>(L"_", 1));
          return child;
        }
        case SPACES:
          const std::wstring wstr(L" \t");
          return std::make_shared<ClassRegexIterator>(wstr.cbegin(), wstr.cend());
      }
    } else { /* we must combine at least two different iterators */
      auto child = std::make_shared<RegexAlternativesIterator>();
      single = child;
      if (characters.size() > 0) {
        child->addChild(std::make_shared<ClassRegexIterator>(characters.cbegin(), characters.cend()));
      }
      for (CharacterClassType classType : ranges) {
        switch (classType) {
          case DIGITS:
            child->addChild(std::make_shared<RangeIterator<'0', '9'>>());
            break;

          case UPPERCASE:
            child->addChild(std::make_shared<RangeIterator<'A', 'Z'>>());
            break;

          case LOWERCASE:
            child->addChild(std::make_shared<RangeIterator<'a', 'z'>>());
            break;

          case WORDCHARACTERS: {
            child->addChild(std::make_shared<RangeIterator<'0', '9'>>());
            child->addChild(std::make_shared<RangeIterator<'a', 'z'>>());
            child->addChild(std::make_shared<RangeIterator<'A', 'Z'>>());
            child->addChild(std::make_shared<TerminalRegexIterator>(L"_", 1));
            break;
          }
          case SPACES:
            const std::wstring wstr(L" \t");
            child->addChild(std::make_shared<ClassRegexIterator>(wstr.cbegin(), wstr.cend()));
            break;
        }
      }
    }
    return single;
  }
}