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


#include <librexgen/regex/regexalternatives.h>
#include <librexgen/iterator/regexalternativesiterator.h>
#include <algorithm>
using namespace std;

RegexAlternatives::~RegexAlternatives() {
  for (container_type::iterator iter = regexObjects.begin();
       iter != regexObjects.end();
       ++iter) {
    delete (*iter);
  }
}

int RegexAlternatives::getMaxSize() const {
  int __max = 0;
  int __size = 0;
  for (container_type::const_iterator iter = regexObjects.begin();
       iter != regexObjects.end();
       ++iter) {
    __size = (*iter)->getMaxSize();
    __max = max(__size, __max);
  }
  return __max * getMaxOccurs();
}

Iterator* RegexAlternatives::singleIterator(IteratorState* state) const {
  RegexAlternativesIterator* rai = new RegexAlternativesIterator(getId());
  for (auto iter = regexObjects.begin(); iter != regexObjects.end(); iter++) {
    rai->addChild((*iter)->iterator(state));
  }
  return rai;
}

Iterator* RegexAlternatives::iterator(IteratorState* state) const {
  Iterator* iter = NULL;
  if (regexObjects.size() == 1) {
    Regex* re = regexObjects[0];
    if (getMinOccurs() == 1 && getMaxOccurs() == 1) {
      iter = re->iterator(state);
    } else {
      iter = new IteratorPermuter(
        re->getId(), re, state, getMinOccurs(), getMaxOccurs());
    }
  } else {
    if (getMinOccurs() == 1 && getMaxOccurs() == 1) {
      iter = singleIterator(state);
    } else {
      iter = new IteratorPermuter(
        getId(), this, state, getMinOccurs(), getMaxOccurs());
    }
  }

  if (getGroupId() > 0) {
    state->registerIterator(getGroupId(), iter);
  }

  return iter;
}
