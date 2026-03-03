#ifndef PADDING_H
#define PADDING_H


#include <stdlib.h>
#include <stdio.h>

unsigned char* pkcs7_padding(const unsigned char* bytes, size_t length, unsigned char blocksize, size_t* new_len);

int pkcs7_unpadding(unsigned char* buffer, size_t* length, unsigned char blocksize);

void free_padding_pkc7s(unsigned char* padded);



#endif