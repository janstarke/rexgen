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

#include <librexgen/parser/rexgenparsercontext.h>
#include <librexgen/regex/regex.h>
#include <librexgen/parser/osdepend.h>
#include <sstream>
#include <string>
#include <cstdio>

using std::istringstream;

int rexgen_parse(RexgenParserContext* context);

EXPORT
Regex* parse_regex(const char* regex, bool ignoreCase, charset enc, FILE* infile) {
  const string re(regex);

  istringstream is(re);

  RexgenParserContext context(&is, ignoreCase, enc, infile);
  if (rexgen_parse(&context) != 0) {
    return NULL;
  }
#pragma message("this must be handled with normal syntax error reporting")
  assert(!context.hasInvalidGroupReferences());
  // IteratorState* state = new IteratorState(context.getGroups());
  // Iterator* iter = context.result->iterator(state);
  return context.result;
}
