#ifndef AES_H
#define AES_H
#include <stdint.h>

int encrypt_aes(uint8_t* plaintext, size_t plaintext_len, uint8_t* key, uint8_t* iv, uint8_t* ciphertext);
int decrypt_aes(uint8_t* ciphertext, size_t ciphertext_len, uint8_t* key, uint8_t* iv, uint8_t* plaintext);
#endif