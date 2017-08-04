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

#ifndef SRC_LIBREXGEN_REGEX_REGEXCONTAINER_H_
#define SRC_LIBREXGEN_REGEX_REGEXCONTAINER_H_

#include <librexgen/regex/regex.h>
#include <librexgen/debug.h>
#include <librexgen/string/simplestring.h>
#include <deque>
#include <algorithm>

class RegexContainer : public Regex {
 public:
  virtual ~RegexContainer() {
    for (auto re : regexObjects) {
      delete re;
    }
  }

  virtual bool usesCallback() const {
    for (auto re : regexObjects) {
      if (re->usesCallback()) {
        return true;
      }
    }
    return Regex::usesCallback();
  }

 protected:
  std::deque<Regex*>* getChildren() { return &regexObjects; }
  std::deque<Regex*> regexObjects;
};

#endif  // SRC_LIBREXGEN_REGEX_REGEXCONTAINER_H_
