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

#ifndef __regex_lexer_h__
#define __regex_lexer_h__

typedef int token_t;
typedef enum {
  normal,
  in_quantifier
} lexer_state;

const token_t T_DIGIT = 1;
const token_t T_ALPHA = 2;
const token_t T_HEXCHAR = 3;
const token_t T_SPECIAL = 4;
const token_t T_ANSICHAR = 5;
const token_t T_UNICODECHAR = 6;
const token_t T_ESCAPED = 7;
const token_t T_PIPE = 8;
const token_t T_ANY_CHAR = 9;

const token_t T_BEGIN_CLASS = 101;
const token_t T_END_CLASS = 102;
const token_t T_BEGIN_GROUP = 103;
const token_t T_END_GROUP = 104;
const token_t T_BEGIN_QUANTIFIER = 105;
const token_t T_HYPHEN = 106;

const token_t T_BEGIN = 201;
const token_t T_NUMBER = 202;
const token_t T_END_QUANTIFIER = 203;

#endif