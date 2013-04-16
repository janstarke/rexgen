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
