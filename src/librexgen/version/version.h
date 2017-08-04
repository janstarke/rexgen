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

#ifndef SRC_LIBREXGEN_VERSION_VERSION_H_
#define SRC_LIBREXGEN_VERSION_VERSION_H_
#include <librexgen/osdepend.h>

#ifdef __cplusplus
extern "C" {
#endif

#define JS_REGEX_MAJOR_VERSION @librexgen_major@
#define JS_REGEX_MINOR_VERSION @librexgen_minor@
#define JS_REGEX_BUILD_VERSION @librexgen_release@

#define __rexgen_xstr(s) __rexgen_str(s)
#define __rexgen_str(s) #s

#define JS_REGEX_RELEASE __rexgen_xstr(JS_REGEX_MAJOR_VERSION) "." \
        __rexgen_xstr(JS_REGEX_MINOR_VERSION)

EXPORT
const char* rexgen_version();

EXPORT
unsigned int rexgen_version_int();

#ifdef __cplusplus
}
#endif

#endif /* SRC_LIBREXGEN_VERSION_VERSION_H_ */
