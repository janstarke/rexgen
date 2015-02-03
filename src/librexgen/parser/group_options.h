/*
    rexgen - a tool to create words based on regular expressions
    Copyright (C) 2012-2015  Jan Starke <jan.starke@outofbed.org>

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

#ifndef __group_options_h__
#define __group_options_h__

/*
 * if the specific characters is configured to CASE_IGNORE,
 * it can be casefolded (and must be switched to CASE_ITERATE
 * or it can be switched to CASE_PRESERVE
 */
#define CASE_IGNORE		0
#define CASE_ITERATE	1
#define CASE_PRESERVE	2

struct t_group_options {
  t_group_options()
    : handle_case(CASE_IGNORE),group_id(-1) {}
  int handle_case;
	int group_id;
};


#endif /* __group_options_h__ */
