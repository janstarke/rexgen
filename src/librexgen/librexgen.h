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

#ifndef __libregex_h__
#define __libregex_h__
#include <librexgen/regex/regex.h>
#include <librexgen/iterator/iterator.h>
#include <librexgen/parser/osdepend.h>
#include <librexgen/rexgen_options.h>
#include <librexgen/parser/rexgenparsercontext.h>

EXPORT
Regex* parse_regex(const char* regex, const RexgenOptions& options);

EXPORT
Iterator* regex_iterator(const char* regex, const RexgenOptions& options);

Regex* parse_regex(RexgenParserContext* context);

#endif /* __libregex_h__ */
