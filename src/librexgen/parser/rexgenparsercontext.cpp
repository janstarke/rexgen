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
#include <algorithm>
#include <utility>

void RexgenParserContext::updateAllGroupReferences() {
  for_each(groups.cbegin(), groups.cend(), [this](pair<int, Regex*> p) {
    updateGroupReferences(p.second);
  });
}

void RexgenParserContext::updateGroupReferences(const Regex* re) {
	for (auto ref=groupRefs.begin(); ref!=groupRefs.end(); ++ref) {
		for (auto gr=(*ref).second->begin(); gr!=(*ref).second->end(); ++gr) {
			if ((*ref).first == re->getGroupId()) {
				(*gr)->setRegex(re);
			}
		}
	}
}

bool RexgenParserContext::hasInvalidGroupReferences() const {
  bool invalids = false;
	for (auto ref=groupRefs.cbegin(); ref!=groupRefs.cend(); ++ref) {
		for (auto gr=(*ref).second->cbegin(); gr!=(*ref).second->cend(); ++gr) {
			invalids |= ((*gr)->getRegex() == NULL);
		}
	}
  return invalids;
}

RexgenParserContext::~RexgenParserContext() {
  DestroyScanner();

	for_each(groupRefs.begin(), groupRefs.end(),
		[](pair<int, set<GroupReference*> *> ref) 
	{
		delete ref.second;
	});
}

 void RexgenParserContext::registerGroupReference(GroupReference* gr) {
	 /* this is neeeded to later set the refered Regex */
	 auto references = groupRefs.find(gr->getGroupId());
	 if (references == groupRefs.end()) {
		 groupRefs[gr->getGroupId()] = new set<GroupReference* >();
		 references = groupRefs.find(gr->getGroupId());
	 }
	 (*references).second->insert(gr);
 }
  
 const set<GroupReference*>* RexgenParserContext::getGroupReferences(int id) const {
   auto references = groupRefs.find(id);
	 if (references == groupRefs.end()) {
		 return nullptr;
	 }
	 return (*references).second;
 }
  
 void RexgenParserContext::registerGroup(Regex* re) {
   groups[re->getGroupId()] = re;
 }
 Regex* RexgenParserContext::getGroupRegex(int id) const {
   return groups.at(id);
 }
 
const map<int, Regex*>& RexgenParserContext::getGroups() const { return groups; }

Regex* RexgenParserContext::getStreamRegex() {
 if (streamRegex == nullptr) {
    streamRegex = new StreamRegex(options.infile);
    return streamRegex;
  } else {
    GroupReference* gr = new GroupReference(streamRegex->getId());
    gr->setRegex(streamRegex);
    return gr;
  }
}
