/* Copyright LRH.

   
*/

#include <stdlib.h>

#include "./common/platform.h"
#include "types.h"

/* Default brotli_alloc_func */
void* BrotliDefaultAllocFunc(void* opaque, size_t size) {
  BROTLI_UNUSED(opaque);
  return malloc(size);
}

/* Default brotli_free_func */
void BrotliDefaultFreeFunc(void* opaque, void* address) {
  BROTLI_UNUSED(opaque);
  free(address);
}
