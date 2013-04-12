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

#include <librexgen/unicode/uchar.h>
#include <librexgen/unicode/utf32.h>

void codepoint_to_uchar(uchar_t* dst, uint32_t codepoint, charset cs) {
  size_t shift = 0;
  size_t index = 0;
  
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
    case CHARSET_UTF16:
#pragma message "TODO: create UTF16 conversion"
      dst->char_length = 2;
      dst->character.ucs2.low = 0;
      dst->character.ucs2.high = 
      ( o32_host_order.value == O32_LITTLE_ENDIAN ?
        flip_byteorder((uint16_t)(codepoint & 0x0000ffff)):
        codepoint);
      break;
    case CHARSET_UTF32:
      dst->char_length = 4;
      dst->character.ucs4.value = 
      ( o32_host_order.value == O32_LITTLE_ENDIAN ?
            flip_byteorder(codepoint):
            codepoint);
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
    case 4: *utf16_dst = uch.character.bytes[0]; utf16_dst += 2;
    case 2: *utf16_dst = uch.character.bytes[2];
  }
  return 4;
}

uint8_t uchar_to_utf32(const uchar_t& uch, byte* utf32_dst) {
  *utf32_dst = uch.character.ucs4.value;
  return 4;
}

uint8_t uchar_to_utf(const uchar_t& uch, byte* dst) {
  switch (uch.variant) {
    case CHARSET_ANSI: return uchar_to_ansi(uch, dst);
    case CHARSET_UTF8: return uchar_to_utf8(uch, dst);
    case CHARSET_UTF16: return uchar_to_utf16(uch, dst);
    case CHARSET_UTF32: return uchar_to_utf32(uch, dst);
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
