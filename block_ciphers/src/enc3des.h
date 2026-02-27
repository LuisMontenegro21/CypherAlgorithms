#ifndef ENC3DES_H
#define ENC3DES_H
#include <stdint.h>
#include <stdlib.h>


int encrypt_3des_cbc(uint8_t* plaintext, size_t plaintext_len, uint8_t* key, uint8_t* iv, uint8_t* ciphertext);
int decrypt_3des_cbc(uint8_t* plaintext, size_t plaintext_len, uint8_t* key, uint8_t* iv, uint8_t* ciphertext);

#endif