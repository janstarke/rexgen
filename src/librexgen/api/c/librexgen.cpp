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

#include <librexgen/api/c/librexgen.h>
#include <librexgen/unicode/uchar.h>
#include <librexgen/rexgen_options.h>
#include <librexgen/regex/regex.h>
#include <librexgen/iterator/iterator.h>
#include <librexgen/simplestring.h>
#include <librexgen/librexgen.h>
#include <librexgen/parser/syntaxerror.h>
#include <cstdio>

using namespace std;

static const char* c_rexgen_last_error = NULL;

extern "C" {
	EXPORT
	const char* c_rexgen_get_last_error() {
		return c_rexgen_last_error;
	}
	void c_rexgen_set_last_error(const char* msg){
		c_rexgen_last_error =	msg;
	}
}

