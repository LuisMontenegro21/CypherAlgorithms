#ifndef KEYS_H
#define KEYS_H
#include <stddef.h>

int os_random(unsigned char *out, size_t n);

int aes_keygen(unsigned char *key, size_t key_len);

static unsigned char des_odd_parity(unsigned char b);

int des_keygen(unsigned char key[8]);

int des3_keygen(unsigned char *key, size_t key_len);

#endif