/*
    rexgen - a tool to create words based on regular expressions
    Copyright (C) 2012-2013  Jan Starke <jan.starke@outofbed.org>

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


#ifndef __uchar_h__
#define __uchar_h__

#include <stdint.h>
#include <stddef.h>
#include <librexgen/string/unicode.h>
#include <librexgen/osdepend.h>

typedef uint8_t charset;
#define CHARSET_ANSI    1
#define CHARSET_UTF8    2
#define CHARSET_UTF16BE 3
#define CHARSET_UTF32BE 4
#define CHARSET_UTF16LE 5
#define CHARSET_UTF32LE 6

#if ! defined(__cplusplus) || defined(_WIN32) || __cplusplus==1 || __cplusplus==199711L
typedef uint16_t char16_t;
typedef uint32_t char32_t;
#endif

typedef struct __uchar_t {
  charset variant;
  uint8_t char_length;

  uint16_t __padding__;

  /* this one is needed for simple iteration in in UTF8 and UTF16*/
  uint32_t codepoint;

  union {
    byte    bytes[4];
    struct {
      uint8_t  pad[3];
      char     value;
    } ansi;
    struct {
      char16_t high;
      char16_t low;
    } ucs2;
    struct {
      char32_t value;
    } ucs4;
  } character;
} uchar_t;

#ifdef __cplusplus
extern "C" {
#endif

EXPORT
const byte* firstByteAddressOf(const uchar_t* c);

EXPORT
uchar_t char_to_uchar(char ch);

EXPORT
void codepoint_to_uchar(uchar_t* dst, uint32_t codepoint, charset cs);

EXPORT
uint8_t uchar_to_ansi(const uchar_t* uch, byte* ansi_dst);

EXPORT
uint8_t uchar_to_utf8(const uchar_t* uch, byte* utf8_dst);

EXPORT
uint8_t uchar_to_utf16(const uchar_t* uch, byte* utf16_dst);

EXPORT
uint8_t uchar_to_utf32(const uchar_t* uch, byte* utf32_dst);

EXPORT
uint8_t uchar_to_utf(const uchar_t* uch, byte* dst);

EXPORT
uchar_t create_BOM(charset cs);

EXPORT
int uchar_isascii(const uchar_t* uch);

#ifdef __cplusplus
}
#endif

#endif
