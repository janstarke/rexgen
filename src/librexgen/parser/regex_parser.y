%locations
%defines
%error-verbose
%parse-param {RexgenParserContext* context}
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
  
  using namespace std;

  //extern "C"
  int yylex(/*YYSTYPE* lvalp, YYLTYPE *llocp*/);
  void yyerror(/*YYLTYPE* locp, */RexgenParserContext * /* ctx */, const char *s)
  {
        //cerr << "error in col " << locp->first_column << ": " << s << endl;
        cerr << "error: " << s << endl;
  }
  
  //#define scanner context->scanner
%}

%start T_RegexAlternatives

%union {
  wchar_t		character;
  int 			integer;

	t_group_options* group_options;
  Regex* 		regex;
  RegexAlternatives* 	regex_alternatives;
  CompoundRegex* 	    compound_regex;
  Quantifier* 		    quantifier;
  ClassRegex* 		    class_regex;
  TerminalRegex* 	    terminal_regex;
  GroupReference*     group_reference;

  /* stream_regex may store a StreamRegex* or GroupReference*,
   * see documentation of getStreamRegex for mor information
   */
  Regex*              stream_regex;

}

%token <character> T_PIPE
%token <character> T_ANY_CHAR
%token <character> T_HYPHEN
%token <character> T_BEGIN_QUANTIFIER
%token <character> T_END_QUANTIFIER
%token <character> T_OPTIONAL_QUANTIFIER
%token <integer>   T_NUMBER
%token <integer>   T_GROUPID
%token <integer>   T_STREAM
%token <group_options> T_BEGIN_GROUP
%token <character> T_END_GROUP
%token <character> T_BEGIN_CLASS
%token <character> T_END_CLASS
%token <character> T_COMMA
%token <character> T_CLASS_DIGIT
%token <character> T_CLASS_WORD

%type <regex_alternatives> T_RegexAlternatives
%type <compound_regex> CompoundRegex
%type <regex> Regex
%type <regex> PlainRegex
%type <quantifier> Quantifier
%type <regex> SimpleRegex
%type <class_regex> ClassRegex
%type <class_regex> ClassContent
%type <class_regex> SimpleClassContent
%type <class_regex> CharacterClassDigit
%type <class_regex> CharacterClassWord
%type <regex_alternatives> GroupRegex
%type <group_reference> GroupReference;
%type <stream_regex> Stream;


%%

T_RegexAlternatives:
  CompoundRegex {
      $$ = new RegexAlternatives();
      $$->addRegex($1);
      context->result = $$;
      $$->setGroupId(0);
      context->updateAllGroupReferences();
  };
  
T_RegexAlternatives:
  CompoundRegex T_PIPE T_RegexAlternatives
  { $$ = $3;
    $$->addRegex($1);
  };

CompoundRegex:
  Regex
  { $$ = new CompoundRegex();
    $$->prependRegex($1);
  };
  
CompoundRegex:
  Regex CompoundRegex
  { $$ = $2;
    $$->prependRegex($1);
  };
  
Regex:
  PlainRegex
  {
    $$ = $1;
  };
Regex:
  PlainRegex Quantifier
  {
    $$ = (Regex*)$1;
    Quantifier* q = (Quantifier*)$2;
    $$->setQuantifier(*(q));
    delete q;
  };

PlainRegex:
        SimpleRegex 	{ $$ = static_cast<Regex*>($1); }
    |   CharacterClassDigit { $$ = $1; }
	  | 	ClassRegex 	{ $$ = static_cast<Regex*>($1); }
	  |	GroupRegex	{ $$ = static_cast<Regex*>($1); }
	  |	GroupReference	{ $$ = static_cast<Regex*>($1);	}
          |     Stream          { $$ = static_cast<Regex*>($1); };

SimpleRegex: T_ANY_CHAR {
	$$ = new TerminalRegex($1);
};

ClassRegex:
    CharacterClassWord  { $$ = $1; }
  | T_BEGIN_CLASS T_HYPHEN ClassContent T_END_CLASS { $$ = $3; $$->addCharacter(btowc('-')); }
  | T_BEGIN_CLASS          ClassContent T_END_CLASS { $$ = $2; };
ClassContent:
    SimpleClassContent  { $$ = $1; }
  | SimpleClassContent ClassContent {
    $2->merge($1);
    delete $1;
    $$ = $2;
  }

SimpleClassContent:
	  T_ANY_CHAR T_HYPHEN T_ANY_CHAR {
      $$ = new ClassRegex(); 
      $$->addRange($1, $3);
	}
	| T_CLASS_DIGIT {
      $$ = new ClassRegex();
      $$->addRange(ClassRegex::DIGITS);
  }
	| CharacterClassWord  { $$ = $1; }
	| T_ANY_CHAR {
    $$ = new ClassRegex();
    $$->addCharacter($1);
  }

CharacterClassDigit:
	T_CLASS_DIGIT {
    $$ = new ClassRegex();
    $$->addRange(ClassRegex::DIGITS);
	}
CharacterClassWord:
  T_CLASS_WORD {
    $$ = new ClassRegex();
    $$->addRange(ClassRegex::WORDCHARACTERS);
  }
  
GroupRegex:
  T_BEGIN_GROUP T_RegexAlternatives T_END_GROUP
  { 
    $$ = $2; 
		$$->setGroupOptions($1);
		delete $1;
    context->registerGroup($$);
    context->updateGroupReferences($$);
  };

Quantifier:
  T_OPTIONAL_QUANTIFIER {
    $$ = new Quantifier(0, 1);
  }
  | T_BEGIN_QUANTIFIER T_NUMBER T_END_QUANTIFIER {
      $$ = new Quantifier($2, $2);
    }
  | T_BEGIN_QUANTIFIER T_NUMBER T_COMMA T_NUMBER T_END_QUANTIFIER {
      $$ = new Quantifier($2, $4);
  };

GroupReference: T_GROUPID {
  $$ = new GroupReference($1);
  context->registerGroupReference($$);
};

Stream: T_STREAM {
  if (context->getInFile() == NULL && context->getStreamCallback() == NULL) {
    throw SyntaxError("You cannot use a stream reference without specifying a stream source or callback function.", @1.first_column);
  }
  $$ = context->getStreamRegex();
};

%%
#include "scanner.cpp"
