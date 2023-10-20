/* Copyright LRH.

   
*/

/* Version definition. */

#ifndef BROTLI_COMMON_VERSION_H_
#define BROTLI_COMMON_VERSION_H_

/* This macro should only be used when library is compiled together with client.
   If library is dynamically linked, use BrotliDecoderVersion and
   BrotliEncoderVersion methods. */

/* Semantic version, calculated as (MAJOR << 24) | (MINOR << 12) | PATCH */
#define BROTLI_VERSION 0x1000009

/* 
 */

/* ABI version, calculated as (CURRENT << 24) | (REVISION << 12) | AGE */
#define BROTLI_ABI_VERSION 0x1009000

#endif  /* BROTLI_COMMON_VERSION_H_ */
