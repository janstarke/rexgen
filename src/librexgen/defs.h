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

#ifndef SRC_LIBREXGEN_DEFS_H_
#define SRC_LIBREXGEN_DEFS_H_


typedef uint8_t charset;
#define CHARSET_ANSI    1
#define CHARSET_UTF8    2
#define CHARSET_UTF16BE 3
#define CHARSET_UTF32BE 4
#define CHARSET_UTF16LE 5
#define CHARSET_UTF32LE 6

typedef char byte_t;
typedef uint32_t codepoint_t;

typedef uint8_t uchar_flags_t;
typedef uint8_t uchar_info_t;
typedef wchar_t uchar_codepoint_t;

#define UCHAR_FLAGS_CHANGE_CASE         0x01
#define UCHAR_FLAGS_PRESERVE_CASE       0x02
#define UCHAR_FLAGS_USE_CASEFOLDED      0x04

#endif /* SRC_LIBREXGEN_DEFS_H_ */
