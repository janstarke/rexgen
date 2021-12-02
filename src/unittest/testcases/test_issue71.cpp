/*
    rexgen - a tool to create words based on regular expressions
    Copyright (C) 2012-2019 Jan Starke <jan.starke@outofbed.org>

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

#include <catch2/catch.hpp>
#include <cstring>
#include <algorithm>
#include "../utils.h"

size_t issue71_stream_cb(char* dst, const size_t buffer_size) {
  const char* word = "test";
  size_t bytes = std::min(buffer_size, std::strlen(word));
  std::strncpy(dst, "test", buffer_size);
  return bytes;
}

TEST_CASE("Issue71", "StreamRegex")  {validateRegex("\\0",         10, issue71_stream_cb);}
