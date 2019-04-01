/*
    rexgen - a tool to create words based on regular expressions
    Copyright (C) 2012-2017 Jan Starke <jan.starke@outofbed.org>

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

#include <librexgen/iterator/topiterator.h>
#include <catch2/catch.hpp>
#include <list>
#include "utils.h"
#include <boost/regex.hpp>

bool matches(const std::string& value, const boost::regex& regex) {
  return boost::regex_match(value, regex);
}

size_t count(std::shared_ptr<rexgen::TopIterator> iter, const boost::regex& regex, bool stateful) {
  size_t cnt = 0;
  std::string str;

  while (iter->next()) {
    str.clear();
    iter->value(str);
    REQUIRE(matches(str, regex));
    ++cnt;

    if (stateful) {
      /* save and restore the iterator state */
      auto s = iter->getCurrentState();
      iter->setCurrentState(s);
    }
  }
  return cnt;
}

void validateRegex(const char* input_regex,
                   const size_t nValues) {
  boost::regex _re(input_regex);

  rexgen::RexgenOptions options;
  auto regex = parse_regex(input_regex, options);
  REQUIRE(regex != nullptr);

  REQUIRE(count(std::make_shared<rexgen::TopIterator>(regex), _re, true) == nValues);
  REQUIRE(count(std::make_shared<rexgen::TopIterator>(regex), _re, false) == nValues);
}

void validateFailure(const char* input_regex) {
  rexgen::RexgenOptions options;
  auto regex = parse_regex(input_regex, options);

  rexgen::IteratorState state;
  auto iter = regex->singleIterator(state);

  REQUIRE_THROWS(iter->next());
}