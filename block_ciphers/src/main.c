#include <stdio.h>
#include "padding.h"
#include <string.h>

int main(){
    uint8_t msg[] = "HELLO";
    size_t len = strlen((char*)msg);

    size_t padded_len;
    uint8_t *padded = (uint8_t*)pkcs7_padding(msg, len, 8, &padded_len);

    printf("original len: %zu\n", len);
    printf("padded len:   %zu\n", padded_len);

    // print hex
    for (size_t i = 0; i < padded_len; i++)
        printf("%02X ", padded[i]);
    printf("\n");

    free_padding_pkc7s(padded);
}