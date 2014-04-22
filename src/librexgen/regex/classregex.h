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


#ifndef CLASSREGEX_H
#define CLASSREGEX_H

#include <vector>
#include <string>
#include <librexgen/regex/regex.h>
#include <librexgen/iterator/classregexiterator.h>
#include <librexgen/iterator/iteratorpermuter.h>
#include <librexgen/string/unicode.h>
#include <librexgen/string/uchar.h>
#include <librexgen/string/simplestring.h>

using namespace std;

class ClassRegex : public Regex {
 public:
  ClassRegex(charset variant) : encoding(variant) { }

  inline void addCharacter(const uint32_t& ch, bool ignoreCase) {
    uchar_t uch;
    codepoint_to_uchar(&uch, ch, encoding);
    addCharacter(uch, ignoreCase);
  }


  int addRange(const uint32_t& a, const uint32_t& b, bool ignoreCase) {
    uchar_t uch_a, uch_b;
    codepoint_to_uchar(&uch_a, a, encoding);
    codepoint_to_uchar(&uch_b, b, encoding);
    return addRange(uch_a, uch_b, ignoreCase);
  }

  bool contains(const uint32_t& ch) const {
    uchar_t uch;
    codepoint_to_uchar(&uch, ch, encoding);
    return contains(uch);
  }

  RegexType getRegexType() const { return Class; }

  void appendContent(SimpleString& dst, int level) const;

  const char* getXmlTag() const { return "class"; }

  Iterator* singleIterator(IteratorState* /* state */) const;

 private:
  void addCharacter(const uchar_t& ch, bool ignoreCase);
  int addRange(const uchar_t& a, const uchar_t& b, bool ignoreCase);
  bool contains(const uchar_t& ch) const;

  int __insert_character(const uchar_t& ch);
  int __append_character(const uchar_t& ch);
  vector<uchar_t> characters;
  const charset encoding;
};

#endif // CLASSREGEX_H
