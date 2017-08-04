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

#ifndef SRC_LIBREXGEN_C_LIBREXGEN_H_
#define SRC_LIBREXGEN_C_LIBREXGEN_H_

#include <librexgen/c/types.h>
#include <librexgen/c/iterator.h>
#include <librexgen/c/simplestring.h>
#include <librexgen/common/deprecated.h>
#include <librexgen/version.h>
#include <stdio.h>
#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif

EXPORT
const char* c_rexgen_get_last_error();
void c_rexgen_set_last_error(const char* msg);

EXPORT
DEPRECATED(
c_regex_ptr c_regex_cb(
  const char* regex_str,
  callback_fp cb));

EXPORT
c_regex_ptr c_regex_cb_mb(
        const char* regex_str,
        callback_fp_mb cb);

EXPORT
void c_regex_delete(c_regex_ptr regex);

EXPORT
int c_regex_uses_callback(c_regex_ptr i);

#ifdef __cplusplus
}
#endif

#endif  /* SRC_LIBREXGEN_C_LIBREXGEN_H_ */
