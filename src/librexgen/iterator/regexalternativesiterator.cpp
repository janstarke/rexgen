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
namespace rexgen {
  RegexAlternativesIterator::RegexAlternativesIterator()
          : IteratorContainer() {
    resetPosition();
    state = resetted;
  }

  bool RegexAlternativesIterator::next() {
    ENTER_METHOD;

    if (state == resetted) {
      state = usable;
      bool res = false;
      for (std::unique_ptr<Iterator>& i : iterators) {
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

  void RegexAlternativesIterator::addChild(std::unique_ptr<Iterator>&& i) {
    ENTER_METHOD;
    IteratorContainer::addChild(std::move(i));
    resetPosition();
//  i->next();
    LEAVE_METHOD;
  }

  std::shared_ptr<SerializableState> RegexAlternativesIterator::getCurrentState() const {
    auto s = Iterator::getCurrentState();
    s->addValue(getPosition() - iterators.begin());

    for (const std::unique_ptr<Iterator>& i : iterators) {
      s->addValue(i->getCurrentState());
    }
    return s;
  }

  void RegexAlternativesIterator::setCurrentState(const std::shared_ptr<SerializableState>& s) {
    Iterator::setCurrentState(s);

    for (std::unique_ptr<Iterator>& i : iterators) {
      i->setCurrentState(s->getChildState(i->getId()));
    }

    setPosition(iterators.begin() + s->getValue(0));
  }
}