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


#include <librexgen/parser/rexgenparsercontext.h>
#include <librexgen/parser/syntaxerror.h>
#include <librexgen/regex/regexcontainer.h>
#include <librexgen/regex/regexbackreference.h>
#include <algorithm>
#include <utility>

void RexgenParserContext::updateAllGroupReferences() {
  for (auto p : groups) {
    updateGroupReferences(p.second);
  }
}

void RexgenParserContext::checkCycles() const {
  for (auto p : groups) {
		checkCycles(p.first, dynamic_cast<const Regex*>(p.second));
  }
}


void RexgenParserContext::checkCycles(int gId, const Regex* re) const {
	switch (re->getRegexType()) {
		case Reference:
			if (re->getGroupId() == gId) {
					throw SyntaxError("invalid group reference found");
			}
			break;

		case Alternative:
		case Compound:
			dynamic_cast<const RegexContainer*>
				(re)->mapToConstChildren([gId,this](const Regex* r) {
					this->checkCycles(gId, r);
				});
			break;

		default:
			break;
	}
}

void RexgenParserContext::updateGroupReferences(const Regex* re) {
  for (map<int, set<GroupReference*> *>::const_iterator ref=groupRefs.begin();
       ref!=groupRefs.end(); ++ref) {
    for (set<GroupReference*>::iterator gr=(*ref).second->begin();
         gr!=(*ref).second->end(); ++gr) {
      if ((*ref).first == re->getGroupId()) {
        (*gr)->setRegex(re);
      }
    }
  }
}

bool RexgenParserContext::hasInvalidGroupReferences() const {
  bool invalids = false;
  for (map<int, set<GroupReference*> *>::const_iterator ref=groupRefs.begin();
       ref!=groupRefs.end(); ++ref) {
    for (set<GroupReference*>::iterator gr=(*ref).second->begin();
         gr!=(*ref).second->end(); ++gr) {
      invalids |= ((*gr)->getRegex() == NULL);
    }
  }
  return invalids;
}

RexgenParserContext::~RexgenParserContext() {
  DestroyScanner();

  for (map<int, set<GroupReference*> *>::const_iterator ref=groupRefs.begin();
       ref!=groupRefs.end(); ++ref) {
    delete (*ref).second;
  }
}

void RexgenParserContext::registerGroupReference(GroupReference* gr) {
  /* this is neeeded to later set the refered Regex */
  map<int, set<GroupReference*>*>::iterator references = groupRefs.find(
        gr->getGroupId());
  if (references == groupRefs.end()) {
    groupRefs[gr->getGroupId()] = new set<GroupReference* >();
    references = groupRefs.find(gr->getGroupId());
  }

  (*references).second->insert(gr);
}

const set<GroupReference*>* RexgenParserContext::getGroupReferences(
  int id) const {
  map<int, set<GroupReference*>*>::const_iterator references = groupRefs.find(id);
  if (references == groupRefs.end()) {
    return NULL;
  }
  return (*references).second;
}

void RexgenParserContext::registerGroup(Regex* re) {
  groups[re->getGroupId()] = re;
}
Regex* RexgenParserContext::getGroupRegex(int id) const {
  map<int, Regex*>::const_iterator iter = groups.find(id);
  if (iter != groups.end()) {
    return iter->second;
  }
  return NULL;
}

const map<int, Regex*>& RexgenParserContext::getGroups() const { return groups; }

/* this is the handling of \0 - terminals in the regex. the first occurance
 * of \0 creates a StreamRegex and returns it, all following occurances
 * return a reference to the previously created StreamRegex.
 * We must make this distinction, because StreamReference handles
 * calls to next() by going to the next word, and calling next() for
 * the whole regex would result in multiple calls to next() for each single
 * occurance of \0. So, we return a GroupReference, which does not forward
 * the invocation of next() to the StreamRegex
 */
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

Regex* RexgenParserContext::cloneCaptureGroup(int gId) {
	Regex* re = groups[gId];
	return new RegexBackreference(re);
}
