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

#include <librexgen/regex/quantifier.h>
#include <librexgen/iterator/iterator.h>
#include <iostream>
#include <librexgen/unicode.h>
#include <librexgen/debug.h>
#include <librexgen/iterator/iteratorstate.h>
#include <librexgen/simplestring.h>

typedef enum {
  Compound,
  Alternative,
  Terminal,
  Class,
  Reference
} RegexType;

class Regex  {
public:
  Regex() : quantifier(1,1) {id=createId();}
  virtual ~Regex() {}
  
  inline unsigned int getMinOccurs() const { return quantifier.getMin(); }
  inline unsigned int getMaxOccurs() const { return quantifier.getMax(); }
  
  inline void setMinOccurs(unsigned int _min) { quantifier.setMin(_min); }
  inline void setMaxOccurs(unsigned int _max) { quantifier.setMax(_max); }
  
  inline void setQuantifier(const Quantifier& q) { quantifier = q; }
    
  virtual const char* getXmlTag() const = 0;
  virtual RegexType getRegexType() const = 0;
  
  virtual inline int getMaxSize() const {
    return getMaxOccurs();
  }
  
  inline void appendRawValue(SimpleString& dst) const {
    appendRawValue(dst, 0);
  }
  
  inline void appendRawValue(SimpleString& dst, int level) const {
    return xmlEncapsulate(dst, getXmlTag(), level);
  }
  
  void appendSpace(SimpleString& dst, int count) const;
  
  virtual void appendContent(SimpleString& dst, int level) const = 0;
  
  virtual void xmlEncapsulate(SimpleString& dst, const char* clazz, int level) const;
  
  virtual Iterator* singleIterator(IteratorState* state) const = 0;  
  virtual Iterator* iterator(IteratorState* state) const = 0;
  
  Iterator* iterator() const { return iterator(new IteratorState()); };
  
  int getId() const { return id; }
  
  virtual int getGroupId() const { return -1; }
  
protected:
  
  virtual int createId() {
    return ++next_id;
  }
  
private:
  Quantifier quantifier;
  static int next_id;
  int id;
};

#endif