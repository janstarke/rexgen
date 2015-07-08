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
#include <librexgen/string/uchar.h>
#include <librexgen/string/utf32.h>
#include <unicode/uchar.h>

/*
 * PUBLIC INTERFACE
 */

#ifdef __cplusplus
extern "C" {
#endif

EXPORT
uint8_t create_BOM(charset cs, byte* bom ) {
  return encode_uchar(codepoint_to_uchar(0xfeff), cs, bom);
}

#ifdef __cplusplus
}
#endif

/*
 * PRIVATE INTERFACE
 */
static int has_to_flip(charset cs) {
  return
    ( o32_host_order.value == O32_LITTLE_ENDIAN &&
      (cs == CHARSET_UTF16BE || cs == CHARSET_UTF32BE) ) ||
    ( o32_host_order.value == O32_BIG_ENDIAN &&
      ( cs == CHARSET_UTF16LE || cs == CHARSET_UTF32LE) );
}

EXPORT
uchar_t codepoint_to_uchar(uint16_t ch) {
  uchar_t u;
  memset(&u, 0, sizeof(uchar_t));
  u.codepoint = ch;
  return u;
}

uint8_t __encode_uchar(const uchar_t& uch, charset cs, byte* dst) {
  const int flip = has_to_flip(cs);
  uint32_t tmp;
  binary_character_t* bch;

  switch (cs) {
  case CHARSET_ANSI:
    /* cut off the remaining bytes; but
     * NOTE: the value of bch will be invalid
     */
    *dst = (uint8_t) 0x00ff & uch.codepoint;
    return 1;
  case CHARSET_UTF8:
    /* convert codepoint to utf8 presentation */
    return convert_utf32_to_utf8(dst, uch.full_codepoint());
  case CHARSET_UTF16LE:
  case CHARSET_UTF16BE:
    if (uch.plane == BMP) {
      const uint16_t tmp16 = uch.codepoint;
      bch = reinterpret_cast<binary_character_t*>(dst-2);
      bch->ucs2.low = (flip ? flip_byteorder16(tmp16) : tmp16);
      return 2;
    }

    tmp = uch.full_codepoint();
    bch = reinterpret_cast<binary_character_t*>(dst);
    bch->ucs4.value =
      (( 0xD8 | (((uint16_t)(tmp>>10)) & 0x3FF)) << 16) |
      (0xDC | (((uint16_t)(tmp))     & 0x3FF));
    if (flip) {
      flip_byteorder32(bch->ucs4.value);
    }
    return 4;
  case CHARSET_UTF32BE:
  case CHARSET_UTF32LE:
    bch = reinterpret_cast<binary_character_t*>(dst);
    tmp = uch.full_codepoint();
    bch->ucs4.value = ( flip ? flip_byteorder32(tmp): tmp);
    return 4;
  }
  return -1;
}

EXPORT
uint8_t uchar_to_ansi(const binary_character_t* bch, byte* ansi_dst) {
  *ansi_dst = bch->ansi.value;
  return 1;
}

EXPORT
uint8_t uchar_to_utf8(const binary_character_t* bch, byte* utf8_dst) {
  if (bch->bytes[0]) { /* copy 4 bytes */
    *((char32_t*)utf8_dst) = bch->ucs4.value;
    return 4;
  }

  if (bch->bytes[1]) { /* copy 3 bytes */
    *utf8_dst = bch->bytes[1];
    *((char16_t*)(utf8_dst+1)) = bch->ucs2.low;
    return 3;
  }

  if (bch->bytes[2]) { /* copy 2 bytes */
    *((char16_t*)utf8_dst) = bch->ucs2.low;
    return 2;
  }

  /* copy 1 byte */
  *utf8_dst = bch->ansi.value;
  return 1;
}

EXPORT
uint8_t uchar_to_utf16(const binary_character_t* bch, byte* utf16_dst) {
  if (bch->ucs2.high) { /* copy 4 bytes */
    *((char32_t*)utf16_dst) = bch->ucs4.value;
    return 4;
  }

  /* copy 2 bytes */
  *((uint16_t*)(utf16_dst)) = bch->ucs2.low;
  return 2;
}

EXPORT
uint8_t uchar_to_utf32(const binary_character_t* bch, byte* utf32_dst) {
  *((uint32_t*)utf32_dst) = bch->ucs4.value;
  return 4;
}


