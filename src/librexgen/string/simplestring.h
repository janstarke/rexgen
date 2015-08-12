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


#ifndef SIMPLESTRING_H
#define SIMPLESTRING_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <array>
#include <librexgen/string/uchar.h>
#include <librexgen/string/unicode.h>
#include <librexgen/osdepend.h>
#include <librexgen/c/simplestring.h>

#ifdef __cplusplus

using std::vector;
using std::array;

static const size_t SIMPLESTRING_MAXLEN=512;

class SimpleString {
 public:
  SimpleString();
	~SimpleString() { delete[] characters; }

  uchar_t& operator[](size_t idx) {
    return characters[idx];
  }

  size_t to_ansi_string(char* buffer, const size_t buffer_size) const;
  size_t to_utf8_string(char* buffer, const size_t buffer_size) const;

	bool can_change_case(size_t idx) const {
		return (( u_hasBinaryProperty(characters[idx].codepoint, UCHAR_CHANGES_WHEN_UPPERCASED)
				  		|| u_hasBinaryProperty(characters[idx].codepoint, UCHAR_CHANGES_WHEN_LOWERCASED))
					&& UCHAR_CAN_CHANGE_CASE(characters[idx]));
	}

	void set_preserve_case() {
		for (size_t idx=0; idx<length; ++idx) {
			UCHAR_SET_PRESERVE_CASE(characters[idx]);
		}
	}

	inline
	void toggle_case(size_t idx) {
		characters[idx].toggle_case();
	}

  bool isalpha(unsigned int n) const;
  bool islower(unsigned int n) const;
  bool isupper(unsigned int n) const;

  void tolower(unsigned int n);
  void toupper(unsigned int n);

  inline void push_back(const char ch) {
		if (length >= SIMPLESTRING_MAXLEN) { return; }
		characters[length++] = ch;
	}

  inline void push_back(const uchar_t& c) {
		if (length >= SIMPLESTRING_MAXLEN) { return; }
		characters[length++] = c;
	}
  void append(const char* ch, const size_t ch_len);
	void append(const SimpleString& other) {
		if ((length + other.length) < SIMPLESTRING_MAXLEN) {
			memcpy(&characters[length], &other.characters[0], (other.length*sizeof(characters[0])));
			length += other.length;
		}
	}

  void clear()        { length=0; }
  size_t size() const { return length;  }
  bool empty() const  { return (length == 0); }
  size_t get_buffer_size() const;

  void print(FILE* out) const;

 protected:
	uchar_t* characters;
	size_t length;
	bool use_nonansi;
};

#endif /* __cplusplus */

#endif /* SIMPLESTRING_H */
