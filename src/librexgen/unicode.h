#ifndef __unicode_h__
#define __unicode_h__
#include <cstdarg>

/* for readability issues:
 *   we use 'char' for characters; one character per 'char'-value
 *   we use 'byte' for binary values, which may contain
 *     a character or part of a character
 */
typedef char byte; 


#ifdef _WIN32
#include <tchar.h>

#ifndef UNICODE
#error UNICODE is not defined
#endif

#ifndef _UNICODE
#error _UNICODE is not defined
#endif

typedef wchar_t char_type;
#define utf_snprintf(buffer,count,format,...) _snwprintf((buffer),(count),format,__VA_ARGS__)
#define utf_strlen wcslen
#define utf_strncat wcsncat
#define utf_strncpy wcsncpy
#define utf_strconv_from_locale u8_strconv_from_locale

//#define _T(STR) ( const_cast<char_type*>( reinterpret_cast<const char_type*>( _T ## STR )))
#define _C(STR) ( (const char_type*) _T(STR) )

#define PRINTF_FORMAT "%s"


#else /* ! _WIN32 */
#include <unistdio.h>
#include <unistr.h>
#include <uniconv.h>

#ifndef UTF_VARIANT
#define UTF_VARIANT 32
#endif

#define UTF32

typedef uint32_t char_type;
#define utf_snprintf u32_snprintf
#define utf_strlen u32_strlen
#define utf_strncat u32_strncat
#define utf_strncpy u32_strncpy
#define utf_strconv_from_locale u32_strconv_from_locale

#define _T(STR) ( const_cast<char_type*>( reinterpret_cast<const char_type*>( u ## STR )))
#define _C(STR) ( (const char_type*) u ## STR )

#define PRINTF_FORMAT "%llU"

#endif /* _WIN32 */

#endif /* __unicode_h__ */
