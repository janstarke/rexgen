/*
    Copyright (C) 2012-2013  Jan Starke <rexgen@outofbed.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/
*/

#ifndef __osdepend_h__
#define __osdepend_h__

#if defined(_WIN32)
#include <io.h>
#define __attribute__(X) 
inline int isatty(int fd ) { return _isatty(fd); }
#define YY_NO_UNISTD_H

#define EXPORT __declspec (dllexport)

typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;

#else /* ! defined(_WIN32) */

#define EXPORT
#define _tmain main
#define _tcscmp strcmp
#define _tfopen fopen

#endif

#endif /* __osdepend_h__ */
