%{
/*
    rexgen - a tool to create words based on regular expressions
    Copyright (C) 2012-2019  Jan Starke <jan.starke@outofbed.org>

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
%}

%{
#include <librexgen/parser/RexgenFlexLexer.h>
#undef YY_DECL
#define YY_DECL \
    rexgen::RexgenParser::symbol_type rexgen::RexgenFlexLexer::rexgen_lex (RexgenParsingDriver& driver)
//YY_DECL;
%}

%option c++
%option noyywrap
%option nounput
%option debug
%option yyclass="rexgen::RexgenFlexLexer"

%{
  #include <librexgen/regex/regex.h>
  #include <librexgen/regex/regexalternatives.h>
  #include <librexgen/regex/compoundregex.h>
  #include <librexgen/regex/quantifier.h>
  #include <librexgen/regex/terminalregex.h>
  #include <librexgen/regex/classregex.h>
  #include <librexgen/regex/groupreference.h>
  #include <librexgen/string/unicode.h>
  #include <librexgen/osdepend.h>
  #include <librexgen/parser/syntaxerror.h>
  #include <librexgen/parser/group_options.h>
  #include <librexgen/parser/RexgenFlexLexer.h>
%}

DIGIT                       [0-9]
ALPHA                       [_a-zA-Z]
ANSICHAR                    \\x[0-9a-fA-F]{2,2}
UNICODECHAR                 \\u[0-9a-fA-F]{4,4}
LINEFEED                    \\n
CARRIAGERETURN              \\r
CLASS_DIGIT                 \\d
CLASS_WORD                  \\w
CLASS_SPACE                 \\s
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

{ANSICHAR}                 {                          return RexgenParser::make_T_ANY_CHAR(parseAnsiChar(yytext)); }
{UNICODECHAR}              {                          return RexgenParser::make_T_ANY_CHAR(parseUnicodeChar(yytext)); }
{MULTIBYTE_CHARACTER}      {                          return RexgenParser::make_T_ANY_CHAR(*wcontent_ptr++); }
{CLASS_DIGIT}	             {                          return RexgenParser::make_T_CLASS_DIGIT(); }
{CLASS_WORD}               {                          return RexgenParser::make_T_CLASS_WORD(); }
{CLASS_SPACE}              {                          return RexgenParser::make_T_CLASS_SPACE(); }
{LINEFEED}                 {                          return RexgenParser::make_T_ANY_CHAR(btowc('\n')); }
{CARRIAGERETURN}           {                          return RexgenParser::make_T_ANY_CHAR(btowc('\r')); }
{ESCAPED}                  {                          return RexgenParser::make_T_ANY_CHAR(btowc(yytext[1]));}
"|"                        {                          return RexgenParser::make_T_PIPE(); }
"["                        { BEGIN(IN_CLASS);         return RexgenParser::make_T_BEGIN_CLASS(); }
"]"                        { BEGIN(INITIAL);          return RexgenParser::make_T_END_CLASS(); }
{BEGIN_GROUP_WITH_OPTIONS} {                          return beginGroupWithOptions(driver); }
{BEGIN_GROUP}              {                          return beginGroup(driver); }
{END_GROUP}                {                          return RexgenParser::make_T_END_GROUP(); }
<IN_CLASS>"?"              {                          return RexgenParser::make_T_ANY_CHAR(btowc(yytext[0])); }
"?"                        {                          return RexgenParser::make_T_OPTIONAL_QUANTIFIER(); }
"{"                        { BEGIN(IN_QUANTIFIER);    return RexgenParser::make_T_BEGIN_QUANTIFIER(); }
"}"                        { BEGIN(INITIAL);          return RexgenParser::make_T_END_QUANTIFIER(); }
{GROUPID}                  {                          return RexgenParser::make_T_GROUPID(atoi(&yytext[1])); }
{STREAM}                   {                          return RexgenParser::make_T_STREAM(atoi(&yytext[1]));  }
<IN_QUANTIFIER>","         {                          return RexgenParser::make_T_COMMA(); }
<IN_CLASS>"-"              {                          return RexgenParser::make_T_HYPHEN(); }
<IN_QUANTIFIER>{DIGIT}+    {                          return RexgenParser::make_T_NUMBER(atoi(yytext)); }
.                          {                          return RexgenParser::make_T_ANY_CHAR(btowc(yytext[0])); }

%%