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

#ifdef __cplusplus
extern "C" {
#endif

static int has_to_flip(charset cs) {
  return
    ( o32_host_order.value == O32_LITTLE_ENDIAN &&
      (cs == CHARSET_UTF16BE || cs == CHARSET_UTF32BE) ) ||
    ( o32_host_order.value == O32_BIG_ENDIAN &&
      ( cs == CHARSET_UTF16LE || cs == CHARSET_UTF32LE) );
}

EXPORT
const byte* firstByteAddressOf(const uchar_t* c) {
  return & (c->character.bytes[
              sizeof(c->character.bytes)/sizeof(c->character.bytes[0]) - c->char_length]);
}

EXPORT
uchar_t char_to_uchar(char ch) {
  uchar_t u;
	memset(&u, 0, sizeof(uchar_t));
  u.character.ansi.value = ch;
  u.variant = CHARSET_ANSI;
  u.char_length = 1;
  return u;
}

EXPORT
uint8_t encode_codepoint(uint32_t codepoint, charset cs, binary_character_t* bch) {
  size_t shift = 0;
  size_t index = 0;
  const int flip = has_to_flip(cs);
	bch->ucs4.value = 0;
	uint8_t length = 0;

  switch (cs) {
  case CHARSET_ANSI:
    bch->ansi.value = (uint8_t) 0x00ff & codepoint;
    break;
  case CHARSET_UTF8:
    /* this is the most common case and should be very fast */
    if (codepoint <= 0x7f) {
      bch->ansi.value = (uint8_t) 0x00ff & codepoint;
			length = 1;
      break;
    }
    /* convert codepoint to utf8 presentation */
    length = convert_utf32_to_utf8(bch->bytes, codepoint);

    /* align bytes */
    shift = 4 - length;
    index = 3;
    switch (length) {
    case 3:
      bch->bytes[index] = bch->bytes[index-shift];
      --index;
    case 2:
      bch->bytes[index] = bch->bytes[index-shift];
      --index;
    case 1:
      bch->bytes[index] = bch->bytes[index-shift];
    }
    index = 0;
    switch (length) {
    case 1:
      bch->bytes[index++] = 0;
    case 2:
      bch->bytes[index++] = 0;
    case 3:
      bch->bytes[index] = 0;
    }
    break;
  case CHARSET_UTF16LE:
  case CHARSET_UTF16BE:
    if (codepoint <= 0xffff) {
      const uint16_t tmp = (uint16_t)(0x0000ffff&codepoint);
      length = 2;
      bch->ucs2.high = 0;
      bch->ucs2.low = (flip ? flip_byteorder16(tmp) : tmp);
      break;
    }

    if (codepoint <= 0x10ffff) {
      length = 4;
      const uint32_t tmp = codepoint - 0x100000;
      bch->ucs4.value =
        (( 0xD8 | (((uint16_t)(tmp>>10)) & 0x3FF)) << 16) |
        (0xDC | (((uint16_t)(tmp))     & 0x3FF));
      if (flip) {
        flip_byteorder32(bch->ucs4.value);
      }
      break;
    }
    length = 0;
    bch->ucs4.value = 0;
    break;
  case CHARSET_UTF32BE:
  case CHARSET_UTF32LE:
    length = 4;
    bch->ucs4.value = ( flip ? flip_byteorder32(codepoint): codepoint);
    break;
  }
	return length;
}

EXPORT
void codepoint_to_uchar(uchar_t* dst, uint32_t codepoint, charset cs) {
	memset(dst, 0, sizeof(uchar_t));
  dst->variant = cs;
  dst->char_length = 1;

	uint32_t cpUpper, cpLower;
	if (u_isULowercase(codepoint)) {
		cpLower = codepoint;
		cpUpper = u_toupper(codepoint);
	} else if (u_isUUppercase(codepoint)) {
		cpLower = u_toupper(codepoint);
		cpUpper = codepoint;
	} else {
		cpLower = codepoint;
		cpUpper = 0xFFFFFFFF;
		UCHAR_SET_PRESERVE_CASE(*dst);
	}
	dst->codepoint     = cpLower;

	/* convert the character itself */
	dst->char_length = encode_codepoint(dst->codepoint, cs, &dst->character);

	/* convert the uppercase/lowercase variant of the character */
	encode_codepoint(cpUpper, cs, &(dst->casefolded[0]));

	/* if the uppercase and lowercase variant are equal, then preserve case */
	if (dst->casefolded[0].ucs4.value == dst->character.ucs4.value) {
		UCHAR_SET_PRESERVE_CASE(*dst);
	} else {
		dst->casefolded[1].ucs4.value = UCHAR_UNASSIGNED;
		dst->casefolded[2].ucs4.value = UCHAR_UNASSIGNED;
	}
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

EXPORT
uint8_t uchar_to_binary(const uchar_t* uch, byte* dst) {

	uint8_t len = 0;

#warning this converter function must be assigned only once, for performance reasons
	uint8_t (*converter_function)(const binary_character_t*, byte*) = NULL;
  switch (uch->variant) {
  case CHARSET_ANSI:    converter_function = uchar_to_ansi; break;
  case CHARSET_UTF8:    converter_function = uchar_to_utf8; break;
  case CHARSET_UTF16BE:
  case CHARSET_UTF16LE: converter_function = uchar_to_utf16; break;
  case CHARSET_UTF32BE:
  case CHARSET_UTF32LE: converter_function = uchar_to_utf32; break;
  }

	if (uch->flags & UCHAR_FLAGS_USE_CASEFOLDED) {
		len += converter_function(&uch->casefolded[0], dst);
		if (uch->casefolded[1].ucs4.value != UCHAR_UNASSIGNED) {
			len += converter_function(&uch->casefolded[1], dst+len);
			if (uch->casefolded[2].ucs4.value != UCHAR_UNASSIGNED) {
				len += converter_function(&uch->casefolded[2], dst+len);
			}
		}
	} else {
		len = converter_function(&uch->character, dst);
	}
  return len;
}

EXPORT
bool uchar_isascii(const uchar_t& uch) {
  return (      (uch.variant == CHARSET_ANSI)
                ||        (uch.char_length == 1)
                ||        (uch.character.bytes[0]==0
                           && uch.character.bytes[1]==0
                           && uch.character.bytes[2]==0));
}

EXPORT
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

EXPORT
void uchar_toggle_case(uchar_t& uch) {
	uch.flags ^= UCHAR_FLAGS_USE_CASEFOLDED;
}

#ifdef __cplusplus
}
#endif

