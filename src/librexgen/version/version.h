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

#ifndef __VERSION_H__
#define __VERSION_H__
#include <librexgen/osdepend.h>

#ifdef __cplusplus
extern "C" {
#endif

#define JS_REGEX_MAJOR_VERSION @librexgen_major@
#define JS_REGEX_MINOR_VERSION @librexgen_minor@
#define JS_REGEX_BUILD_VERSION @librexgen_build@

#define xstr(s) str(s)
#define str(s) #s

#define JS_REGEX_RELEASE xstr(JS_REGEX_MAJOR_VERSION) "." xstr(JS_REGEX_MINOR_VERSION)

EXPORT
const char* rexgen_version();

#ifdef __cplusplus
}
#endif

#endif /* __VERSION_H__ */
