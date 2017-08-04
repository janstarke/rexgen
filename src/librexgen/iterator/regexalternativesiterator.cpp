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

#include <librexgen/iterator/regexalternativesiterator.h>
#include <librexgen/debug.h>
#include <librexgen/string/unicode.h>
#include <assert.h>
#include <cstring>
#include <deque>
#include <vector>
#include <set>

RegexAlternativesIterator::RegexAlternativesIterator(int _id)
  : IteratorContainer(_id) {
  resetPosition();
  state = resetted;
}

bool RegexAlternativesIterator::next() {
  ENTER_METHOD;

  if (state == resetted) {
    state = usable;
    bool res = false;
    for (auto i : iterators) {
      res |= (i->next());
    }
    RETURN(res);
  }

  if ((*getPosition())->next()) {
    RETURN(true);
  }
  incrementPosition();
  if (getPosition() == iterators.end()) {
    resetPosition();
    RETURN(false);
  }
  // (*iter)->next();
  RETURN(true);
}

bool RegexAlternativesIterator::hasNext() const {
  ENTER_METHOD;
  if (iterators.size() == 0 || state == not_usable) {
    /* if we don't have any iterator, you cannot call next() */
    RETURN(false);
  }

  if (state == resetted) {
    /* we can return true here,
     * because we know that we have at least one iterator
     */
    RETURN(true);
  }

  if (getPosition() == iterators.end()) {
    RETURN(false);
  }

  if ((*(getPosition()))->hasNext()) {
    RETURN(true);
  } else {
    children_list_type::iterator tmp = getPosition();
    ++tmp;
    RETURN(tmp != iterators.end());
  }
}

void RegexAlternativesIterator::addChild(Iterator* i) {
  ENTER_METHOD;
  iterators.push_back(i);
  resetPosition();
//  i->next();
  LEAVE_METHOD;
}

bool RegexAlternativesIterator::canUseValue() const {
  if (!Iterator::canUseValue()) {
    return false;
  }
  if (getPosition() == iterators.end()) {
    return false;
  }
  return ((*(getPosition()))->canUseValue());
}

SerializableState* RegexAlternativesIterator::getCurrentState() const {
  SerializableState* s = Iterator::getCurrentState();
  s->addValue(getPosition() - iterators.begin());

  for (auto i : iterators) {
    s->addValue(i->getCurrentState());
  }
  return s;
}

void RegexAlternativesIterator::setCurrentState(const SerializableState* s) {
  Iterator::setCurrentState(s);

  for (auto i : iterators) {
    i->setCurrentState(s->getChildState(i->getId()));
  }

  setPosition(iterators.begin() + s->getValue(0));
}
