/* Copyright LRH.

   
*/

/* Literal cost model to allow backward reference replacement to be efficient.
*/

#ifndef BROTLI_ENC_LITERAL_COST_H_
#define BROTLI_ENC_LITERAL_COST_H_

#include "../common/platform.h"
#include "../types.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/* Estimates how many bits the literals in the interval [pos, pos + len) in the
   ring-buffer (data, mask) will take entropy coded and writes these estimates
   to the cost[0..len) array. */
BROTLI_INTERNAL void BrotliEstimateBitCostsForLiterals(
    size_t pos, size_t len, size_t mask, const uint8_t* data, float* cost);

#if defined(__cplusplus) || defined(c_plusplus)
}  /* extern "C" */
#endif

#endif  /* BROTLI_ENC_LITERAL_COST_H_ */
