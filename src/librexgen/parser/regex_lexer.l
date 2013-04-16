%option prefix="rexgen_"
%option bison-bridge
%option bison-locations
%option reentrant
%option noyywrap
%option nounput
%{
/*
    Copyright (C) 2012-2013  Jan Starke <rexgen@outofbed.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/
*/
  #include <librexgen/regex/regex.h>
  #include <librexgen/regex/regexalternatives.h>
  #include <librexgen/regex/compoundregex.h>
  #include <librexgen/regex/quantifier.h>
  #include <librexgen/regex/terminalregex.h>
  #include <librexgen/regex/classregex.h>
  #include <librexgen/regex/groupreference.h>
  #include <librexgen/parser/rexgenparsercontext.h>
  #include <librexgen/unicode.h>
  #include <librexgen/parser/osdepend.h>
  #include "parser.hpp"
  #include <cstdio>
  
  #define YY_EXTRA_TYPE RexgenParserContext*
//  #define YY_USER_ACTION yylloc->first_line = yylinelo
  
  #define YY_INPUT(buf,result,max_size) {	\
    char c;					\
    (*yyextra->is) >> noskipws >> c;		\
    if (yyextra->is->eof())			\
      result = YY_NULL;				\
    else {					\
      buf[0] = c;				\
      result = 1;				\
    }						\
  }
  
  static char hex2bin(const char c) {
    if (c>='0' && c<='9') return c-'0';
    if (c>='a' && c<='f') return (10+c-'a');
    if (c>='A' && c<='F') return (10+c-'A');
    return (char)0xff;
  }
  
  static char parseAnsiChar(const char* text) {
    return (hex2bin(text[2])<<4) | (hex2bin(text[3]));
  }
  
  static uint32_t parseUnicodeChar(const char* text) {
    return (hex2bin(text[2])<<12)
	  | (hex2bin(text[3])<<8)
	  | (hex2bin(text[4])<<4)
	  | (hex2bin(text[5]));
  }
%}

DIGIT		[0-9]
ALPHA		[_a-zA-Z]
ANSICHAR	\\x[0-9a-fA-F]{2,2}
UNICODECHAR	\\u[0-9a-fA-F]{4,4}
LINEFEED	\\n
CARRIAGERETURN	\\r
SPECIAL		[ \t\r\n.,;:=/%&?<>-]
GROUPID		\\[0-9]+
ESCAPED		\\[^xnur0-9]

%s IN_QUANTIFIER
%s IN_CLASS
%%

{ANSICHAR}		{ yylval->character = parseAnsiChar(yytext); return T_ANY_CHAR;}
{UNICODECHAR}		{ yylval->character = parseUnicodeChar(yytext); return T_ANY_CHAR;}
{ESCAPED}		{ yylval->character = (char)yytext[1]; return T_ANY_CHAR; }
{LINEFEED}		{ yylval->character = '\n'; return T_ANY_CHAR; }
{CARRIAGERETURN}	{ yylval->character = '\r'; return T_ANY_CHAR; }
"|"			{ return T_PIPE; }
"["			{ BEGIN(IN_CLASS); return T_BEGIN_CLASS; }
"]"			{ BEGIN(INITIAL); return T_END_CLASS; }
"("			{ return T_BEGIN_GROUP; }
")"			{ return T_END_GROUP; }
"{"			{ BEGIN(IN_QUANTIFIER); return T_BEGIN_QUANTIFIER; }
"}"			{ BEGIN(INITIAL); return T_END_QUANTIFIER; }
{GROUPID}		{ yylval->integer = atoi(&yytext[1]); return T_GROUPID; }
<IN_QUANTIFIER>","	{ return T_COMMA; }
<IN_CLASS>"-"		{ return T_HYPHEN; }
<IN_QUANTIFIER>{DIGIT}+		{ yylval->integer = atoi(yytext); return T_NUMBER; }
{DIGIT}|{ALPHA}|{SPECIAL}	{ yylval->character = yytext[0]; return T_ANY_CHAR; }
%%


  void RexgenParserContext::InitScanner() {
    yylex_init(&scanner);
    yyset_extra(this, scanner);
#ifdef YYDEBUG
    rexgen_set_debug(1, scanner);
#endif
  }
  
  void RexgenParserContext::DestroyScanner() {
    yylex_destroy(scanner);
  }
