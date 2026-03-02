#include "enc3des.h"
#include <openssl/evp.h>


int encrypt_3des_cbc(uint8_t* plaintext, size_t plaintext_len, uint8_t* key, uint8_t* iv, uint8_t* ciphertext){
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    int len, ciphertext_len;
    // cast to uint_8 -> unsigned char 
    EVP_EncryptInit_ex(ctx, EVP_des_ede3_cbc(), NULL, key, iv);
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, (int)plaintext_len);

    ciphertext_len = len;
    // ciphertext + len moves pointer the size of ciphertext 
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len); // includes PKCS7
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    return ciphertext_len;
}
int decrypt_3des_cbc(uint8_t* ciphertext, size_t ciphertext_len, uint8_t* key, uint8_t* iv, uint8_t* plaintext){
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    int len, plaintext_len;
    EVP_DecryptInit_ex(ctx, EVP_des_ede3_cbc(), NULL, key, iv);
    EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, (int)ciphertext_len);
    plaintext_len = len;
    // plaintext + len moves the pointer the size of plaintext
    EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
    EVP_CIPHER_CTX_free(ctx);
    return plaintext_len;
}
