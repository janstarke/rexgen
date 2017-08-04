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

#ifndef SRC_LIBREXGEN_OSDEPEND_H_
#define SRC_LIBREXGEN_OSDEPEND_H_

#if defined(_WIN32)
#include <io.h>
#define __attribute__(X)
#ifdef __cplusplus
inline
#endif
int isatty(int fd ) { return _isatty(fd); }
#define YY_NO_UNISTD_H

#define EXPORT __declspec (dllexport)

typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;

#else /* ! defined(_WIN32) */
#include <stdint.h>

#define EXPORT
#define _tmain main
#define _tcscmp strcmp
#define _tfopen fopen

#endif

#endif  /* SRC_LIBREXGEN_OSDEPEND_H_ */
