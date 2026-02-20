#include "padding.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

uint8_t* pkcs7_padding(const uint8_t* bytes, size_t length, uint8_t blocksize, size_t* new_len) {

    uint8_t padding = blocksize - (length % blocksize);
    if (padding == 0)
        padding = blocksize;

    *new_len = length + padding;

    uint8_t* result = malloc(*new_len);
    if (!result) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    memcpy(result, bytes, length);

    for (size_t i = length; i < *new_len; i++) {
        result[i] = padding;
    }

    return (char*)result;
}


int pkcs7_unpadding(uint8_t* buffer, size_t* length, uint8_t blocksize) {

    if (*length == 0)
        return -1;

    uint8_t pad = buffer[*length - 1];

    if (pad == 0 || pad > blocksize) return -1;

    if (pad > *length) return -1;

    for (size_t i = 0; i < pad; ++i) {
        if (buffer[*length - 1 - i] != pad)
            return -1;
    }

    *length -= pad;

    return 0;
}

uint8_t free_padding_pkc7s(uint8_t* padded){
	free(padded);
}