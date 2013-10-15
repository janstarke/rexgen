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
#include <set>
#include <cstdio>
#include <librexgen/regex/groupreference.h>
#include <librexgen/regex/streamregex.h>
#include <librexgen/unicode/uchar.h>
#include <librexgen/rexgen_options.h>

using namespace std;

class Regex;

class RexgenParserContext
{

public:
  RexgenParserContext(istream* input, const RexgenOptions& __options )
		: options(__options), streamRegex(nullptr) {
    this->is = input;
    this->result = NULL;
    this->scanner = NULL;
    groupId = 1;
    InitScanner();
  }
  
  virtual ~RexgenParserContext();
  void registerGroupReference(GroupReference* gr);
  const set<GroupReference*>* getGroupReferences(int id) const;
  void registerGroup(Regex* re);
  Regex* getGroupRegex(int id) const;
  
  const map<int, Regex*>& getGroups() const;
  
  void updateAllGroupReferences();
  void updateGroupReferences(const Regex* re);
  bool hasInvalidGroupReferences() const;

  void* scanner;
  istream * is;
  Regex* result;
  
  int groupId;
  
  bool ignoreCase() const { return options.ignore_case; }
  charset encoding() const { return options.encoding; }
  FILE* getInFile() const { return options.infile; }
  
  Regex* getStreamRegex();

protected:
  void InitScanner();
  void DestroyScanner();
  
private:
  const RexgenOptions& options;
  map<int, set <GroupReference*> *> groupRefs;
  map<int, Regex*> groups;
  StreamRegex* streamRegex;
};

#endif // REXGENPARSERCONTEXT_H
