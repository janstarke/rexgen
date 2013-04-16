/*
    Copyright (C) 2012-2013  Jan Starke <rexgen@outofbed.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/
*/

#include <librexgen/parser/rexgenparsercontext.h>
#include <librexgen/regex/regex.h>
#include <librexgen/librexgen.h>
#include <librexgen/unicode.h>
#include <librexgen/simplestring.h>
#include <cstdio>
#include <signal.h>
#include <locale.h>
#include "terms.h"

#if ! defined(_WIN32)
typedef char _TCHAR;
#include <uniconv.h>
#include <execinfo.h>
#endif

static char regex_buffer[512];

using namespace std;
#ifdef YYDEBUG
#if YYDEBUG == 1
extern int rexgen_debug;
#endif
#endif
static void usage() {
  cerr  << "rexgen  Copyright (C) 2012-2013  Jan Starke <rexgen@outofbed.org>" << endl
        << "This program comes with ABSOLUTELY NO WARRANTY; for details run rexgen with '-w'." << endl
        << "This is free software, and you are welcome to redistribute it" << endl
        << "under certain conditions; run rexgen with `-c' for details." << endl << endl;
  cerr << "Usage:   rexgen [-i] [-t] <regex>" << endl;
  cerr << "   -t:   print syntax tree" << endl;
  cerr << "   -i:   ignore case" << endl;
  cerr << "   -u8:  encode values in UTF-8" << endl;
  cerr << "   -u16: encode values in UTF-16" << endl;
  cerr << "   -u32: encode values in UTF-32" << endl << endl;
  cerr << "   -w:   display warranty information" << endl;
  cerr << "   -c:   display redistribution conditions" << endl;
}

static struct {
  bool display_tree;
  bool ignore_case;
  int utf_variant;
} rexgen_options;

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

const char* parse_arguments(int argc, _TCHAR** argv) {
  const char* regex = nullptr;
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
      case 'c':
        display_conditions();
        exit(0);
      case 'w':
        display_warranty();
        exit(0);
      case 'i':
        rexgen_options.ignore_case = true;
        break;
      case 't':
        rexgen_options.display_tree = true;
        break;
      case 'u': /* unicode encoding */
#ifdef _WIN32
        rexgen_options.utf_variant = _tstoi(&(argv[n][2]));
#else
        rexgen_options.utf_variant = atoi(&(argv[n][2]));
#endif
        if (rexgen_options.utf_variant == 8 ||
            rexgen_options.utf_variant == 16 ||
            rexgen_options.utf_variant == 32) {
          break;
        }
        cerr << "invalid output encoding specified" << endl;
        usage();
        exit(1);
      default:
        fprintf(stderr, "invalid argument: %s\n", argv[n]);
        usage();
        exit(1);
    }
  }
  return regex;
}

int _tmain(int argc, _TCHAR* argv[]) {
  SimpleString buffer;
  SimpleString syntaxTree;
#ifdef YYDEBUG
#if YYDEBUG == 1
  rexgen_debug = 1;
#endif 
#endif
  
  setlocale();
  rexgen_options.utf_variant = 8; /* use UTF-8 by default */
  const char* regex_str = parse_arguments(argc, argv);
  if (regex_str == nullptr) {
    usage();
    return 1;
  }

  Regex* regex = parse_regex(regex_str);
  if (regex == NULL) {
    return 1;
  }
  
  if (rexgen_options.display_tree) {
    regex->appendRawValue(syntaxTree);
    syntaxTree.terminate();
    syntaxTree.print(stdout);
  }
    
  Iterator* iter = regex->iterator();

  while (iter->next()) {
    buffer.clear();
    iter->value(buffer);
    buffer.push_back('\n');
    buffer.terminate();
    buffer.print(stdout);
  }
  delete regex;
  return 0;
}
