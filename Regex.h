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

#ifndef __Regex_h__
#define __Regex_h__

#include "types.h"
#include "quantifier.h"
#include "iterator.h"
#include <iostream>
#include <log4cpp/Category.hh>
#include "unicode.h"
#include "debug.h"

class Regex  {
public:
  Regex() : LOGGER(log4cpp::Category::getRoot()), quantifier(1,1) {id=createId();}
  
  inline unsigned int getMinOccurs() const { return quantifier.getMin(); }
  inline unsigned int getMaxOccurs() const { return quantifier.getMax(); }
  
  inline void setMinOccurs(unsigned int _min) { quantifier.setMin(_min); }
  inline void setMaxOccurs(unsigned int _max) { quantifier.setMax(_max); }
  
  inline void setQuantifier(const Quantifier& q) { quantifier = q; }
    
  virtual const char_type* getXmlTag() const = 0;
  
  virtual inline int getMaxSize() const {
    return getMaxOccurs();
  }
  
  inline int appendRawValue(char_type* dst, int len) const {
    return appendRawValue(dst, len, 0);
  }
  
  inline int appendRawValue(char_type* dst, ssize_t size, int level) const {
    return xmlEncapsulate(dst, size, getXmlTag(), level);
  }
  
  inline int appendSpace(char_type* dst, ssize_t size, int count) const {
    int length = 0;
    while (count > 0 && size>1) {
      *dst = ' ';
      ++dst;
      --size;
      --count;
      ++length;
    }
    if (size >= 1) {
      *dst = '\0';
    }
    return length;
  }
  
  virtual int appendContent(char_type* dst, ssize_t size, int level) const = 0;
  
  inline virtual int xmlEncapsulate(char_type* dst, ssize_t size, const char_type* clazz, int level) const {
    int l;
    int length = 0;
    const char* format;
    
#if defined(UTF8)
    format = "<%U id=\"%d\" min=\"%d\" max=\"%d\">\n";
#elif defined(UTF16)
    format = "<%lU id=\"%d\" min=\"%d\" max=\"%d\">\n";
#else
    format = "<%llU id=\"%d\" min=\"%d\" max=\"%d\">\n";
#endif
    
    l = utf_snprintf(dst, size, format, clazz, getId(), getMinOccurs(), getMaxOccurs());
    length += l;
    if ((size -= l) < 0) goto finish;
    dst += l;
    
    
    l = appendContent(dst, size, level+1);
    length += l;
    if ((size -= l) < 0) goto finish;
    dst += l;
    
    l = appendSpace(dst, size, level);
    length += l;
    if ((size -= l) < 0) goto finish;
    dst += level;

#if defined(UTF8)
    format = "</%U>\n";
#elif defined(UTF16)
    format = "</%lU>\n";
#else
    format = "</%llU>\n";
#endif

    length += utf_snprintf(dst, size, format, getXmlTag());

finish:
     return length;
  }
  
  static char_type parseFirstCharacter(const char_type* s);
  
  virtual Iterator* singleIterator() const = 0;
  
  virtual Iterator* iterator() const = 0;
  
  int getId() const { return id; }
  
protected:
  log4cpp::Category& LOGGER;
  
  virtual int createId() {
    return ++next_id;
  }
  
private:
  Quantifier quantifier;
  static int next_id;
  int id;
};

#endif