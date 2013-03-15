#ifndef __osdepend_h__
#define __osdepend_h__

#if defined(_WIN32)
#include <io.h>
#define __attribute__(X) 
inline int isatty(int fd ) { return _isatty(fd); }
#define YY_NO_UNISTD_H

#define EXPORT __declspec (dllexport)
#endif

#endif /* __osdepend_h__ */
