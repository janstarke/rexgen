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
  if (LOGGER.isDebugEnabled()) {	\
    size_t len = 0;			\
    int s = 0;				\
    LOGGER.debug("%2d %s%s:%d::%s() BEGIN",\
		 get_level(),		\
		 spaces('+',get_level()),\
		 abi::__cxa_demangle(typeid(*this).name(), 0, &len, &s), \
		 getId(), __FUNCTION__);		\
  }					\
} while(0)

#define LEAVE_METHOD do {		\
  if (LOGGER.isDebugEnabled()) {	\
    size_t len = 0;			\
    int s = 0;				\
    LOGGER.debug("%2d %s%s:%d::%s()",	\
		get_level(),		\
		spaces('-',get_level()),\
		 abi::__cxa_demangle(typeid(*this).name(), 0, &len, &s), \
		 getId(), __FUNCTION__);	\
  }					\
  leave_level();			\
  return;				\
} while (0)

#define RETURN(res) do {		\
  int x = res;				\
  if (LOGGER.isDebugEnabled()) {	\
    size_t len = 0;			\
    int s = 0;				\
    LOGGER.debug("%2d %s%s:%d::%s() = %d",	\
		get_level(),		\
		spaces('-',get_level()),\
		 abi::__cxa_demangle(typeid(*this).name(), 0, &len, &s), \
		 getId(), __FUNCTION__, x);	\
  }					\
  leave_level();			\
  return x;				\
} while (0)

#define TRACE0(msg) do {		\
  if (LOGGER.isDebugEnabled()) {	\
    size_t len = 0;			\
    int s = 0;				\
    LOGGER.debug("%s::%s(): %s",	\
		 abi::__cxa_demangle(typeid(*this).name(), 0, &len, &s), \
		 __FUNCTION__, msg);		\
  }					\
  } while (0)
  
#define TRACE_INT(msg, d) do {		\
  if (LOGGER.isDebugEnabled()) {	\
    size_t len = 0;			\
    int s = 0;				\
    LOGGER.debug("%s::%s(): " #msg,	\
		 abi::__cxa_demangle(typeid(*this).name(), 0, &len, &s), \
		 __FUNCTION__, d );		\
  }					\
  } while (0)

#else /* ! REXGEN_DEBUG != 1 */

#define ENTER_METHOD
#define LEAVE_METHOD return
#define RETURN(r) return(r)
#define TRACE0(msg)
#define TRACE_INT(msg, d)

#endif /* REXGEN_DEBUG */

#endif