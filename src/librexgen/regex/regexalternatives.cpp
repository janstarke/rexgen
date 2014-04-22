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

#include <algorithm>
#include <librexgen/iterator/iteratorstate.h>
#include <librexgen/regex/regex.h>
#include <librexgen/regex/regexalternatives.h>
#include <librexgen/iterator/regexalternativesiterator.h>
using namespace std;

int RegexAlternatives::getMaxSize() const {
  int __max = 0;
  int __size = 0;
  for (deque<Regex*>::const_iterator iter = regexObjects.begin();
       iter != regexObjects.end();
       ++iter) {
    __size = (*iter)->getMaxSize();
    __max = max(__size, __max);
  }
  return __max * getMaxOccurs();
}

Iterator* RegexAlternatives::singleIterator(IteratorState* state) const {
  RegexAlternativesIterator* rai = new RegexAlternativesIterator(getId());
  for (deque<Regex*>::const_iterator iter = regexObjects.begin();
       iter != regexObjects.end(); iter++) {
    rai->addChild((*iter)->iterator(state));
  }
  return rai;
}

Iterator* RegexAlternatives::iterator(IteratorState* state) const {
  Iterator* iter = NULL;

  iter = state->getIterator(getGroupId());
  if (iter != NULL) {
    return iter;
  }

  if (regexObjects.size() == 1) {
    Regex* re = regexObjects[0];
    if (getMinOccurs() == 1 && getMaxOccurs() == 1) {
      iter = re->iterator(state);
    } else {
      iter = new IteratorPermuter(
        re->getId(), re, state, getMinOccurs(), getMaxOccurs());
    }
  } else {
    iter = RegexContainer::iterator(state);
  }

  if (getGroupId() > 0) {
    state->registerIterator(getGroupId(), iter);
  }

  return iter;
}
