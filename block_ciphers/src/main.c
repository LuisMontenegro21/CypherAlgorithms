#include <stdio.h>
#include <string.h>
#include "padding.h"
// #include "keys.h"


void print_hexadecimal(uint8_t* msg, size_t length){
    for (size_t i = 0; i<length; ++i) printf("%02hhx ", msg[i]);
    printf("\n");
}

int main(){
    uint8_t msg[] = "Hello";
    size_t len = strlen((char*)msg);

    size_t padded_len;
    uint8_t *padded = (uint8_t*)pkcs7_padding(msg, len, 8, &padded_len);

    printf("original len: %zu\n", len);
    printf("padded len:   %zu\n", padded_len);
    print_hexadecimal(padded, padded_len); // print padded
    if (pkcs7_unpadding(padded, &padded_len, 8) != 0){
        perror("Error unpadding");
        exit(-1);
    }
    print_hexadecimal(padded, padded_len); // print unpadded
    free_padding_pkc7s(padded);
}