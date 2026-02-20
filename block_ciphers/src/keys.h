#ifdef _WIN32
#include <windows.h>
#include <bcrypt.h>
#pragma comment(lib, "bcrypt.lib")
 /*
Hecho con ayuda de ChatGPT 5.2 por cuestiones de tiempo ;-;
 */
int os_random(uint8_t *out, size_t n) {
    return BCryptGenRandom(NULL, out, (ULONG)n, BCRYPT_USE_SYSTEM_PREFERRED_RNG) == 0 ? 0 : -1;
}
#endif

int aes_keygen(uint8_t *key, size_t key_len) {
    if (key_len != 16 && key_len != 24 && key_len != 32) return -1;
    return os_random(key, key_len);
}

static uint8_t des_odd_parity(uint8_t b) {

    uint8_t x = b & 0xFE; 
    x ^= x >> 4; x ^= x >> 2; x ^= x >> 1;

    return (b & 0xFE) | ((x & 1) ^ 1);
}

int des_keygen(uint8_t key[8]) {
    if (os_random(key, 8) != 0) return -1;
    for (int i = 0; i < 8; i++) key[i] = des_odd_parity(key[i]);
    return 0;
}

int des3_keygen(uint8_t *key, size_t key_len) {
    if (key_len != 16 && key_len != 24) return -1;
    if (os_random(key, key_len) != 0) return -1;

    // Fix odd parity for each DES key byte
    for (size_t i = 0; i < key_len; i++) key[i] = des_odd_parity(key[i]);

    return 0;
}