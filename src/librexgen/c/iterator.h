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


#ifndef SRC_LIBREXGEN_C_ITERATOR_H_
#define SRC_LIBREXGEN_C_ITERATOR_H_

#include <assert.h>
#include <librexgen/c/librexgen.h>
#include <librexgen/string/unicode.h>
#include <librexgen/c/simplestring.h>
#include <librexgen/osdepend.h>
#include <librexgen/common/deprecated.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void* c_iterator_ptr;

EXPORT
c_iterator_ptr c_regex_iterator(c_regex_ptr regex);

EXPORT
c_iterator_ptr c_regex_iterator_cb_mb(
  const char* regex_str,
  int ignore_case,
  callback_fp_mb cb);

EXPORT
DEPRECATED(c_iterator_ptr c_regex_iterator_cb(
        const char* regex_str,
        int ignore_case,
        callback_fp cb));

EXPORT
int c_iterator_next(c_iterator_ptr iter);
EXPORT
void c_iterator_value(c_iterator_ptr next, c_simplestring_ptr dst);
EXPORT
void c_iterator_delete(c_iterator_ptr i);

EXPORT
void c_iterator_get_statex(c_iterator_ptr i, void** dstptr);
EXPORT
void c_iterator_set_statex(c_iterator_ptr i, void* dstptr);
EXPORT
void c_iterator_get_state(c_iterator_ptr i, char** dstptr);
EXPORT
void c_iterator_set_state(c_iterator_ptr i, char* dstptr);
EXPORT
void c_iterator_delete_state_buffer(char* srcptr);

#ifdef __cplusplus
}
#endif

#endif  /* SRC_LIBREXGEN_C_ITERATOR_H_ */

