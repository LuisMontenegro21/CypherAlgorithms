#ifndef ENC3DES_H
#define ENC3DES_H
#include <stddef.h>


int encrypt_3des_cbc(unsigned char* plaintext, size_t plaintext_len, unsigned char* key, unsigned char* iv, unsigned char* ciphertext);
int decrypt_3des_cbc(unsigned char* ciphertext, size_t ciphertext_len, unsigned char* key, unsigned char* iv, unsigned char* plaintext);

#endif