%locations
%defines
%error-verbose
%parse-param {RexgenParserContext* context}
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

  #include <iostream>
  #include <librexgen/debug.h>
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
  uint32_t		character;
  int 			integer;

	t_group_options* group_options;
  Regex* 		regex;
  RegexAlternatives* 	regex_alternatives;
  CompoundRegex* 	compound_regex;
  Quantifier* 		quantifier;
  ClassRegex* 		class_regex;
  TerminalRegex* 	terminal_regex;
  GroupReference* 	group_reference;

}

%token <character> T_PIPE
%token <character> T_ANY_CHAR
%token <character> T_HYPHEN
%token <character> T_BEGIN_QUANTIFIER
%token <character> T_END_QUANTIFIER
%token <integer>   T_NUMBER
%token <integer>   T_GROUPID
%token <integer>   T_STREAM
%token <group_options> T_BEGIN_GROUP
%token <character> T_END_GROUP
%token <integer>   T_GROUP_OPTIONS
%token <character> T_BEGIN_CLASS
%token <character> T_END_CLASS
%token <character> T_COMMA

%type <regex_alternatives> T_RegexAlternatives
%type <compound_regex> CompoundRegex
%type <regex> Regex
%type <regex> PlainRegex
%type <quantifier> Quantifier
%type <regex> SimpleRegex
%type <class_regex> ClassRegex
%type <class_regex> ClassContent
%type <class_regex> ClassContentWithoutHyphen
%type <regex_alternatives> GroupRegex
%type <group_reference> GroupReference;
%type <regex> Stream;


%%

T_RegexAlternatives:
  CompoundRegex {
      RegexAlternatives* alt = new RegexAlternatives();
      alt->addRegex($1);
      context->result = alt;
      alt->setGroupId(0);
      context->updateAllGroupReferences();
      $$ = alt;
  };
  
T_RegexAlternatives:
  CompoundRegex T_PIPE T_RegexAlternatives
  { RegexAlternatives* alt = $3;
    alt->addRegex($1);
    $$ = alt;
  };

CompoundRegex:
  Regex
  { CompoundRegex* cr = new CompoundRegex();
    cr->prependRegex($1);
    $$ = cr;
  };
  
CompoundRegex:
  Regex CompoundRegex
  { CompoundRegex* cr = (CompoundRegex*)$2;
    cr->prependRegex((Regex*)$1);
    $$ = cr;
  };
  
Regex:
  PlainRegex
  {
    $$ = $1;
  };
Regex:
  PlainRegex Quantifier
  {
    Regex* re = (Regex*)$1;
    Quantifier* q = (Quantifier*)$2;
    re->setQuantifier(*(q));
    $$ = re;
  };

PlainRegex:	SimpleRegex 	{ $$ = static_cast<Regex*>($1); }
	  | 	ClassRegex 	{ $$ = static_cast<Regex*>($1); }
	  |	GroupRegex	{ $$ = static_cast<Regex*>($1); }
	  |	GroupReference	{ $$ = static_cast<Regex*>($1);	}
          |     Stream          { $$ = static_cast<Regex*>($1); };

SimpleRegex: T_ANY_CHAR {
  if (context->ignoreCase()) {
    ClassRegex* re = new ClassRegex(context->encoding());
    re->addCharacter($1, context->ignoreCase());
    $$=re;
  } else {
    $$ = new TerminalRegex($1, context->encoding());
  }
};

ClassRegex:  T_BEGIN_CLASS ClassContent T_END_CLASS { $$ = $2; };
ClassContent: T_HYPHEN ClassContentWithoutHyphen {
  ClassRegex* re = $2;
  re->addCharacter('-', false);
  $$ = re; };
ClassContent: ClassContentWithoutHyphen { $$ = $1; };
ClassContentWithoutHyphen:
  T_ANY_CHAR
  { ClassRegex* re = new ClassRegex(context->encoding());
    re->addCharacter($1, context->ignoreCase());
    $$=re; };
ClassContentWithoutHyphen:
  T_ANY_CHAR ClassContentWithoutHyphen
  { ClassRegex* re = (ClassRegex*) $2; re->addCharacter($1, context->ignoreCase()); $$=re; };
ClassContentWithoutHyphen:
  T_ANY_CHAR T_HYPHEN T_ANY_CHAR
  { ClassRegex* re = new ClassRegex(context->encoding()); 
    if (re->addRange($1, $3, context->ignoreCase()) < 1) {
      throw SyntaxError("empty range specified in class regex", @1.first_column);
    }
    $$=re; }
|  T_ANY_CHAR T_HYPHEN T_ANY_CHAR ClassContentWithoutHyphen
  { ClassRegex* re = $4; re->addRange($1, $3, context->ignoreCase()); $$=re; };
  
GroupRegex:
  T_BEGIN_GROUP
  {
    $<group_options>$->group_id = context->groupId++;
  }
  T_RegexAlternatives T_END_GROUP
  { 
    RegexAlternatives* ra = $3; 
		ra->setGroupOptions($<group_options>2);
		delete $<group_options>2;
    context->registerGroup(ra);
    context->updateGroupReferences(ra);
    $$ = ra;
  };

Quantifier:	
  T_BEGIN_QUANTIFIER T_NUMBER T_COMMA T_NUMBER T_END_QUANTIFIER
{
  Quantifier* q = new Quantifier($2, $4);
  $$ = q;
};

GroupReference: T_GROUPID {
  GroupReference* gr = new GroupReference($1);
  context->registerGroupReference(gr);
  $$ = gr;
};

Stream: T_STREAM {
  if (context->getInFile() == NULL && context->getStreamCallback() == NULL) {
    throw SyntaxError("You cannot use a stream reference without specifying a stream source or callback function.", @1.first_column);
  }
   $$ = context->getStreamRegex();
};

%%
#include "scanner.cpp"
