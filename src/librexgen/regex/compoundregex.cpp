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
#include <memory>
namespace rexgen {
  void CompoundRegex::prependRegex(const std::shared_ptr<Regex>& regex) {
    ENTER_METHOD;

    /* optimization for terminals */
    if (regexObjects.size() > 0) {

      /* check if provided regex is terminal */
      auto regex_terminal = std::dynamic_pointer_cast<TerminalRegex>(regex);
      if (regex_terminal != nullptr) {

        /* check if first regex is terminal */
        auto tre = std::dynamic_pointer_cast<TerminalRegex>(regexObjects[0]);
        if (tre != nullptr) {
          if (regex->getMinOccurs() == 1
              && regex->getMaxOccurs() == 1
              && tre->getMinOccurs() == 1
              && tre->getMaxOccurs() == 1) {
            tre->prepend(regex_terminal);

            LEAVE_METHOD;
          }
        }
      }
    }

    regexObjects.push_front(std::move(regex));
    LEAVE_METHOD;
  }

  void CompoundRegex::appendRegex(const std::shared_ptr<Regex>& regex) {
    ENTER_METHOD;
    regexObjects.push_back(regex);
    LEAVE_METHOD;
  }

  Iterator *CompoundRegex::singleIterator(IteratorState *state) const {
    if (regexObjects.size() == 1) {
      return regexObjects[0]->iterator(state);
    }

    CompoundRegexIterator *cri = new CompoundRegexIterator(getId());
    std::for_each(regexObjects.begin(), regexObjects.end(),
            [&cri,&state](const std::shared_ptr<Regex>& r) {cri->addChild(r->iterator(state));});
    return cri;
  }

  Iterator *CompoundRegex::iterator(IteratorState *state) const {
    if (regexObjects.size() == 1) {
      const std::shared_ptr<Regex>& re = regexObjects[0];
      if (getMinOccurs() == 1 && getMaxOccurs() == 1) {
        return re->iterator(state);
      } else {
        return new IteratorPermuter(
                re->getId(), re.get(), state, getMinOccurs(), getMaxOccurs());
      }
    }
    return RegexContainer::iterator(state);
  }
}

