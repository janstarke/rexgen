/*
    rexgen - a tool to create words based on regular expressions
    Copyright (C) 2012-2019  Jan Starke <jan.starke@outofbed.org>

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

#include "RexgenParser.h"

#include <librexgen/regex/regex.h>
#include <librexgen/parser/rexgenparsercontext.h>
#include <librexgen/parser/syntaxerror.h>
#include <string>
#include <memory>

namespace rexgen {
  int rexgen_parse(RexgenParserContext *context);

  std::shared_ptr<Regex> RexgenParser::parse(const std::string &regex_str, const RexgenOptions &__options) const {
    RexgenParserContext context(regex_str.c_str(), __options);

    try {
      if (rexgen_parse(&context) == 0) {
        return std::move(context.getResult());
      }
    } catch (SyntaxError &exc) {
      context.handleParserError(exc.getMessage());
      return nullptr;
    }
    if (context.hasInvalidGroupReferences()) {
      context.handleParserError("This regular expression has an invalid back reference");
      return nullptr;
    }
    return nullptr;
  }
}