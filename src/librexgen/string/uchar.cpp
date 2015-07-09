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
 * PRIVATE INTERFACE
 */

uint8_t uchar_to_ansi(const uchar_t& uch, byte* dst) {
	if (uch.plane==BMP && uch.codepoint < 256) {
		*dst = static_cast<byte>(uch.codepoint);
		return 1;
	}
  *dst = 0xfe;
	return 1;
}

uint8_t uchar_to_utf8(const uchar_t& uch, byte* dst) {
	if (uch.plane==BMP && uch.codepoint < 128) {
		*dst = static_cast<byte>(uch.codepoint);
		return 1;
	}
  return convert_utf32_to_utf8(dst, uch.full_codepoint());
}

void __uchar_toggle_case(uchar_t& uch) {
  if (u_isULowercase(uch.codepoint)) {
    uch.codepoint = u_toupper(uch.codepoint);
  } else if(u_isUUppercase(uch.codepoint)){
    uch.codepoint = u_tolower(uch.codepoint);
  }
}

