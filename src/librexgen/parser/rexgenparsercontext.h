/*
    rexgen - a tool to create words based on regular expressions
    Copyright (C) 2012-2017  Jan Starke <jan.starke@outofbed.org>

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


#ifndef SRC_LIBREXGEN_PARSER_REXGENPARSERCONTEXT_H_
#define SRC_LIBREXGEN_PARSER_REXGENPARSERCONTEXT_H_

#include <librexgen/regex/streamregex.h>
#include <librexgen/regex/groupreference.h>
#include <librexgen/rexgen_options.h>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <cstdio>

class Regex;

class RexgenParserContext {
 public:
  RexgenParserContext(const char* input, const RexgenOptions& __options);

  virtual ~RexgenParserContext();
  void registerGroupReference(GroupReference* gr);
  const std::set<GroupReference*>* getGroupReferences(int id) const;
  void registerGroup(Regex* re);
  Regex* getGroupRegex(int id) const;

  const map<int, Regex*>& getGroups() const;

  void updateAllGroupReferences();
  void updateGroupReferences(const Regex* re);
  bool hasInvalidGroupReferences() const;

  void* scanner;
  std::vector<wchar_t> wcinput;
  std::vector<wchar_t>::const_iterator next_char;
  wchar_t current_char;
  Regex* result;

  int groupId;

  FILE* getInFile() const { return options.infile; }
  callback_fp_mb getStreamCallback() const { return options.stream_callback; }

  bool hasNextChar() const { return (next_char != wcinput.cend()); }
  wchar_t getNextChar();
  wchar_t getCurrentChar() const { return current_char; }

  /** this is the handling of `\0` - terminals in the regex. the first occurance
   * of `\0` creates a StreamRegex and returns it, all following occurances
   * return a reference to the previously created StreamRegex.
   * We must make this distinction, because StreamReference handles
   * calls to next() by going to the next word, and calling next() for
   * the whole regex would result in multiple calls to next() for each single
   * occurance of `\0`. So, we return a GroupReference, which does not forward
   * the invocation of next() to the StreamRegex
   */
  Regex* getStreamRegex();

 protected:
  /**
   * initialize the scanner. This method is implemented
   * in regex_lexer.l
   */
  void InitScanner();

  /**
   * destroy the scanner and clean up the allocated memory.
   * This method is implemented in regex_lexer.l
   */
  void DestroyScanner();

 private:
  const RexgenOptions& options;
  std::map<int, std::set <GroupReference*> *> groupRefs;
  std::map<int, Regex*> groups;
  StreamRegex* streamRegex;
};

#endif  // SRC_LIBREXGEN_PARSER_REXGENPARSERCONTEXT_H_
