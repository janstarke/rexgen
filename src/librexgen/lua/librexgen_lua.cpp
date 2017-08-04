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
#include <lua5.2/lua.h>
#include <lua5.2/lualib.h>
#include <lua5.2/lauxlib.h>
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
    Iterator* iter =
      * reinterpret_cast<Iterator**>(lua_touserdata(L, lua_upvalueindex(1)));
    if (iter->next()) {
      rexgen_value(L, iter);
      return 1;
    } else {
      return 0;
    }
  }

  EXPORT
  int rexgen_parse_regex(lua_State* L) {
    SimpleString xml;
    RexgenOptions options;

    Iterator** iter;
    iter = reinterpret_cast<Iterator**>(lua_newuserdata(L, sizeof(*iter)));
    luaL_getmetatable(L, "rexgen.iter");
    lua_setmetatable(L, -2);
    *iter = regex_iterator(luaL_checklstring(L, 1, NULL), options);
    lua_pushcclosure(L, rexgen_iter, 1);

    return 1;
  }

  EXPORT
  int rexgen_value(lua_State* L, const Iterator* iter) {
    char* buffer = NULL;
    SimpleString str;

    iter->value(str);
    const size_t buffer_size = (str.size()+1)*4;
    buffer = new char[buffer_size];
    size_t bytes = str.to_ansi_string(buffer, buffer_size);
    lua_pushlstring(L, buffer, bytes);
    delete [] buffer;
    str.clear();

    return 1;
  }
}

