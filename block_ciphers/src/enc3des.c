#include "enc3des.h"
#include <openssl/evp.h>


int encrypt_3des_cbc(unsigned char* plaintext, size_t plaintext_len, unsigned char* key, unsigned char* iv, unsigned char* ciphertext){
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
int decrypt_3des_cbc(unsigned char* ciphertext, size_t ciphertext_len, unsigned char* key, unsigned char* iv, unsigned char* plaintext){
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    int len, plaintext_len;
    EVP_DecryptInit_ex(ctx, EVP_des_ede3_cbc(), NULL, key, iv);
    EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, (int)ciphertext_len);
    plaintext_len = len;
    // plaintext + len moves the pointer the size of plaintext
    EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
    plaintext_len += len;
    EVP_CIPHER_CTX_free(ctx);
    return plaintext_len;
}
