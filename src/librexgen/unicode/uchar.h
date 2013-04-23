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


#ifndef __uchar_h__
#define __uchar_h__

#include <librexgen/unicode.h>
#include <librexgen/parser/osdepend.h>

enum charset : uint8_t {
  CHARSET_ANSI,
  CHARSET_UTF8,
  CHARSET_UTF16,
  CHARSET_UTF32
};

struct uchar_t{
  charset variant;
  uint8_t char_length;
  
  /* this one is needed for simple iteration in in UTF8 and UTF16*/
  uint16_t codepoint;
  
  union {
    byte    bytes[4];
    struct {
      uint8_t  pad[3];
      char     value;
    } ansi;
    struct {
      char16_t low;
      char16_t high;
    } ucs2;
    struct {
      char32_t value;
    } ucs4;
  } character;
};

inline const byte* firstByteAddressOf(const uchar_t& c) {
  return & (c.character.bytes[
    sizeof(c.character.bytes)/sizeof(c.character.bytes[0]) - c.char_length]);
}

inline uchar_t char_to_uchar(char ch) {
  uchar_t u;
  u.character.ucs4.value = 0;
  u.character.ansi.value = ch;
  u.variant = CHARSET_ANSI;
  u.char_length = 1;
  return u;
}

void codepoint_to_uchar(uchar_t* dst, uint32_t codepoint, charset cs);

uint8_t uchar_to_ansi(const uchar_t& uch, byte* ansi_dst);

uint8_t uchar_to_utf8(const uchar_t& uch, byte* utf8_dst);

uint8_t uchar_to_utf16(const uchar_t& uch, byte* utf16_dst);

uint8_t uchar_to_utf32(const uchar_t& uch, byte* utf32_dst);

uint8_t uchar_to_utf(const uchar_t& uch, byte* dst);

bool uchar_isascii(const uchar_t& uch);

#endif