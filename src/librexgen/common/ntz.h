/*
    rexgen - a tool to create words based on regular expressions
    Copyright (C) 2012-2014  Jan Starke <jan.starke@outofbed.org>

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


#ifndef NTZ_H
#define NTZ_H

#include <cstdint>

#ifdef WIN32
#include <intrin.h>
#if __x86_64__
#define ntz(x) (__lzcnt64(x)-1)
#else
#define ntz(x) (__lzcnt(x)-1)
#endif /* __x86_64__ */
#else /* ! WIN32 */
#if __x86_64__
#define ntz(x) (ffsll(x)-1)
#else
#define ntz(x) (ffsl(x)-1)
#endif /* __x86_64__ */
#endif /* WIN32 */

#endif /* NTZ_H */
