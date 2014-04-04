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

#ifndef __utf32_h__
#define __utf32_h__

#include <limits.h>
#include <stdint.h>
#include <stddef.h>

#if CHAR_BIT != 8
#error "unsupported char size"
#endif

enum {
  O32_LITTLE_ENDIAN = 0x03020100ul,
  O32_BIG_ENDIAN = 0x00010203ul,
  O32_PDP_ENDIAN = 0x00000302ul
};

static const union {
  unsigned char bytes[4];
  uint32_t value;
} o32_host_order = { { 0, 1, 2, 3 } };
#define O32_HOST_ORDER (o32_host_order)

#define UNI_SUR_HIGH_START      0xD800
#define UNI_SUR_HIGH_END        0xDBFF
#define UNI_SUR_LOW_START       0xDC00
#define UNI_SUR_LOW_END         0xDFFF
#define UNI_MAX_LEGAL_UTF32     0x0010FFFF

const uint32_t byte_mask = 0xbf;
const uint32_t byte_mark = 0x80;
static const uint8_t first_byte_mark[7] = {
  0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc };
  
  static inline uint32_t flip_byteorder32(uint32_t v) {
    return
    ((v & 0x000000ff) << 24) |
    ((v & 0x0000ff00) << 8)  |
    ((v & 0x00ff0000) >> 8)  |
    ((v & 0xff000000) >> 24);
  }
  
  static inline uint16_t flip_byteorder16(uint16_t v) {
    return 
    (((v & 0x00ff) << 8)  |  ((v & 0xff00) >> 8));
  }

inline size_t convert_utf32_to_utf8 (char* dst, uint32_t value) {
  short bytes_to_write = 0;
  
  if (value >= UNI_SUR_HIGH_START && value <= UNI_SUR_LOW_END) {
    return 0;
  }
  
  if (value < 0x80)                     bytes_to_write = 1;
  else if (value < 0x800)               bytes_to_write = 2;
  else if (value < 0x10000)             bytes_to_write = 3;
  else if (value < UNI_MAX_LEGAL_UTF32) bytes_to_write = 4;
  else                                  return 0;
  
  dst += bytes_to_write;
  switch (bytes_to_write) {
    case 4: *--dst = ((char)value | byte_mark) & byte_mask; value >>= 6;
    case 3: *--dst = ((char)value | byte_mark) & byte_mask; value >>= 6;
    case 2: *--dst = ((char)value | byte_mark) & byte_mask; value >>= 6;
    case 1: *--dst = ((char)value | first_byte_mark[bytes_to_write]);
  }
  return bytes_to_write;
}

#endif
