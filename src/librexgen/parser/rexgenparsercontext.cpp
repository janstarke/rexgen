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


#include <librexgen/parser/rexgenparsercontext.h>
#include <algorithm>
#include <utility>
#include <cstring>

RexgenParserContext::RexgenParserContext(const char* input,
                                         const RexgenOptions& __options)
        : options(__options), streamRegex(NULL) {
  this->result = NULL;
  this->scanner = NULL;
  groupId = 1;
  InitScanner();

  int size;
  wchar_t wc = 0;
  mbstate_t mbs;
  std::memset(&mbs, 0, sizeof(mbs));
  do {
    size = mbrtowc(&wc, input, MB_CUR_MAX, &mbs);
    if (size > 0) {
      wcinput.push_back(wc);
      input += size;
    }
  } while (size > 0);
  next_char = wcinput.cbegin();
}

/**
 * iterates through all group references and calls
 * updateGroupReferences for each
 */
void RexgenParserContext::updateAllGroupReferences() {
  for (auto p : groups) {
    updateGroupReferences(p.second);
  }
}

void RexgenParserContext::updateGroupReferences(const Regex* re) {
  for (auto ref : groupRefs) {
    for (auto gr : (*ref.second)) {
      if (ref.first == re->getGroupId()) {
        gr->setRegex(re);
      }
    }
  }
}

bool RexgenParserContext::hasInvalidGroupReferences() const {
  bool invalids = false;
  for (auto ref : groupRefs) {
    for (auto gr : *(ref.second)) {
      invalids |= (gr->getRegex() == NULL);
    }
  }
  return invalids;
}

RexgenParserContext::~RexgenParserContext() {
  DestroyScanner();

  for (auto ref : groupRefs) {
    delete ref.second;
  }
}

void RexgenParserContext::registerGroupReference(GroupReference* gr) {
  /* this is needed to later set the refered Regex */
  std::map<int, std::set<GroupReference*>*>::iterator references =
          groupRefs.find(gr->getGroupId());
  if (references == groupRefs.end()) {
    groupRefs[gr->getGroupId()] = new std::set<GroupReference* >();
    references = groupRefs.find(gr->getGroupId());
  }
  (*references).second->insert(gr);
}

const std::set<GroupReference*>* RexgenParserContext::getGroupReferences(
  int id) const {
  auto references = groupRefs.find(id);
  if (references == groupRefs.end()) {
    return NULL;
  }
  return (*references).second;
}

void RexgenParserContext::registerGroup(Regex* re) {
  groups[re->getGroupId()] = re;
}
Regex* RexgenParserContext::getGroupRegex(int id) const {
  std::map<int, Regex*>::const_iterator iter = groups.find(id);
  if (iter != groups.end()) {
    return iter->second;
  }
  return NULL;
}

const std::map<int, Regex*>& RexgenParserContext::getGroups() const {
  return groups;
}

Regex* RexgenParserContext::getStreamRegex() {
  if (streamRegex == NULL) {
    streamRegex = new StreamRegex(options.stream_callback);
    return streamRegex;
  } else {
    GroupReference* gr = new GroupReference(streamRegex->getId());
    gr->setRegex(streamRegex);
    return gr;
  }
}

wchar_t RexgenParserContext::getNextChar() {
  current_char = *next_char;
  ++next_char;
  return current_char;
}
