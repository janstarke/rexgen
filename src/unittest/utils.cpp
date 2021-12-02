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

bool matches(const char* value, const char* regex) {
  boost::regex _re(regex);
  return boost::regex_match(value, _re);
}

static std::deque<std::string> stream_content_list;

size_t stream_callback(char* dst, const size_t buffer_size){
  if (stream_content_list.empty()) {
    return 0;
  }

  auto word = stream_content_list.back();
  stream_content_list.pop_back();
  size_t bytes = std::min(buffer_size, word.length());
  std::strncpy(dst, word.c_str(), buffer_size);
  return bytes;
};

void validateRegex(const char* input_regex,
                   const size_t nValues,
                   bool stateful,
                   const char* stream_content = nullptr) {
  rexgen::RexgenOptions options;
  if (stream_content != nullptr) {
    stream_content_list.clear();
    stream_content_list.push_front(stream_content);
    options.stream_callback = stream_callback;
  }
  auto regex = parse_regex(input_regex, options);
  REQUIRE(regex != nullptr);

  std::string control_regex(input_regex);
  if (stream_content != nullptr) {
    std::string::size_type pos;
    while ((pos = control_regex.find("\\0")) != std::string::npos) {
      control_regex.replace(pos, 2, stream_content);
    }
  }

  auto iter = std::make_shared<rexgen::TopIterator>(regex);

  SimpleString str;
  std::list<std::string> generated_values;
  while (iter->next()) {
    str.clear();
    iter->value(&str);
    const char* generated_value = str.c_str();
    const char* ctl_regex = control_regex.c_str();
    REQUIRE(matches(generated_value, ctl_regex));
    generated_values.push_back(str);

    if (stateful) {
      /* save and restore the iterator state */
      auto s = iter->getCurrentState();
      iter->setCurrentState(s);
    }
  }
  REQUIRE(generated_values.size() == nValues);
}

void validateRegex(const char* input_regex,
                   const size_t nValues) {
  validateRegex(input_regex, nValues, false);
  validateRegex(input_regex, nValues, true);
}

void validateRegex(const char* input_regex,
                   const size_t nValues,
                   const char* stream_content) {
  validateRegex(input_regex, nValues, false, stream_content);
  validateRegex(input_regex, nValues, true, stream_content);
}

void validateFailure(const char* input_regex) {
  rexgen::RexgenOptions options;
  auto regex = parse_regex(input_regex, options);

  rexgen::IteratorState state;
  auto iter = regex->singleIterator(state);

  REQUIRE_THROWS(iter->next());
}