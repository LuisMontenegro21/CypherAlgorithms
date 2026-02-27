#include <stdio.h>
#include <string.h>
#include "padding.h"
#include "enc3des.h"
#include "keys.h"


void print_hexadecimal(uint8_t* msg, size_t length){
    for (size_t i = 0; i<length; ++i) printf("%02hhx ", msg[i]);
    printf("\n");
}

int main(){
    uint8_t key[24];
    uint8_t iv[8];
    if (des3_keygen(key, strlen(key))){
        perror("Error");
        exit(-1);
    }

    uint8_t plaintext[] = "Testing 3DES CBC mode";
    uint8_t ciphertext[128];
    uint8_t decrypted[128];
    int ct_len = encrypt_3des_cbc(plaintext, strlen(plaintext), key, iv, ciphertext);
    print_hexadecimal(ciphertext, (size_t)ct_len);
    int pt_len = decrypt_3des_cbc(ciphertext, (size_t)ct_len, key, iv, decrypted);
    decrypted[pt_len] = '\0';
    printf("\nDecrypted: %s \n" , decrypted);

    return 0;
}