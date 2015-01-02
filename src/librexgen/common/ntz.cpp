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

#include <librexgen/ntz.h>

static int pop(unsigned int x) {
	unsigned long long y;
	y = x * 0x0002000400080010ULL;
	y = y & 0x1111111111111111ULL;
	y = y * 0x1111111111111111ULL;
	y = y >> 60;
	return y;
}


/* http://www.hackersdelight.org/hdcodetxt/ntz.c.txt */
/* Norbert Juffa's code, answer to exercise 1 of Chapter 5 (2nd ed). */
int ntz11(unsigned int n) {
	static unsigned char tab[32] =
   {   0,  1,  2, 24,  3, 19, 6,  25,
      22,  4, 20, 10, 16,  7, 12, 26,
      31, 23, 18,  5, 21,  9, 15, 11,
      30, 17,  8, 14, 29, 13, 28, 27
   };
   unsigned int k;
   n = n & (-n);        /* isolate lsb */
#if defined(SLOW_MUL)
   k = (n << 11) - n;
   k = (k <<  2) + k;
   k = (k <<  8) + n;
   k = (k <<  5) - k;
#else
   k = n * 0x4d7651f;
#endif
   return n ? tab[k>>27] : 32;
}

template <class COUNTER_T>
int ntz (COUNTER_T x) {
	#if sizeof(x)==32
		return ntz11(x);
	#elif sizeof(x)=64
		return ntz11((unsigned int) x & 0x00000000ffffffff)
					+ntz11((unsigned int) (x& 0xffffffff00000000)>>32);
	#else
		#error "no ntz() implementation for this word size"
	#endif
}
