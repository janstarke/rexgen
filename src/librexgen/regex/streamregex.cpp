/*
    rexgen - a tool to create words based on regular expressions
    Copyright (C) 2012-2015  Jan Starke <jan.starke@outofbed.org>

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

#include <librexgen/regex/streamregex.h>
#include <librexgen/genericerror.h>

#include <unistd.h>
#include <cstdio>
using namespace std;

unsigned long long int StreamRegex::size() const {
  /* files with more than 2^32 newlines do not make sense to be handled */
  size_t __size = 0;

  /* duplicate original file pointer */
  FILE *fp2 = fdopen (dup (fileno (infile)), "r");
  if (fp2 == NULL) {
    throw new GenericError("unable to duplicate file pointer");
  }

  /* loop through file, inspired by http://blog.fefe.de/?ts=aa3c0cd3 */
  size_t buffer[1024*1024];
  size_t bytes_read;
  size_t h, t;
  do {
    bytes_read = fread(buffer, 1, sizeof(buffer), fp2);
    h = bytes_read / sizeof(buffer[0]); /* number of elements read */
    t = bytes_read % sizeof(buffer[0]); /* number of bytes after the last full element */

    /* handle 4-byte values */
    size_t idx;
    for (idx = 0; idx<h; ++idx) {
      size_t x = buffer[idx]
#if UINTMAX_MAX==UINT64_MAX
      ^ 0x0a0a0a0a0a0a0a0a;
#elif UINTMAX_MAX==UINT32_MAX
      ^ 0x0a0a0a0a;
#endif

    /* now, every byte in x is either 0x00 (if it contained a newline) or != 0x00 (otherwise) */
    /*
    __size += 0
#if UINTMAX_MAX==UINT64_MAX || UINTMAX_MAX==UINT32_MAX
          + ((x&((size_t)0xff<<(7*8))) == 0)
          + ((x&((size_t)0xff<<(6*8))) == 0)
          + ((x&((size_t)0xff<<(5*8))) == 0)
          + ((x&((size_t)0xff<<(4*8))) == 0)
#endif
          + ((x&((size_t)0xff<<(3*8))) == 0)
          + ((x&((size_t)0xff<<(2*8))) == 0)
          + ((x&((size_t)0xff<<(1*8))) == 0)
          + ((x&((size_t)0xff<<(0*8))) == 0);
    */

#if UINTMAX_MAX==UINT64_MAX || UINTMAX_MAX==UINT32_MAX
    __size += ((x&((size_t)0xff<<(7*8))) == 0);
    __size += ((x&((size_t)0xff<<(6*8))) == 0);
    __size += ((x&((size_t)0xff<<(5*8))) == 0);
    __size += ((x&((size_t)0xff<<(4*8))) == 0);
#endif
    __size += ((x&((size_t)0xff<<(3*8))) == 0);
    __size += ((x&((size_t)0xff<<(2*8))) == 0);
    __size += ((x&((size_t)0xff<<(1*8))) == 0);
    __size += ((x&((size_t)0xff<<(0*8))) == 0);

    }

    size_t* ptr = &buffer[h];
    for (idx=0; idx<t; ++idx, ++ptr) {
      __size += ((*ptr) == 0x0a);
    }
  } while (bytes_read == sizeof(buffer));

  return __size;
}

