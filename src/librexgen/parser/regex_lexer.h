/*
    Copyright (c) 2012, Jan Starke <jan.starke@outofbed.org>
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
        * Neither the name of the <organization> nor the
        names of its contributors may be used to endorse or promote products
        derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY Jan Starke <jan.starke@outofbed.org> ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL Jan Starke <jan.starke@outofbed.org> BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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