%locations
%defines
%error-verbose
%require "3"
%language "c++"
%define api.value.type variant
%parse-param {rexgen::RexgenParserContext& context}
%lex-param   {rexgen::RexgenParserContext& context}
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

  #include <iostream>
  #include <librexgen/debug.h>
  #include <librexgen/regex/regex.h>
  #include <librexgen/regex/regexalternatives.h>
  #include <librexgen/regex/compoundregex.h>
  #include <librexgen/regex/terminalregex.h>
  #include <librexgen/regex/classregex.h>
  #include <librexgen/regex/quantifier.h>
  #include <librexgen/regex/groupreference.h>
  #include <librexgen/regex/streamregex.h>
  #include <librexgen/parser/rexgenparsercontext.h>
  #include <librexgen/osdepend.h>
  #include <librexgen/parser/syntaxerror.h>
  #include "parser.hpp"
  #include <librexgen/parser/group_options.h>
  
  #include <cstdio>
  #include <memory>
%}

%start T_RegexAlternatives
/*
%union {
  wchar_t		character;
  int 			integer;
  t_group_options* group_options;
  Regex* 		regex;
  RegexAlternatives* regex_alternatives;
  CompoundRegex* 	    compound_regex;
  Quantifier* 		    quantifier;
  ClassRegex* 		    class_regex;
  TerminalRegex* 	    terminal_regex;
  GroupReference*     group_reference;

  // stream_regex may store a StreamRegex* or GroupReference*,
  // see documentation of getStreamRegex for mor information
  //
  Regex*              stream_regex;

}
*/

%token <wchar_t> T_PIPE
%token <wchar_t> T_ANY_CHAR
%token <wchar_t> T_HYPHEN
%token <wchar_t> T_BEGIN_QUANTIFIER
%token <wchar_t> T_END_QUANTIFIER
%token <wchar_t> T_OPTIONAL_QUANTIFIER
%token <int>   T_NUMBER
%token <int>   T_GROUPID
%token <int>   T_STREAM
%token <t_group_options> T_BEGIN_GROUP
%token <wchar_t> T_END_GROUP
%token <wchar_t> T_BEGIN_CLASS
%token <wchar_t> T_END_CLASS
%token <wchar_t> T_COMMA
%token <wchar_t> T_CLASS_DIGIT
%token <wchar_t> T_CLASS_WORD

%type <std::shared_ptr<rexgen::RegexAlternatives>> T_RegexAlternatives
%type <std::shared_ptr<rexgen::Regex>> CompoundRegex
%type <std::shared_ptr<rexgen::Regex>> Regex
%type <std::shared_ptr<rexgen::Regex>> PlainRegex
%type <std::shared_ptr<rexgen::Quantifier>> Quantifier
%type <std::shared_ptr<rexgen::Regex>> SimpleRegex
%type <std::shared_ptr<rexgen::ClassRegex>> ClassRegex
%type <std::shared_ptr<rexgen::ClassRegex>> ClassContent
%type <std::shared_ptr<rexgen::ClassRegex>> SimpleClassContent
%type <std::shared_ptr<rexgen::ClassRegex>> CharacterClassDigit
%type <std::shared_ptr<rexgen::ClassRegex>> CharacterClassWord
%type <std::shared_ptr<rexgen::RegexAlternatives>> GroupRegex
%type <std::shared_ptr<rexgen::GroupReference>> GroupReference;
%type <std::shared_ptr<rexgen::Regex>> Stream;


%%

T_RegexAlternatives:
  CompoundRegex {
      $$ = std::make_shared<rexgen::RegexAlternatives>();
      std::shared_ptr<rexgen::Regex> re = std::move($1);
      $$->addRegex(re);
      $$->setGroupId(0);
      context.setResult($$);
      context.updateAllGroupReferences();
  };

T_RegexAlternatives:
  CompoundRegex T_PIPE T_RegexAlternatives
  { $$ = std::move($3);
    $$->addRegex($1);
  };

CompoundRegex:
  Regex
  { $$ = std::make_shared<rexgen::CompoundRegex>();
    static_cast<rexgen::CompoundRegex*>($$.get())->prependRegex($1);
  };

CompoundRegex:
  Regex CompoundRegex
  { $$ = std::move($2);
    static_cast<rexgen::CompoundRegex*>($$.get())->prependRegex($1);
  };

Regex:
  PlainRegex
  {
    $$ = std::move($1);
  };
Regex:
  PlainRegex Quantifier
  {
    $$ = std::move($1);
    $$->setQuantifier(*($2));
  };

PlainRegex:
        SimpleRegex 	    { $$ = std::move($1); }
    |   CharacterClassDigit { $$ = std::move($1); }
    | 	ClassRegex 	    { $$ = std::move($1); }
    |	GroupRegex	    { $$ = std::move($1); }
    |	GroupReference	    { $$ = std::move($1); }
    |   Stream              { $$ = std::move($1); };

SimpleRegex: T_ANY_CHAR {
	$$ = std::make_shared<rexgen::TerminalRegex>($1);
};

ClassRegex:
    CharacterClassWord  { $$ = std::move($1); }
  | T_BEGIN_CLASS T_HYPHEN ClassContent T_END_CLASS { $$ = std::move($3); $$->addCharacter(btowc('-')); }
  | T_BEGIN_CLASS          ClassContent T_END_CLASS { $$ = std::move($2); };
ClassContent:
    SimpleClassContent  { $$ = std::move($1); }
  | SimpleClassContent ClassContent {
    $2->merge($1);
    $$ = std::move($2);
  }

SimpleClassContent:
	  T_ANY_CHAR T_HYPHEN T_ANY_CHAR {
      $$ = std::make_shared<rexgen::ClassRegex>();
      $$->addRange($1, $3);
	}
	| T_CLASS_DIGIT {
      $$ = std::make_shared<rexgen::ClassRegex>();
      $$->addRange(rexgen::ClassRegex::DIGITS);
  }
	| CharacterClassWord  { $$ = std::move($1); }
	| T_ANY_CHAR {
    $$ = std::make_shared<rexgen::ClassRegex>();
    $$->addCharacter($1);
  }

CharacterClassDigit:
	T_CLASS_DIGIT {
    $$ = std::make_shared<rexgen::ClassRegex>();
    $$->addRange(rexgen::ClassRegex::DIGITS);
	}
CharacterClassWord:
  T_CLASS_WORD {
    $$ = std::make_shared<rexgen::ClassRegex>();
    $$->addRange(rexgen::ClassRegex::WORDCHARACTERS);
  }
  
GroupRegex:
  T_BEGIN_GROUP T_RegexAlternatives T_END_GROUP
  {
    $$ = std::move($2);
    std::weak_ptr<rexgen::Regex> ptr = std::static_pointer_cast<rexgen::Regex>($$);
    $$->setGroupOptions($1);
    context.registerGroup(ptr);
    context.updateGroupReferences(ptr);
  };

Quantifier:
  T_OPTIONAL_QUANTIFIER {
    $$ = std::make_shared<rexgen::Quantifier>(0, 1);
  }
  | T_BEGIN_QUANTIFIER T_NUMBER T_END_QUANTIFIER {
      $$ = std::make_shared<rexgen::Quantifier>($2, $2);
    }
  | T_BEGIN_QUANTIFIER T_NUMBER T_COMMA T_NUMBER T_END_QUANTIFIER {
      $$ = std::make_shared<rexgen::Quantifier>($2, $4);
  };

GroupReference: T_GROUPID {
  $$ = std::make_shared<rexgen::GroupReference>($1);
  context.registerGroupReference($$);
};

Stream: T_STREAM {
  if (context.getInFile() == NULL && context.getStreamCallback() == NULL) {
    throw SyntaxError("You cannot use a stream reference without specifying a stream source or callback function.", @1.first_column);
  }
  $$ = context.getStreamRegex();
};

%%
#include "scanner.cpp"
