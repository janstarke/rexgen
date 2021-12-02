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

#include <librexgen/iterator/iteratorstate.h>
#include <librexgen/regex/regexalternatives.h>
#include <librexgen/iterator/regexalternativesiterator.h>
#include <librexgen/iterator/compoundregexiterator.h>
#include <librexgen/iterator/caseiterator.h>
#include <librexgen/iterator/FastIteratorPermuter.h>

namespace rexgen {
  std::shared_ptr<Iterator> RegexAlternatives::singleIterator(IteratorState& state) const {
    if (regexObjects.size() == 1) {
      return regexObjects[0]->iterator(state);
    }

    auto rai = std::make_unique<RegexAlternativesIterator>();
    for (auto i : regexObjects) {
      rai->addChild(i->iterator(state));
    }
    return rai;
  }

  std::shared_ptr<Iterator> RegexAlternatives::iterator(IteratorState& state) const {

    std::shared_ptr<Iterator> iter;
    if (regexObjects.size() == 1) {
      if (getMinOccurs() == 1 && getMaxOccurs() == 1) {
        iter = regexObjects[0]->iterator(state);
      } else {
       iter = std::make_unique<IteratorPermuter>(*(regexObjects[0]), state, getMinOccurs(), getMaxOccurs());
      }
    } else {
      iter = RegexContainer::iterator(state);
    }

    if (handle_case != CASE_IGNORE) {
      iter = std::make_shared<CaseIterator>(iter, handle_case);
    }

    if (getGroupId() > 0) {
      state.registerIterator(getGroupId(), iter);
    }

    assert(iter != nullptr);
    return iter;
  }
}