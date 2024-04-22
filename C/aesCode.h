#ifndef __AESCODE_H
#define __AESCODE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

bool EncryptDataToCipherTxt(uint8_t *orign, uint8_t *result, int length);

bool DecryptCipherTxtToData(uint8_t *orign, uint8_t *result, int length);

#endif
