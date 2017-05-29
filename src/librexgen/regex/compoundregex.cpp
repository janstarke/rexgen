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


#include <librexgen/regex/compoundregex.h>
#include <librexgen/regex/terminalregex.h>
#include <librexgen/iterator/compoundregexiterator.h>
#include <librexgen/debug.h>
#include <deque>

void CompoundRegex::prependRegex(Regex* regex) {
  ENTER_METHOD;

  /* optimization for terminals */
  if (regex->getRegexType() == Terminal) {
    if (children() > 0) {
      if (firstChild()->getRegexType() == Terminal) {
        TerminalRegex* tre = reinterpret_cast<TerminalRegex*>(firstChild());
        if (regex->getMinOccurs() == 1
            && regex->getMaxOccurs() == 1
            && tre->getMinOccurs() == 1
            && tre->getMaxOccurs() == 1) {
          TerminalRegex* tre_new = reinterpret_cast<TerminalRegex*>(regex);
          tre->prepend(tre_new);

          /* we have merged two terminals,
           * so we don't need the first one anymore
           */
          delete regex;
          LEAVE_METHOD;
        }
      }
    }
  }

  push_front(regex);
  LEAVE_METHOD;
}

void CompoundRegex::appendRegex(Regex* regex) {
  ENTER_METHOD;
  push_back(regex);
  LEAVE_METHOD;
}

Iterator* CompoundRegex::singleIterator(IteratorState* state) const {
  if (children() == 1) {
    return firstChild()->iterator(state);
  }

  CompoundRegexIterator* cri = new CompoundRegexIterator(getId());
  mapToChildren([&cri, state](const Regex* re){
    cri->addChild(re->iterator(state));
  });
  return cri;
}

Iterator* CompoundRegex::iterator(IteratorState* state) const {
  if (children() == 1) {
    if (getMinOccurs() == 1 && getMaxOccurs() == 1) {
      return firstChild()->iterator(state);
    } else {
      return new IteratorPermuter(
              firstChild()->getId(), firstChild(), state, getMinOccurs(), getMaxOccurs());
    }
  }
  return RegexContainer::iterator(state);
}


