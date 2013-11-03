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

#ifndef __librexgen_api_c_h__
#define __librexgen_api_c_h__

#include <librexgen/unicode/uchar.h>
#include <librexgen/rexgen_options.h>
#include <librexgen/regex/regex.h>
#include <librexgen/iterator/iterator.h>
#include <librexgen/simplestring.h>

extern "C" {

	typedef void* c_iterator_ptr;
	typedef void* c_simplestring_ptr;

	EXPORT
	c_iterator_ptr c_regex_iterator(
					const char* regex_str,
					int ignore_case,
					charset encoding,
					int randomize,
					FILE* infile);

	EXPORT
	int c_iterator_next(c_iterator_ptr iter);
	EXPORT
	void c_iterator_value(c_iterator_ptr next, c_simplestring_ptr dst);
	EXPORT
	void c_iterator_delete(c_iterator_ptr i) {
		delete (reinterpret_cast<Iterator*>(i));
	}

	EXPORT
	const char* c_rexgen_get_last_error();
	void c_rexgen_set_last_error(const char* msg); 

	EXPORT
	c_simplestring_ptr c_simplestring_new() { return new SimpleString(); }

	EXPORT
	void c_simplestring_delete(c_simplestring_ptr s) {
		delete (reinterpret_cast<SimpleString*>(s));
	}

	EXPORT
	void c_simplestring_newline(c_simplestring_ptr s) {
		(reinterpret_cast<SimpleString*>(s))->newline();
	}
	EXPORT
	void c_simplestring_print(c_simplestring_ptr s, FILE* dst, int flush = 0) {
		(reinterpret_cast<SimpleString*>(s))->print(dst, (bool)flush);
	}
	EXPORT
	void c_simplestring_push_back(c_simplestring_ptr s, uchar_t ch) {
		(reinterpret_cast<SimpleString*>(s))->push_back(ch);
	}
}
#endif /* __librexgen_api_c_h__ */
