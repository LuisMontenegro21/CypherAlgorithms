#include "aes.h"
#include <openssl/evp.h>
#include <stddef.h>

int encrypt_aes_cbc(unsigned char* plaintext, size_t plaintext_len, unsigned char* key, unsigned char* iv, unsigned char* ciphertext){
    int len, ciphertext_len;
    EVP_CIPHER_CTX *ctx;
    ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
    EVP_CIPHER_CTX_set_padding(ctx, 0);
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, (int)plaintext_len);
    ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;
    EVP_CIPHER_CTX_free(ctx);
    return ciphertext_len;
}

int decrypt_aes_cbc(unsigned char* ciphertext, size_t ciphertext_len, unsigned char* key, unsigned char* iv, unsigned char* plaintext){
    int len, plaintext_len;
    EVP_CIPHER_CTX *ctx;
    ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, (int)ciphertext_len);
    plaintext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    plaintext_len += len;
    EVP_CIPHER_CTX_free(ctx);
    return plaintext_len;
}


int encrypt_aes_ecb(unsigned char* plaintext, size_t plaintext_len, unsigned char* key, unsigned char* ciphertext){
    int len, ciphertext_len;
    EVP_CIPHER_CTX *ctx;
    ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, key, NULL);
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, (int)plaintext_len);
    ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;
    EVP_CIPHER_CTX_free(ctx);
    return ciphertext_len;
}
int decrypt_aes_ecb(unsigned char* ciphertext, size_t ciphertext_len, unsigned char* key, unsigned char* plaintext){
    int len, plaintext_len;
    EVP_CIPHER_CTX *ctx;
    ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, key, NULL);
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, (int)ciphertext_len);
    plaintext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    plaintext_len += len;
    EVP_CIPHER_CTX_free(ctx);
    return plaintext_len;
}