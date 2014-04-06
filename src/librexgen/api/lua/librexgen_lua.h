/*
    rexgen - a tool to create words based on regular expressions    
    Copyright (C) 2012-2013  Jan Starke <jan.starke@outofbed.org>

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

#ifndef __librexgen_lua_h__
#define __librexgen_lua_h__

#include <librexgen/iterator/iterator.h>
#include <librexgen/string/unicode.h>
#include <librexgen/string/simplestring.h>

extern "C" {
#include <lua5.2/lua.h>
#include <lua5.2/lualib.h>
#include <lua5.2/lauxlib.h>
}
extern "C" {
int rexgen_parse_regex(lua_State* L);

int rexgen_value(lua_State* L, const Iterator* iter);

int luaopen_rexgen(lua_State* L);

int rexgen_iter(lua_State* L);

int rexgen_get_syntax_tree(lua_State* L);
}

void push_utf8_string(lua_State* L, const SimpleString& str);

#endif /* __librexgen_lua_h__ */
