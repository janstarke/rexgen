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

#include <librexgen/debug.h>

static int level = 0;
static char space_buffer[512];

void enter_level() {
  ++level;
}
void leave_level() {
  --level;
}

int get_level() {
  return level;
}

char* spaces(char c, int s) {
  if (((size_t)s) > (sizeof(space_buffer)/sizeof(space_buffer[0])-1)) {
    return 0;
  }
  for (int n = 0; n < s; ++n) {
    space_buffer[n] = c;
  }
  space_buffer[s] = '\0';
  return space_buffer;
}
