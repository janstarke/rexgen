
#include <librexgen/parser/rexgenparsercontext.h>
#include <librexgen/regex/regex.h>
#include <librexgen/librexgen.h>
#include <librexgen/unicode.h>
#include <librexgen/simplestring.h>
#include <cstdio>
#include <signal.h>
#include <locale.h>

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
  cerr << "Usage:   rexgen [-i] [-t] <regex>" << endl;
  cerr << "   -t:   print syntax tree" << endl;
  cerr << "   -i:   ignore case" << endl;
#ifndef _WIN32
  cerr << "Locale: " << locale_charset() << endl;
#endif
}

static struct {
  bool display_tree;
  bool ignore_case;
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
      case 'i':
        rexgen_options.ignore_case = true;
        break;
      case 't':
        rexgen_options.display_tree = true;
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
  char_type xml[1024];
  SimpleString buffer;
#ifdef YYDEBUG
#if YYDEBUG == 1
  rexgen_debug = 1;
#endif 
#endif
  
  setlocale();
  
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
    regex->appendRawValue(xml, sizeof(xml)/sizeof(xml[0]));
#ifdef _WIN32
	cout << "result:" << endl << xml << endl;
#else
    ulc_fprintf(stdout, "result:\n" PRINTF_FORMAT "\n", xml);
#endif
  }
    
  Iterator* iter = regex->iterator();

  while (iter->next()) {
    buffer.clear();
    iter->value(buffer);
    buffer.push_back('\n');
    buffer.push_back(0);
    buffer.print(stdout);
  }
  delete regex;
  return 0;
}
