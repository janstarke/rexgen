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

#include <librexgen/regex/regex.h>
#include <librexgen/iterator/iteratorpermuter.h>
#include <set>

IteratorPermuter::IteratorPermuter(int _id, const Regex* re, IteratorState* is,
                                   unsigned int min, unsigned int max)
  : IteratorContainer(_id), min_occurs(min), max_occurs(max), regex(re),
    hasNextElement(true), occurs(min_occurs) {
  for (unsigned int n=0; n < max_occurs; ++n) {
    addChild(regex->singleIterator(is));
  }
  init();
}

IteratorPermuter::~IteratorPermuter() {
  for (auto i : iterators) {
    if (i->isSingleton()) {
      delete i;
    }
  }
}

void IteratorPermuter::value(SimpleString* dst) const {
  ENTER_METHOD;
  for (unsigned int n=0; n < occurs; ++n) {
    iterators[n]->value(dst);
  }
  LEAVE_METHOD;
}

bool IteratorPermuter::hasNext() const {
  ENTER_METHOD;

  if (state == resetted) {
    RETURN(true);
  }

  if (occurs < max_occurs) {
    RETURN(true);
  }

  RETURN(existsIteratorWithNextElement());
}

bool IteratorPermuter::next() {
  ENTER_METHOD;

  /* special case handling for resetted state */
  if (state == resetted) { state = usable; RETURN(true); }

  /* special case handling for quantifier which starts with 0, i.e. {0,3} */
  if (state == usable && occurs == 0) { ++occurs; RETURN(true); }

  unsigned int n = 0;
  for (; n < occurs; ++n) { if (iterators[n]->next()) { break; } }
  if (n == max_occurs) { occurs = min_occurs; RETURN(false); }
  if (n == occurs)  { ++occurs; }
  RETURN(true);
}

void IteratorPermuter::init() {
  ENTER_METHOD;

  bool has_next = false;
  for (auto i : iterators) {
    i->next();
    has_next |= i->hasNext();
  }
  hasNextElement = has_next;

  occurs = min_occurs;
  current = 0;
  state = resetted;
  LEAVE_METHOD;
}

bool IteratorPermuter::existsIteratorWithNextElement() const {
  ENTER_METHOD;
  for (auto i : iterators) {
    if (i->hasNext()) {
      RETURN(true);
    }
  }
  RETURN(false);
}

