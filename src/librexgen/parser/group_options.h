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

#ifndef SRC_LIBREXGEN_PARSER_GROUP_OPTIONS_H_
#define SRC_LIBREXGEN_PARSER_GROUP_OPTIONS_H_

/*
 * if the specific characters is configured to CASE_IGNORE,
 * it can be casefolded (and must be switched to CASE_ITERATE
 */
#define CASE_IGNORE   0
#define CASE_ITERATE  1

struct t_group_options {
  t_group_options()
    : handle_case(CASE_IGNORE), group_id(-1) {}
  int handle_case;
  int group_id;
};


#endif /* SRC_LIBREXGEN_PARSER_GROUP_OPTIONS_H_ */
