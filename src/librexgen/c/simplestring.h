/*
    rexgen - a tool to create words based on regular expressions
    Copyright (C) 2012-2017  Jan Starke <jan.starke@outofbed.org>

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


#ifndef SRC_LIBREXGEN_C_SIMPLESTRING_H_
#define SRC_LIBREXGEN_C_SIMPLESTRING_H_

#include <librexgen/string/unicode.h>
#include <librexgen/osdepend.h>
#include <librexgen/common/deprecated.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void* c_simplestring_ptr;

EXPORT
c_simplestring_ptr c_simplestring_new();

EXPORT
void c_simplestring_delete(c_simplestring_ptr s);

EXPORT
const char* c_simplestring_to_string(c_simplestring_ptr s);

EXPORT
DEPRECATED(int c_simplestring_to_utf8_string(c_simplestring_ptr s, char* buffer,
                                             size_t buffer_size));

EXPORT
void c_simplestring_clear(c_simplestring_ptr s);

EXPORT
void c_simplestring_truncate_bytes(c_simplestring_ptr s, size_t length);

#ifdef __cplusplus
}
#endif

#endif  /* SRC_LIBREXGEN_C_SIMPLESTRING_H_ */
