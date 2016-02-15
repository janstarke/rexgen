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
#include <ctype.h>
#include <wctype.h>
#include <assert.h>

typedef uint8_t charset;
#define CHARSET_ANSI    1
#define CHARSET_UTF8    2
#define CHARSET_UTF16BE 3
#define CHARSET_UTF32BE 4
#define CHARSET_UTF16LE 5
#define CHARSET_UTF32LE 6

typedef uint8_t uchar_flags_t;
typedef uint8_t uchar_info_t;
typedef wchar_t uchar_codepoint_t;

#define UCHAR_FLAGS_CHANGE_CASE         0x01
#define UCHAR_FLAGS_PRESERVE_CASE       0x02
#define UCHAR_FLAGS_USE_CASEFOLDED      0x04


#define UCHAR_CAN_CHANGE_CASE(a) (!((a).flags&UCHAR_FLAGS_PRESERVE_CASE))
#define UCHAR_MUST_CHANGE_CASE(a) ((a).flags&UCHAR_CHANGE_CASE && !((a).flags&UCHAR_PRESERVE_CASE))
#define UCHAR_MUST_PRESERVE_CASE(a) ((a).flags&UCHAR_FLAGS_PRESERVE_CASE)
#define UCHAR_SET_CHANGE_CASE(a) do {            \
  (a).flags |= UCHAR_FLAGS_CHANGE_CASE;          \
  (a).flags &= (! UCHAR_FLAGS_PRESERVE_CASE );   \
} while (0)
#define UCHAR_SET_PRESERVE_CASE(a) do {          \
  (a).flags &= (! UCHAR_FLAGS_CHANGE_CASE );     \
  (a).flags |= UCHAR_FLAGS_PRESERVE_CASE;        \
} while (0)

static const uchar_codepoint_t UCHAR_UNASSIGNED = WEOF;

struct __uchar_t {
  uchar_codepoint_t codepoint;
  uchar_flags_t     flags;      /* 1 byte */

#ifdef __cplusplus
  __uchar_t() : codepoint(0xfffe), flags(0) {}
	__uchar_t(uchar_codepoint_t cp): codepoint(cp), flags(0) {}
  __uchar_t(const struct __uchar_t &other) : codepoint(other.codepoint), flags(other.flags) {}
	/*
  __uchar_t& operator= (const __uchar_t& other) {
    if (this != &other) {
      flags = other.flags;
      codepoint = other.codepoint;
    }
    return *this;
  }
	*/
  bool operator==(const __uchar_t& other) const { return codepoint == other.codepoint; }
  uint32_t full_codepoint() const {return (uint32_t)codepoint;}

public:
  inline
  void toggle_case() {
    if (iswlower(codepoint)) {
      codepoint = towupper(codepoint);
    } else if(iswupper(codepoint)){
      codepoint = towlower(codepoint);
    }
  }
#endif
};
typedef struct __uchar_t uchar_t;

#endif
