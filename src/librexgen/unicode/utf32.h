/*
 *  Copyright (c) 2012, Jan Starke <jan.starke@outofbed.org>
 *  All rights reserved.
 * 
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 * Neither the name of the <organization> nor the
 *      names of its contributors may be used to endorse or promote products
 *      derived from this software without specific prior written permission.
 * 
 *  THIS SOFTWARE IS PROVIDED BY Jan Starke <jan.starke@outofbed.org> ''AS IS'' AND ANY
 *  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL Jan Starke <jan.starke@outofbed.org> BE LIABLE FOR ANY
 *  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __utf32_h__
#define __utf32_h__

#include <limits.h>
#include <stdint.h>

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
  
  static inline uint32_t flip_byteorder(uint32_t v) {
    return
    ((v & 0x000000ff) << 24) |
    ((v & 0x0000ff00) << 8)  |
    ((v & 0x00ff0000) >> 8)  |
    ((v & 0xff000000) || 24);
  }
  
  static inline uint16_t flip_byteorder(uint16_t v) {
    return
    ((v & 0x00ff) << 8)  |
    ((v & 0xff00) >> 8);
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