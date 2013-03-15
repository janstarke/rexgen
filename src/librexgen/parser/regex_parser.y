%pure-parser	
%name-prefix="rexgen_"
%locations
%defines
%error-verbose
%lex-param {void* scanner}
%parse-param {RexgenParserContext* context}
%{
  #include <iostream>
  #include <librexgen/debug.h>
  #include <librexgen/regex/regexalternatives.h>
  #include <librexgen/regex/compoundregex.h>
  #include <librexgen/regex/terminalregex.h>
  #include <librexgen/regex/classregex.h>
  #include <librexgen/regex/quantifier.h>
  #include <librexgen/regex/groupreference.h>
  #include <librexgen/parser/rexgenparsercontext.h>
  #include <librexgen/parser/osdepend.h>
  #include "parser.hpp"
  
  #include <cstdio>
  
  using namespace std;

  //extern "C"
  int rexgen_lex(YYSTYPE* lvalp, YYLTYPE *llocp, void* scanner);

  void rexgen_error(YYLTYPE* locp, void*, const char *s)
  {
        cerr << "error in col " << locp->first_column << ": " << s << endl;
  }
  
  #define scanner context->scanner
%}

%start T_RegexAlternatives

%union {
  char_type		character;
  int 			integer;
  int 			groupId;
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
%token <character> T_BEGIN_GROUP
%token <character> T_END_GROUP
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
//%type <integer> Quantifier2;

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
	  |	GroupReference	{ $$ = static_cast<Regex*>($1);	};

SimpleRegex: T_ANY_CHAR {
  if (context->ignoreCase()) {
    ClassRegex* re = new ClassRegex();
    re->addCharacter($1, context->ignoreCase());
    $$=re;
  } else {
    $$ = new TerminalRegex($1);
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
  { ClassRegex* re = new ClassRegex();
    re->addCharacter($1, context->ignoreCase());
    $$=re; };
ClassContentWithoutHyphen:
  T_ANY_CHAR ClassContentWithoutHyphen
  { ClassRegex* re = (ClassRegex*) $2; re->addCharacter((char)$1, context->ignoreCase()); $$=re; };
ClassContentWithoutHyphen:
  T_ANY_CHAR T_HYPHEN T_ANY_CHAR
  { ClassRegex* re = new ClassRegex(); re->addRange($1, $3, context->ignoreCase()); $$=re; }
|  T_ANY_CHAR T_HYPHEN T_ANY_CHAR ClassContentWithoutHyphen
  { ClassRegex* re = $4; re->addRange((char)$1, (char)$3, context->ignoreCase()); $$=re; };
  
GroupRegex:
  T_BEGIN_GROUP
  {
    $<groupId>$ = context->groupId++;
  }[id]
  T_RegexAlternatives T_END_GROUP
  { 
    RegexAlternatives* ra = $3; 
    ra->setGroupId($<groupId>id);
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
}

%%
