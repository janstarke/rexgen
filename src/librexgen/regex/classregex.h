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


#ifndef SRC_LIBREXGEN_REGEX_CLASSREGEX_H_
#define SRC_LIBREXGEN_REGEX_CLASSREGEX_H_

#include <librexgen/regex/regex.h>
#include <librexgen/iterator/classregexiterator.h>
#include <librexgen/iterator/iteratorpermuter.h>
#include <librexgen/iterator/rangeiterator.h>
#include <librexgen/iterator/regexalternativesiterator.h>
#include <librexgen/iterator/terminalregexiterator.h>
#include <librexgen/string/unicode.h>
#include <librexgen/string/simplestring.h>
#include <vector>

class ClassRegex : public Regex {
 public:
  typedef enum {
    DIGITS,
    UPPERCASE,
    LOWERCASE,
    WORDCHARACTERS,
    SPACES
  } CharacterClassType;

  ClassRegex() : requires_multibyte(false) {}

  void addCharacter(const wchar_t & ch);
  void addRange(const wchar_t& a, const wchar_t& b);
  void addRange(CharacterClassType ct);
  bool contains(const wchar_t& ch) const;
  RegexType getRegexType() const { return Class; }

  void merge(const ClassRegex* other);

  Iterator* singleIterator(IteratorState* /* state */) const;

 private:
  void __insert_character(const wchar_t& ch);
  void __append_character(const wchar_t& ch);
  void removeCharacterInstances(const wchar_t& ch);
  void removeCharacterInstances(const wchar_t& min, const wchar_t& max);
  void removeCharacterInstances(CharacterClassType ct) {
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

  std::vector<wchar_t> characters;
  std::vector<CharacterClassType> ranges;
  bool requires_multibyte;
};

#endif  // SRC_LIBREXGEN_REGEX_CLASSREGEX_H_
