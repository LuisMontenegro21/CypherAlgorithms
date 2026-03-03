#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "keys.h"
#include <errno.h>
#include <sys/random.h>


int os_random(unsigned char *out, size_t n) {
    size_t got = 0;
    while (got < n) {
        ssize_t r = getrandom(out + got, n - got, 0);
        if (r < 0) {
            if (errno == EINTR) continue;
            printf("Error in OS Random\n");
            return -1;
        }
        got += (size_t)r;
    }
    return 0;
}


int aes_keygen(unsigned char *key, size_t key_len) {
    if (key_len != 16 && key_len != 24 && key_len != 32) {
        printf("Error in random aeskeygen");
        return -1;
    }
    return os_random(key, key_len);
}


unsigned char des_odd_parity(unsigned char b) {

    unsigned char x = b & 0xFE; // x = b AND 254
    x ^= x >> 4; // x = x XOR x bitwise move 4 to the right  
    x ^= x >> 2; // x = x XOR x bitwise move 2 to the right
    x ^= x >> 1; // x = x XOR x bitwise move 1 to the right

    return (b & 0xFE) | ((x & 1) ^ 1); // (b AND 254) OR (x AND 1) XOR 1
}

int des_keygen(unsigned char key[8]) {
    if (os_random(key, 8) != 0) {
        printf("Error in random deskeygen");
        return -1;
    }
    for (int i = 0; i < 8; ++i) key[i] = des_odd_parity(key[i]);
    return 0;
}

int des3_keygen(unsigned char *key, size_t key_len) {
    if (key_len != 16 && key_len != 24) {
        printf("Error in key_len: 16 or 24 bytes expected '%zu' found\n", key_len);
        return -1;
    }
    if (os_random(key, key_len) != 0) {
        printf("Error in random des3keygen\n");
        return -1;
    }

    // Fix odd parity for each DES key byte
    for (size_t i = 0; i < key_len; ++i) key[i] = des_odd_parity(key[i]);

    return 0;
}