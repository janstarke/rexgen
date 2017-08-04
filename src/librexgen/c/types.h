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

#ifndef SRC_LIBREXGEN_C_TYPES_H_
#define SRC_LIBREXGEN_C_TYPES_H_

/* do not include cstddef, because types.h must be includable
 * by ANSI-C code
 */
#include <stddef.h>
#include <stdint.h>
#include <wchar.h>

typedef void* c_regex_ptr;

/* callback to read multibyte strings */
typedef size_t (*callback_fp_mb)(char* dst, const size_t buffer_size);

/* callback to read wide character strings */
typedef size_t (*callback_fp)(wchar_t* dst, const size_t buffer_size);

#endif  /* SRC_LIBREXGEN_C_TYPES_H_ */
