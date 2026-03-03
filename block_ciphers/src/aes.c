#include "aes.h"
#include <openssl/evp.h>
#include "stdint.h"

int encrypt_aes_cbc(uint8_t* plaintext, size_t plaintext_len, uint8_t* key, uint8_t* iv, uint8_t* ciphertext){
    int len, ciphertext_len;
    EVP_CIPHER_CTX *ctx;
    ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, (int)plaintext_len);
    ciphertext_len = len;
    EVP_Encrypt_Final_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;
    EVP_CIPHER_CTX_free(ctx);
    return ciphertext_len;
}

int decrypt_aes_cbc(uint8_t* ciphertext, size_t ciphertext_len, uint8_t* key, uint8_t* iv, uint8_t* plaintext){
    int len, ciphertext_len;
    EVP_CIPHER_CTX *ctx;
    ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, (int)plaintext_len);
    ciphertext_len = len;
    EVP_Encrypt_Final_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;
    EVP_CIPHER_CTX_free(ctx);
    return ciphertext_len;
}


int encrypt_aes_ecb(uint8_t* plaintext, size_t plaintext_len, uint8_t* key, uint8_t* iv, uint8_t* ciphertext){
    int len, ciphertext_len;
    EVP_CIPHER_CTX *ctx;
    ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, key, iv);
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, (int)plaintext_len);
    ciphertext_len = len;
    EVP_Encrypt_Final_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;
    EVP_CIPHER_CTX_free(ctx);
    return ciphertext_len;
}
int decrypt_aes_ecb(uint8_t* ciphertext, size_t ciphertext_len, uint8_t* key, uint8_t* iv, uint8_t* plaintext){
    int len, ciphertext_len;
    EVP_CIPHER_CTX *ctx;
    ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, key, iv);
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, (int)plaintext_len);
    ciphertext_len = len;
    EVP_Encrypt_Final_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;
    EVP_CIPHER_CTX_free(ctx);
    return ciphertext_len;
}