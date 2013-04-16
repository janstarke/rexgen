/*
    Copyright (c) 2012, Jan Starke <jan.starke@outofbed.org>
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
        * Neither the name of the <organization> nor the
        names of its contributors may be used to endorse or promote products
        derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY Jan Starke <jan.starke@outofbed.org> ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL Jan Starke <jan.starke@outofbed.org> BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
  ClassRegex(charset variant) : encoding(variant){ }
  
  void addCharacter(const uchar_t& ch, bool ignoreCase);
  inline void addCharacter(char ch, bool ignoreCase) {
    uchar_t uch;
    codepoint_to_uchar(&uch, ch, encoding);
    addCharacter(uch, ignoreCase);
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
  
  Iterator* iterator(IteratorState* state) const;
  
  Iterator* singleIterator(IteratorState* /* state */) const 
  { return new ClassRegexIterator(getId(), &characters[0], characters.size()); }

private:
  void __insert_character(const uchar_t& ch);
  void __append_character(const uchar_t& ch);
  vector<uchar_t> characters;
  const charset encoding;
};

#endif // CLASSREGEX_H
