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