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

#include <librexgen/lua/librexgen_lua.h>
#include <librexgen/librexgen.h>
#include <librexgen/iterator/iterator.h>
#include <librexgen/regex/regex.h>
#include <librexgen/string/simplestring.h>
#include <librexgen/rexgen_options.h>
#include <librexgen/osdepend.h>

extern "C" {
#include "lua.h"
}

#include <vector>
#include <string>

static const luaL_Reg rexgen_lib[] = {
  { "parse_regex",      rexgen_parse_regex },
  {NULL, NULL}
};

extern "C" {
  EXPORT
  int luaopen_rexgen(lua_State* L) {
    luaL_newlib(L, rexgen_lib);
    return 1;
  }

  EXPORT
  int rexgen_iter(lua_State* L) {
    c_iterator_ptr iter = lua_tointeger(L, 1);
    if (c_iterator_next(iter)) {
      rexgen_value(L, iter);
      return 1;
    } else {
      return 0;
    }
  }

  size_t callback(char* dst, const size_t buffer_size) {
    size_t len = 0;
    while (len == 0) {
      /* read next word */
      if (fgets(dst, buffer_size, stdin) == NULL) {
        return 0;
      }

      /* remove trailing newlines */
      len = strnlen(dst, buffer_size);
      while (len > 0 && dst[len - 1] == '\n') {
        --len;
        dst[len] = '\0';
      }
    }
    return len;
  }

  void parser_error(const char* msg) {
    fprintf(stderr, "%s\n", msg);
  }

  EXPORT
  int rexgen_parse_regex(lua_State* L) {
    SimpleString xml;

    auto regex = c_regex_cb_mb(luaL_checklstring(L, 1, NULL), callback, parser_error);
    c_iterator_ptr iter = c_regex_iterator(regex);
    lua_pushinteger(L, iter);

    return 1;
  }

  EXPORT
  int rexgen_value(lua_State* L, c_iterator_ptr iter) {
    c_simplestring_ptr str = c_simplestring_new();

    c_iterator_value(iter, str);
    const std::string value = c_simplestring_to_string(str);

    lua_pushlstring(L, value.c_str(), value.size());
    return 1;
  }
}

