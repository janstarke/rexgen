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

#include <librexgen/parser/rexgenparsercontext.h>
#include <librexgen/regex/regex.h>
#include <librexgen/librexgen.h>
#include <librexgen/api/c/librexgen_c.h>
#include <librexgen/unicode.h>
#include <librexgen/simplestring.h>
#include <librexgen/rexgen_options.h>
#include <librexgen/parser/syntaxerror.h>
#include <librexgen/version.h>
#include <cstdio>
#include <cstdio>
#include <signal.h>
#include <locale.h>
#include "terms.h"

#if ! defined(_WIN32)
typedef char _TCHAR;
#include <execinfo.h>
#endif

static char regex_buffer[512];
int ignore_case = 0;
int randomize = 0;
charset encoding = CHARSET_UTF8;
FILE* infile = nullptr;
const _TCHAR* infile_name =  nullptr;
static bool prependBOM = false;

enum {
  display_syntax_tree,
  generate_values
} rexgen_operation;

using namespace std;
#ifdef YYDEBUG
#if YYDEBUG == 1
extern int rexgen_debug;
#endif
#endif

static void usage() {
  cerr  << "rexgen  Copyright (C) 2012-2013  Jan Starke <rexgen@outofbed.org>" << endl
        << "This program comes with ABSOLUTELY NO WARRANTY;" << endl 
				<< "for details run rexgen with '-w'." << endl
        << "This is free software, and you are welcome to redistribute it" << endl
        << "under certain conditions; run rexgen with `-c' for details." << endl << endl;
  cerr << "USAGE: rexgen [<options>] <regex>" << endl;
  cerr << endl << "OPTIONS:" << endl;
  cerr << "   -t:        print syntax tree" << endl;
  cerr << "   -i:        ignore case" << endl;
  cerr << "   -r:        randomize order of values (will be slower)" << endl;
  cerr << "   -f <file>: read from file; use - to read from stdin" << endl;
  cerr << "              you can use \\0 to refer to the current line" << endl;
  cerr << "   -u8:       encode values in UTF-8" << endl;
  cerr << "   -u16[le]:  encode values in UTF-16BE (resp. UTF-16LE)" << endl;
  cerr << "   -u32[le]:  encode values in UTF-32BE (resp. UTF-32LE)" << endl;
  cerr << "   -b:        prepend output with byte order mark" << endl;
  cerr << "   -w:        display warranty information" << endl;
  cerr << "   -c:        display redistribution conditions" << endl;
	cerr << "   -v:        display version information" << endl;
}


static void setlocale() {
  const char* defaultLocale = "en_US.UTF8";
  const char* sysLocale = NULL;
  
  if ((sysLocale = getenv("LC_CTYPE")) != NULL) {
    setlocale(LC_CTYPE, sysLocale);
  }
  if ((sysLocale = getenv("LC_MESSAGES")) != NULL) {
    setlocale(LC_CTYPE, sysLocale);
  }
  if ((sysLocale = getenv("LC_ALL")) != NULL) {
    setlocale(LC_CTYPE, sysLocale);
  }
  if (sysLocale == NULL) {
    setlocale(LC_ALL, defaultLocale);
  }
}

static void display_warranty() {
  cout  << "THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY" << endl
        << "APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT" << endl
        << "HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY" << endl
        << "OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO," << endl
        << "THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR" << endl
        << "PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM" << endl
        << "IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF" << endl
        << "ALL NECESSARY SERVICING, REPAIR OR CORRECTION." << endl;
}

static void display_conditions() {
  cout << terms_and_conditions << endl;
}

static void display_version() {
	cout << "rexgen-" << rexgen::getVersion() << endl;
}

const char* parse_arguments(int argc, _TCHAR** argv) {
  const char* regex = nullptr;
  
  rexgen_operation = generate_values;
  
  for (int n=1; n<argc; ++n) {
    if (argv[n][0] != '-') {
      if (regex == NULL) {
        _TCHAR* src = argv[n];
        char* dst = regex_buffer;
        size_t buffer_size = sizeof(regex_buffer)/sizeof(regex_buffer[0]);
        while((*dst++ = (char)*src++) != 0) {
          if (--buffer_size <= 0) {
            *dst = 0;
            break;
          }
        }
        regex = regex_buffer;
      } else {
        fprintf(stderr, "more than one regex given\n");
        usage();
        exit(1);
      }
      continue;
    }
    switch(argv[n][1]) {
      case '-':
        n = argc;
        break;
      case 'b':
        prependBOM = true;
        break;
      case 'c':
        display_conditions();
        exit(0);
      case 'w':
        display_warranty();
        exit(0);
			case 'v':
				display_version();
				exit(0);
      case 'f':
        ++n;
        infile_name = argv[n];
        break;
      case 'i':
        ignore_case = 1;
        break;
      case 't':
        rexgen_operation = display_syntax_tree;
        break;
      case 'r':
        randomize = 1;
        break;
      case 'u': /* unicode encoding */
        if        (0 == _tcscmp(&argv[n][1], _T("u8"))) {
          encoding = CHARSET_UTF8;
        } else if (0 == _tcscmp(&argv[n][1], _T("u16"))) {
          encoding = CHARSET_UTF16BE;
        } else if (0 == _tcscmp(&argv[n][1], _T("u32"))) {
          encoding = CHARSET_UTF32BE;
        } else if (0 == _tcscmp(&argv[n][1], _T("u16le"))) {
          encoding = CHARSET_UTF16LE;
        } else if (0 == _tcscmp(&argv[n][1], _T("u32le"))) {
          encoding = CHARSET_UTF32LE;
        } else {
          cerr << "invalid output encoding specified" << endl;
          usage();
          exit(1);
        }
        break;
      default:
        fprintf(stderr, "invalid argument: %s\n", argv[n]);
        usage();
        exit(1);
    }
  }
  return regex;
}

int _tmain(int argc, _TCHAR* argv[]) {
  c_simplestring_ptr buffer = c_simplestring_new();
  SimpleString syntaxTree;
  //Regex* regex = nullptr;
  c_iterator_ptr iter = nullptr;
  int retval = 0;
  
#ifdef YYDEBUG
#if YYDEBUG == 1
  rexgen_debug = 1;
#endif 
#endif
  
  setlocale();
  encoding = CHARSET_UTF8; /* use UTF-8 by default */
  const char* regex_str = parse_arguments(argc, argv);
  if (regex_str == nullptr) {
    usage();
    return 1;
  }
  
  if (infile != nullptr) {
    if (0 == _tcscmp(infile_name, _T("-"))) {
      infile = stdin;
    } else {
      infile = _tfopen(infile_name, _T("r"));
      if (infile == nullptr) {
        perror("unable to open input file");
        return 1;
      }
    }
  }

  
 /* 
  if (rexgen_operation == display_syntax_tree) {
    try {
      regex = parse_regex(regex_str, rexgen_options);
    } catch (SyntaxError& error) {
      cout << "Syntax error:" << endl << error.getMessage() << endl;
      retval = 1;
      goto cleanup_and_exit;
    }
    
    if (regex == nullptr) {
      return 1;
    }
    
    regex->appendRawValue(syntaxTree);
    syntaxTree.print(stdout, true);
    delete regex;
    return 0;
  }
	*/
  
  if (prependBOM) {
		c_simplestring_push_back(buffer, create_BOM(encoding));
  }
  try {
    iter = c_regex_iterator(
							regex_str, ignore_case, encoding, randomize, infile);
  } catch (SyntaxError& error) {
    cout << "Syntax error:" << endl << error.getMessage() << endl;
    retval = 1;
    goto cleanup_and_exit;
  }
  if (iter == nullptr) {
    goto cleanup_and_exit;
  }

  while (c_iterator_next(iter)) {
		c_iterator_value(iter, buffer);
    c_simplestring_newline(buffer);
		c_simplestring_print(buffer, stdout);
  }
	c_simplestring_print(buffer, stdout, 1);
  
cleanup_and_exit:
	c_simplestring_delete(buffer);
  c_iterator_delete(iter);
#if defined(_WIN32) && defined(_DEBUG)
  getchar();
#endif
  return retval;
}
