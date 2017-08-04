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

#include <librexgen/common/ntz.h>
#include <cinttypes>
#include <cstddef>
#include <cstdint>

/* http://www.hackersdelight.org/hdcodetxt/ntz.c.txt
 * Norbert Juffa's code, answer to exercise 1 of Chapter 5 (2nd ed).
 */
int ntz11(unsigned int n) {
  static unsigned char tab[32] = {
    0,  1,  2, 24,  3, 19, 6,  25,
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

#if !defined(__USE_INLINE_NTZ__)
#if __x86_64__
unsigned int ntz(std::uint64_t x) {
  const unsigned int lower_part =
      (const unsigned int) (x & 0x00000000ffffffff);
  /* no need to AND-out the 32 right-most here,
   * since they are shifted out */
  const unsigned int higher_part = (const unsigned int) (x>>32);

  if (lower_part == 0) {
    return sizeof(lower_part)*8 + ntz11(higher_part);
  } else {
    return                        ntz11(lower_part);
  }
}
#else

unsigned int ntz(std::uint32_t x) {
  return ntz11(x);
}
#endif /* __x86_64__ */
#endif /* ! defined(__USE_INLINE_NTZ__) */
