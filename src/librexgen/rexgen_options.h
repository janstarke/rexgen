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

#ifndef SRC_LIBREXGEN_REXGEN_OPTIONS_H_
#define SRC_LIBREXGEN_REXGEN_OPTIONS_H_

#include <librexgen/c/types.h>
#include <librexgen/defs.h>
#include <cstdio>

class RexgenOptions {
 public:
  RexgenOptions()
    : ignore_case(false),
      encoding(CHARSET_UTF8),
      infile(NULL),
      stream_callback(NULL) { }
  bool ignore_case;
  charset encoding;
  std::FILE* infile;
  callback_fp_mb stream_callback;
};

#endif  // SRC_LIBREXGEN_REXGEN_OPTIONS_H_

