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


#include <librexgen/regex/compoundregex.h>
#include <librexgen/regex/terminalregex.h>
#include <librexgen/iterator/compoundregexiterator.h>
#include <librexgen/debug.h>
#include <deque>

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

          /* we have merged two terminals,
           * so we don't need the first one anymore
           */
          delete regex;
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
  if (regexObjects.size() == 1) {
    return regexObjects[0]->iterator(state);
  }

  CompoundRegexIterator* cri = new CompoundRegexIterator(getId());
  for (std::deque<Regex*>::const_iterator iter = regexObjects.begin();
       iter != regexObjects.end(); ++iter) {
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


