%option prefix="rexgen_"
%option bison-bridge
%option bison-locations
%option reentrant
%option noyywrap
%option nounput
%{
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
  #include <librexgen/regex/regex.h>
  #include <librexgen/regex/regexalternatives.h>
  #include <librexgen/regex/compoundregex.h>
  #include <librexgen/regex/quantifier.h>
  #include <librexgen/regex/terminalregex.h>
  #include <librexgen/regex/classregex.h>
  #include <librexgen/regex/groupreference.h>
  #include <librexgen/parser/rexgenparsercontext.h>
  #include <librexgen/unicode.h>
  #include <librexgen/osdepend.h>
  #include <librexgen/parser/syntaxerror.h>
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

  static void UTF8_validate_second_byte(const unsigned char c) {
    if (c < 0x80 || c >= 0xC0) {
        throw SyntaxError("invalid UTF8  byte sequence");
    }
  }

  static uint32_t parseUTF8(const unsigned char* text) {
    if (text[0] < 0x80) { return text[0]; }
    if (text[0] < 0xC0) { throw SyntaxError("invalid UTF8 byte sequence"); }
    if (text[0] <= 0xDF) {
      UTF8_validate_second_byte(text[1]);
      return    ( (0x1F & text[0])<<6)
              | (  0x3F & text[1]);
    }

    if (text[0] <= 0xEF) {
      UTF8_validate_second_byte(text[1]);
      UTF8_validate_second_byte(text[2]);
      return    ( (0x0F & text[0])<<12)
              | ( (0x3F & text[1])<<6)
              | (  0x3F & text[2]);
    }

    if (text[0] <= 0xF7) {
      UTF8_validate_second_byte(text[1]);
      UTF8_validate_second_byte(text[2]);
      UTF8_validate_second_byte(text[3]);
      return    ( (0x0F & text[0])<<18)
              | ( (0x3F & text[1])<<12)
              | ( (0x3F & text[2])<<6)
              | (  0x3F & text[3]);
    }
    throw SyntaxError("unknown UTF8 byte sequence");
  }
%}

DIGIT		[0-9]
ALPHA		[_a-zA-Z]
ANSICHAR	\\x[0-9a-fA-F]{2,2}
UNICODECHAR	\\u[0-9a-fA-F]{4,4}
LINEFEED	\\n
CARRIAGERETURN	\\r
SPECIAL		[ \t\r\n.,;:=/%&?<>-]
GROUPID		\\[1-9]
STREAM          \\0
ESCAPED		\\[^xnur0-9]

UTF8_2          [\xC0-\xDF][\x80-\xBF]
UTF8_3          [\xE0-\xEF][\x80-\xBF][\x80-\xBF]
UTF8_4          [\xF0-\xF7][\x80-\xBF][\x80-\xBF][\x80-\xBF]

%s IN_QUANTIFIER
%s IN_CLASS
%%

{ANSICHAR}		{ yylval->character = parseAnsiChar(yytext); return T_ANY_CHAR;}
{UNICODECHAR}		{ yylval->character = parseUnicodeChar(yytext); return T_ANY_CHAR;}
{UTF8_2}                { yylval->character = parseUTF8(reinterpret_cast<unsigned char*>(yytext)); return T_ANY_CHAR;}
{UTF8_3}                { yylval->character = parseUTF8(reinterpret_cast<unsigned char*>(yytext)); return T_ANY_CHAR;}
{UTF8_4}                { yylval->character = parseUTF8(reinterpret_cast<unsigned char*>(yytext)); return T_ANY_CHAR;}
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
{STREAM}                { yylval->integer = atoi(&yytext[1]); return T_STREAM; }
<IN_QUANTIFIER>","	{ return T_COMMA; }
<IN_CLASS>"-"		{ return T_HYPHEN; }
<IN_QUANTIFIER>{DIGIT}+		{ yylval->integer = atoi(yytext); return T_NUMBER; }
.                       { yylval->character = yytext[0]; return T_ANY_CHAR; }

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
