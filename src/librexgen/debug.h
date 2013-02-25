#ifndef __debug_h__
#define __debug_h__

#include <cxxabi.h>


void enter_level();
void leave_level();

int get_level();
char* spaces(char c, int s);

#ifndef REXGEN_DEBUG
#define REXGEN_DEBUG 0
#endif

#ifndef YYDEBUG
#define YYDEBUG 0
#endif

#if REXGEN_DEBUG==1
#define ENTER_METHOD do {		\
  enter_level();			\
    size_t len = 0;			\
    int s = 0;				\
    fprintf(stderr, "%2d %s%s:%d::%s() BEGIN\n",\
		 get_level(),		\
		 spaces('+',get_level()),\
		 abi::__cxa_demangle(typeid(*this).name(), 0, &len, &s), \
		 getId(), __FUNCTION__);		\
} while(0)

#define LEAVE_METHOD do {		\
    size_t len = 0;			\
    int s = 0;				\
    fprintf(stderr, "%2d %s%s:%d::%s()\n",	\
		get_level(),		\
		spaces('-',get_level()),\
		 abi::__cxa_demangle(typeid(*this).name(), 0, &len, &s), \
		 getId(), __FUNCTION__);	\
  leave_level();                        \
  return;				\
} while (0)

#define RETURN(res) do {		\
  int x = res;				\
    size_t len = 0;			\
    int s = 0;				\
    fprintf(stderr, "%2d %s%s:%d::%s() = %d\n",	\
		get_level(),		\
		spaces('-',get_level()),\
		 abi::__cxa_demangle(typeid(*this).name(), 0, &len, &s), \
		 getId(), __FUNCTION__, x);	\
  leave_level();			\
  return x;				\
} while (0)

#define TRACE0(msg) do {		\
    size_t len = 0;			\
    int s = 0;				\
    fprintf(stderr, "%s::%s(): %s\n",	\
		 abi::__cxa_demangle(typeid(*this).name(), 0, &len, &s), \
		 __FUNCTION__, msg);		\
  } while (0)
  
#define TRACE_INT(msg, d) do {		\
    size_t len = 0;			\
    int s = 0;				\
    fprintf(stderr, "%s::%s(): " #msg "\n",	\
		 abi::__cxa_demangle(typeid(*this).name(), 0, &len, &s), \
		 __FUNCTION__, d );		\
  } while (0)

#else /* ! REXGEN_DEBUG != 1 */

#define ENTER_METHOD
#define LEAVE_METHOD return
#define RETURN(r) return(r)
#define TRACE0(msg)
#define TRACE_INT(msg, d)

#endif /* REXGEN_DEBUG */

#endif