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


#ifndef SRC_LIBREXGEN_REGEX_REGEXALTERNATIVES_H_
#define SRC_LIBREXGEN_REGEX_REGEXALTERNATIVES_H_

#include <librexgen/regex/regex.h>
#include <librexgen/regex/regexcontainer.h>
#include <librexgen/iterator/iteratorpermuter.h>
#include <librexgen/string/simplestring.h>
#include <librexgen/parser/group_options.h>
#include <deque>

class RegexAlternatives : public RegexContainer {
 public:
  RegexAlternatives(): RegexContainer(), groupId(-1), handle_case(CASE_IGNORE) {
  }
  inline void addRegex(Regex* regex) { getChildren()->push_front(regex); }

  RegexType getRegexType() const { return Alternative; }

  Iterator* iterator(IteratorState* state) const;

  Iterator* singleIterator(IteratorState* state) const;

  int getGroupId() const { return groupId; }
  void setGroupId(int _id) { groupId = _id; }

  void setGroupOptions(const t_group_options* opts) {
    handle_case = opts->handle_case;
    setGroupId(opts->group_id);
  }
 private:
  int groupId;
  int handle_case;
};

#endif  // SRC_LIBREXGEN_REGEX_REGEXALTERNATIVES_H_
