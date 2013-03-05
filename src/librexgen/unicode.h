#ifndef __unicode_h__
#define __unicode_h__

#include <unistdio.h>
#include <unistr.h>
#include <uniconv.h>

class SimpleString;

#include <string>
#include <vector>
using std::basic_string;
using std::vector;

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
#define utf_strconv_from_locale u8_strconv_from_locale

#define _T(STR) ( const_cast<char_type*>( reinterpret_cast<const char_type*>( u8 ## STR )))
#define _C(STR) ( (const char_type*) u8 ## STR )

#define PRINTF_FORMAT "%U"

#elif UTF_VARIANT==16

#define UTF16

typedef uint16_t char_type;
#define utf_snprintf u16_snprintf
#define utf_strlen u16_strlen
#define utf_strncat u16_strncat
#define utf_strncpy u16_strncpy
#define utf_strconv_from_locale u16_strconv_from_locale

#define _T(STR) ( const_cast<char_type*>( reinterpret_cast<const char_type*>( u ## STR )))
#define _C(STR) ( (const char_type*) u ## STR )

#define PRINTF_FORMAT "%lU"

#elif UTF_VARIANT==32

#define UTF32

typedef uint32_t char_type;
#define utf_snprintf u32_snprintf
#define utf_strlen u32_strlen
#define utf_strncat u32_strncat
#define utf_strncpy u32_strncpy
#define utf_strconv_from_locale u32_strconv_from_locale

#define _T(STR) ( const_cast<char_type*>( reinterpret_cast<const char_type*>( U ## STR )))
#define _C(STR) ( (const char_type*) U ## STR )

#define PRINTF_FORMAT "%llU"

#else
#error "invalid value for UTF_VARIANT; valid would be one of 8, 16, 32"
#endif /* UTF_VARIANT */

typedef SimpleString string_type;

#include <librexgen/simplestring.h>

#endif /* __unicode_h__ */