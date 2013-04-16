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


#include <librexgen/parser/rexgenparsercontext.h>
#include <algorithm>
#include <utility>

void RexgenParserContext::updateAllGroupReferences() {
  for_each(groups.cbegin(), groups.cend(), [this](pair<int, Regex*> p) {
    updateGroupReferences(p.second);
  });
}

void RexgenParserContext::updateGroupReferences(const Regex* re) {
  for_each(groupRefs.begin(), groupRefs.end(),
      [re](pair<int, GroupReference*> gr) {
    if (gr.first == re->getGroupId()) {
      gr.second->setRegex(re);
    }
  });
}

bool RexgenParserContext::hasInvalidGroupReferences() const {
  bool invalids = false;
  for_each(groupRefs.cbegin(), groupRefs.cend(),
  [&invalids](pair<int, GroupReference*> gr) {
    invalids |= (gr.second->getRegex() == NULL);
  });
  return invalids;
}

RexgenParserContext::~RexgenParserContext() {
  DestroyScanner();
}

