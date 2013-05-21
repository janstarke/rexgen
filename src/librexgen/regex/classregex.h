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


#ifndef CLASSREGEX_H
#define CLASSREGEX_H

#include "regex.h"
#include <vector>
#include <string>
#include <librexgen/iterator/classregexiterator.h>
#include <librexgen/iterator/iteratorpermuter.h>
#include <librexgen/unicode.h>
#include <librexgen/unicode/uchar.h>
#include <librexgen/simplestring.h>

using namespace std;

class ClassRegex : public Regex {
public:
  ClassRegex(charset variant) : encoding(variant), canUseAsciiIterator(true){ }
  
  void addCharacter(const uchar_t& ch, bool ignoreCase);
  inline void addCharacter(char ch, bool ignoreCase) {
    uchar_t uch;
    codepoint_to_uchar(&uch, ch, encoding);
    addCharacter(uch, ignoreCase);
    canUseAsciiIterator &= (uch.char_length == 1);
  }
  
  void addRange(const uchar_t& a, const uchar_t& b, bool ignoreCase);
  void addRange(const char& a, const char& b, bool ignoreCase) {
    uchar_t uch_a, uch_b;
    codepoint_to_uchar(&uch_a, a, encoding);
    codepoint_to_uchar(&uch_b, b, encoding);
    addRange(uch_a, uch_b, ignoreCase);
  }
  
  bool contains(const uchar_t& ch) const;
  bool contains(char ch) const {
    uchar_t uch;
    codepoint_to_uchar(&uch, ch, encoding);
    return contains(uch);
  }
  
  RegexType getRegexType() const { return Class; }
  
  void appendContent(SimpleString& dst, int level) const;
  
  virtual inline const char* getXmlTag() const { return "class"; }
  
  Iterator* singleIterator(IteratorState* /* state */) const; 

private:
  void __insert_character(const uchar_t& ch);
  void __append_character(const uchar_t& ch);
  vector<uchar_t> characters;
  const charset encoding;
  bool canUseAsciiIterator;
};

#endif // CLASSREGEX_H
