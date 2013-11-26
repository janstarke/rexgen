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


#include <librexgen/iterator/iterator.h>
#include <librexgen/api/cxx/librexgen.h>
#include <librexgen/api/c/librexgen.h>
#include <librexgen/rexgen_options.h>
#include <librexgen/parser/syntaxerror.h>

#ifdef __cplusplus
extern "C" {
#endif

EXPORT
c_iterator_ptr c_regex_iterator(
				const char* regex_str,
				int ignore_case=0,
				charset encoding=CHARSET_UTF8,
				int randomize=0,
				FILE* infile=NULL) {
	RexgenOptions options;
	options.ignore_case = (bool)ignore_case;
	options.encoding = encoding;
	options.randomize = (bool)randomize;
	options.infile = infile;

	Iterator* iter = nullptr;
	try {
		iter = regex_iterator(regex_str, options);
	} catch(SyntaxError& error) {
		c_rexgen_set_last_error(error.getMessage());
		return NULL;
	}
	return iter;
}

EXPORT
int c_iterator_next(c_iterator_ptr iter) {
	return (reinterpret_cast<Iterator*>(iter))->next();
}

EXPORT
void c_iterator_value(c_iterator_ptr iter, c_simplestring_ptr dst) {
	(reinterpret_cast<Iterator*>(iter))->value(*(reinterpret_cast<SimpleString*>(dst)));
}


EXPORT
void c_iterator_delete(c_iterator_ptr i) {
	delete (reinterpret_cast<Iterator*>(i));
}

#ifdef __cplusplus
}
#endif

