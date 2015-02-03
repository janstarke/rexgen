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


#include <ctype.h>
#include <librexgen/string/simplestring.h>

SimpleString::SimpleString(size_t msize)
	:characters(msize) {
	clear();
}

uchar_t& SimpleString::operator[](const unsigned int& idx) {
	return characters[idx];
}

const uchar_t& SimpleString::getAt(const unsigned int& idx) const {
  return (const uchar_t&) characters[idx];
}

size_t SimpleString::size() const {
	return characters.size();
}


bool SimpleString::isalpha(unsigned int n) const {
	return (uchar_isascii(characters[n]) && ::isalpha(characters[n].character.ansi.value));
}
bool SimpleString::islower(unsigned int n) const {
	return (uchar_isascii(characters[n]) && ::islower(characters[n].character.ansi.value));
}

bool SimpleString::isupper(unsigned int n) const {
	return (uchar_isascii(characters[n]) && ::isupper(characters[n].character.ansi.value));
}

void SimpleString::tolower(unsigned int n) {
	if (uchar_isascii(characters[n])) {
		characters[n].character.ansi.value = ::tolower(characters[n].character.ansi.value);
	}
}
void SimpleString::toupper(unsigned int n) {
	if (uchar_isascii(characters[n])) {
		characters[n].character.ansi.value = ::toupper(characters[n].character.ansi.value);
	}
}


void SimpleString::append(const char* ch) {
	while (*ch != '\0') {
		push_back(char_to_uchar(*ch++));
	}
}

size_t SimpleString::get_buffer_size() const {
	return characters.size();
}

void SimpleString::clear() {
	characters.clear();
}

void SimpleString::push_back(char ch) {
	push_back(char_to_uchar(ch));
}

void SimpleString::push_back(const uchar_t& c) {
	characters.push_back(c);
}

void SimpleString::newline() {
	return push_back('\n');
}

int SimpleString::to_binary_string(char* dst, size_t buffer_size) const {
	char* ptr = dst;
	int count = 0;
	for (unsigned int idx=0; idx<characters.size() && buffer_size>(4+1); ++idx) {
		const uint8_t char_size = uchar_to_binary(&characters[idx], ptr);
		ptr += char_size;
		buffer_size -= char_size;
	}
	if (buffer_size > 1) {
		*ptr = 0;
		++count;
	}
	return count;
}

#ifdef __cplusplus
extern "C" {
#endif

EXPORT
c_simplestring_ptr c_simplestring_new() { return new SimpleString(); }

EXPORT
void c_simplestring_delete(c_simplestring_ptr s) {
  delete (reinterpret_cast<SimpleString*>(s));
}

EXPORT
void c_simplestring_newline(c_simplestring_ptr s) {
  (reinterpret_cast<SimpleString*>(s))->newline();
}

EXPORT
void c_simplestring_push_back(c_simplestring_ptr s, uchar_t ch) {
  (reinterpret_cast<SimpleString*>(s))->push_back(ch);
}

EXPORT
int c_simplestring_to_binary_string(c_simplestring_ptr s, char* buffer, size_t buffer_size) {
  return (reinterpret_cast<SimpleString*>(s))->to_binary_string(buffer, buffer_size);
}

EXPORT
void c_simplestring_clear(c_simplestring_ptr s) {
  (reinterpret_cast<SimpleString*>(s))->clear();
}

#ifdef __cplusplus
}
#endif

