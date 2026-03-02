#include <stdio.h>
#include <string.h>
#include "enc3des.h"
#include "encdes.h"
#include "keys.h"

void print_hexadecimal(uint8_t* msg, size_t length){
    for (size_t i = 0; i<length; ++i) printf("%02hhx ", msg[i]);
    printf("\n");
}

int main(){
    // uint8_t key[24];
    // uint8_t iv[8];

    // int res = des3_keygen(key, sizeof(key));
    // if (res != 0){
    //     printf("Response: %d\n", res);
    //     perror("Error");
    //     exit(-1);
    // }

    // uint8_t plaintext[] = "Testing DES ECB mode";
    // uint8_t ciphertext[128];
    // uint8_t decrypted[128];
    // int ct_len = encrypt_3des_cbc(plaintext, strlen(plaintext), key, iv, ciphertext);
    // print_hexadecimal(ciphertext, (size_t)ct_len);
    // int pt_len = decrypt_3des_cbc(ciphertext, (size_t)ct_len, key, iv, decrypted);
    // decrypted[pt_len] = '\0';
    // size_t decrypted_length = strlen(decrypted);
    // printf("\nDecrypted: %s Length: %zu\n" , decrypted, decrypted_length);
    uint8_t key[8];
    uint8_t plaintext[] = "Testing DES ECB mode";
    uint8_t ciphertext[128];
    uint8_t decrypted[128];
    int size = (int)strlen(plaintext);
    des_keygen(key);
    int padding = encrypt_des_ecb(plaintext, key, ciphertext, &size);
    print_hexadecimal(ciphertext, sizeof(ciphertext));
    int original_len = decrypt_des_ecb(ciphertext, key, decrypted, &size);


    return 0;
}