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

#ifndef SRC_LIBREXGEN_STRING_UTF8_H
#define SRC_LIBREXGEN_STRING_UTF8_H

#ifdef __cplusplus

#include <cstdint>
#include <cstddef>
#include <string>
#include <librexgen/defs.h>

size_t codepoint_length(std::string::value_type first_byte) {
  return __builtin_clz(~first_byte) - ((sizeof(first_byte)-1)*8);
}

codepoint_t codepoint_from_utf8(const std::string ch, std::string::size_type at_index);

std::string& utf8_from_codepoint(const codepoint_t& codepoint, std::string* dst);

#endif /* __cplusplus */

#endif //SRC_LIBREXGEN_STRING_UTF8_H
