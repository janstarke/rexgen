#ifndef __CASEFOLDING_H__
#define __CASEFOLDING_H__
#include <librexgen/string/uchar.h>

/*
 * For any of these functions, bch must point to an array of at least 3
 * elements. The actual length of this array will not be checked!!!!
 */

bool
casefold_common (uint32_t cp, charset cs, binary_character_t* bch);

bool
casefold_simple (uint32_t cp, charset cs, binary_character_t* bch);

bool
casefold_special (uint32_t cp, charset cs, binary_character_t* bch);

#endif /* __CASEFOLDING_H__ */
