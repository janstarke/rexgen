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

#include <librexgen/api/c/librexgen.h>
#include <librexgen/version.h>
#include <stdio.h>
#include <signal.h>
#include <locale.h>
#include "terms.h"

#if ! defined(_WIN32)
typedef char _TCHAR;
#include <execinfo.h>
#endif

#ifndef __cplusplus
typedef int bool;
#define false 0
#define true 1
#endif

static char regex_buffer[512];
int ignore_case = 0;
int randomize = 0;
charset encoding = CHARSET_UTF8;
FILE* infile = NULL;
const _TCHAR* infile_name =  NULL;
static bool prependBOM = false;

enum {
  display_syntax_tree,
  generate_values
} rexgen_operation;

#ifdef YYDEBUG
#if YYDEBUG == 1
extern int rexgen_debug;
#endif
#endif

static void rexgen_usage() {
  fprintf(stderr,
		"rexgen  Copyright (C) 2012-2013  Jan Starke <rexgen@outofbed.org>\n"
    "This program comes with ABSOLUTELY NO WARRANTY;\n" 
		"for details run rexgen with '-w'.\n"
    "This is free software, and you are welcome to redistribute it\n"
    "under certain conditions; run rexgen with `-c' for details.\n\n");
  fprintf(stderr,
		"USAGE: rexgen [<options>] <regex>\n");
  fprintf(stderr,
		"OPTIONS:\n"
   	"   -t:        print syntax tree\n"
   	"   -i:        ignore case\n"
   	"   -r:        randomize order of values (will be slower)\n"
   	"   -f <file>: read from file; use - to read from stdin\n"
   	"              you can use \\0 to refer to the current line\n"
   	"   -u8:       encode values in UTF-8\n"
   	"   -u16[le]:  encode values in UTF-16BE (resp. UTF-16LE)\n"
   	"   -u32[le]:  encode values in UTF-32BE (resp. UTF-32LE)\n"
   	"   -b:        prepend output with byte order mark\n"
   	"   -w:        display warranty information\n"
   	"   -c:        display redistribution conditions\n"
	 	"   -v:        display version information\n");
}


static void rexgen_setlocale() {
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

static void rexgen_display_warranty() {
	fprintf(stderr, 
  	"THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY\n"
    "APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT\n"
    "HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY\n"
    "OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,\n"
    "THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR\n"
    "PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM\n"
    "IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF\n"
    "ALL NECESSARY SERVICING, REPAIR OR CORRECTION.\n");
}

static void rexgen_display_conditions() {
  fprintf(stderr, "%s\n", terms_and_conditions);
}

static void rexgen_display_version() {
	fprintf(stderr, "rexgen-%s\n", rexgen_version());
}

const char* rexgen_parse_arguments(int argc, _TCHAR** argv) {
  const char* regex = NULL;
	int n;
  
  rexgen_operation = generate_values;
  
  for (n=1; n<argc; ++n) {
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
        rexgen_usage();
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
        rexgen_display_conditions();
        exit(0);
      case 'w':
        rexgen_display_warranty();
        exit(0);
			case 'v':
				rexgen_display_version();
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
          fprintf(stderr, "invalid output encoding specified\n");
          rexgen_usage();
          exit(1);
        }
        break;
      default:
        fprintf(stderr, "invalid argument: %s\n", argv[n]);
        rexgen_usage();
        exit(1);
    }
  }
  return regex;
}

int _tmain(int argc, _TCHAR* argv[]) {
  c_simplestring_ptr buffer = c_simplestring_new();
  /*
	SimpleString syntaxTree;
  Regex* regex = NULL;
	*/
  c_iterator_ptr iter = NULL;
  int retval = 0;
  
#ifdef YYDEBUG
#if YYDEBUG == 1
  rexgen_debug = 1;
#endif 
#endif
  
  rexgen_setlocale();
  encoding = CHARSET_UTF8; /* use UTF-8 by default */
  const char* regex_str = rexgen_parse_arguments(argc, argv);
  if (regex_str == NULL) {
    rexgen_usage();
    return 1;
  }
  
  if (infile != NULL) {
    if (0 == _tcscmp(infile_name, _T("-"))) {
      infile = stdin;
    } else {
      infile = _tfopen(infile_name, _T("r"));
      if (infile == NULL) {
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
    
    if (regex == NULL) {
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
	iter = c_regex_iterator(
						regex_str, ignore_case, encoding, randomize, infile);
  if (iter == NULL) {
		fprintf(stderr, "Syntax Error:\n%s\n", c_rexgen_get_last_error());
		retval = 1;
    goto cleanup_and_exit;
  }

  while (c_iterator_next(iter)) {
		c_iterator_value(iter, buffer);
    c_simplestring_newline(buffer);
		c_simplestring_print(buffer, stdout, 0);
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
