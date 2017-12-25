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

#include <list>
#include <librexgen/iterator/topiterator.h>
#include <librexgen/rexgen_options.h>
#include "utils.h"

bool matches(const char* value, const char* regex) {
  pcrecpp::RE _re(regex);
  return _re.FullMatch(value);
}

void validateRegex(const char* input_regex,
                   const size_t nValues) {

  RexgenOptions options;
  options.stream_callback = streamCallback;
  Regex* regex = parse_regex(input_regex, options);

  Iterator* iter = new TopIterator(regex);

  // register regex alternatives
  iter->updateReferences(NULL);

  // update references
  iter->updateReferences(NULL);

  // update attributes (e.g. case folding )
  iter->updateAttributes(NULL);

  SimpleString str;
  std::list<string> generated_values;
  while (iter->next()) {
    str.clear();
    iter->value(&str);
    const char* generated_value = str.c_str();
    ASSERT_PRED2(matches, generated_value, input_regex);
    generated_values.push_back(str);

    /* save and restore the iterator state */
    SerializableState* s = iter->getCurrentState();
    iter->setCurrentState(s);
  }
  ASSERT_EQ(generated_values.size(), nValues);
  delete iter;
  delete regex;
}

void validateFailure(const char* input_regex) {
  RexgenOptions options;
  Regex* regex = parse_regex(input_regex, options);

  IteratorState state;
  Iterator* iter = regex->singleIterator(&state);

  ASSERT_ANY_THROW(iter->next());

  delete iter;
  delete regex;
}

static Iterator* streamGenerator = NULL;
size_t streamCallback(char* dst, const size_t buffer_size){
  if (streamGenerator == NULL) {
    RexgenOptions options;
    Regex* regex = parse_regex("(Lorem|ipsum|123)", options);

    streamGenerator = new TopIterator(regex);

    // register regex alternatives
    streamGenerator->updateReferences(NULL);

    // update references
    streamGenerator->updateReferences(NULL);

    // update attributes (e.g. case folding )
    streamGenerator->updateAttributes(NULL);
  }

  if (! streamGenerator->next()) {
    streamGenerator = NULL;
    return 0;
  }

  SimpleString str;
  streamGenerator->value(&str);
  strncpy(dst, str.c_str(), buffer_size);
  return str.length();
}