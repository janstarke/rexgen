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

#include <librexgen/parser/parse_escapes.h>

static uint8_t parseHexChar(char c) {
  if (c >= '0' && c <= '9') {
    return ((c) - '0');
  } else if (c >= 'a' && c <= 'f') {
    return ((c) - 'a' + 10);
  } else if (c >= 'A' && c <= 'F') {
    return ((c) - 'A' + 10);
  }
  return -1;
}

static uint32_t parseHexString(const char* ptr, size_t length) {
  char32_t hexvalue = 0;
  while (*ptr != 0 && length > 0) {
    const uint8_t v = parseHexChar(*ptr);
    if (v == -1) { return -1; }
    hexvalue = (hexvalue << 4) + v;
    ptr++;
    length--;
  }
  return hexvalue;
}

/**
 * returns the codepoint of the character; e.g.
 * 'A'          => 0x0041
 * '\n'         => 0x000a
 * '\r'         => 0x000d
 * '\xAA'       => 0x00AA
 * '\uUUUU'     => 0xUUUU
 */
uint16_t parseFirstCharacter(const char* c) {
  uint16_t codepoint;

  if (c[0] == '\0') {
    return c[0];
  }
  if (c[0] == '\\' && c[1] != '\0') {
    switch (c[1]) {
    case 'n':
      return '\n';
    case 'r':
      return '\r';
    case '0':
      return '\0';
    case 'x':
      return (char_type) parseHexString((c+2), 2);
    case 'u':
      return parseHexString((c+2), 4);
    default:
      return c[1];
    }
  }
  return c[0];
}
