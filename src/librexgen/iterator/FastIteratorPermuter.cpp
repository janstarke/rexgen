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
#include <librexgen/iterator/FastIteratorPermuter.h>
#include <set>
namespace rexgen {
  FastIteratorPermuter::FastIteratorPermuter(const Regex& re, IteratorState& is, unsigned int occurs)
          : IteratorContainer(), hasNextElement(true) {
    assert(occurs > 0);
    for (unsigned int n = 0; n < occurs; ++n) {
      addChild(re.singleIterator(is));
    }
    init();
  }

  void FastIteratorPermuter::value(SimpleString *dst) const {
    for (auto i : iterators) {
      i->value(dst);
    }
  }

  bool FastIteratorPermuter::next() {
    ENTER_METHOD;

    /* special case handling for resetted state */
    if (state == resetted) {
      state = usable;
      RETURN(true);
    }

    for (auto i : iterators) {
      if (i->next()) {
        return true;
      }
    }
    return false;
  }

  bool FastIteratorPermuter::hasNext() const {
    ENTER_METHOD;

    if (state == resetted) {
      RETURN(true);
    }

    RETURN(existsIteratorWithNextElement());
  }

  void FastIteratorPermuter::init() {
    ENTER_METHOD;

    bool has_next = false;
    for (auto i : iterators) {
      i->next();
      has_next |= i->hasNext();
    }
    hasNextElement = has_next;

    state = resetted;
    LEAVE_METHOD;
  }

  bool FastIteratorPermuter::existsIteratorWithNextElement() const {
    ENTER_METHOD;
    for (auto i : iterators) {
      if (i->hasNext()) {
        RETURN(true);
      }
    }
    RETURN(false);
  }

}