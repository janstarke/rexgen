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
void c_simplestring_clear(c_simplestring_ptr s) {
  (reinterpret_cast<SimpleString*>(s))->clear();
}

#ifdef __cplusplus
}
#endif

