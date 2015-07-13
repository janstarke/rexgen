/*
    rexgen - a tool to create words based on regular expressions
    Copyright (C) 2012-2015 Jan Starke <jan.starke@outofbed.org>

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <locale.h>
#include <librexgen/c/librexgen.h>
#include <librexgen/c/iterator.h>
#include <librexgen/version.h>
#include "terms.h"

#if ! defined(_WIN32)
typedef char _TCHAR;
#endif

#ifndef __cplusplus
typedef int bool;
#define false 0
#define true 1
#endif

static char regex_buffer[512];
int(*encoder)(c_simplestring_ptr, char*, size_t) = c_simplestring_to_ansi_string;
FILE* infile = NULL;
const _TCHAR* infile_name =  NULL;

#ifdef YYDEBUG
#if YYDEBUG == 1
extern int rexgen_debug;
#endif
#endif

static void rexgen_usage() {
  fprintf(stderr,
          "rexgen  Copyright (C) 2012-2015 Jan Starke <rexgen@outofbed.org>\n"
          "This program comes with ABSOLUTELY NO WARRANTY;\n"
          "for details run rexgen with '-w'.\n"
          "This is free software, and you are welcome to redistribute it\n"
          "under certain conditions; run rexgen with `-c' for details.\n\n");
  fprintf(stderr,
          "USAGE: rexgen [<options>] <regex>\n");
  fprintf(stderr,
          "OPTIONS:\n"
          "   -f <file>: read from file; use - to read from stdin\n"
          "              you can use \\0 to refer to the current line\n"
          "   -u8:       encode values in UTF-8\n"
          "   -u16[le]:  encode values in UTF-16BE (resp. UTF-16LE)\n"
          "   -u32[le]:  encode values in UTF-32BE (resp. UTF-32LE)\n"
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

  for (n=1; n<argc; ++n) {
    if (argv[n][0] != '-') {
      if (regex == NULL) {
        _TCHAR* src = argv[n];
        char* dst = regex_buffer;
        size_t buffer_size = sizeof(regex_buffer)/sizeof(regex_buffer[0]);
        while ((*dst++ = (char)*src++) != 0) {
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
    switch (argv[n][1]) {
    case '-':
      n = argc;
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
    case 'u': /* unicode encoding */
      if        (0 == _tcscmp(&argv[n][1], _T("u8"))) {
        encoder = c_simplestring_to_utf8_string;
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

/* super simple callback function.  Simply does 'same' function as the normal
 * -f file taken from the StreamIterator::readNextWord() function however, it
 * is done in a callback. Now another app can write it's own callback function
 * (such as JtR's wordlist, rules, or Markov modes). This callback allows the
 * calling program a lot more insight, which may be needed to better implement
 * things such as state save/restore logic.  With a callback we know that the
 * and 83 calls to c_iterator_next() first 867412 lines of the file have been
 * processed against 867413rd line. This make restart a lot quicker, where we
 * simply skip 867412 lines, then throw away 83 c_iterator_next() calls, and
 * then start processing.  Without knowing the line count, we would simply have
 * to call c_iterator_next() many times, to restore the location of the restart.
 */
const char* callback() {
  static char Buf[512];
  unsigned int idx = 0;
  if (feof(infile)) { return NULL; }
  if (fgets(Buf, sizeof(Buf)-1, infile) == 0) {
    return NULL;
  }
  while (idx < sizeof(Buf)-2 && Buf[idx] != '\r' && Buf[idx] != '\n') {
    ++idx;
  }
  Buf[idx] = 0;
  return Buf;
}

int _tmain(int argc, _TCHAR* argv[]) {
  c_simplestring_ptr buffer = NULL;
  char binary_string[512];
  c_regex_ptr regex = NULL;
  c_iterator_ptr iter = NULL;
  int retval = 0;
  const char* regex_str = NULL;
#ifdef DEBUG_STATE
  char* state = NULL;
#endif /* DEBUG_STATE */

#ifdef YYDEBUG
#if YYDEBUG == 1
  rexgen_debug = 1;
#endif
#endif

  rexgen_setlocale();
  regex_str = rexgen_parse_arguments(argc, argv);
  if (regex_str == NULL) {
    rexgen_usage();
    return 1;
  }

  if (infile_name != NULL) {
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

  regex = c_regex_cb(regex_str, callback);
  if (regex == NULL) {
    fprintf(stderr, "Syntax Error:\n%s\n", c_rexgen_get_last_error());
    retval = 1;
    goto cleanup_and_exit;
  }

  if (c_regex_uses_callback(regex) && infile == NULL) {
    fprintf(stderr, "You must specify a filename when you use '\\0'\n");
    retval = 1;
    goto cleanup_and_exit;
  }

  iter = c_regex_iterator(regex);
  if (iter == NULL) {
    fprintf(stderr, "Syntax Error:\n%s\n", c_rexgen_get_last_error());
    retval = 1;
    goto cleanup_and_exit;
  }

  /*  to test restore state, simply put the restore string here, AND use exactly the same regex input string */
  /* c_iterator_set_state(iter, "RXS1.1,b,0,3,1,1,2,0,9,0,0,a,1,1,0"); */
  /* */
#ifdef DEBUG_STATE
  c_iterator_get_state(iter, &state);
  printf ("initial state = %s\n", state);
  c_iterator_delete_state_buffer(state);
#endif /* DEBUG_STATE */

	buffer = c_simplestring_new();
  while (c_iterator_next(iter)) {
    c_iterator_value(iter, buffer);
    encoder(buffer, binary_string, sizeof(binary_string));
    printf("%s\n", binary_string);

#ifdef DEBUG_STATE
    /* These show how to save-restore state */
    c_iterator_get_state(iter, &state);
    printf ("state         = %s\n", state);
    c_iterator_set_state(iter, state);
    c_iterator_delete_state_buffer(state);
#endif /* DEBUG_STATE */
    c_simplestring_clear(buffer);
  }

#ifdef DEBUG_STATE
  c_iterator_get_state(iter, &state);
  printf ("final state   = %s\n", state);
  c_iterator_delete_state_buffer(state);
#endif /* DEBUG_STATE */

cleanup_and_exit:
  c_simplestring_delete(buffer);
  c_iterator_delete(iter);
  c_regex_delete(regex);

#if defined(_WIN32) && defined(_DEBUG)
  getchar();
#endif
  return retval;
}

