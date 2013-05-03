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

#include <librexgen/unicode/uchar.h>
#include <librexgen/unicode/utf32.h>

static bool has_to_flip(charset cs) {
  return
  ( o32_host_order.value == O32_LITTLE_ENDIAN && 
    (cs == CHARSET_UTF16BE || cs == CHARSET_UTF32BE) ) ||
  ( o32_host_order.value == O32_BIG_ENDIAN && 
    ( cs == CHARSET_UTF16LE || cs == CHARSET_UTF32LE) );
}

void codepoint_to_uchar(uchar_t* dst, uint32_t codepoint, charset cs) {
  size_t shift = 0;
  size_t index = 0;
  const bool flip = has_to_flip(cs);
  
  dst->variant = cs;
  dst->char_length = 1;
  dst->codepoint = codepoint;
  dst->character.ucs4.value = 0; /* reset all other bytes to zero */
  switch (cs) {
    case CHARSET_ANSI:
      dst->character.ansi.value = (uint8_t) 0x00ff & codepoint;
      break;
    case CHARSET_UTF8:
      /* this is the most common case and should be very fast */
      if (codepoint <= 0x7f) {
        dst->character.ansi.value = (uint8_t) 0x00ff & codepoint;
        break;
      }
      /* reset value; this is necessary for fast alignment shifting later */
      dst->character.ucs4.value = 0;
      
      /* convert codepoint to utf8 presentation */
      dst->char_length = convert_utf32_to_utf8(dst->character.bytes, codepoint);
      
      /* align bytes */
      shift = 4 - dst->char_length;
      index = 3;
      switch (dst->char_length) {
        case 3: dst->character.bytes[index] = dst->character.bytes[index-shift]; --index;
        case 2: dst->character.bytes[index] = dst->character.bytes[index-shift]; --index;
        case 1: dst->character.bytes[index] = dst->character.bytes[index-shift];
      }
      index = 0;
      switch (dst->char_length) {
        case 1: dst->character.bytes[index++] = 0;
        case 2: dst->character.bytes[index++] = 0;
        case 3: dst->character.bytes[index] = 0;
      }
      break;
    case CHARSET_UTF16LE:
    case CHARSET_UTF16BE:
      if (codepoint <= 0xffff) {
        const uint16_t tmp = (uint16_t)(0x0000ffff&codepoint);
        dst->char_length = 2;
        dst->character.ucs2.high = 0;
        dst->character.ucs2.low = (flip ? flip_byteorder(tmp) : tmp);
        break;
      }
      
      if (codepoint <= 0x10ffff) {
        dst->char_length = 4;
        const uint32_t tmp = codepoint - 0x100000;
        dst->character.ucs4.value =
              ((0b11011000 | (((uint16_t)(tmp>>10)) & 0b1111111111)) << 16) |
              (0b11011100 | (((uint16_t)(tmp))     & 0b1111111111));
        if (flip) {
          flip_byteorder(dst->character.ucs4.value);
        }
        break;
      }
      dst->char_length = 0;
      dst->character.ucs4.value = 0;
      break;
    case CHARSET_UTF32BE:
    case CHARSET_UTF32LE:
      dst->char_length = 4;
      dst->character.ucs4.value = ( flip ? flip_byteorder(codepoint): codepoint);
      break;
      
  }
}

uint8_t uchar_to_ansi(const uchar_t& uch, byte* ansi_dst) {
  *ansi_dst = uch.character.ansi.value;
  return 1;
}

uint8_t uchar_to_utf8(const uchar_t& uch, byte* utf8_dst) {
  switch(uch.char_length) {
    case 4: *utf8_dst++ = uch.character.bytes[0];
    case 3: *utf8_dst++ = uch.character.bytes[1];
    case 2: *utf8_dst++ = uch.character.bytes[2];
    case 1: *utf8_dst = uch.character.bytes[3];
  }
  return uch.char_length;
}

uint8_t uchar_to_utf16(const uchar_t& uch, byte* utf16_dst) {
  switch(uch.char_length) {
    case 4: 
      *((uint16_t*)utf16_dst) = uch.character.ucs2.high;
      utf16_dst += 2;
    case 2:
      *((uint16_t*)utf16_dst) = uch.character.ucs2.low;
  }
  return uch.char_length;
}

uint8_t uchar_to_utf32(const uchar_t& uch, byte* utf32_dst) {
  *((uint32_t*)utf32_dst) = uch.character.ucs4.value;
  return 4;
}

uint8_t uchar_to_utf(const uchar_t& uch, byte* dst) {
  
  switch (uch.variant) {
    case CHARSET_ANSI: return uchar_to_ansi(uch, dst);
    case CHARSET_UTF8: return uchar_to_utf8(uch, dst);
    case CHARSET_UTF16BE:
    case CHARSET_UTF16LE: return uchar_to_utf16(uch, dst);
    case CHARSET_UTF32BE:
    case CHARSET_UTF32LE: return uchar_to_utf32(uch, dst);
  }
  return 0;
}

bool uchar_isascii(const uchar_t& uch) {
  return (      (uch.variant == CHARSET_ANSI)
  ||        (uch.char_length == 1)
  ||        (uch.character.bytes[0]==0
  && uch.character.bytes[1]==0
  && uch.character.bytes[2]==0));
}

uchar_t create_BOM(charset cs) {
  uint32_t codepoint = 0;
  switch (cs) {
    case CHARSET_ANSI:
      codepoint = 0;
      break;
    default:
      codepoint = 0xfeff;
  }
  uchar_t uc;
  codepoint_to_uchar(&uc, codepoint, cs);
  return uc;
}
