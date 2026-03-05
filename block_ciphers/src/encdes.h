#ifndef ENCDES_H
#define ENCDES_H
#include <stddef.h>

int encrypt_des_ecb(unsigned char* plaintext, size_t plaintext_len,  unsigned char* key, unsigned char* ciphertext);
int decrypt_des_ecb(unsigned char* ciphertext, size_t ciphertext_len ,unsigned char* key, unsigned char* plaintext);


#endif