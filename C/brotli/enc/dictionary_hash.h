/* Copyright LRH.

   
*/

/* Hash table on the 4-byte prefixes of static dictionary words. */

#ifndef BROTLI_ENC_DICTIONARY_HASH_H_
#define BROTLI_ENC_DICTIONARY_HASH_H_

#include "../types.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

extern const uint16_t kStaticDictionaryHashWords[32768];
extern const uint8_t kStaticDictionaryHashLengths[32768];

#if defined(__cplusplus) || defined(c_plusplus)
}  /* extern "C" */
#endif

#endif  /* BROTLI_ENC_DICTIONARY_HASH_H_ */
