#ifndef __osdepend_h__
#define __osdepend_h__

#if defined(_WIN32)
#include <io.h>
#define __attribute__(X) 
inline int isatty(int fd ) { return _isatty(fd); }
#define YY_NO_UNISTD_H

#define EXPORT __declspec (dllexport)

typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;

#else /* ! defined(_WIN32) */

#define EXPORT
#define _tmain main

#endif

#endif /* __osdepend_h__ */
