#include "padding.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// padding for size 8
unsigned char* pkcs7_padding(const unsigned char* bytes, size_t length, unsigned char blocksize, size_t* new_len) {

    unsigned char padding = blocksize - (length % blocksize);
    if (padding == 0)
        padding = blocksize;

    *new_len = length + padding;

    unsigned char* result = malloc(*new_len);
    if (!result) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    memcpy(result, bytes, length);
    // printf("New len: %zu\n", *new_len);
    for (size_t i = length; i < *new_len; ++i) {
        // printf("Iteration: %zu Padding: %u\n", i, (unsigned int)padding);
        result[i] = padding;
    }

    return result;
}


int pkcs7_unpadding(unsigned char* buffer, size_t* length, unsigned char blocksize) {

    if (*length == 0)
        return -1;

    unsigned char pad = buffer[*length - 1];

    if (pad == 0 || pad > blocksize) return -1;

    if (pad > *length) return -1;

    for (size_t i = 0; i < pad; ++i) {
        if (buffer[*length - 1 - i] != pad)
            return -1;
    }

    *length -= pad;

    return 0;
}

void free_padding_pkc7s(unsigned char* padded){
    printf("Freeing memory\n");
	free(padded);
}