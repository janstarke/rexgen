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


#include <librexgen/regex/compoundregex.h>
#include <librexgen/regex/terminalregex.h>
#include <librexgen/iterator/compoundregexiterator.h>
#include <librexgen/debug.h>

void CompoundRegex::prependRegex(Regex* regex) {
  ENTER_METHOD;

  /* optimization for terminals */
  if (regex->getRegexType() == Terminal) {
    if (regexObjects.size() > 0) {
      if (regexObjects[0]->getRegexType() == Terminal) {
        TerminalRegex* tre = reinterpret_cast<TerminalRegex*>(regexObjects[0]);
        if (regex->getMinOccurs() == 1
              && regex->getMaxOccurs() == 1
              && tre->getMinOccurs() == 1
              && tre->getMaxOccurs() == 1) {
          TerminalRegex* tre_new = reinterpret_cast<TerminalRegex*>(regex);
          tre->prepend(tre_new);
          LEAVE_METHOD;
        }
      }
    }
  }

  regexObjects.push_front(regex);
  LEAVE_METHOD;
}

void CompoundRegex::appendRegex(Regex* regex) {
  ENTER_METHOD;
  regexObjects.push_back(regex);
  LEAVE_METHOD;
}

Iterator* CompoundRegex::singleIterator(IteratorState* state) const {
  CompoundRegexIterator* cri = new CompoundRegexIterator(getId());
  for (auto iter = regexObjects.cbegin();
       iter != regexObjects.cend(); ++iter) {
    cri->addChild((*iter)->iterator(state));
  }
  return cri;
}

Iterator* CompoundRegex::iterator(IteratorState* state) const {
  if (regexObjects.size() == 1) {
    Regex* re = regexObjects[0];
    if (getMinOccurs() == 1 && getMaxOccurs() == 1) {
      return re->iterator(state);
    } else {
      return new IteratorPermuter(
        re->getId(), re, state, getMinOccurs(), getMaxOccurs());
    }
  }
  return RegexContainer::iterator(state);
}


