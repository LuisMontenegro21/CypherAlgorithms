#ifndef AES_H
#define AES_H
#include <stddef.h>

int encrypt_aes_cbc(unsigned char* plaintext, size_t plaintext_len, unsigned char* key, unsigned char* iv, unsigned char* ciphertext);
int decrypt_aes_cbc(unsigned char* ciphertext, size_t ciphertext_len, unsigned char* key, unsigned char* iv, unsigned char* plaintext);

int encrypt_aes_ecb(unsigned char* plaintext, size_t plaintext_len, unsigned char* key, unsigned char* ciphertext);
int decrypt_aes_ecb(unsigned char* ciphertext, size_t ciphertext_len, unsigned char* key, unsigned char* plaintext);

#endif