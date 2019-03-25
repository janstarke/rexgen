%skeleton "lalr1.cc"
%require "3.2"
%language "c++"
%defines
%define parse.error verbose
%define parse.assert
%define parse.trace
%debug
%define api.value.type variant
%define api.token.constructor
%define api.namespace {rexgen}
%define api.parser.class {RexgenParser}

%code requires {
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
  #include <librexgen/debug.h>
  #include <librexgen/regex/regex.h>
  #include <librexgen/regex/regexalternatives.h>
  #include <librexgen/regex/compoundregex.h>
  #include <librexgen/regex/terminalregex.h>
  #include <librexgen/regex/classregex.h>
  #include <librexgen/regex/quantifier.h>
  #include <librexgen/regex/groupreference.h>
  #include <librexgen/regex/streamregex.h>
  #include <librexgen/osdepend.h>
  #include <librexgen/parser/syntaxerror.h>
  #include <librexgen/parser/group_options.h>
  
  #include <cstdio>
  #include <memory>
  #include <iostream>
  namespace rexgen {
    class RexgenParsingDriver;
    class RexgenFlexLexer;
  }
}

%parse-param {std::shared_ptr<rexgen::RexgenFlexLexer> scanner}
%param       {rexgen::RexgenParsingDriver& driver}

%code {
  #include <librexgen/parser/rexgenparsingdriver.h>
  #include <librexgen/parser/RexgenFlexLexer.h>
  #include <librexgen/parser/syntaxerror.h>
  #undef yylex
  #define yylex scanner->rexgen_lex

  namespace rexgen{
    void RexgenParser::error(const std::string& message) {
      throw SyntaxError(message);
    }
  }
}

%start T_Root

%token           T_PIPE
%token <wchar_t> T_ANY_CHAR
%token           T_HYPHEN
%token           T_BEGIN_QUANTIFIER
%token           T_END_QUANTIFIER
%token           T_OPTIONAL_QUANTIFIER
%token <int>     T_NUMBER
%token <int>     T_GROUPID
%token <int>     T_STREAM
%token           T_END_GROUP
%token           T_BEGIN_CLASS
%token           T_END_CLASS
%token           T_COMMA
%token           T_CLASS_DIGIT
%token           T_CLASS_WORD
%token           T_CLASS_SPACE
%token <std::shared_ptr<rexgen::t_group_options> > T_BEGIN_GROUP

%type <std::shared_ptr<rexgen::RegexAlternatives>> T_Root
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
%type <std::shared_ptr<rexgen::ClassRegex>> CharacterClassSpace
%type <std::shared_ptr<rexgen::RegexAlternatives>> GroupRegex
%type <std::shared_ptr<rexgen::GroupReference>> GroupReference;
%type <std::shared_ptr<rexgen::Regex>> Stream;
%%

T_Root: T_RegexAlternatives {
  $$ = std::move($1);
  $$->setGroupId(0);
  driver.setResult($$);
  driver.updateAllGroupReferences();
}

T_RegexAlternatives:
  CompoundRegex {
      $$ = std::make_shared<rexgen::RegexAlternatives>();
      std::shared_ptr<rexgen::Regex> re = std::move($1);
      $$->addRegex(re);
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
    | 	ClassRegex 	    { $$ = std::move($1); }
    |	GroupRegex	    { $$ = std::move($1); }
    |	GroupReference	    { $$ = std::move($1); }
    |   Stream              { $$ = std::move($1); };

SimpleRegex: T_ANY_CHAR {
	$$ = std::make_shared<rexgen::TerminalRegex>($1);
};

ClassRegex:
    CharacterClassDigit { $$ = std::move($1); }
  | CharacterClassWord  { $$ = std::move($1); }
  | CharacterClassSpace { $$ = std::move($1); }
  | T_BEGIN_CLASS T_HYPHEN ClassContent T_END_CLASS { $$ = std::move($3); $$->addCharacter(btowc('-')); }
  | T_BEGIN_CLASS          ClassContent T_END_CLASS { $$ = std::move($2); };
  | T_BEGIN_CLASS                       T_END_CLASS { $$ = std::make_shared<rexgen::ClassRegex>(); }
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
   | CharacterClassDigit  { $$ = std::move($1); }
   | CharacterClassWord   { $$ = std::move($1); }
   | CharacterClassSpace  { $$ = std::move($1); }
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

CharacterClassSpace:
    T_CLASS_SPACE {
      $$ = std::make_shared<rexgen::ClassRegex>();
      $$->addRange(rexgen::ClassRegex::SPACES);
    }
  
GroupRegex:
  T_BEGIN_GROUP T_RegexAlternatives T_END_GROUP
  {
    $$ = std::move($2);
    std::weak_ptr<rexgen::Regex> ptr = std::static_pointer_cast<rexgen::Regex>($$);
    auto go = $1;
    $$->setGroupOptions(*(go));
    driver.registerGroup(ptr);
    driver.updateGroupReferences(ptr);
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
  driver.registerGroupReference($$);
};

Stream: T_STREAM {
  if (driver.getInFile() == NULL && driver.getStreamCallback() == NULL) {
    throw SyntaxError("You cannot use a stream reference without specifying a stream source or callback function.");
  }
  $$ = driver.getStreamRegex();
};

%%

