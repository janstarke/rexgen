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


#ifndef REXGENPARSERCONTEXT_H
#define REXGENPARSERCONTEXT_H

#include <iostream>
#include <map>
#include "../regex/regex.h"
#include <librexgen/regex/groupreference.h>
#include <librexgen/unicode/uchar.h>

using namespace std;

class RexgenParserContext
{

public:
  RexgenParserContext(istream* input = &cin, bool _ic = false, charset _enc=CHARSET_UTF8)
  : ic(_ic), enc(_enc) {
    this->is = input;
    this->result = NULL;
    this->scanner = NULL;
    groupId = 1;
    InitScanner();
  }
  
  virtual ~RexgenParserContext();
  
  void registerGroupReference(GroupReference* gr) {
    groupRefs[gr->getGroupId()] = gr;
  }
  
  GroupReference* getGroupReference(int id) const {
    return groupRefs.at(id);
  }
  
  void registerGroup(Regex* re) {
    groups[re->getGroupId()] = re;
  }
  Regex* getGroupRegex(int id) const {
    return groups.at(id);
  }
  
  const map<int, Regex*>& getGroups() const { return groups; }
  
  void updateAllGroupReferences();
  void updateGroupReferences(const Regex* re);
  bool hasInvalidGroupReferences() const;

  void* scanner;
  istream * is;
  Regex* result;
  
  int groupId;
  
  bool ignoreCase() const { return ic; }
  charset encoding() const { return enc; }

protected:
  void InitScanner();
  void DestroyScanner();
  
private:
  const bool ic;
  const charset enc;
  map<int, GroupReference*> groupRefs;
  map<int, Regex*> groups;
};

#endif // REXGENPARSERCONTEXT_H
