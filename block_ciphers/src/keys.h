#ifndef KEYS_H
#define KEYS_H
#include <stdint.h>
#include <stdlib.h>

int os_random(uint8_t *out, size_t n);

int aes_keygen(uint8_t *key, size_t key_len);

static uint8_t des_odd_parity(uint8_t b);

int des_keygen(uint8_t key[8]);

int des3_keygen(uint8_t *key, size_t key_len);

#endif