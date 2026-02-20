#ifndef PADDING_H
#define PADDING_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

uint8_t* pkcs7_padding(const uint8_t* bytes, size_t length, uint8_t blocksize, size_t* new_len);

int pkcs7_unpadding(uint8_t* buffer, size_t* length, uint8_t blocksize);

uint8_t free_padding_pkc7s(uint8_t* padded);



#endif