#ifndef __unicode_h__
#define __unicode_h__

#include <unistdio.h>
#include <unistr.h>

#ifndef UTF_VARIANT
#define UTF_VARIANT 32
#endif

#if UTF_VARIANT==8

#define UTF8

typedef uint8_t char_type;
#define utf_snprintf u8_snprintf
#define utf_strlen u8_strlen
#define utf_strncat u8_strncat
#define utf_strncpy u8_strncpy

#define _T(STR) ( (char_type*) u8 ## STR )

#elif UTF_VARIANT==16

#define UTF16

typedef uint16_t char_type;
#define utf_snprintf u16_snprintf
#define utf_strlen u16_strlen
#define utf_strncat u16_strncat
#define utf_strncpy u16_strncpy

#define _T(STR) ( (char_type*) u ## STR )

#elif UTF_VARIANT==32

#define UTF32

typedef uint32_t char_type;
#define utf_snprintf u32_snprintf
#define utf_strlen u32_strlen
#define utf_strncat u32_strncat
#define utf_strncpy u32_strncpy

#define _T(STR) ( (char_type*) U ## STR )

#else
#error "invalid value for UTF_VARIANT; valid would be one of 8, 16, 32"
#endif /* UTF_VARIANT */

#endif /* __unicode_h__ */