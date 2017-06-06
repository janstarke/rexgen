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

#include <librexgen/c/simplestring.h>
#include <librexgen/string/simplestring.h>
#include <cstdlib>

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
const char* c_simplestring_to_string(c_simplestring_ptr s) {
  return (static_cast<SimpleString*>(s))->c_str();
}

EXPORT
int c_simplestring_to_utf8_string(c_simplestring_ptr s, char* buffer,
                                  size_t buffer_size) {
  const SimpleString* str = static_cast<SimpleString*>(s);
  char tmp_buffer[8];
  wchar_t wc;
  int result = 0;
  locale_t utf8_locale = newlocale(LC_ALL_MASK, "en_US.UTF-8", 0);

  const char* ptr = str->data();
  const char* end = ptr + str->size();
  while (ptr < end) {
    int next = std::mblen(ptr, end-ptr);
    if (next == -1) {
      throw std::runtime_error("mblen(): conversion error");
    }

    mbtowc(&wc, ptr, end-ptr);
    const int size = wctomb_l(&tmp_buffer[0], wc, utf8_locale);
    if (size < 1) {
      throw std::runtime_error("wctomb_l(): conversion error");
    }
    if (size < ((int)buffer_size-result)) {
      memcpy(buffer+result, tmp_buffer, size);
      result += size;
    } else {
      *buffer = 0;
      break;
    }
    ptr += next;
  }

  return result;
}

EXPORT
void c_simplestring_clear(c_simplestring_ptr s) {
  (reinterpret_cast<SimpleString*>(s))->clear();
}

#ifdef __cplusplus
}
#endif

