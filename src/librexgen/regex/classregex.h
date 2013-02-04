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
#include "../iterator/classregexiterator.h"
#include "../iterator/iteratorpermuter.h"
#include "../unicode.h"


using namespace std;
class ClassRegexIterator;
class ClassRegex : public Regex {
  friend class ClassRegexIterator;
public:
  
  virtual ~ClassRegex() {}
  inline void addCharacter(char_type ch) {
    //characters.push_back(ch);
    characters.insert(characters.begin(), ch);
  }
  inline void addRange(char_type a, char_type b) {
    while (a <= b) { 
      //characters.push_back(a++);
      characters.insert(characters.begin(), a++);
    }
  }
  
  RegexType getRegexType() const { return Class; }
  
  virtual int appendContent(char_type* dst, ssize_t size, int level) const;
  
  virtual inline const char_type* getXmlTag() const { return _T("class"); }
  
  Iterator* iterator() const;
  
  Iterator* singleIterator() const 
  { return new ClassRegexIterator(getId(), characters.cbegin(), characters.cend()); }
private:
  vector<char_type> characters;
};

#endif // CLASSREGEX_H
