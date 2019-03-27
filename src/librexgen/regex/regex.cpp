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
#include <librexgen/iterator/compoundregexiterator.h>

namespace rexgen {
  int Regex::next_id = 0;

  std::shared_ptr<Iterator> Regex::iterator(IteratorState& state) const {
    if (getMinOccurs() == 1 && getMaxOccurs() == 1) {
      return singleIterator(state);
    }

    auto compound = std::make_shared<CompoundRegexIterator>();
    for (unsigned int n=0; n<getMinOccurs(); ++n) {
      compound->addChild(singleIterator(state));
    }
    assert(getMaxOccurs() >= getMinOccurs());
    if (getMinOccurs() != getMaxOccurs()) {
      compound->addChild(std::make_shared<IteratorPermuter>(*this, state, getMaxOccurs() - getMinOccurs()));
    }
    return compound;
  }
}