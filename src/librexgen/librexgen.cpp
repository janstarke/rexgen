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

#include <librexgen/librexgen.h>
#include <librexgen/parser/rexgenparsingdriver.h>
#include <librexgen/iterator/topiterator.h>
#include <librexgen/parser/syntaxerror.h>
#include <sstream>
#include <string>
#include <memory>

EXPORT
std::shared_ptr<rexgen::Regex> parse_regex(const char* regex, const rexgen::RexgenOptions& options) {
  rexgen::RexgenParsingDriver driver(options);

  try {
    auto result = driver.parse(regex);
/*
    if (driver.hasInvalidGroupReferences()) {
      driver.handleParserError("This regular expression has an invalid back reference");
      return nullptr;
    }
*/
    return result;
  } catch (SyntaxError &exc) {
    driver.handleParserError(exc.getMessage());
    return nullptr;
  }
}

EXPORT
std::shared_ptr<rexgen::Iterator> regex_iterator(const char* regex, const rexgen::RexgenOptions& options) {
  if (auto re = parse_regex(regex, options)) {
    return std::make_shared<rexgen::TopIterator>(re);
  }
  return nullptr;
}
