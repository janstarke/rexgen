%option noyywrap
%option nounput
%{
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
  #include <librexgen/regex/regex.h>
  #include <librexgen/regex/regexalternatives.h>
  #include <librexgen/regex/compoundregex.h>
  #include <librexgen/regex/quantifier.h>
  #include <librexgen/regex/terminalregex.h>
  #include <librexgen/regex/classregex.h>
  #include <librexgen/regex/groupreference.h>
  #include <librexgen/parser/rexgenparsercontext.h>
  #include <librexgen/string/unicode.h>
  #include <librexgen/osdepend.h>
  #include <librexgen/parser/syntaxerror.h>
  #include <librexgen/parser/group_options.h>
  #include "parser.hpp"
  #include <cstdio>

	static RexgenParserContext* global_context = NULL;
	static wchar_t current_wchar_input;
  
  #define YY_EXTRA_TYPE RexgenParserContext*
//  #define YY_USER_ACTION yylloc->first_line = yylinelo
  #define YY_INPUT(buf,result,max_size) do {result=__yy_input(buf, max_size);}while(0)

  static int __yy_input(char* buf, size_t max_size) {
    if (! global_context->hasNextChar()) {
        return YY_NULL;
    }

    const wchar_t wc = global_context->getNextChar();

    int single_byte = wctob(wc);
    if (single_byte != EOF) {
        buf[0] = static_cast<char>(single_byte);
        return 1;
    }

    /* if we read a multibyte character, we simply return 0xfe in yytext
     * to flag the situation. In this case, the scanner must explicitly
     * call global_context->getCurrentChar to retrieve the widechar
     */
    buf[0] = static_cast<char>(0xfe);
    return 1;
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

DIGIT                       [0-9]
ALPHA                       [_a-zA-Z]
ANSICHAR                    \\x[0-9a-fA-F]{2,2}
UNICODECHAR                 \\u[0-9a-fA-F]{4,4}
LINEFEED                    \\n
CARRIAGERETURN              \\r
CLASS_DIGIT                 \\d
CLASS_WORD                  \\w
SPECIAL                     [ \t\r\n,;:=/%&<>-]
NORMAL                      [^ \t\r\n.,;:=/%&?<>-]
GROUPID                     \\[1-9]
STREAM                      \\0
ESCAPED                     \\[^xnurdw0-9]
BEGIN_GROUP_WITH_OPTIONS    \(\?[i]*(-[i]+)?:
BEGIN_GROUP                 \(
END_GROUP                   \)

MULTIBYTE_CHARACTER  \xFE

%s IN_QUANTIFIER
%s IN_CLASS
%%

{ANSICHAR}              { yylval.character = parseAnsiChar(yytext);                 return T_ANY_CHAR; }
{UNICODECHAR}           { yylval.character = parseUnicodeChar(yytext);              return T_ANY_CHAR; }
{MULTIBYTE_CHARACTER}   { yylval.character = global_context->getCurrentChar(); return T_ANY_CHAR; }
{ESCAPED}               { yylval.character = btowc(yytext[1]);                      return T_ANY_CHAR; }
{LINEFEED}              { yylval.character = btowc('\n');                           return T_ANY_CHAR; }
{CARRIAGERETURN}        { yylval.character = btowc('\r');                           return T_ANY_CHAR; }
{CLASS_DIGIT}	        { yylval.character = 0; return T_CLASS_DIGIT; }
{CLASS_WORD}            { yylval.character = 0; return T_CLASS_WORD;  }
"|"                     { return T_PIPE; }
"["                     { BEGIN(IN_CLASS); return T_BEGIN_CLASS; }
"]"                     { BEGIN(INITIAL); return T_END_CLASS; }

{BEGIN_GROUP_WITH_OPTIONS}	{
	bool enable_mode = true;
	yylval.group_options = new t_group_options();
	yylval.group_options->group_id = global_context->groupId++;
	for (int idx=2; idx < yyleng-1; ++idx) {
		switch(yytext[idx]) {
			case 'i':
				yylval.group_options->handle_case = 
					enable_mode 
									?	CASE_ITERATE
									: CASE_IGNORE ;
				break;
			case '-':
				enable_mode = false;
				break;
			default:
				throw SyntaxError("Invalid modifier for special group");
		}
	}
	return T_BEGIN_GROUP;
}

{BEGIN_GROUP}           {
	yylval.group_options = new t_group_options();
	yylval.group_options->group_id = global_context->groupId++;
	return T_BEGIN_GROUP; 
}
{END_GROUP}             { return T_END_GROUP; }
"?"                     { return T_OPTIONAL_QUANTIFIER; }
"{"                     { BEGIN(IN_QUANTIFIER); return T_BEGIN_QUANTIFIER; }
"}"                     { BEGIN(INITIAL); return T_END_QUANTIFIER; }
{GROUPID}               { yylval.integer = atoi(&yytext[1]); return T_GROUPID; }
{STREAM}                { yylval.integer = atoi(&yytext[1]); return T_STREAM; }
<IN_QUANTIFIER>","      { return T_COMMA; }
<IN_CLASS>"-"           { return T_HYPHEN; }
<IN_QUANTIFIER>{DIGIT}+ { yylval.integer = atoi(yytext); return T_NUMBER; }
{NORMAL}                { yylval.character = yytext[0]; return T_ANY_CHAR; }
{SPECIAL}               { yylval.character = yytext[0]; return T_ANY_CHAR; }
.                       { }

%%


  void RexgenParserContext::InitScanner() {
    //yylex_init(&scanner);
    //yyset_extra(this, scanner);
		global_context = this;
#ifdef YYDEBUG
    //yyset_debug(1, scanner);
#endif
  }
  
  void RexgenParserContext::DestroyScanner() {
    yylex_destroy();
  }
