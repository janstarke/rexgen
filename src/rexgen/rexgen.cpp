
#include <librexgen/parser/rexgenparsercontext.h>
#include <librexgen/regex/regex.h>
#include <librexgen/librexgen.h>
#include <librexgen/unicode.h>
#include <cstdio>
#include <execinfo.h>
#include <signal.h>
#include <uniconv.h>
#include <locale.h>

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
  cerr << "Locale: " << locale_charset() << endl;
}

static struct {
  bool display_tree;
  bool ignore_case;
} rexgen_options;


static void handler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, 2);
  exit(1);
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

const char* parse_arguments(int argc, char** argv) {
  const char* regex = NULL;
  for (int n=1; n<argc; ++n) {
    if (argv[n][0] != '-') {
      if (regex == NULL) {
        regex = argv[n];
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

int main(int argc, char** argv) {
  char_type xml[1024];
  char_type buffer[512];
  const char* format;
  int len;
#ifdef YYDEBUG
#if YYDEBUG == 1
  rexgen_debug = 1;
#endif 
#endif
  
  signal(SIGSEGV, handler);
  signal(SIGABRT, handler);  
  setlocale();
  
  Regex* regex = parse_regex(parse_arguments(argc, argv));
  if (regex == NULL) {
    return 1;
  }
  
  if (rexgen_options.display_tree) {
    regex->appendRawValue(xml, sizeof(xml)/sizeof(xml[0]));
    format = "result:\n" PRINTF_FORMAT "\n";
    ulc_fprintf(stdout, format, xml);
  }
    
  Iterator* iter = regex->iterator();

  format = PRINTF_FORMAT "\n";
  while (iter->hasNext()) {
    iter->next();
    len = iter->value(buffer, sizeof(buffer)/sizeof(buffer[0])-1);
    buffer[len] = '\0';

    ulc_fprintf(stdout, format, buffer);
  }
  delete regex;
  return 0;
}
