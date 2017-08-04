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

#ifndef SRC_LIBREXGEN_LUA_LIBREXGEN_LUA_H_
#define SRC_LIBREXGEN_LUA_LIBREXGEN_LUA_H_

#include <librexgen/iterator/iterator.h>
#include <librexgen/string/unicode.h>
#include <librexgen/string/simplestring.h>
#include <librexgen/osdepend.h>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
extern "C" {
  EXPORT
  int rexgen_parse_regex(lua_State* L);

  EXPORT
  int rexgen_value(lua_State* L, const Iterator* iter);

  EXPORT
  int luaopen_rexgen(lua_State* L);

  EXPORT
  int rexgen_iter(lua_State* L);
}

#endif /* SRC_LIBREXGEN_LUA_LIBREXGEN_LUA_H_ */
