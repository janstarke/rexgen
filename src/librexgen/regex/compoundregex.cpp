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


#include "compoundregex.h"
#include "terminalregex.h"
#include "../iterator/compoundregexiterator.h"
#include "../debug.h"

CompoundRegex::~CompoundRegex()
{
  for (container_type::iterator iter = regexObjects.begin();
       iter != regexObjects.end();
       iter++) {
    delete *iter;
  }
}

void CompoundRegex::prependRegex(Regex* regex) {
  ENTER_METHOD;
  
  /* optimization for terminals */
  if (regex->getRegexType() == Terminal) {
    if (regexObjects.size() > 0) {
      if (regexObjects[0]->getRegexType() == Terminal) {
	TerminalRegex* tre = dynamic_cast<TerminalRegex*>(regexObjects[0]);
	if (	regex->getMinOccurs() == 1
	  &&	regex->getMaxOccurs() == 1
	  &&	tre->getMinOccurs() == 1
	  &&	tre->getMaxOccurs() == 1) {
	  TerminalRegex* tre_new = dynamic_cast<TerminalRegex*>(regex);
	  tre->prependSingleCharacter(tre_new->getValue());
	  LEAVE_METHOD;
	}
      }
    }
  }
  
  regexObjects.push_front(regex);
  LEAVE_METHOD;
}

void CompoundRegex::appendRegex(Regex* regex) {
  ENTER_METHOD;
  regexObjects.push_back(regex);
  LEAVE_METHOD;
}

Iterator* CompoundRegex::singleIterator(IteratorState* state) const
{
  CompoundRegexIterator* cri = new CompoundRegexIterator(getId());
  for (container_type::const_iterator iter = regexObjects.begin();
	iter != regexObjects.end();iter++) {
    cri->addChild((*iter)->iterator(state));
  }
  return cri;
}

Iterator* CompoundRegex::iterator(IteratorState* state) const
{
    if (regexObjects.size() == 1) {
    Regex* re = regexObjects[0];
    if (getMinOccurs() == 1 && getMaxOccurs() == 1) {
      return re->iterator(state);
    } else {
      return new IteratorPermuter<Regex>(re->getId(), re, state, getMinOccurs(), getMaxOccurs());
    }
  }

  if (getMinOccurs() == 1 && getMaxOccurs() == 1) {
    return singleIterator(state);
  } else {
    return new IteratorPermuter<CompoundRegex>(getId(), this, state, getMinOccurs(), getMaxOccurs());
  }
}


