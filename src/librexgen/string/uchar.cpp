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

#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stddef.h>
#include <librexgen/string/uchar.h>
#include <unicode/uchar.h>

/*
 * PRIVATE INTERFACE
 */

#define UNI_SUR_HIGH_START      0xD800
#define UNI_SUR_HIGH_END        0xDBFF
#define UNI_SUR_LOW_START       0xDC00
#define UNI_SUR_LOW_END         0xDFFF
#define UNI_MAX_LEGAL_UTF32     0x0010FFFF

const uint32_t byte_mask = 0xbf;
const uint32_t byte_mark = 0x80;
const uint8_t first_byte_mark[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };

size_t convert_utf32_to_utf8 (char* dst, uint32_t value) {
  short bytes_to_write = 0;

  if (value >= UNI_SUR_HIGH_START && value <= UNI_SUR_LOW_END) {
    return 0;
  }

  if (value < 0x80) { bytes_to_write = 1; }
  else if (value < 0x800) { bytes_to_write = 2; }
  else if (value < 0x10000) { bytes_to_write = 3; }
  else if (value < UNI_MAX_LEGAL_UTF32) { bytes_to_write = 4; }
  else { return 0; }

  dst += bytes_to_write;
  switch (bytes_to_write) {
  case 4:
    *--dst = ((char)value | byte_mark) & byte_mask;
    value >>= 6;
  case 3:
    *--dst = ((char)value | byte_mark) & byte_mask;
    value >>= 6;
  case 2:
    *--dst = ((char)value | byte_mark) & byte_mask;
    value >>= 6;
  case 1:
    *--dst = ((char)value | first_byte_mark[bytes_to_write]);
  }
  return bytes_to_write;
}

