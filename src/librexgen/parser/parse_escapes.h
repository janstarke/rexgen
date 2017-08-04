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

#ifndef SRC_LIBREXGEN_PARSER_PARSE_ESCAPES_H_
#define SRC_LIBREXGEN_PARSER_PARSE_ESCAPES_H_

/* returns the codepoint of the character; e.g.
 * 'A'          => 0x0041
 * '\n'         => 0x000a
 * '\r'         => 0x000d
 * '\xAA'       => 0x00AA
 * '\uUUUU'     => 0xUUUU
 */
uint16_t parseFirstCharacter(const char* c);

uint8_t parseHexChar(char c);
uint32_t parseHexString(const char* ptr, size_t length);

#endif  // SRC_LIBREXGEN_PARSER_PARSE_ESCAPES_H_
