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


#ifndef REXGENPARSERCONTEXT_H
#define REXGENPARSERCONTEXT_H

#include <iostream>
#include <map>
#include <set>
#include <cstdio>
#include <librexgen/regex/groupreference.h>
#include <librexgen/regex/streamregex.h>
#include <librexgen/string/uchar.h>
#include <librexgen/rexgen_options.h>

using namespace std;

class Regex;

class RexgenParserContext {

 public:
  RexgenParserContext(istream* input, const RexgenOptions& __options )
    : options(__options), streamRegex(NULL) {
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
  istream* is;
  Regex* result;

  int groupId;

  FILE* getInFile() const { return options.infile; }
  callback_fp getStreamCallback() const { return options.stream_callback; }

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
