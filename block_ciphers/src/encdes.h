#ifndef ENCDES_H
#define ENCDES_H
#include <stdint.h>

int encrypt_des_ecb(uint8_t* plaintext, uint8_t* key, uint8_t* ciphertext, int* size);
int decrypt_des_ecb(uint8_t* ciphertext, uint8_t* key, uint8_t* plaintext, int* size);


#endif